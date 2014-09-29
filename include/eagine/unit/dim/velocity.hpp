/**
 *  @file eagine/unit/dim/velocity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_VELOCITY_1308281038_HPP
#define EAGINE_UNIT_DIM_VELOCITY_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace EAGine {
namespace unit {

typedef decltype(length()/time()) velocity;

template <>
struct info<velocity>
{
	typedef meta::string<'v','e','l','o','c','i','t','y'> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

