/**
 *  @file eagine/unit/dim/mass_density.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_MASS_DENSITY_1308281038_HPP
#define EAGINE_UNIT_DIM_MASS_DENSITY_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace EAGine {
namespace unit {

typedef decltype(mass()/volume()) mass_density;

template <>
struct info<mass_density>
{
	typedef meta::string<
		'm','a','s','s',' ','d','e','n','s','i','t','y'
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

