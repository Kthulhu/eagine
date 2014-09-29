/**
 *  @file eagine/unit/dim/frequency.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_FREQUENCY_1308281038_HPP
#define EAGINE_UNIT_DIM_FREQUENCY_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace EAGine {
namespace unit {

typedef decltype(number_of_cycles()/time()) frequency;

template <>
struct info<frequency>
{
	typedef meta::string<
		'f','r','e','q','u','e','n','c','y'
	> name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

