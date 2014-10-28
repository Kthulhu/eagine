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
#include <eagine/base/memory.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/meta/type_traits.hpp>
#include <cstring>

namespace EAGine {
namespace base {

// _sh_ptr_hlp_alloc
// helper allocator used by stack_allocator
// to allocate the shared_pointer data-block
// in same memory block used by that stack_allocator
// DO NOT use directly
template <typename T>
class _sh_ptr_hlp_alloc
{
public:
	memory_block  _blk;
	memory_block* _pfb;

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
		typedef _sh_ptr_hlp_alloc<U> other;
	};

	_sh_ptr_hlp_alloc(const memory_block& blk, memory_block* pfb)
	noexcept
	 : _blk(blk)
	 , _pfb(pfb)
	{ }

	template <typename U>
	_sh_ptr_hlp_alloc(const _sh_ptr_hlp_alloc<U>& that)
	noexcept
	 : _blk(that._blk)
	 , _pfb(that._pfb)
	{ }

	size_type max_size(void) const
	noexcept
	{
		return _blk.size() / sizeof(T);
	}

	pointer allocate(size_type n, const void* = nullptr)
	{
		assert(n < max_size());
		assert(_pfb);
		*_pfb = _blk.slice(n*sizeof(T));
		return (pointer)_blk.addr();
	}

	void deallocate(const_pointer p, size_type n)
	noexcept
	{
		assert(p == _blk.addr());
	}
};

// base_stack_allocator
// non-rebindable non-copyable stack allocator
// used as shared delegate by stack_allocator.
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

	base_stack_allocator(const base_stack_allocator&) = delete;

	~base_stack_allocator(void)
	noexcept
	{
		if(!meta::is_trivially_destructible<T>())
		{
			assert(_pos == _btm);
		}
	}

	void reset(const memory_block& blk)
	{
		_btm = (T*)blk.aligned_begin(alignof(T));
		_top = (T*)blk.aligned_end(alignof(T));
		_pos = _btm;
		_min = _btm;
		_dif = 0;
	}

	size_type max_size(void) const
	noexcept
	{
		assert(_pos <= _top);
		return _top - _pos;
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

	pointer allocate_noexcept(size_type n)
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

	pointer allocate(size_type n)
	{
		pointer p = allocate_noexcept(n);
		if(p == nullptr)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	pointer truncate(pointer p, pointer pn, pointer nn)
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
};

// stack_allocator - fwd
template <typename T>
class stack_allocator;

// stack_allocator<void>
template <>
class stack_allocator<void>
{
private:
	memory_block _blk;
public:
	stack_allocator(void) = default;

	stack_allocator(const memory_block& blk)
	noexcept
	 : _blk(blk)
	{ }

	operator memory_block(void) const
	noexcept
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

// stack_allocator<T>
template <typename T>
class stack_allocator
{
private:
	typedef shared_ptr<base_stack_allocator<T>> _sbsa_t;
	_sbsa_t _bsa;

	static _sbsa_t _make_bsa(const memory_block& blk)
	{
		typedef base_stack_allocator<T> _bsa_t;

		memory_block fb;
		_sh_ptr_hlp_alloc<T> ta(blk, &fb);

		_sbsa_t result = allocate_shared<_bsa_t>(ta);

		assert(result);
		result->reset(fb);

		return result;
	}
public:
	stack_allocator(void)
	noexcept
	{ }

	stack_allocator(const memory_block& blk)
	noexcept
	 : _bsa(_make_bsa(blk))
	{ }

	stack_allocator(const stack_allocator&) = default;

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

	pointer address(reference r)
	noexcept
	{
		return allocator<T>().address(r);
	}

	const_pointer address(const_reference r)
	noexcept
	{
		return allocator<T>().address(r);
	}

	size_type max_size(void) const
	noexcept
	{
		if(_bsa)
		{
			return _bsa->max_size();
		}
		return 0;
	}

	bool has_allocated(const_pointer p, size_type n) const
	noexcept
	{
		assert(_bsa);
		return _bsa->has_allocated(p, n);
	}
	

	pointer allocate_noexcept(size_type n, const void* = nullptr)
	noexcept
	{
		assert(_bsa);
		return _bsa->allocate_noexcept(n);
	}

	pointer allocate(size_type n, const void* = nullptr)
	{
		assert(_bsa);
		return _bsa->allocate(n);
	}

	pointer reallocate(pointer p, size_type pn, size_type nn)
	{
		assert(_bsa);
		return _bsa->reallocate(p, pn, nn);
	}

	pointer truncate(pointer p, size_type pn, size_type nn)
	noexcept
	{
		assert(_bsa);
		return _bsa->truncate(p, pn, nn);
	}

	void deallocate(const_pointer p, size_type n)
	noexcept
	{
		assert(_bsa);
		_bsa->deallocate(p, n);
	}

	template <typename U, typename ... A>
	void construct(U* p, A&&...a)
	noexcept(noexcept(U(std::forward<A>(a)...)))
	{
		::new((void*)p) U(std::forward<A>(a)...);
	}

	void destroy(pointer p)
	noexcept(noexcept(((T*)p)->~T()))
	{
		((T*)p)->~T();
	}

	template <typename U>
	void destroy(U* p)
	noexcept(noexcept(p->~U()))
	{
		p->~U();
	}

	friend bool operator == (
		const stack_allocator& a,
		const stack_allocator& b
	) noexcept
	{
		return(a._bsa == b._bsa);
	}

	friend bool operator != (
		const stack_allocator& a,
		const stack_allocator& b
	) noexcept
	{
		return(a._bsa != b._bsa);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

