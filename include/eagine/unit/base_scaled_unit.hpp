/**
 *  @file eagine/unit/base_scaled_unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_BASE_SCALED_UNIT_1308281038_HPP
#define EAGINE_UNIT_BASE_SCALED_UNIT_1308281038_HPP

#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/scales.hpp>

namespace EAGine {
namespace unit {
namespace base {

template <typename Scale, typename Unit>
struct scaled_unit
{
	typedef typename Unit::dimension dimension;
	typedef Scale scale;
	typedef scaled_unit type;
};
typedef scaled_unit<scales::pi, radian> pi_rad;

typedef scaled_unit<scales::kilo, gram> kilogram;
typedef scaled_unit<scales::milli, gram> milligram;

typedef scaled_unit<scales::kilo, meter> kilometer;
typedef scaled_unit<scales::milli, meter> millimeter;

typedef scaled_unit<scales::milli, second> millisecond;

template <typename Scale, typename Unit>
struct unit_info<scaled_unit<Scale, Unit>>
{
	typedef meta::concat<
		typename scales::scale_info<Scale>::name,
		typename unit_info<Unit>::name
	> name;

	typedef meta::concat<
		typename scales::scale_info<Scale>::symbol,
		typename unit_info<Unit>::symbol
	> symbol;
};

typedef scaled_unit<scales::rational<60, 1>, second> minute;

template <>
struct unit_info<minute>
{
	typedef meta::string<'m','i','n','u','t','e'> name;
	typedef meta::string<'m','i','n'> symbol;
};

typedef scaled_unit<scales::rational<3600, 1>, second> hour;

template <>
struct unit_info<hour>
{
	typedef meta::string<'h','o','u','r'> name;
	typedef meta::string<'h','r'> symbol;
};

typedef scaled_unit<scales::rational<86400, 1>, second> day;

template <>
struct unit_info<day>
{
	typedef meta::string<'d','a','y'> name;
	typedef meta::string<'D'> symbol;
};


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
} // namespace unit
} // namespace EAGine

#endif //include guard

