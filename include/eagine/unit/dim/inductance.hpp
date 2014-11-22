/**
 *  @file eagine/unit/dim/inductance.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_INDUCTANCE_1308281038_HPP
#define EAGINE_UNIT_DIM_INDUCTANCE_1308281038_HPP

#include <eagine/unit/dim/magnetic_flux.hpp>

namespace eagine {
namespace unit {

typedef decltype(magnetic_flux()/electric_current()) inductance;

template <>
struct info<inductance>
{
	typedef meta::string<
		'i','n','d','u','c','t','a','n','c','e'

	> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

