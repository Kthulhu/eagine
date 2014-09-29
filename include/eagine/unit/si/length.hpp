/**
 *  @file eagine/unit/si/length.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_LENGTH_1308281038_HPP
#define EAGINE_UNIT_SI_LENGTH_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// meter
struct meter : unit<length, meter> { };

template <>
struct unit_info<meter>
{
	typedef meta::string<'m','e','t','e','r'> name;
	typedef meta::string<'m'> symbol;
};

} // namespace base

// si::base_unit<length>
template <>
struct si::base_unit<base::length> : base::meter { };

// meter
typedef unit<length, si> meter;

// derived
typedef make_scaled_unit<
	base::scaled_unit<scales::milli, base::meter>,
	si
>::type millimeter;

typedef make_scaled_unit<
	base::scaled_unit<scales::kilo, base::meter>,
	si
>::type kilometer;

} // namespace unit
} // namespace EAGine

#endif //include guard

