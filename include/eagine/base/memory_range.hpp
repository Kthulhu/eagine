/**
 *  @file eagine/base/memory_range.hpp
 *  @brief Memory range.
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_MEMORY_RANGE_1408161723_HPP
#define EAGINE_BASE_MEMORY_RANGE_1408161723_HPP

#include <eagine/base/memory_block.hpp>
#include <cstdint>

namespace eagine {
namespace base {

template <typename T>
class typed_memory_range
 : public crtp_memory_range<
	typed_memory_range<T>,
	typed_memory_range<T>,
	T, T
>
{
private:
	T* _addr;
	std::size_t _size;

	T* _cast(typename meta::add_same_constness<T, void>::type* ptr)
	noexcept
	{
		assert(std::uintptr_t(ptr) % alignof(T) == 0);
		return static_cast<T*>(ptr);
	}
public:
	typedef basic_memory_block<meta::is_const<T>::value> raw_block;

	typed_memory_range(void)
	noexcept
	 : _addr(nullptr)
	 , _size(0)
	{ }

	typed_memory_range(T* addr_, std::size_t size_)
	noexcept
	 : _addr(addr_)
	 , _size(size_)
	{ }

	typed_memory_range(T* bgn_, T* end_)
	noexcept
	 : _addr(bgn_)
	 , _size(end_-bgn_)
	{ }

	typed_memory_range(const raw_block& raw)
	noexcept
	 : _addr(_cast(raw.aligned_begin(alignof(T))))
	 , _size(_cast(raw.aligned_end(alignof(T)))-_addr)
	{ }

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<!Const, T*>::type
	addr(void)
	noexcept
	{
		return _addr;
	}

	const T* addr(void) const
	noexcept
	{
		return _addr;
	}

	std::size_t size(void) const
	noexcept
	{
		return _size;
	}
};

typedef typed_memory_range<byte> byte_range;
typedef typed_memory_range<const byte> const_byte_range;

template <typename Derived, typename Slice, typename T>
class crtp_derived_memory_range
 : public crtp_memory_range<Derived, Slice, T, T>
{
public:
	typed_memory_range<const T> range(void) const
	noexcept
	{
		return {
			this->self().addr(),
			this->self().size()
		};
	}

	template <bool Const = meta::is_const<T>::value>
	typename meta::enable_if<
		!Const,
		typed_memory_range<T>
	>::type range(void)
	noexcept
	{
		return {
			this->self().addr(),
			this->self().size()
		};
	}

	operator typed_memory_range<const T>(void) const
	noexcept
	{
		return range();
	}

	template <
		bool Const = meta::is_const<T>::value,
		typename = typename meta::enable_if<!Const>::type
	>
	operator typed_memory_range<T>(void)
	noexcept
	{
		return range();
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

