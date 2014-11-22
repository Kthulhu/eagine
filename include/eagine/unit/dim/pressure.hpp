/**
 *  @file eagine/unit/dim/pressure.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_PRESSURE_1308281038_HPP
#define EAGINE_UNIT_DIM_PRESSURE_1308281038_HPP

#include <eagine/unit/dim/force.hpp>
#include <eagine/unit/dim/area.hpp>

namespace eagine {
namespace unit {

typedef decltype(force()/area()) pressure;

template <>
struct info<pressure>
{
	typedef meta::string<'p','r','e','s','s','u','r','e'> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

