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
#include <cstring>

namespace EAGine {
namespace base {

template <typename T>
class stack_allocator;

template <>
class stack_allocator<void>
{
private:
	memory_block _blk;
public:
	stack_allocator(void) = default;

	stack_allocator(const memory_block& blk)
	 : _blk(blk)
	{ }

	operator memory_block(void) const
	{
		return _blk;
	}

	typedef void value_type;
	typedef void* pointer;
	typedef const void* const_pointer;

	template <typename U>
	struct rebind
	{
		typedef stack_allocator<U> other;
	};
};

template <typename T>
class stack_allocator
{
private:
	const T* const _btm;
	const T* const _top;
	const T* _pos;
	const T* _min;
	std::size_t _dif;
public:
	stack_allocator(void)
	 : _btm(nullptr)
	 , _top(nullptr)
	 , _pos(nullptr)
	 , _min(nullptr)
	 , _dif(0)
	{ }

	stack_allocator(const memory_block& blk)
	 : _btm((T*)blk.aligned_begin(alignof(T)))
	 , _top((T*)blk.aligned_end(alignof(T)))
	 , _pos(_btm)
	 , _min(_btm)
	 , _dif(0)
	{ }

	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	template <typename U>
	struct rebind
	{
		typedef stack_allocator<U> other;
	};

	pointer address(reference r) noexcept
	{
		return allocator<T>().address(r);
	}

	const_pointer address(const_reference r) noexcept
	{
		return allocator<T>().address(r);
	}

	size_type max_size(void) const noexcept
	{
		assert(_pos <= _top);
		return _top - _pos;
	}

	pointer allocate(size_type n, const void* = nullptr)
	{
		if(n > max_size())
		{
			throw std::bad_alloc();
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

	pointer reallocate(pointer p, size_type pn, size_type nn)
	{
		if(p+pn == _pos)
		{
			difference_type d = nn - pn;
			assert(_min <= _pos);
			if(_min == _pos)
			{
				_min += d;
			}
			else
			{
				_dif += d;
			}

			_pos += d;
			return p;
		}
		else
		{
			pointer r = allocate(nn);
			std::memmove(r, p, nn<pn?nn:pn);
			deallocate(p, pn);
			return r;
		}
	}

	pointer truncate(pointer p, size_type pn, size_type nn)
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
				_min = p;
			}
		}
		if(_dif == 0)
		{
			_pos = _min;
		}
	}

	template <typename U, typename ... A>
	void construct(U* p, A&&...a)
	{
		::new((void*)p) U(std::forward<A>(a)...);
	}

	void destroy(pointer p)
	{
		((T*)p)->~T();
	}

	template <typename U>
	void destroy(U* p)
	{
		p->~U();
	}

	friend bool operator == (
		const stack_allocator& a,
		const stack_allocator& b
	)
	{
		return	(a._btm == b._btm) && (a._top == b._top);
	}

	friend bool operator != (
		const stack_allocator& a,
		const stack_allocator& b
	)
	{
		return	(a._btm != b._btm) || (a._top != b._top);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

