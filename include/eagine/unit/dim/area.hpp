/**
 *  @file eagine/unit/dim/area.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_AREA_1308281038_HPP
#define EAGINE_UNIT_DIM_AREA_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace EAGine {
namespace unit {

typedef decltype(length()*length()) area;

template <>
struct info<area>
{
	typedef meta::string<'a','r','e','a'> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

