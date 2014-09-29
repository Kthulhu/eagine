/**
 *  @file eagine/unit/si/mass.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_MASS_1308281038_HPP
#define EAGINE_UNIT_SI_MASS_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// gram
struct gram : unit<mass, gram> { };

template <>
struct unit_info<gram>
{
	typedef meta::string<'g','r','a','m'> name;
	typedef meta::string<'g'> symbol;
};

} // namespace base

// si::base_unit<mass>
template <>
struct si::base_unit<base::mass>
 : base::scaled_unit<scales::kilo, base::gram>
{ };

// kilogram
typedef unit<mass, si> kilogram;

// derived
typedef make_scaled_unit<
	base::scaled_unit<scales::one, base::gram>,
	si
>::type gram;

typedef make_scaled_unit<
	base::scaled_unit<scales::milli, base::gram>,
	si
>::type milligram;

} // namespace unit
} // namespace EAGine

#endif //include guard

