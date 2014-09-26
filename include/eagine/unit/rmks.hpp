/**
 *  @file eagine/unit/rmks.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_RMKS_1308281038_HPP
#define EAGINE_UNIT_RMKS_1308281038_HPP

#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/base_scaled_unit.hpp>

namespace EAGine {
namespace unit {

// radian/meter/kilogram/second unit system
struct rmks
{
	template <typename BaseDim>
	struct base_unit;
};

template <>
struct rmks::base_unit<base::angle>  : base::radian { };

template <>
struct rmks::base_unit<base::length> : base::meter { };

template <>
struct rmks::base_unit<base::mass>   : base::kilogram { };

template <>
struct rmks::base_unit<base::time>   : base::second { };

} // namespace unit
} // namespace EAGine

#endif //include guard

