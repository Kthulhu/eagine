/**
 *  @file eagine/unit/dim/electrical_resistance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ELECTRICAL_RESISTANCE_1308281038_HPP
#define EAGINE_UNIT_DIM_ELECTRICAL_RESISTANCE_1308281038_HPP

#include <eagine/unit/dim/electric_tension.hpp>

namespace EAGine {
namespace unit {

typedef decltype(electric_tension()/electric_current()) electrical_resistance;

template <>
struct info<electrical_resistance>
{
	typedef meta::string<
		'e','l','e','c','t','r','i','c','a','l',' ',
		'r','e','s','i','s','t','a','n','c','e'
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

