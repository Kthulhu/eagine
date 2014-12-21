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

namespace eagine {
namespace math {

// reordered_matrix_constructor
template <typename MC>
struct reordered_matrix_constructor
{
	MC _mc;

	constexpr inline
	operator typename reordered_matrix<
		typename constructed_matrix<MC>::type
	>::type (void) const
	{
		typedef typename constructed_matrix<MC>::type M;
		return reorder(M(_mc));
	}
};

// is_matrix_constructor<reordered_constructor>
template <typename MC>
struct is_matrix_constructor<reordered_matrix_constructor<MC>>
 : meta::true_type
{ };

// constructed_matrix<reordered_constructor>
template <typename MC>
struct constructed_matrix<reordered_matrix_constructor<MC>>
 : reordered_matrix<typename constructed_matrix<MC>::type>
{ };

// reordered_matrix_constructor * T
template <typename MC, typename T>
static constexpr inline
typename meta::enable_if<
	!is_matrix_constructor<T>::value,
	reordered_matrix_constructor<MC>
>::type
operator * (const reordered_matrix_constructor<MC>& rmc, T t)
{
	return {rmc._mc*t};
}

// reordered_matrix_constructor + reordered_matrix_constructor
template <typename MC>
static constexpr inline
reordered_matrix_constructor<MC>
operator + (
	const reordered_matrix_constructor<MC>& rmc1,
	const reordered_matrix_constructor<MC>& rmc2
)
{
	return {rmc1._mc + rmc2._mc};
}

// reorder_mat_ctr(matrix_constructor)
template <typename MC>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC>::value,
	reordered_matrix_constructor<MC>
>::type reorder_mat_ctr(const MC& mc)
{
	return {mc};
}

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
	typedef typename vect::data<T, 3>::type _dT;
	_dT _d;

	constexpr translation(_dT d)
	 : _d{d}
	{ }

	constexpr translation(T dx, T dy, T dz)
	 : _d{dx, dy, dz}
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return matrix<T,4,4, true>{{
			{ T(1), T(0), T(0),_d[0]},
			{ T(0), T(1), T(0),_d[1]},
			{ T(0), T(0), T(1),_d[2]},
			{ T(0), T(0), T(0), T(1)}
		}};
	}
};

// translation matrix 4x4 column-major
template <typename T>
struct translation<matrix<T,4,4,false>>
{
	typedef typename vect::data<T, 3>::type _dT;
	_dT _d;

	constexpr translation(T dx, T dy, T dz)
	 : _d{dx, dy, dz}
	{ }

	constexpr inline
	operator matrix<T,4,4,false> (void) const
	{
		return matrix<T,4,4,false>{{
			{ T(1), T(0), T(0), T(0)},
			{ T(0), T(1), T(0), T(0)},
			{ T(0), T(0), T(1), T(0)},
			{_d[0],_d[1],_d[2], T(1)}
		}};
	}
};

// translation * T
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
translation<matrix<T,R,C,RM>>
operator * (const translation<matrix<T,R,C,RM>>& c, T t)
{
	return {c._d*vect::fill<T,R-1>::apply(t)};
}

// translation + translation
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
translation<matrix<T,R,C,RM>>
operator + (
	const translation<matrix<T,R,C,RM>>& c1,
	const translation<matrix<T,R,C,RM>>& c2
)
{
	return {c1._d+c2._d};
}

// reorder_mat_ctr(translation)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
translation<matrix<T,R,C,!RM>>
reorder_mat_ctr(const translation<matrix<T,R,C,RM>>& t)
{
	return {t._d};
}

// translation_I
template <typename X, unsigned I>
struct translation_I;

// translation along the I-th axis matrix 4x4 row-major
template <typename T, unsigned I>
struct translation_I<matrix<T,4,4, true>, I>
{
	T _d;

	constexpr inline T v(unsigned i) const
	{
		return (i == I)?_d:T(0);
	}

	constexpr translation_I(T d)
	 : _d(d)
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return matrix<T,4,4, true>{{
			{T(1),T(0),T(0),v(0)},
			{T(0),T(1),T(0),v(1)},
			{T(0),T(0),T(1),v(2)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// translation along the I-th axis matrix 4x4 column-major
template <typename T, unsigned I>
struct translation_I<matrix<T,4,4,false>, I>
{
	T _d;

	constexpr inline T v(unsigned i) const
	{
		return (i == I)?_d:T(0);
	}

	constexpr translation_I(T d)
	 : _d(d)
	{ }

	constexpr inline
	operator matrix<T,4,4,false> (void) const
	{
		return matrix<T,4,4,false>{{
			{T(1),T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{v(0),v(1),v(2),T(1)}
		}};
	}
};

// translation_I * T
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,RM>, I>
operator * (const translation_I<matrix<T,R,C,RM>, I>& c, T t)
{
	return {c._d*t};
}

// translation_I + translation_I
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,RM>, I>
operator + (
	const translation_I<matrix<T,R,C,RM>, I>& c1,
	const translation_I<matrix<T,R,C,RM>, I>& c2
)
{
	return {c1._d+c2._d};
}

// reorder_mat_ctr(translation_I)
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,!RM>, I>
reorder_mat_ctr(const translation_I<matrix<T,R,C,RM>, I>& t)
{
	return {t._d};
}

// translation x
template <typename M>
using translation_x = translation_I<M, 0>;

// is_matrix_constructor<translation_x>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<translation_x<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// translation y
template <typename M>
using translation_y = translation_I<M, 1>;

// is_matrix_constructor<translation_y>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<translation_y<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// translation z
template <typename M>
using translation_z = translation_I<M, 2>;

// is_matrix_constructor<translation_z>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<translation_z<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation_I
template <typename X, unsigned I>
struct rotation_I;

// is_matrix_constructor<rotation_x>
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
struct is_matrix_constructor<rotation_I<matrix<T,R,C,RM>, I>>
 : meta::true_type
{ };

// rotation around I-th-axis matrix 4x4
template <typename T, bool RM, unsigned I>
struct rotation_I<matrix<T,4,4, RM>, I>
{
	T _a;

	constexpr rotation_I(angle<T> a)
	 : _a(value(a))
	{ }

	typedef meta::integral_constant<unsigned, 0> _x;
	typedef meta::integral_constant<unsigned, 1> _y;
	typedef meta::integral_constant<unsigned, 2> _z;

	constexpr inline
	matrix<T,4,4, RM> _make(T cx, T sx, _x) const
	{
		return matrix<T,4,4, RM>{{
			{T(1),T(0),T(0),T(0)},
			{T(0),  cx, -sx,T(0)},
			{T(0),  sx,  cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4, RM> _make(T cx, T sx, _y) const
	{
		return matrix<T,4,4, RM>{{
			{  cx,T(0),  sx,T(0)},
			{T(0),T(1),T(0),T(0)},
			{ -sx,T(0),  cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4, RM> _make(T cx, T sx, _z) const
	{
		return matrix<T,4,4, RM>{{
			{  cx, -sx,T(0),T(0)},
			{  sx,  cx,T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4, RM> (void) const
	{
		using std::cos;
		using std::sin;
		typedef meta::integral_constant<unsigned, I> _axis;
		return _make(cos(_a), sin(_a)*(RM?1:-1), _axis());
	}
};

// reorder_mat_ctr(rotation_I)
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
rotation_I<matrix<T,R,C,!RM>, I>
reorder_mat_ctr(const rotation_I<matrix<T,R,C,RM>, I>& r)
{
	return {r._a};
}

// rotation x
template <typename M>
using rotation_x = rotation_I<M, 0>;

// is_matrix_constructor<rotation_x>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_x<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation y
template <typename M>
using rotation_y = rotation_I<M, 1>;

// is_matrix_constructor<rotation_y>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_y<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation z
template <typename M>
using rotation_z = rotation_I<M, 2>;

// is_matrix_constructor<rotation_z>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_z<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// scale
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
	typedef typename vect::data<T, 3>::type _dT;
	_dT _s;

	constexpr scale(_dT s)
	 : _s{s}
	{ }

	constexpr scale(T sx, T sy, T sz)
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return matrix<T,4,4, RM>{{
			{_s[0], T(0), T(0), T(0)},
			{ T(0),_s[1], T(0), T(0)},
			{ T(0), T(0),_s[2], T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}
};

// scale * T
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
scale<matrix<T,R,C,RM>>
operator * (const scale<matrix<T,R,C,RM>>& c, T t)
{
	return {c._s*vect::fill<T,(R>C?R:C)-1>::apply(t)};
}

// scale + scale
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
scale<matrix<T,R,C,RM>>
operator + (
	const scale<matrix<T,R,C,RM>>& c1,
	const scale<matrix<T,R,C,RM>>& c2
)
{
	return {c1._s+c2._s};
}

// reorder_mat_ctr(scale)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
scale<matrix<T,R,C,!RM>>
reorder_mat_ctr(const scale<matrix<T,R,C,RM>>& s)
{
	return {s._s};
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
		return matrix<T,4,4, RM>{{
			{  _s,T(0),T(0),T(0)},
			{T(0),  _s,T(0),T(0)},
			{T(0),T(0),  _s,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// uniform_scale * T
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
uniform_scale<matrix<T,R,C,RM>>
operator * (const uniform_scale<matrix<T,R,C,RM>>& c, T t)
{
	return {c._s*t};
}

// uniform_scale * uniform_scale 
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
uniform_scale<matrix<T,R,C,RM>>
operator + (
	const uniform_scale<matrix<T,R,C,RM>>& c1,
	const uniform_scale<matrix<T,R,C,RM>>& c2
)
{
	return {c1._s+c2._s};
}

// reorder_mat_ctr(uniform_scale)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
uniform_scale<matrix<T,R,C,!RM>>
reorder_mat_ctr(const uniform_scale<matrix<T,R,C,RM>>& us)
{
	return {us._s};
}

// reflection_I
template <typename X, unsigned I>
struct reflection_I;

// is_matrix_constructor<reflection_I>
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
struct is_matrix_constructor<reflection_I<matrix<T,R,C,RM>, I>>
 : meta::true_type
{ };

// reflection_I matrix 4x4
template <typename T, bool RM, unsigned I>
struct reflection_I<matrix<T,4,4,RM>, I>
{
	T _r;

	constexpr reflection_I(bool r = true)
	 : _r(r?-1:1)
	{ }

	constexpr inline
	T v(unsigned i) const
	{
		return (I == i)?_r:T(1);
	}

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return matrix<T,4,4, RM>{{
			{v(0),T(0),T(0),T(0)},
			{T(0),v(1),T(0),T(0)},
			{T(0),T(0),v(2),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reflection_I * T
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
reflection_I<matrix<T,R,C,RM>, I>
operator * (const reflection_I<matrix<T,R,C,RM>, I>& c, T t)
{
	return {c._r*t};
}

// reflection_I + reflection_I
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
reflection_I<matrix<T,R,C,RM>, I>
operator + (
	const reflection_I<matrix<T,R,C,RM>, I>& c1,
	const reflection_I<matrix<T,R,C,RM>, I>& c2
)
{
	return {c1._r+c2._r};
}

// reorder_mat_ctr(reflection_I)
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static constexpr inline
reflection_I<matrix<T,R,C,!RM>, I>
reorder_mat_ctr(const reflection_I<matrix<T,R,C,RM>, I>& r)
{
	return {r._r};
}

// reflection x
template <typename M>
using reflection_x = reflection_I<M, 0>;

// is_matrix_constructor<reflection_x>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_x<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// reflection y
template <typename M>
using reflection_y = reflection_I<M, 1>;

// is_matrix_constructor<reflection_y>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_y<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// reflection z
template <typename M>
using reflection_z = reflection_I<M, 2>;

// is_matrix_constructor<reflection_z>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_z<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// shear
template <typename X>
struct shear;

// is_matrix_constructor<shear>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<shear<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// shear matrix 4x4 row-major
template <typename T>
struct shear<matrix<T,4,4, true>>
{
	typedef typename vect::data<T, 3>::type _dT;
	_dT _s;

	constexpr shear(_dT s)
	 : _s{s}
	{ }

	constexpr shear(T sx, T sy, T sz)
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return matrix<T,4,4, true>{{
			{ T(1),_s[0],_s[0], T(0)},
			{_s[1], T(1),_s[1], T(0)},
			{_s[2],_s[2], T(1), T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}
};

// shear matrix 4x4 column-major
template <typename T>
struct shear<matrix<T,4,4,false>>
{
	typedef typename vect::data<T, 3>::type _dT;
	_dT _s;

	constexpr shear(_dT s)
	 : _s{s}
	{ }

	constexpr shear(T sx, T sy, T sz)
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	operator matrix<T,4,4,false> (void) const
	{
		return matrix<T,4,4,false>{{
			{ T(1),_s[1],_s[2], T(0)},
			{_s[0], T(1),_s[2], T(0)},
			{_s[0],_s[1], T(1), T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}
};

// shear * T
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
shear<matrix<T,R,C,RM>>
operator * (const shear<matrix<T,R,C,RM>>& c, T t)
{
	return {c._s*vect::fill<T, (R>C?R:C)-1>::apply(t)};
}

// shear * shear 
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
shear<matrix<T,R,C,RM>>
operator + (
	const shear<matrix<T,R,C,RM>>& c1,
	const shear<matrix<T,R,C,RM>>& c2
)
{
	return {c1._s+c2._s};
}

// reorder_mat_ctr(shear)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
shear<matrix<T,R,C,!RM>>
reorder_mat_ctr(const shear<matrix<T,R,C,RM>>& s)
{
	return {s._s};
}

// ortho
template <typename X>
struct ortho;

// is_matrix_constructor<ortho>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<ortho<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// ortho matrix 4x4
template <typename T, bool RM>
struct ortho<matrix<T,4,4,RM>>
{
	typedef typename vect::data<T, 6>::type _dT;
	_dT _s;

	constexpr ortho(const _dT& s)
	 : _s(s)
	{ }

	constexpr ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): _s{x_left, x_right, y_bottom, y_top, z_near, z_far}
	{ }

	constexpr inline T _x_left(void) const { return _s[0]; }
	constexpr inline T _x_right(void) const { return _s[1]; }
	constexpr inline T _y_bottom(void) const { return _s[2]; }
	constexpr inline T _y_top(void) const { return _s[3]; }
	constexpr inline T _z_near(void) const { return _s[4]; }
	constexpr inline T _z_far(void) const { return _s[5]; }

	constexpr inline T _m00(void) const
	{
		return T(2) / (_x_right() - _x_left());
	}

	constexpr inline T _m11(void) const
	{
		return T(2) / (_y_top() - _y_bottom());
	}

	constexpr inline T _m22(void) const
	{
		return -T(2) / (_z_far() - _z_near());
	}

	constexpr inline T _m30(void) const
	{
		return -(_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline T _m31(void) const
	{
		return -(_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline T _m32(void) const
	{
		return -(_z_far() + _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline
	matrix<T,4,4, true> _make(meta::true_type) const
	{
		return matrix<T,4,4, true>{{
			{_m00(),   T(0),   T(0), _m30()},
			{  T(0), _m11(),   T(0), _m31()},
			{  T(0),   T(0), _m22(), _m32()},
			{  T(0),   T(0),   T(0),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false> _make(meta::false_type) const
	{
		return matrix<T,4,4,false>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{  T(0),   T(0), _m22(),   T(0)},
			{_m30(), _m31(), _m32(),   T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4, RM> (void) const
	{
		return _make(meta::integral_constant<bool, RM>());
	}
};

// ortho * T
template <typename T, bool RM>
static constexpr inline
ortho<matrix<T,4,4,RM>>
operator * (const ortho<matrix<T,4,4,RM>>& c, T t)
{
	return {c._s * vect::fill<T,6>::apply(t)};
}

// ortho + ortho
template <typename T, bool RM>
static constexpr inline
ortho<matrix<T,4,4,RM>>
operator + (
	const ortho<matrix<T,4,4,RM>>& c1,
	const ortho<matrix<T,4,4,RM>>& c2
)
{
	return {c1._s + c2._s};
}

// reorder_mat_ctr(ortho)
template <typename T, bool RM>
static constexpr inline
ortho<matrix<T,4,4,!RM>>
reorder_mat_ctr(const ortho<matrix<T,4,4,RM>>& c)
{
	return {c._s};
}

// perspective
template <typename X>
struct perspective;

// is_matrix_constructor<perspective>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<perspective<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// perspective matrix 4x4 row-major
template <typename T, bool RM>
struct perspective<matrix<T,4,4,RM>>
{
	typedef typename vect::data<T, 6>::type _dT;
	_dT _s;

	constexpr perspective(const _dT& s)
	 : _s(s)
	{ }

	constexpr perspective(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): _s{x_left, x_right, y_bottom, y_top, z_near, z_far}
	{ }

	constexpr inline T _x_left(void) const { return _s[0]; }
	constexpr inline T _x_right(void) const { return _s[1]; }
	constexpr inline T _y_bottom(void) const { return _s[2]; }
	constexpr inline T _y_top(void) const { return _s[3]; }
	constexpr inline T _z_near(void) const { return _s[4]; }
	constexpr inline T _z_far(void) const { return _s[5]; }

	static inline
	perspective x(
		angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(xfov > angle<T>(0));

		T x_right = z_near * tan(xfov * T(0.5));
		T x_left = -x_right;

		T y_bottom = x_left / aspect;
		T y_top = x_right / aspect;

		return perspective(
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	static inline
	perspective y(
		angle<T> yfov,
		T aspect,
		T z_near,
		T z_far
	)
	{
		assert(aspect > T(0));
		assert(yfov > angle<T>(0));

		T y_top = z_near * tan(yfov * T(0.5));
		T y_bottom = -y_top;

		T x_left = y_bottom * aspect;
		T x_right = y_top * aspect;

		return perspective(
			x_left,
			x_right,
			y_bottom,
			y_top,
			z_near,
			z_far
		);
	}

	constexpr inline T _m00(void) const
	{
		return (T(2) * _z_near()) / (_x_right() - _x_left());
	}

	constexpr inline T _m11(void) const
	{
		return (T(2) * _z_near()) / (_y_top() - _y_bottom());
	}

	constexpr inline T _m22(void) const
	{
		return -(_z_far() + _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline T _m20(void) const
	{
		return (_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline T _m21(void) const
	{
		return (_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline T _m23(void) const
	{
		return -T(1);
	}

	constexpr inline T _m32(void) const
	{
		return -(T(2) * _z_far() * _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline
	matrix<T,4,4, true> _make(meta::true_type) const
	{
		return matrix<T,4,4, true>{{
			{_m00(),   T(0), _m20(),   T(0)},
			{  T(0), _m11(), _m21(),   T(0)},
			{  T(0),   T(0), _m22(), _m32()},
			{  T(0),   T(0), _m23(),   T(0)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false> _make(meta::false_type) const
	{
		return matrix<T,4,4,false>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{_m20(), _m21(), _m22(), _m23()},
			{  T(0),   T(0), _m32(),   T(0)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return _make(meta::integral_constant<bool, RM>());
	}
};

// perspective * T
template <typename T, bool RM>
static constexpr inline
perspective<matrix<T,4,4,RM>>
operator * (const perspective<matrix<T,4,4,RM>>& c, T t)
{
	return {c._s * vect::fill<T,6>::apply(t)};
}

// perspective + perspective
template <typename T, bool RM>
static constexpr inline
perspective<matrix<T,4,4,RM>>
operator + (
	const perspective<matrix<T,4,4,RM>>& c1,
	const perspective<matrix<T,4,4,RM>>& c2
)
{
	return {c1._s + c2._s};
}

// reorder_mat_ctr(perspective)
template <typename T, bool RM>
static constexpr inline
perspective<matrix<T,4,4,!RM>>
reorder_mat_ctr(const perspective<matrix<T,4,4,RM>>& c)
{
	return {c._s};
}

// screen_stretch
template <typename X>
struct screen_stretch;

// is_matrix_constructor<screen_stretch>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<screen_stretch<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// screen_stretch matrix 4x4
template <typename T, bool RM>
struct screen_stretch<matrix<T,4,4,RM>>
{
	typedef typename vect::data<T, 4>::type _dT;
	_dT _s;

	constexpr screen_stretch(const _dT& s)
	 : _s(s)
	{ }

	constexpr screen_stretch(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top
	): _s{x_left, x_right, y_bottom, y_top}
	{ }

	constexpr inline T _x_left(void) const { return _s[0]; }
	constexpr inline T _x_right(void) const { return _s[1]; }
	constexpr inline T _y_bottom(void) const { return _s[2]; }
	constexpr inline T _y_top(void) const { return _s[3]; }

	constexpr inline T _m00(void) const
	{
		return T(2) / (_x_right() - _x_left());
	}

	constexpr inline T _m11(void) const
	{
		return T(2) / (_y_top() - _y_bottom());
	}

	constexpr inline T _m30(void) const
	{
		return -(_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline T _m31(void) const
	{
		return -(_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline
	matrix<T,4,4, true> _make(meta::true_type) const
	{
		return matrix<T,4,4, true>{{
			{_m00(),   T(0),   T(0), _m30()},
			{  T(0), _m11(),   T(0), _m31()},
			{  T(0),   T(0),   T(1),   T(0)},
			{  T(0),   T(0),   T(0),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false> _make(meta::false_type) const
	{
		return matrix<T,4,4,false>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{  T(0),   T(0),   T(1),   T(0)},
			{_m30(), _m31(),   T(0),   T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return _make(meta::integral_constant<bool, RM>());
	}
};

// screen_stretch * T
template <typename T, bool RM>
static constexpr inline
screen_stretch<matrix<T,4,4,RM>>
operator * (const screen_stretch<matrix<T,4,4,RM>>& c, T t)
{
	return {c._s * vect::fill<T,4>::apply(t)};
}

// screen_stretch + screen_stretch
template <typename T, bool RM>
static constexpr inline
screen_stretch<matrix<T,4,4,RM>>
operator + (
	const screen_stretch<matrix<T,4,4,RM>>& c1,
	const screen_stretch<matrix<T,4,4,RM>>& c2
)
{
	return {c1._s * c2._s};
}

// reorder_mat_ctr(screen_stretch)
template <typename T, bool RM>
static constexpr inline
screen_stretch<matrix<T,4,4,!RM>>
reorder_mat_ctr(const screen_stretch<matrix<T,4,4,RM>>& c)
{
	return {c._s};
}

} // namespace math
} // namespace eagine

#endif //include guard

