/**
 *  @file eagine/unit/si/solid_angle.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_SOLID_ANGLE_1308281038_HPP
#define EAGINE_UNIT_SI_SOLID_ANGLE_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace eagine {
namespace unit {
namespace base {

// steradian
struct steradian : unit<angle, steradian> { };

template <>
struct unit_info<steradian>
{
	typedef meta::string<'s','t','e','r','a','d','i','a','n'> name;
	typedef meta::string<'s','r'> symbol;
};

} // namespace base

// si::base_unit<solid_angle>
template <>
struct si::base_unit<base::solid_angle> : base::steradian { };

// steradian
typedef unit<solid_angle, si> steradian;

} // namespace unit
} // namespace eagine

#endif //include guard

