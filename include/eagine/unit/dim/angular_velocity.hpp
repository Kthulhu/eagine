/**
 *  @file eagine/unit/dim/angular_velocity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ANGULAR_VELOCITY_1308281038_HPP
#define EAGINE_UNIT_DIM_ANGULAR_VELOCITY_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace eagine {
namespace unit {

typedef decltype(angle()/time()) angular_velocity;

template <>
struct info<angular_velocity>
{
	typedef meta::string<
		'a','n','g','u','l','a','r',' ',
		'v','e','l','o','c','i','t','y'
	> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

