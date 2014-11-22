/**
 *  @file eagine/unit/si/radioactivity.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_RADIOACTIVITY_1308281038_HPP
#define EAGINE_UNIT_SI_RADIOACTIVITY_1308281038_HPP

#include <eagine/unit/dim/radioactivity.hpp>
#include <eagine/unit/si/common.hpp>

namespace eagine {
namespace unit {

// becquerel
typedef unit<radioactivity, si> becquerel;

template <>
struct info<becquerel>
{
	typedef meta::string<'b','e','c','q','u','e','r','e','l'> name;
	typedef meta::string<'B','q'> symbol;
};

} // namespace unit
} // namespace eagine

#endif //include guard

