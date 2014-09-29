/**
 *  @file eagine/unit/dim/power.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_POWER_1308281038_HPP
#define EAGINE_UNIT_DIM_POWER_1308281038_HPP

#include <eagine/unit/dim/energy.hpp>

namespace EAGine {
namespace unit {

typedef decltype(energy()/time()) power;

template <>
struct info<power>
{
	typedef meta::string<'p','o','w','e','r'> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

