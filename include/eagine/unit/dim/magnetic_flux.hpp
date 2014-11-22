/**
 *  @file eagine/unit/dim/magnetic_flux.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_MAGNETIC_FLUX_1308281038_HPP
#define EAGINE_UNIT_DIM_MAGNETIC_FLUX_1308281038_HPP

#include <eagine/unit/dim/energy.hpp>

namespace eagine {
namespace unit {

typedef decltype(energy()/electric_current()) magnetic_flux;

template <>
struct info<magnetic_flux>
{
	typedef meta::string<
		'm','a','g','n','e','t','i','c',' ','f','l','u','x'
	> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

