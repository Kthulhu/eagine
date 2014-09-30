/**
 *  @file eagine/unit/si/power.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_POWER_1308281038_HPP
#define EAGINE_UNIT_SI_POWER_1308281038_HPP

#include <eagine/unit/dim/power.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// watt
typedef unit<power, si> watt;

template <>
struct info<watt>
{
	typedef meta::string<'w','a','t','t'> name;
	typedef meta::string<'W'> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

