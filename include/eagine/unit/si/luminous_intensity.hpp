/**
 *  @file eagine/unit/si/luminous_intensity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_LUMINOUS_INTENSITY_1308281038_HPP
#define EAGINE_UNIT_SI_LUMINOUS_INTENSITY_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// candela
struct candela : unit<luminous_intensity, candela> { };

template <>
struct unit_info<candela>
{
	typedef meta::string<'c','a','n','d','e','l','a'> name;
	typedef meta::string<'c','d'> symbol;
};

} // namespace base

// si::base_unit<luminous_intensity>
template <>
struct si::base_unit<base::luminous_intensity> : base::candela { };

typedef unit<luminous_intensity, si> candela;

} // namespace unit
} // namespace EAGine

#endif //include guard

