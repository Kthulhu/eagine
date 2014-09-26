/**
 *  @file eagine/unit/base_dim.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_BASE_DIM_1308281038_HPP
#define EAGINE_UNIT_BASE_DIM_1308281038_HPP

#include <eagine/meta/int_const.hpp>
#include <eagine/meta/string.hpp>
#include <eagine/unit/scales.hpp>

namespace EAGine {
namespace unit {
namespace base {

template <typename Derived>
struct dimension
{
	typedef Derived type;
};

struct angle  : dimension<angle> { };
struct length : dimension<length> { };
struct mass   : dimension<mass> { };
struct time   : dimension<time> { };

template <typename Dimension>
struct dim_num;

template <> struct dim_num<angle>  : meta::integral_constant<int, 0>{ };
template <> struct dim_num<mass>   : meta::integral_constant<int, 1> { };
template <> struct dim_num<length> : meta::integral_constant<int, 2> { };
template <> struct dim_num<time>   : meta::integral_constant<int, 3> { };

template <typename Dimension>
struct dim_info;

template <>
struct dim_info<angle>
{
	typedef meta::string<'a','n','g','l','e'> name;
};

template <>
struct dim_info<mass>
{
	typedef meta::string<'m','a','s','s'> name;
};

template <>
struct dim_info<length>
{
	typedef meta::string<'l','e','n','g','t','h'> name;
};

template <>
struct dim_info<time>
{
	typedef meta::string<'t','i','m','e'> name;
};

} // namespace base
} // namespace unit
} // namespace EAGine

#endif //include guard

