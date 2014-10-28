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

