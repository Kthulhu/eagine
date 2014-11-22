/**
 *  @file eagine/unit/si/electrical_capacitance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRICAL_CAPACITANCE_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRICAL_CAPACITANCE_1308281038_HPP

#include <eagine/unit/dim/electrical_capacitance.hpp>
#include <eagine/unit/si/common.hpp>

namespace eagine {
namespace unit {

// farad
typedef unit<electrical_capacitance, si> farad;

template <>
struct info<farad>
{
	typedef meta::string<'f','a','r','a','d'> name;
	typedef meta::string<'F'> symbol;
};

} // namespace unit
} // namespace eagine

#endif //include guard

