/**
 *  @file eagine/unit/dim/acceleration.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ACCELERATION_1308281038_HPP
#define EAGINE_UNIT_DIM_ACCELERATION_1308281038_HPP

#include <eagine/unit/dim/velocity.hpp>

namespace EAGine {
namespace unit {

typedef decltype(velocity()/time()) acceleration;

template <>
struct info<acceleration>
{
	typedef meta::string<
		'a','c','c','e','l','e','r','a','t','i','o','n'
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

