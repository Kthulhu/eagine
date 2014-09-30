/**
 *  @file eagine/unit/si/frequency.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_FREQUENCY_1308281038_HPP
#define EAGINE_UNIT_SI_FREQUENCY_1308281038_HPP

#include <eagine/unit/dim/frequency.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// hertz
typedef unit<frequency, si> hertz;

template <>
struct info<hertz>
{
	typedef meta::string<'h','e','r','t','z'> name;
	typedef meta::string<'H','z'> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

