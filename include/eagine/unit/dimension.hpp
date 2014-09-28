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
#include <eagine/unit/traits.hpp>
#include <eagine/meta/type_traits.hpp>

namespace EAGine {
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
typedef dimension<base::angle , 1> angle;
typedef dimension<base::length, 1> length;
typedef dimension<base::mass,   1> mass;
typedef dimension<base::time,   1> time;

// derived dimensions
typedef decltype(length()*length()) area;
typedef decltype(length()*length()*length()) volume;
typedef decltype(length()/time()) velocity;
typedef decltype(velocity()/time()) acceleration;

typedef decltype(acceleration()*mass()) force;
typedef decltype(force()*length()) energy;
typedef decltype(force()/area()) pressure;
typedef decltype(energy()/time()) power;

} // namespace unit
} // namespace EAGine

#endif //include guard

