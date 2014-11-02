/**
 *  @file eagine/base/stack_alloc.hpp
 *  @brief Stack memory allocator.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_STACK_ALLOC_1308281038_HPP
#define EAGINE_BASE_STACK_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/meta/type_traits.hpp>

namespace EAGine {
namespace base {

// base_stack_allocator
// non-rebindable non-copyable stack allocator
// use with care!
template <typename T>
class base_stack_allocator
{
private:
	T* _btm;
	T* _top;
	T* _pos;
	T* _min;
	std::size_t _dif;
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	base_stack_allocator(const base_stack_allocator&) = delete;

	base_stack_allocator(base_stack_allocator&& tmp)
	noexcept
	 : _btm(tmp._btm)
	 , _top(tmp._top)
	 , _pos(tmp._pos)
	 , _min(tmp._min)
	 , _dif(tmp._dif)
	{
		tmp._btm = nullptr;
		tmp._top = nullptr;
		tmp._pos = nullptr;
		tmp._min = nullptr;
		tmp._dif = 0;
	}

	base_stack_allocator(void)
	noexcept
	 : _btm(nullptr)
	 , _top(nullptr)
	 , _pos(nullptr)
	 , _min(nullptr)
	 , _dif(0)
	{ }

	base_stack_allocator(const memory_block& blk)
	noexcept
	 : _btm((T*)blk.aligned_begin(alignof(T)))
	 , _top((T*)blk.aligned_end(alignof(T)))
	 , _pos(_btm)
	 , _min(_btm)
	 , _dif(0)
	{ }

	~base_stack_allocator(void)
	noexcept
	{
		if(!meta::is_trivially_destructible<T>())
		{
			assert(_pos == _btm);
		}
	}

	size_type max_size(void) const
	noexcept
	{
		assert(_pos <= _top);
		return _top - _pos;
	}

	size_type allocated_size(void) const
	noexcept
	{
		assert(_btm <= _pos);
		return _pos - _btm;
	}

	bool has_allocated(const_pointer p, size_type n) const
	noexcept
	{
		if((p >= _btm) && (p+n <= _top))
		{
			assert(p+n <= _pos);
			return true;
		}
		return false;
	}

	pointer allocate(size_type n)
	noexcept
	{
		if(n > max_size())
		{
			return nullptr;
		}

		pointer result = (pointer)_pos;

		assert(_min <= _pos);
		if(_min == _pos)
		{
			_min += n;
		}
		else
		{
			_dif += n;
		}

		_pos += n;
		return result;
	}

	pointer truncate(pointer p, size_type pn, size_type nn)
	noexcept
	{
		assert(pn >= nn);

		if(p+pn == _pos)
		{
			difference_type d = pn - nn;
			assert(_min <= _pos);
			if(_min == _pos)
			{
				_min -= d;
			}
			else
			{
				_dif -= d;
			}

			_pos -= d;
		}
		return p;
	}

	void deallocate(const_pointer p, size_type n)
	noexcept
	{
		assert(p+n <= _pos);
		if(p+n == _pos)
		{
			assert(_min <= _pos);
			if(_min == _pos)
			{
				_min -= n;
			}
			else
			{
				_dif -= n;
			}

			_pos -= n;
		}
		else
		{
			if(p+n == _min)
			{
				_min -= n;
			}
			else if(p+n > _min)
			{
				_dif -= n;
			}
			else
			{
				_dif += (_min-p)-n;
				_min = (pointer)p;
			}
		}
		if(_dif == 0)
		{
			_pos = _min;
		}
	}

	friend bool operator == (
		const base_stack_allocator& a,
		const base_stack_allocator& b
	)
	{
		if((a._btm == b._btm) && (a._top == b._top))
		{
			assert(a._pos == b._pos);
			assert(a._min == b._min);
			assert(a._dif == b._dif);

			return true;
		}
		return false;
	}
};

// stack_byte_allocator
class stack_byte_allocator
 : public byte_allocator
{
private:
	std::size_t _ref_count;

	base_stack_allocator<byte> _alloc;
public:
	typedef byte value_type;
	typedef std::size_t size_type;

	stack_byte_allocator(stack_byte_allocator&& tmp)
	 : _ref_count(tmp._ref_count)
	 , _alloc(std::move(tmp._alloc))
	{
		tmp._ref_count = 0;
	}

	stack_byte_allocator(void)
	 : _ref_count(1)
	{ }

	stack_byte_allocator(const memory_block& blk)
	 : _ref_count(1)
	 , _alloc(blk)
	{ }

	byte_allocator* duplicate(void)
	noexcept override
	{
		++_ref_count;
		return this;
	}

	bool release(void)
	noexcept override
	{
		return (--_ref_count == 0);
	}

	bool equal(byte_allocator* a) const
	noexcept override
	{
		stack_byte_allocator* sba =
			dynamic_cast<stack_byte_allocator*>(a);

		return (sba != nullptr) && (this->_alloc == sba->_alloc);
	}

	size_type max_size(void)
	noexcept override
	{
		return	_alloc.max_size()>alignof(void*)?
			_alloc.max_size()-alignof(void*):0;
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		size_type m = a - _alloc.allocated_size() % a;
		byte* p = _alloc.allocate(m+n);

		assert((reinterpret_cast<std::uintptr_t>(p+m) % a) == 0);

		if(p == nullptr)
		{
			return nullptr;
		}

		p[m-1] = byte(m);

		return p+m;
	}

	void deallocate(byte* p, size_type n, size_type a)
	noexcept override
	{
		assert(_alloc.has_allocated(p, n));

		size_type m = size_type(p[-1]);

		_alloc.deallocate(p-m, m+n);
	}

/* TODO
	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept override
	{
	}
*/
};

} // namespace base
} // namespace EAGine

#endif //include guard

