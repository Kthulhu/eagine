/**
 *  @file eagine/unit/si/electrical_resistance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRICAL_RESISTANCE_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRICAL_RESISTANCE_1308281038_HPP

#include <eagine/unit/dim/electrical_resistance.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// ohm
typedef unit<electrical_resistance, si> ohm;

template <>
struct info<ohm>
{
	typedef meta::string<'o','h','m'> name;
	typedef meta::string<char(0xCE),char(0xA9)> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

