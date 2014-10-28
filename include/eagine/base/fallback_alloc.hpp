/**
 *  @file eagine/base/fallback_alloc.hpp
 *  @brief Allocator with fallback.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_FALLBACK_ALLOC_1308281038_HPP
#define EAGINE_BASE_FALLBACK_ALLOC_1308281038_HPP

#include <eagine/base/alloc.hpp>
#include <eagine/meta/type_traits.hpp>

namespace EAGine {
namespace base {

template <
	typename T,
	typename DefaultAlloc,
	typename FallbackAlloc = allocator<T>
>
class allocator_with_fallback
{
private:
	DefaultAlloc _dft_alloc;
	FallbackAlloc _fbk_alloc;
	bool _had_to_fbk;

	static_assert(
		meta::is_same<
			typename DefaultAlloc::value_type, T
		>::value &&
		meta::is_same<
			typename DefaultAlloc::value_type,
			typename FallbackAlloc::value_type
		>::value,
		"Both allocators must have the same value type"
	);

	// _has_allocate_noexcept helpers
	template <
		typename X, 
		typename X::pointer
		(X::*)(typename X::size_type, const void*)
	> struct _has_alc_noe_hlp { };

	template <typename X>
	static meta::true_type _has_alc_noe(
		_has_alc_noe_hlp<X, &X::allocate_noexcept>*
	);

	template <typename X>
	static meta::false_type _has_alc_noe(...);

	// _has_allocate_noexcept
	template <typename X>
	struct _has_allocate_noexcept
	 : decltype(_has_alc_noe<X>(nullptr))
	{ };

	// _has_has_allocated helpers
	template <
		typename X, 
		bool
		(X::*)(typename X::const_pointer, typename X::size_type) const
	> struct _has_has_alc_hlp { };

	template <typename X>
	static meta::true_type _has_has_alc(
		_has_has_alc_hlp<X, &X::has_allocated>*
	);

	template <typename X>
	static meta::false_type _has_has_alc(...);

	// _has_has_allocated
	template <typename X>
	struct _has_has_allocated
	 : decltype(_has_has_alc<X>(nullptr))
	{ };
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	typedef DefaultAlloc default_allocator_type;
	typedef FallbackAlloc fallback_allocator_type;

	template <typename U>
	struct rebind
	{
		typedef allocator_with_fallback<
			U,
			typename DefaultAlloc::template rebind<U>::other,
			typename FallbackAlloc::template rebind<U>::other
		> other;
	};

	const DefaultAlloc& default_allocator(void) const
	noexcept
	{
		return _dft_alloc;
	}

	const FallbackAlloc& fallback_allocator(void) const
	noexcept
	{
		return _fbk_alloc;
	}

	bool had_to_fallback(void) const
	noexcept
	{
		return _had_to_fbk;
	}

	allocator_with_fallback(const allocator_with_fallback&) = default;

	allocator_with_fallback(void)
	noexcept
	 : _had_to_fbk(false)
	{ }

	allocator_with_fallback(const DefaultAlloc& dft_alloc)
	noexcept
	 : _dft_alloc(dft_alloc)
	 , _had_to_fbk(false)
	{ }

	allocator_with_fallback(
		const DefaultAlloc& dft_alloc,
		const FallbackAlloc& fbk_alloc
	) noexcept
	 : _dft_alloc(dft_alloc)
	 , _fbk_alloc(fbk_alloc)
	 , _had_to_fbk(false)
	{ }

	template <typename U>
	allocator_with_fallback(const typename rebind<U>::other& that)
	noexcept
	 : _dft_alloc(that.default_allocator())
	 , _fbk_alloc(that.fallback_allocator())
	 , _had_to_fbk(that._had_to_fbk)
	{ }

	size_type max_size(void) const
	noexcept
	{
		size_type mdft = _dft_alloc.max_size();
		size_type mfbk = _fbk_alloc.max_size();

		return (mfbk>mdft)?mfbk:mdft;
	}

	template <typename ConstPointer>
	typename meta::enable_if<
		meta::is_same<ConstPointer, const_pointer>::value ||
		_has_has_allocated<FallbackAlloc>::value,
		bool
	>::type
	has_allocated(ConstPointer p, size_type n) const
	noexcept
	{
		return	_dft_alloc.has_allocated(p, n) ||
			_fbk_alloc.has_allocated(p, n);
	}

	template <typename Void = void>
	typename meta::enable_if<
		meta::is_same<Void, void>::value &&
		_has_allocate_noexcept<FallbackAlloc>::value,
		pointer
	>::type
	allocate_noexcept(size_type n, const Void* h = nullptr)
	noexcept
	{
		if(n <= _dft_alloc.max_size())
		{
			if(pointer p = _dft_alloc.allocate_noexcept(n, h))
			{
				return p;
			}
		}
		_had_to_fbk = true;
		return _fbk_alloc.allocate_noexcept(n, h);
	}

	pointer allocate(size_type n, const void* h = nullptr)
	{
		if(n <= _dft_alloc.max_size())
		{
			if(pointer p = _dft_alloc.allocate_noexcept(n, h))
			{
				return p;
			}
		}
		_had_to_fbk = true;
		return _fbk_alloc.allocate(n, h);
	}

	void deallocate(pointer p, size_type n)
	noexcept
	{
		if(_dft_alloc.has_allocated(p, n))
		{
			_dft_alloc.deallocate(p, n);
		}
		else
		{
			_fbk_alloc.deallocate(p, n);
		}
	}

	friend bool operator == (
		const allocator_with_fallback& a,
		const allocator_with_fallback& b
	)
	{
		return	(a._dft_alloc == b._dft_alloc) &&
			(a._fbk_alloc == b._fbk_alloc);
	}

	friend bool operator != (
		const allocator_with_fallback& a,
		const allocator_with_fallback& b
	)
	{
		return	(a._dft_alloc != b._dft_alloc) &&
			(a._fbk_alloc != b._fbk_alloc);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

