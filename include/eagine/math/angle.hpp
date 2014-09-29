/**
 *  @file eagine/math/angle.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_ANGLE_1308281038_HPP
#define EAGINE_MATH_ANGLE_1308281038_HPP

#include <eagine/unit/quantity.hpp>
#include <eagine/unit/si/angle.hpp>
#include <cmath>

namespace EAGine {
namespace math {

template <typename T>
using angle = unit::quantity<unit::radian, T>;

template <typename T>
inline auto asin(T v) -> angle<decltype(::std::asin(v))>
{
	return {::std::asin(v)};
}

template <typename T>
inline auto acos(T v) -> angle<decltype(::std::acos(v))>
{
	return {::std::acos(v)};
}

template <typename T>
inline auto atan(T v) -> angle<decltype(::std::atan(v))>
{
	return {::std::atan(v)};
}

template <typename T>
inline auto atan2(T y, T x) -> angle<decltype(::std::atan2(y, x))>
{
	return {::std::atan2(y, x)};
}

template <typename T>
inline T sin(angle<T> v)
{
	return ::std::sin(v._v);
}

template <typename T>
inline T cos(angle<T> v)
{
	return ::std::cos(v._v);
}

template <typename T>
inline T tan(angle<T> v)
{
	return ::std::tan(v._v);
}

} // namespace math
} // namespace EAGine

#endif //include guard

