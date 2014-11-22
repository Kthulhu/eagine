/**
 *  @file eagine/base/access_type.hpp
 *  @brief Access type selectors
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_ACCESS_TYPE_1408161720_HPP
#define EAGINE_BASE_ACCESS_TYPE_1408161720_HPP

namespace eagine {
namespace base {

struct access_read_only_t
{
	template <typename T>
	struct result
	{
		typedef const T type;
	};
};

struct access_read_write_t
{
	template <typename T>
	struct result
	{
		typedef T type;
	};
};

constexpr access_read_only_t access_read_only = {};
constexpr access_read_write_t access_read_write = {};

template <typename T>
struct access
{
	typedef access_read_only_t type;
};

template <typename T>
struct access<const T&>
 : access<T>
{ };

template <typename T>
struct access<T&>
{
	typedef access_read_write_t type;
};

} // namespace base
} // namespace eagine

#endif //include guard

