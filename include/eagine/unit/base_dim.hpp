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
#include <eagine/unit/scales.hpp>

namespace EAGine {
namespace unit {
namespace base {

template <typename Derived>
struct dimension
{
	typedef dimension type;
};

template <typename Dimension>
struct dim_order;

struct angle  : dimension<angle> { };
struct length : dimension<length> { };
struct mass   : dimension<mass> { };
struct time   : dimension<time> { };

template <> struct dim_order<angle>  : meta::integral_constant<int, 0>{ };
template <> struct dim_order<length> : meta::integral_constant<int, 1> { };
template <> struct dim_order<mass>   : meta::integral_constant<int, 2> { };
template <> struct dim_order<time>   : meta::integral_constant<int, 3> { };

template <typename Dimension, typename Derived>
struct unit
{
	typedef Dimension dimension;
	typedef scales::one scale;
	typedef unit type;
};

struct radian : unit<angle, radian> { };
struct meter  : unit<length, meter> { };
struct gram   : unit<mass, gram> { };
struct second : unit<time, second> { };

template <typename Scale, typename Unit>
struct scaled_unit
{
	typedef typename Unit::dimension dimension;
	typedef Scale scale;
	typedef scaled_unit type;
};

} // namespace base
} // namespace unit
} // namespace EAGine

#endif //include guard

