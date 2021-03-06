/**
 *  @file eagine/unit/si/common.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_COMMON_1308281038_HPP
#define EAGINE_UNIT_SI_COMMON_1308281038_HPP

#include <eagine/unit/base_dim.hpp>
#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/base_scaled_unit.hpp>
#include <eagine/unit/unit.hpp>
#include <eagine/unit/scaled_unit.hpp>

namespace eagine {
namespace unit {

// international system of units
struct si
{
	template <typename BaseDim>
	struct base_unit;
};

template <>
struct system_id<si>
 : meta::int_constant<0>
{ };

} // namespace unit
} // namespace eagine

#endif //include guard

