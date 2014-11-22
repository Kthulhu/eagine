/**
 *  @file eagine/unit/si/electric_tension.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRIC_TENSION_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRIC_TENSION_1308281038_HPP

#include <eagine/unit/dim/electric_tension.hpp>
#include <eagine/unit/si/common.hpp>

namespace eagine {
namespace unit {

// volt
typedef unit<electric_tension, si> volt;

template <>
struct info<volt>
{
	typedef meta::string<'v','o','l','t'> name;
	typedef meta::string<'V'> symbol;
};

} // namespace unit
} // namespace eagine

#endif //include guard

