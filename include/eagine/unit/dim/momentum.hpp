/**
 *  @file eagine/unit/dim/momentum.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_MOMENTUM_1308281038_HPP
#define EAGINE_UNIT_DIM_MOMENTUM_1308281038_HPP

#include <eagine/unit/dim/velocity.hpp>

namespace EAGine {
namespace unit {

typedef decltype(velocity()*mass()) momentum;

template <>
struct info<momentum>
{
	typedef meta::string<'m','o','m','e','n','t','u','m'> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

