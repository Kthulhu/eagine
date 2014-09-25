/**
 *  @file eagine/unit/base_dim.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_BASE_DIM_1308281038_HPP
#define EAGINE_UNIT_BASE_DIM_1308281038_HPP

namespace EAGine {
namespace unit {

template <typename Dimension>
struct base_dimension
{
	typedef base_dimension type;
};

template <typename BaseDim, typename Unit>
struct base_unit
{
	typedef BaseDim dimension;
	typedef base_unit type;
};

namespace base {

struct angle  : base_dimension<angle> { };
struct length : base_dimension<length> { };
struct mass   : base_dimension<mass> { };
struct time   : base_dimension<time> { };

struct radian : base_unit<angle, radian> { };
struct meter  : base_unit<length, meter> { };
struct gram   : base_unit<mass, gram> { };
struct second : base_unit<time, second> { };

} // namespace base

} // namespace unit
} // namespace EAGine

#endif //include guard

