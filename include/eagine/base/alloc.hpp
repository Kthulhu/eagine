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

#include <eagine/base/type.hpp>
#include <memory>
#include <limits>
#include <cassert>
#include <cstdlib>

namespace EAGine {
namespace base {

// byte_allocator
struct byte_allocator
{
	typedef byte value_type;
	typedef std::size_t size_type;

	virtual ~byte_allocator(void)
	noexcept
	{ }

	virtual byte_allocator* duplicate(void)
	noexcept = 0;

	virtual bool release(void)
	noexcept = 0;

	virtual
	size_type max_size(void)
	noexcept = 0;

	virtual
	byte* allocate(size_type n, size_type a)
	noexcept = 0;

	virtual
	void deallocate(byte* p, size_type n, size_type a)
	noexcept = 0;
};

// byte_reallocator
struct byte_reallocator
 : byte_allocator
{
	virtual
	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept = 0;
};

// c_byte_reallocator
class c_byte_reallocator
 : public byte_reallocator
{
private:
	std::size_t _ref_count;
public:
	c_byte_reallocator(const c_byte_reallocator&) = delete;

	c_byte_reallocator(c_byte_reallocator&& tmp)
	noexcept
	 : _ref_count(tmp._ref_count)
	{
		tmp._ref_count = 0;
	}

	c_byte_reallocator(void)
	noexcept
	 : _ref_count(1)
	{ }

	~c_byte_reallocator(void)
	noexcept
	{
		assert(_ref_count == 0);
	}

	c_byte_reallocator* duplicate(void)
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

	size_type max_size(void)
	noexcept override
	{
		return std::numeric_limits<size_type>::max();
	}

	byte* allocate(size_type n, size_type a)
	noexcept override
	{
		assert(a > 0);

		if(n == 0)
		{
			return nullptr;
		}

		byte* p = (byte*)std::malloc(n);

		// TODO fix if misaligned ?
		assert((reinterpret_cast<std::uintptr_t>(p) % a) == 0);

		return p;
	}

	void deallocate(byte* p, size_type, size_type)
	noexcept override
	{
		if(p != nullptr)
		{
			std::free(p);
		}
	}

	byte* reallocate(byte* p, size_type o, size_type n, size_type a)
	noexcept override
	{
		assert(a > 0);

		if(n == 0)
		{
			deallocate(p, o, a);
			return nullptr;
		}

		p = (byte*)std::realloc(p, n);

		// TODO fix if misaligned ?
		assert((reinterpret_cast<std::uintptr_t>(p) % a) == 0);

		return p;
	}
};

// default byte_allocator
typedef c_byte_reallocator default_byte_allocator;


// allocator
template <typename T>
class allocator
{
private:
	byte_allocator* _pballoc;

	template <typename X>
	static byte_allocator* _get_new(
		const X& that,
		typename std::enable_if<
			std::is_convertible<X*, byte_allocator*>::value
		>::type* = nullptr
	) noexcept
	{
		try { return new X(that); }
		catch(std::bad_alloc&) { return nullptr; }
		return nullptr;
	}

	template <typename X>
	static byte_allocator* _get_new(
		X& that,
		typename std::enable_if<
			std::is_convertible<X*, byte_allocator*>::value
		>::type* = nullptr
	) noexcept
	{
		try { return new X(that); }
		catch(std::bad_alloc&) { return nullptr; }
		return nullptr;
	}

	template <typename X>
	static byte_allocator* _get_new(
		X&& that,
		typename std::enable_if<
			std::is_convertible<X*, byte_allocator*>::value
		>::type* = nullptr
	) noexcept
	{
		try { return new X(std::move(that)); }
		catch(std::bad_alloc&) { return nullptr; }
		return nullptr;
	}

	template <typename U>
	static byte_allocator* _get_new(const allocator<U>& a)
	noexcept
	{
		return a._copy();
	}

	template <typename U>
	static byte_allocator* _get_new(allocator<U>&& a)
	noexcept
	{
		return a._release();
	}

	void _cleanup(void)
	noexcept
	{
		if(_pballoc)
		{
			if(_pballoc->release())
			{
				delete _pballoc;
			}
		}
	}
public:
	// implementation detail DO NOT use directly
	byte_allocator* _release(void)
	noexcept
	{
		byte_allocator* result = _pballoc;
		_pballoc = nullptr;
		return result;
	}

	// implementation detail DO NOT use directly
	byte_allocator* _copy(void) const
	noexcept
	{
		return _pballoc?_pballoc->duplicate():nullptr;
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
		typedef allocator<U> other;
	};

	allocator(void)
	noexcept
	 : allocator(default_byte_allocator())
	{ }

	allocator(const allocator& that)
	noexcept
	 : _pballoc(that._copy())
	{ }

	allocator(allocator&& tmp)
	noexcept
	 : _pballoc(tmp._release())
	{ }

	template <typename X>
	allocator(X&& x)
	noexcept
	 : _pballoc(_get_new(std::forward<X>(x)))
	{ }

	allocator& operator = (const allocator& that)
	noexcept
	{
		_cleanup();
		_pballoc = that._copy();
		return *this;
	}

	allocator& operator = (allocator&& that)
	noexcept
	{
		_cleanup();
		_pballoc = that._release();
		return *this;
	}

	~allocator(void)
	noexcept
	{
		_cleanup();
	}

	T* address(T& r)
	noexcept
	{
		return std::allocator<T>().address(r);
	}

	const T* address(const T& r)
	noexcept
	{
		return std::allocator<T>().address(r);
	}

	size_type max_size(void) const
	noexcept
	{
		return _pballoc?_pballoc->max_size():0;
	}

	T* allocate(size_type n, const void* = nullptr)
	{
		assert(_pballoc);

		byte* p = _pballoc->allocate(n*sizeof(T), alignof(T));

		assert((reinterpret_cast<std::uintptr_t>(p) % alignof(T)) == 0);

		if(p == nullptr)
		{
			throw std::bad_alloc();
		}

		return reinterpret_cast<T*>(p);
	}

	void deallocate(T* p, size_type n)
	{
		assert(_pballoc);

		_pballoc->deallocate(
			reinterpret_cast<byte*>(p),
			n*sizeof(T),
			alignof(T)
		);
	}

	friend bool operator == (const allocator& a, const allocator& b)
	noexcept
	{
		return(a._pballoc == b._pballoc);
	}

	friend bool operator != (const allocator& a, const allocator& b)
	noexcept
	{
		return(a._pballoc != b._pballoc);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

