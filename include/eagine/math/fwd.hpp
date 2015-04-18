/**
 *  @file eagine/math/fwd.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_FWD_1412201321_HPP
#define EAGINE_MATH_FWD_1412201321_HPP

#include <eagine/unit/fwd.hpp>

namespace eagine {
namespace math {

template <typename T, unsigned N, bool V = true>
struct vector;

template <typename T, unsigned N, bool V = true>
struct tvec;

template <typename V, unsigned ... I>
struct has_swizzle;

template <typename Composite>
class composite_data_ref;

template <typename T, unsigned N, bool V = true>
static
composite_data_ref<vector<T, N, V>> data(const vector<T, N, V>&)
noexcept;

template <typename T, unsigned R, unsigned C, bool RowMajor, bool V = true>
struct matrix;

template <typename T, unsigned R, unsigned C, bool RowMajor, bool V = true>
struct tmat;

template <typename T, unsigned R, unsigned C, bool RM, bool V>
static
composite_data_ref<matrix<T, R, C, RM, V>> data(const matrix<T, R, C, RM, V>&)
noexcept;

} // namespace math
} // namespace eagine

#endif //include guard

