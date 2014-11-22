/**
 *  @file eagine/unit/base_scaled_unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_BASE_SCALED_UNIT_1308281038_HPP
#define EAGINE_UNIT_BASE_SCALED_UNIT_1308281038_HPP

#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/scales.hpp>

namespace eagine {
namespace unit {
namespace base {

template <typename Scale, typename Unit>
struct scaled_unit
{
	typedef typename Unit::dimension dimension;
	typedef Scale scale;
	typedef scaled_unit type;
};

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

} // namespace base
} // namespace unit
} // namespace eagine

#endif //include guard

