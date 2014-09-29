/**
 *  @file eagine/unit/si/electric_current.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_ELECTRIC_CURRENT_1308281038_HPP
#define EAGINE_UNIT_SI_ELECTRIC_CURRENT_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// ampere
struct ampere  : unit<electric_current, ampere> { };

template <>
struct unit_info<ampere>
{
	typedef meta::string<'a','m','p','e','r','e'> name;
	typedef meta::string<'A'> symbol;
};

} // namespace base

// si::base_unit<electric_current>
template <>
struct si::base_unit<base::electric_current> : base::ampere { };

// ampere
typedef unit<electric_current, si> ampere;

} // namespace unit
} // namespace EAGine

#endif //include guard

