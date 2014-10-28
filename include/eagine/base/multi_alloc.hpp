/**
 *  @file eagine/base/multi_alloc.hpp
 *  @brief Generic memory allocator.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_MULTI_ALLOC_1308281038_HPP
#define EAGINE_BASE_MULTI_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/base/type.hpp>
#include <eagine/meta/nil_t.hpp>
#include <cstddef>
#include <cassert>

namespace EAGine {
namespace base {

template <typename Alloc>
class multi_allocator
{
private:
	typedef typename Alloc::template rebind<byte>::other _a_t;
	_a_t _a;

	static std::ptrdiff_t _misalign(const byte* p, std::size_t alignment)
	{
		return ((std::uintptr_t)p) % alignment;
	}
public:
	typedef meta::nil_t value_type;
	typedef void* pointer;
	typedef const void* const_pointer;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Alloc base_allocator_type;

	const base_allocator_type& base_allocator(void) const
	noexcept
	{
		return _a;
	}

	multi_allocator(void) = default;
	multi_allocator(const multi_allocator&) = default;

	multi_allocator(const Alloc& a)
	 : _a(a)
	{ }

	template <typename ... Arg>
	explicit multi_allocator(Arg&&...arg)
	 : _a(std::forward<Arg>(arg)...)
	{ }

	template <typename T>
	T* address(T& r) noexcept
	{
		return allocator<T>().address(r);
	}

	template <typename T>
	const T* address(const T& r) noexcept
	{
		return allocator<T>().address(r);
	}

	template <typename T>
	size_type max_size(void) const noexcept
	{
		return _a.max_size() / sizeof(T);
	}

	template <typename T>
	T* allocate(size_type n, const void* = nullptr)
	{
		const std::size_t st = sizeof(T);
		const std::size_t at = alignof(T);

		byte* p = _a.allocate(at+n*st);
		std::size_t m = _misalign(p, at);
		std::size_t s = at-m;

		assert(s < 128);
		p += s;

		*(p-1) = byte(s);

		assert(_misalign(p, at) == 0);
		return (T*)(void*)p;
	}

	template <typename T>
	void deallocate(const T* p, size_type n)
	{
		const std::size_t st = sizeof(T);
		const std::size_t at = alignof(T);

		byte* r = (byte*)(void*)p;

		std::size_t s(*(r-1));
		r = r-s;
		_a.deallocate(r, at+n*st);
	}

	template <typename T>
	void construct(T* p, const T& v)
	{
		std::allocator<T>().construct(p, v);
	}

	template <typename T, typename ... Arg>
	void construct(T* p, Arg&&...arg)
	{
		std::allocator<T>().construct(p, std::forward<Arg>(arg)...);
	}

	template <typename T>
	void destroy(T* p)
	{
		std::allocator<T>().destroy(p);
	}

	friend bool operator == (
		const multi_allocator& a,
		const multi_allocator& b
	)
	{
		return a._a == b._a;
	}

	friend bool operator != (
		const multi_allocator& a,
		const multi_allocator& b
	)
	{
		return a._a != b._a;
	}

	template <typename U>
	struct rebind;
};

template <typename T, typename Alloc>
class multi_alloc_t
{
private:
	multi_allocator<Alloc>* _pma;

	multi_allocator<Alloc>& _ma(void)
	{
		assert(_pma != nullptr);
		return *_pma;
	}

	const multi_allocator<Alloc>& _ma(void) const
	{
		assert(_pma != nullptr);
		return *_pma;
	}
public:
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
		typedef multi_alloc_t<U, Alloc> other;
	};

	multi_allocator<Alloc>* parent(void) const
	{
		return _pma;
	}

	multi_alloc_t(void)
	 : _pma(nullptr)
	{ }

	multi_alloc_t(multi_allocator<Alloc>& ma)
	 : _pma(&ma)
	{ }

	template <typename U>
	multi_alloc_t(const multi_alloc_t<U, Alloc>& mat)
	 : _pma(mat.parent())
	{ }

	pointer address(reference r) noexcept
	{
		return _ma().address(r);
	}

	const_pointer address(const_reference r) noexcept
	{
		return _ma().address(r);
	}

	size_type max_size(void) const noexcept
	{
		return _ma().template max_size<T>();
	}

	pointer allocate(size_type n)
	{
		return _ma().template allocate<T>(n);
	}

	pointer allocate(size_type n, const void* h)
	{
		return _ma().template allocate<T>(n, h);
	}

	void deallocate(const_pointer p, size_type n)
	{
		_ma().deallocate(p, n);
	}

	void construct(pointer p, const_reference r)
	{
		_ma().construct(p, r);
	}

	template <typename ... Arg>
	void construct(pointer p, Arg&&... arg)
	{
		_ma().construct(p, std::forward<Arg>(arg)...);
	}

	void destroy(pointer p)
	{
		_ma().destroy(p);
	}

	template <typename U>
	void destroy(U* p)
	{
		_ma().destroy(p);
	}

	friend bool operator == (const multi_alloc_t& a, const multi_alloc_t& b)
	{
		return	(a._pma == b._pma) || (
			(a._pma && b._pma) &&
			(*a._pma == *b._pma)
		);
	}

	friend bool operator != (const multi_alloc_t& a, const multi_alloc_t& b)
	{
		return	(a._pma != b._pma) && (
			(a._pma && b._pma) &&
			(*a._pma != *b._pma)
		);
	}
};

template <typename Alloc>
template <typename U>
struct multi_allocator<Alloc>::rebind
{
	typedef multi_alloc_t<U, Alloc> other;
};

} // namespace base
} // namespace EAGine

#endif //include guard

