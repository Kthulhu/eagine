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

template <typename Scale1, typename Scale2>
struct mul_scales
{
	typedef mul_scales type;
	static constexpr auto value = Scale1::value*Scale2::value;
};

template <typename Scale1, typename Scale2>
struct div_scales
{
	typedef div_scales type;
	static constexpr auto value = Scale1::value/Scale2::value;
};

template <typename Scale, typename Unit>
struct scaled_unit
{
	typedef typename Unit::dimension dimension;
	typedef Scale scale;
	typedef scaled_unit type;
};

typedef scaled_unit<scales::kilo, gram> kilogram;
typedef scaled_unit<scales::milli, gram> milligram;

typedef scaled_unit<scales::kilo, meter> kilometer;
typedef scaled_unit<scales::milli, meter> millimeter;

typedef scaled_unit<scales::milli, second> millisecond;


template <typename Scale, typename Unit>
struct unit_info<scaled_unit<Scale, Unit>>
{
	typedef meta::concat<
		typename Scale::name,
		typename Unit::name
	> name;

	typedef meta::concat<
		typename Scale::symbol,
		typename Unit::symbol
	> symbol;
};

} // namespace base
} // namespace unit
} // namespace EAGine

#endif //include guard

