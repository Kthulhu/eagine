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
{
private:
	byte* _bgn;
	byte* _end;

	struct _elem
	{
		_elem* _next;
		std::size_t _size;

		static _elem* _cast(byte* ptr, std::size_t size)
		{
			assert(sizeof(_elem) <= size);
			assert((((std::uintptr_t)ptr) % alignof(_elem*)) == 0);
			return (_elem*)(void*)ptr;
		}

		_elem(void)
		 : _next(nullptr)
		 , _size(0)
		{ }

		_elem(byte* ptr, std::size_t size)
		 : _next(_cast(ptr, size))
		 , _size(size)
		{ }
	};

	_elem _head;

	std::size_t _max;
	const std::size_t _chunk_size;

	static std::size_t _adj_align(std::size_t align)
	{
		if(align < alignof(_link))
		{
			align = alignof(_link);
		}

		return align;
	}

	static std::size_t _adj_chunk_size(std::size_t chunk, std::size_t align)
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
	chunk_byte_allocator(
		const memory_block& blk,
		std::size_t chunk,
		std::size_t align
	): _bgn((T*)blk.aligned_begin(_adj_align(align)))
	 , _end((T*)blk.aligned_end(_adj_align(align)))
	 , _head(bgn, _end-_bgn)
	 , _max(_head._size)
	 , _chunk_size(_adj_chunk_size(chunk, _adj_align(align)))
	{
		*_head._next = _elem();
	}

	bool equal(byte_allocator* a) const
	noexcept override
	{
		chunk_byte_allocator* pa =
			dynamic_cast<chung_byte_allocator*>(a);

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

	_size_type max_chunk(void)
	noexcept
	{
		// TODO make this O(1)
		std::size_t max = 0;
		_elem* elem = &_head;

		while(elem)
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
		assert(_max == _max_chunk());
		return _max;
	}

	tribool has_allocated(const byte* p, std::size_t n)
	noexcept override
	{
		if((_bgn <= p) && (p <= e))
		{
			assert(p+n <= e);
			return true;
		}
		return false;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		// TODO
		if(n < max_size())
		{
			_elem* elem = &_head;
			while(elem)
			{
				if(n < elem->size)
				{
					
				}
			}
		}
		return nullptr;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
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
					return buffer_backed_byte_allocator<stack_aligned_byte_allocator>(6*1024, alignof(float));
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
