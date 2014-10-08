/**
 *  @file eagine/base/alloc.hpp
 *  @brief Generic memory allocators.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ALLOC_1308281038_HPP
#define EAGINE_BASE_ALLOC_1308281038_HPP

#include <memory>
#include <cassert>

namespace EAGine {
namespace base {

using ::std::allocator;

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
	stack_allocator(T* btm, std::size_t sze)
	 : _btm(btm)
	 , _top(btm+sze)
	 , _pos(btm)
	 , _min(btm)
	 , _dif(0)
	{
		assert(_btm <= _top);
	}

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
};


} // namespace base
} // namespace EAGine

#endif //include guard

