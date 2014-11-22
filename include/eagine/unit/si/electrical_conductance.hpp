/**
 *  @file eagine/unit/si/electrical_conductance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRICAL_CONDUCTANCE_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRICAL_CONDUCTANCE_1308281038_HPP

#include <eagine/unit/dim/electrical_conductance.hpp>
#include <eagine/unit/si/common.hpp>

namespace eagine {
namespace unit {

// siemens
typedef unit<electrical_conductance, si> siemens;

template <>
struct info<siemens>
{
	typedef meta::string<'s','i','e','m','e','n','s'> name;
	typedef meta::string<'S'> symbol;
};

} // namespace unit
} // namespace eagine

#endif //include guard

