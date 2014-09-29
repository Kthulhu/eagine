/**
 *  @file eagine/unit/si/temperature.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_TEMPERATURE_1308281038_HPP
#define EAGINE_UNIT_SI_TEMPERATURE_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

struct kelvin : unit<temperature, kelvin> { };

template <>
struct unit_info<kelvin>
{
	typedef meta::string<'k','e','l','v','i','n'> name;
	typedef meta::string<'K'> symbol;
};

} // namespace base

// si::base_unit<temperature>
template <>
struct si::base_unit<base::temperature> : base::kelvin { };

// kelvin
typedef unit<temperature, si> kelvin;

} // namespace unit
} // namespace EAGine

#endif //include guard

