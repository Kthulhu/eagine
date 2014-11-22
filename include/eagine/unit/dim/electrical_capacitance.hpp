/**
 *  @file eagine/unit/dim/electrical_capacitance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ELECTRICAL_CAPACITANCE_1308281038_HPP
#define EAGINE_UNIT_DIM_ELECTRICAL_CAPACITANCE_1308281038_HPP

#include <eagine/unit/dim/electric_tension.hpp>

namespace eagine {
namespace unit {

typedef decltype(electric_charge()/electric_tension()) electrical_capacitance;

template <>
struct info<electrical_capacitance>
{
	typedef meta::string<
		'e','l','e','c','t','r','i','c','a','l',' ',
		'c','a','p','a','c','i','t','a','n','c','e'
	> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

