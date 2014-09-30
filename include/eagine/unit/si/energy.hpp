/**
 *  @file eagine/unit/si/energy.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ENERGY_1308281038_HPP
#define EAGINE_UNIT_SI_ENERGY_1308281038_HPP

#include <eagine/unit/dim/energy.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// joule
typedef unit<energy, si> joule;

template <>
struct info<joule>
{
	typedef meta::string<'j','o','u','l','e'> name;
	typedef meta::string<'J'> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

