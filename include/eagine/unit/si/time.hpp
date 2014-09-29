/**
 *  @file eagine/unit/si/time.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_TIME_1308281038_HPP
#define EAGINE_UNIT_SI_TIME_1308281038_HPP

#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {
namespace base {

// second
struct second : unit<time, second> { };

template <>
struct unit_info<second>
{
	typedef meta::string<'s','e','c','o','n','d'> name;
	typedef meta::string<'s'> symbol;
};

// minute
typedef scaled_unit<scales::rational<60, 1>, second> minute;

template <>
struct unit_info<minute>
{
	typedef meta::string<'m','i','n','u','t','e'> name;
	typedef meta::string<'m','i','n'> symbol;
};

// hour
typedef scaled_unit<scales::rational<3600, 1>, second> hour;

template <>
struct unit_info<hour>
{
	typedef meta::string<'h','o','u','r'> name;
	typedef meta::string<'h','r'> symbol;
};

// day
typedef scaled_unit<scales::rational<86400, 1>, second> day;

template <>
struct unit_info<day>
{
	typedef meta::string<'d','a','y'> name;
	typedef meta::string<'D'> symbol;
};

} // namespace base

// si::base_unit<time>
template <>
struct si::base_unit<base::time> : base::second { };

// second
typedef unit<time, si> second;

// derived
typedef make_scaled_unit<base::minute, si>::type minute;
typedef make_scaled_unit<base::hour, si>::type hour;
typedef make_scaled_unit<base::day, si>::type day;

} // namespace unit
} // namespace EAGine

#endif //include guard

