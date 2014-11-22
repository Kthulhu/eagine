/**
 *  @file eagine/unit/dimension.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIMENSION_1308281038_HPP
#define EAGINE_UNIT_DIMENSION_1308281038_HPP

#include <eagine/unit/detail.hpp>
#include <eagine/unit/base_dim.hpp>
#include <eagine/unit/traits.hpp>
#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace unit {

// dimension
template <typename BaseDim, int Pow>
using dimension = bits::dims<
	bits::dim_pow<BaseDim, meta::integral_constant<int, Pow>>,
	bits::nil_t
>;

// multiplication
template <typename D1, typename D2>
typename meta::enable_if<
	is_dimension<D1>::value &&
	is_dimension<D2>::value,
	typename bits::dim_add<D1, D2>::type
>::type operator * (D1, D2);

// division
template <typename D1, typename D2>
typename meta::enable_if<
	is_dimension<D1>::value &&
	is_dimension<D2>::value,
	typename bits::dim_sub<D1, D2>::type
>::type operator / (D1, D2);

// basic dimensions
typedef dimension<base::angle,       1> angle;
typedef dimension<base::solid_angle, 1> solid_angle;

typedef dimension<base::length, 1> length;
typedef dimension<base::mass,   1> mass;
typedef dimension<base::time,   1> time;

typedef dimension<base::temperature,         1> temperature;
typedef dimension<base::electric_current,    1> electric_current;
typedef dimension<base::number_of_cycles,    1> number_of_cycles;
typedef dimension<base::number_of_decays,    1> number_of_decays;
typedef dimension<base::luminous_intensity,  1> luminous_intensity;
typedef dimension<base::amount_of_substance, 1> amount_of_substance;

} // namespace unit
} // namespace eagine

#endif //include guard

