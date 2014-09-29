/**
 *  @file eagine/unit/dim/energy.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ENERGY_1308281038_HPP
#define EAGINE_UNIT_DIM_ENERGY_1308281038_HPP

#include <eagine/unit/dim/force.hpp>

namespace EAGine {
namespace unit {

typedef decltype(force()*length()) energy;

template <>
struct info<energy>
{
	typedef meta::string<'e','n','e','r','g','y'> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

