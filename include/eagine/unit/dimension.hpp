/**
 *  @file eagine/unit/dimension.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_DIMENSION_1308281038_HPP
#define EAGINE_UNIT_DIMENSION_1308281038_HPP

#include <eagine/unit/detail.hpp>
#include <eagine/unit/base_dim.hpp>

namespace EAGine {
namespace unit {

template <typename BaseDim, int Pow>
using dimension = bits::dims<
	bits::dim_pow<BaseDim, meta::integral_constant<int, Pow>>,
	bits::nil_t
>;

typedef dimension<base::angle , 1> angle;
typedef dimension<base::length, 1> length;
typedef dimension<base::mass,   1> mass;
typedef dimension<base::time,   1> time;

} // namespace unit
} // namespace EAGine

#endif //include guard

