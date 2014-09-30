/**
 *  @file eagine/unit/si/force.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_SI_FORCE_1308281038_HPP
#define EAGINE_UNIT_SI_FORCE_1308281038_HPP

#include <eagine/unit/dim/force.hpp>
#include <eagine/unit/si/common.hpp>

namespace EAGine {
namespace unit {

// newton 
typedef unit<force, si> newton;

template <>
struct info<newton>
{
	typedef meta::string<'n','e','w','t','o','n'> name;
	typedef meta::string<'N'> symbol;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

