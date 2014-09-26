/**
 *  @file eagine/unit/default.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_DEFAULT_1308281038_HPP
#define EAGINE_UNIT_DEFAULT_1308281038_HPP

#include <eagine/unit/dimension.hpp>
#include <eagine/unit/base_unit.hpp>
#include <eagine/unit/unit.hpp>
#include <eagine/unit/rmks.hpp>

namespace EAGine {
namespace unit {

typedef unit<angle> radian;
typedef unit<mass> gram;
typedef unit<length> meter;
typedef unit<time> second;

} // namespace unit
} // namespace EAGine

#endif //include guard

