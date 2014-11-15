/**
 *  .file devel/test27.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//------------------
#include <eagine/base/align_alloc.hpp>
#include <eagine/base/expand_alloc.hpp>
#include <eagine/base/buffer_alloc.hpp>
#include <eagine/base/logging_alloc.hpp>
#include <eagine/base/fallback_alloc.hpp>
#include <eagine/base/stack_alloc.hpp>
#include <eagine/base/alloc.hpp>
#include <eagine/base/memory_buffer.hpp>
#include <eagine/dbg/hexdump.hpp>
//------------------
#include <vector>
#include <iostream>
#include <exception>
#include <cstring>

namespace EAGine {
namespace base {

template <typename Policy = default_byte_allocator_policy>
class chunk_byte_allocator
 : public byte_allocator_impl<Policy, chunk_byte_allocator>
{
private:
	byte* _bgn;
	byte* _end;

	struct _elem
	{
		union {
			_elem* _next;
			byte* _addr;
		};
		std::size_t _size;

		static _elem* _cast(byte* ptr, std::size_t size)
		noexcept
		{
			assert(sizeof(_elem) <= size);
			assert((((std::uintptr_t)ptr) % alignof(_elem*)) == 0);
			return (_elem*)(void*)ptr;
		}

		constexpr
		_elem(void)
		noexcept
		 : _next(nullptr)
		 , _size(0)
		{ }

		_elem(byte* ptr, std::size_t size)
		noexcept
		 : _next(_cast(ptr, size))
		 , _size(size)
		{ }
	};

	_elem _head;

	std::size_t _max;
	const std::size_t _chunk_size;

	static std::size_t _adj_align(std::size_t align)
	noexcept
	{
		if(align < alignof(_elem))
		{
			align = alignof(_elem);
		}

		return align;
	}

	static std::size_t _adj_chunk_size(std::size_t chunk, std::size_t align)
	noexcept
	{
		if(chunk < sizeof(std::ptrdiff_t)+sizeof(std::size_t))
		{
			chunk = sizeof(std::ptrdiff_t)+sizeof(std::size_t);
		}

		if((chunk % align) != 0)
		{
			chunk += (align - chunk % align);
			assert((chunk % align) == 0);
		}

		return chunk;
	}
public:
	chunk_byte_allocator(chunk_byte_allocator&& tmp) = default;

	chunk_byte_allocator(
		const memory_block& blk,
		std::size_t chunk = 1,
		std::size_t align = 1
	) noexcept
	 : _bgn((byte*)blk.aligned_begin(_adj_align(align)))
	 , _end((byte*)blk.aligned_end(_adj_align(align)))
	 , _head(_bgn, _end-_bgn)
	 , _max(_head._size)
	 , _chunk_size(_adj_chunk_size(chunk, _adj_align(align)))
	{
		*_head._next = _elem();
	}

	typedef byte value_type;
	typedef std::size_t size_type;

	bool equal(byte_allocator* a) const
	noexcept override
	{
		chunk_byte_allocator* pa =
			dynamic_cast<chunk_byte_allocator*>(a);

		if(a != nullptr)
		{
			if(_bgn == pa->_bgn)
			{
				assert(_end == pa->_end);
				assert(_chunk_size == pa->_chunk_size);
				return true;
			}
		}
		return false;
	}

	size_type _max_chunk(void)
	noexcept
	{
		std::size_t max = 0;
		_elem* elem = &_head;

		while(elem != nullptr)
		{
			if(max < elem->_size)
			{
				max = elem->_size;
			}
			elem = elem->_next;
		}
	
		return max;
	}

	size_type max_size(std::size_t)
	noexcept override
	{
		//assert(_max == _max_chunk());
		//return _max;
		return _max_chunk();
	}

	tribool has_allocated(const byte* p, std::size_t n)
	noexcept override
	{
		if((_bgn <= p) && (p <= _end))
		{
			assert(p+n <= _end);
			return true;
		}
		return false;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		if(n < max_size(a))
		{
			_elem* elem = &_head;
			while(elem)
			{
				if(n <= elem->_size)
				{
					byte* r = elem->_addr;
					std::size_t rem_size = elem->_size - n;
					if(_chunk_size < rem_size)
					{
						std::size_t o =
							(n/_chunk_size)+
							(n%_chunk_size?1:0);
						o *= _chunk_size;

						assert(o >= sizeof(_elem));

						_elem* new_elem = (_elem*)(r+o);

						*new_elem = *elem->_next;
						_head._next = new_elem;
						_head._size = rem_size;
					}
					else
					{
						_head = *elem->_next;
					}
					return r;
				}
				elem = elem->_next;
			}
		}
		return nullptr;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		assert(has_allocated(p, n));

		std::size_t size =
			(n/_chunk_size)+
			(n%_chunk_size?1:0);
		size *= _chunk_size;

		_elem* elem = (_elem*)(void*)p;
		*elem = _head;
		_head._next = elem;
		_head._size = size;

/*
		// TODO join adjacent
		_elem* tmp = elem->_next;
		while(tmp != nullptr)
		{
			if(
		}
*/
	}
};

} // namespace base
} // namespace EAGine

int main(int argc, const char* argv [])
{
	using namespace EAGine::base;
	using namespace EAGine::meta;
	using namespace EAGine::dbg;

	memory_buffer buf1(8*1024);
	memory_block blk1 = buf1;
	std::memset(blk1.addr(), 0, blk1.size());

	{
	concrete_byte_allocator<byte_allocator_with_fallback> cba(
		stack_byte_allocator<>(blk1),
		default_byte_allocator()
	);

	allocator<void> a((cba.reference()));

	typedef std::basic_string<char, std::char_traits<char>, allocator<char>> s_t;

	std::vector<s_t, allocator<s_t>> v(a);

	for(int i=0; i<256; ++i)
	{
		v.push_back(s_t(argv[i%argc], a));
	}

	//std::cout << hexdump(blk1) << std::endl;

	std::cout << cba.get().required_fallback_size() << std::endl;
	std::cout << v.size() << std::endl;
	}

	{
	allocator<void> a((
		logging_byte_allocator<>(
			multi_align_byte_allocator<integer_sequence<std::size_t, alignof(float)>>(
				expanding_byte_allocator<>([](void){
					//return buffer_backed_byte_allocator<stack_aligned_byte_allocator>(6*1024, alignof(float));
					return buffer_backed_byte_allocator<chunk_byte_allocator>(6*1024);
				})
			)
		)
	));

	std::vector<float, allocator<float>> v(a);
	for(int i=0; i<1024; ++i)
	{
		v.push_back(float(i));
	}

	std::cout << v.size() << std::endl;
	}


	return 0;
}
