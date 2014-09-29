/**
 *  @file eagine/unit/dimensionless.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DIMLESS_1308281038_HPP
#define EAGINE_UNIT_DIMLESS_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/unit/detail.hpp>

namespace EAGine {
namespace unit {

typedef bits::dimless dimensionless;

template <>
struct info<dimensionless>
{
	typedef meta::string<'d','i','m','e','n','s','i','o','n','l','e','s','s'>
		name;
};

} // namespace unit
} // namespace EAGine

#endif //include guard

