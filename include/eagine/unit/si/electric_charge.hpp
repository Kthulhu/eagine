/**
 *  @file eagine/unit/si/electric_charge.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRIC_CHARGE_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRIC_CHARGE_1308281038_HPP

#include <eagine/unit/dim/electric_charge.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// coulomb
typedef unit<electric_charge, si> coulomb;

template <>
struct info<coulomb>
{
	typedef meta::string<'c','o','u','l','o','m','b'> name;
	typedef meta::string<'C'> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

