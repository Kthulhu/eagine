/**
 *  @file eagine/unit/base_unit.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_BASE_UNIT_1308281038_HPP
#define EAGINE_UNIT_BASE_UNIT_1308281038_HPP

#include <eagine/unit/base_dim.hpp>

namespace EAGine {
namespace unit {
namespace base {

template <typename Dimension, typename Derived>
struct unit
{
	typedef Dimension dimension;
	typedef scales::one scale;
	typedef Derived type;
};

struct radian : unit<angle,  radian> { };
struct gram   : unit<mass,   gram> { };
struct meter  : unit<length, meter> { };
struct second : unit<time,   second> { };

template <typename Unit>
struct unit_info;

template <>
struct unit_info<radian>
{
	typedef meta::string<'r','a','d','i','a','n'> name;
	typedef meta::string<'r','a','d'> symbol;
};

template <>
struct unit_info<gram>
{
	typedef meta::string<'g','r','a','m'> name;
	typedef meta::string<'g'> symbol;
};

template <>
struct unit_info<meter>
{
	typedef meta::string<'m','e','t','e','r'> name;
	typedef meta::string<'m'> symbol;
};

template <>
struct unit_info<second>
{
	typedef meta::string<'s','e','c','o','n','d'> name;
	typedef meta::string<'s'> symbol;
};

} // namespace base
} // namespace unit
} // namespace EAGine

#endif //include guard

