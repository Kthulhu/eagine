/**
 *  @file eagine/unit/si/angle.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ANGLE_1308281038_HPP
#define EAGINE_UNIT_SI_ANGLE_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// radian
struct radian : unit<angle, radian> { };

template <>
struct unit_info<radian>
{
	typedef meta::string<'r','a','d','i','a','n'> name;
	typedef meta::string<'r','a','d'> symbol;
};

// degree
typedef scaled_unit<
	scales::divided<scales::pi, scales::rational<180, 1>>,
	radian
> degree;

template <>
struct unit_info<degree>
{
	typedef meta::string<'d','e','g','r','e','e'> name;
	typedef meta::string<char(0xC2),char(0xB0)> symbol;
};

// gradian
typedef scaled_unit<
	scales::divided<scales::pi, scales::rational<200, 1>>,
	radian
> gradian;

template <>
struct unit_info<gradian>
{
	typedef meta::string<'g','r','a','d','i','a','n'> name;
	typedef meta::string<'g','r','a','d'> symbol;
};

// quarter
typedef scaled_unit<
	scales::multiplied<scales::pi, scales::rational<1, 2>>,
	radian
> quarter;

template <>
struct unit_info<quarter>
{
	typedef meta::string<'q','u','a','r','t','e','r'> name;
	typedef meta::string<'Q'> symbol;
};

// turn
typedef scaled_unit<
	scales::multiplied<scales::rational<2, 1>, scales::pi>,
	radian
> turn;

template <>
struct unit_info<turn>
{
	typedef meta::string<'t','u','r','n'> name;
	typedef meta::string<'r'> symbol;
};

} // namespace base

// si::base_unit<angle>
template <>
struct si::base_unit<base::angle> : base::radian { };

// radian
typedef unit<angle, si> radian;

// derived
typedef make_scaled_unit<base::degree, si>::type degree;
typedef make_scaled_unit<base::gradian, si>::type gradian;
typedef make_scaled_unit<base::quarter, si>::type quarter;
typedef make_scaled_unit<base::turn, si>::type turn;

typedef make_scaled_unit<base::scaled_unit<scales::pi, base::radian>, si>::type pi_rad;

} // namespace unit
} // namespace EAGine

#endif //include guard

