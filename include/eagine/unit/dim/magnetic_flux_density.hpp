/**
 *  @file eagine/unit/dim/magnetic_flux_density.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_MAGNETIC_FLUX_DENSITY_1308281038_HPP
#define EAGINE_UNIT_DIM_MAGNETIC_FLUX_DENSITY_1308281038_HPP

#include <eagine/unit/dim/magnetic_flux.hpp>
#include <eagine/unit/dim/area.hpp>

namespace EAGine {
namespace unit {

typedef decltype(magnetic_flux()/area()) magnetic_flux_density;

template <>
struct info<magnetic_flux_density>
{
	typedef meta::string<
		'm','a','g','n','e','t','i','c',' ',
		'f','l','u','x',' ',
		'd','e','n','s','i','t','y'
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

