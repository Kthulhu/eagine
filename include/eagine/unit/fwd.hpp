/**
 *  @file eagine/unit/fwd.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_FWD_1308281038_HPP
#define EAGINE_UNIT_FWD_1308281038_HPP

namespace EAGine {
namespace unit {

template <typename Dims, typename System>
struct unit;

template <typename Dims, typename Scales, typename System>
struct scaled_unit;

template <typename U1, typename U2>
struct add_result;

template <typename U1, typename U2>
struct sub_result;

template <typename U1, typename U2>
struct mul_result;

template <typename U1, typename U2>
struct div_result;

} // namespace unit
} // namespace EAGine

#endif //include guard

