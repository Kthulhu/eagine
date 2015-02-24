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

template <typename T, unsigned N>
struct vector;

template <typename T, unsigned N>
struct tvec;

template <typename Vector>
class vector_data_ref;

template <typename T, unsigned N>
static
vector_data_ref<vector<T, N>> data(const vector<T, N>&)
noexcept;

template <typename T, unsigned R, unsigned C, bool RowMajor>
struct matrix;

template <typename T, unsigned R, unsigned C, bool RowMajor>
struct tmat;

template <typename Matrix>
class matrix_data_ref;

template <typename T, unsigned R, unsigned C, bool RM>
static
matrix_data_ref<matrix<T, R, C, RM>> data(const matrix<T, R, C, RM>&)
noexcept;

} // namespace math
} // namespace eagine

#endif //include guard

