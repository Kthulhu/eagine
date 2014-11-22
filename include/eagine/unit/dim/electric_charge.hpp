/**
 *  @file eagine/unit/dim/electric_charge.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIM_ELECTRIC_CHARGE_1308281038_HPP
#define EAGINE_UNIT_DIM_ELECTRIC_CHARGE_1308281038_HPP

#include <eagine/unit/dimension.hpp>

namespace eagine {
namespace unit {

typedef decltype(electric_current()*time()) electric_charge;

template <>
struct info<electric_charge>
{
	typedef meta::string<
		'e','l','e','c','t','r','i','c',' ',
		'c','h','a','r','g','e' 
	> name;
};

} // namespace unit
} // namespace eagine

#endif //include guard

