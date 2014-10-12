/**
 *  @file eagine/math/matrix_ctrs.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_MATRIX_CTRS_1308281038_HPP
#define EAGINE_MATH_MATRIX_CTRS_1308281038_HPP

#include <eagine/math/matrix.hpp>

namespace EAGine {
namespace math {

// translation
template <typename X>
struct translation;

// is_matrix_constructor<translation>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<translation<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// translation matrix 4x4 row-major
template <typename T>
struct translation<matrix<T,4,4, true>>
{
	T _dx, _dy, _dz;

	constexpr translation(T dx, T dy, T dz)
	 : _dx(dx), _dy(dy), _dz(dz)
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return {{
			{T(1),T(0),T(0), _dx},
			{T(0),T(1),T(0), _dy},
			{T(0),T(0),T(1), _dz},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// translation matrix 4x4 column-major
template <typename T>
struct translation<matrix<T,4,4,false>>
{
	T _dx, _dy, _dz;

	constexpr translation(T dx, T dy, T dz)
	 : _dx(dx), _dy(dy), _dz(dz)
	{ }

	constexpr inline
	operator matrix<T,4,4,false> (void) const
	{
		return {{
			{T(1),T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{ _dx, _dy, _dz,T(1)}
		}};
	}
};

// reorder(translation)
template <typename T, bool RM>
static constexpr inline
translation<matrix<T,4,4,!RM>>
reorder(const translation<matrix<T,4,4,RM>>& t)
{
	return {t._dx, t._dy, t._dz};
}

// _scale
template <typename X>
struct scale;

// is_matrix_constructor<scale>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<scale<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// scale matrix 4x4 row-major
template <typename T, bool RM>
struct scale<matrix<T,4,4,RM>>
{
	T _sx, _sy, _sz;

	constexpr scale(T sx, T sy, T sz)
	 : _sx(sx), _sy(sy), _sz(sz)
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return {{
			{ _sx,T(0),T(0),T(0)},
			{T(0), _sy,T(0),T(0)},
			{T(0),T(0), _sz,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder(scale)
template <typename T, bool RM>
static constexpr inline
scale<matrix<T,4,4,!RM>>
reorder(const scale<matrix<T,4,4,RM>>& s)
{
	return {s._sx, s._sy, s._sz};
}

// uniform_scale
template <typename X>
struct uniform_scale;

// is_matrix_constructor<uniform_scale>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<uniform_scale<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// uniform_scale matrix 4x4 row-major
template <typename T, bool RM>
struct uniform_scale<matrix<T,4,4,RM>>
{
	T _s;

	constexpr uniform_scale(T s)
	 : _s(s)
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return {{
			{  _s,T(0),T(0),T(0)},
			{T(0),  _s,T(0),T(0)},
			{T(0),T(0),  _s,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder(uniform_scale)
template <typename T, bool RM>
static constexpr inline
uniform_scale<matrix<T,4,4,!RM>>
reorder(const uniform_scale<matrix<T,4,4,RM>>& us)
{
	return {us._s};
}

} // namespace math
} // namespace EAGine

#endif //include guard

