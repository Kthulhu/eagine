/**
 *  @file eagine/base/offset_ptr.hpp
 *  @brief Offset pointers
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_OFFSET_PTR_1408161723_HPP
#define EAGINE_BASE_OFFSET_PTR_1408161723_HPP

#include <eagine/base/type.hpp>
#include <cstddef>
#include <cassert>

namespace eagine {
namespace base {

template <typename T, typename OffsT>
struct basic_offset_ptr
{
private:
	OffsT _offs;
public:
	basic_offset_ptr(OffsT offs)
	noexcept
	 : _offs(offs)
	{ }

	const T* addr(void) const
	noexcept
	{
		return (T*)(_offs?(((byte*)this)+_offs):(byte*)nullptr);
	}

	const T* get(void) const
	noexcept
	{
		return addr();
	}

	operator const T* (void) const
	noexcept
	{
		return addr();
	}

	explicit operator bool (void) const
	noexcept
	{
		return addr() != nullptr;
	}

	const T& operator * (void) const
	noexcept
	{
		assert(bool(*this));
		return *addr();
	}

	const T* operator -> (void) const
	noexcept
	{
		assert(bool(*this));
		return addr();
	}
};

template <typename T>
using offset_ptr = basic_offset_ptr<T, std::ptrdiff_t>;

} // namespace base
} // namespace eagine

#endif //include guard

