/**
 *  @file eagine/unit/dim/electric_tension.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ELECTRIC_TENSION_1308281038_HPP
#define EAGINE_UNIT_DIM_ELECTRIC_TENSION_1308281038_HPP

#include <eagine/unit/dim/power.hpp>

namespace EAGine {
namespace unit {

typedef decltype(power()/electric_current()) electric_tension;

template <>
struct info<electric_tension>
{
	typedef meta::string<
		'e','l','e','c','t','r','i','c',' ',
		't','e','n','s','i','o','n' 
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

