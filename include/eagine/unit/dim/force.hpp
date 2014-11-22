/**
 *  @file eagine/unit/dim/force.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_FORCE_1308281038_HPP
#define EAGINE_UNIT_DIM_FORCE_1308281038_HPP

#include <eagine/unit/dim/acceleration.hpp>

namespace eagine {
namespace unit {

typedef decltype(acceleration()*mass()) force;

template <>
struct info<force>
{
	typedef meta::string<'f','o','r','c','e'> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

