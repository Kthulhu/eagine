/**
 *  @file eagine/unit/fwd.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_FWD_1308281038_HPP
#define EAGINE_UNIT_FWD_1308281038_HPP

namespace EAGine {
namespace unit {
namespace bits {

template <typename Head, typename Tail>
struct dims;

template <typename Dims1, typename Dims2>
struct dim_add;

template <typename Dims1, typename Dims2>
struct dim_sub;

} // namespace bits

namespace base {

template <typename Derived>
struct dimension;

template <typename Dimension, typename Derived>
struct unit;

template <typename Scale, typename Unit>
struct scaled_unit;

template <typename Dimension>
struct dim_num;

} // base

struct si;

template <typename System>
struct system_id;

template <typename Unit>
struct info;

template <typename Dims, typename System = si>
struct unit;

template <typename Dims, typename Scales, typename System>
struct scaled_unit;

template <typename UnitFrom, typename UnitTo>
struct value_conv;

template <typename U1>
struct lit_result;

template <typename U1, typename U2>
struct add_result;

template <typename U1, typename U2>
struct sub_result;

template <typename U1, typename U2>
struct mul_result;

template <typename U1, typename U2>
struct div_result;

template <typename Unit, typename T = double>
struct quantity;

} // namespace unit
} // namespace EAGine

#endif //include guard

