/**
 *  @file eagine/math/matrix_ctrs.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
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
	noexcept
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
noexcept
{
	return {rmc._mc*t};
}

// reordered_matrix_constructor + reordered_matrix_constructor
template <typename MC>
static constexpr inline
reordered_matrix_constructor<MC>
operator * (
	const reordered_matrix_constructor<MC>& rmc1,
	const reordered_matrix_constructor<MC>& rmc2
) noexcept
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
noexcept
{
	return {mc};
}

// translation
template <typename X>
struct translation;

// is_matrix_constructor<translation>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<translation<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// translation matrix 4x4 row-major
template <typename T, bool V>
struct translation<matrix<T,4,4, true,V>>
{
	typedef typename vect::data<T, 3, V>::type _dT;
	_dT _d;

	constexpr
	translation(_dT d)
	noexcept
	 : _d(d)
	{ }

	constexpr
	translation(T dx, T dy, T dz)
	noexcept
	 : _d{dx, dy, dz}
	{ }

	constexpr inline
	matrix<T,4,4, true,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{ T(1), T(0), T(0),_d[0]},
			{ T(0), T(1), T(0),_d[1]},
			{ T(0), T(0), T(1),_d[2]},
			{ T(0), T(0), T(0), T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4, true,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// translation matrix 4x4 column-major
template <typename T, bool V>
struct translation<matrix<T,4,4,false,V>>
{
	typedef typename vect::data<T, 3, V>::type _dT;
	_dT _d;

	constexpr
	translation(_dT d)
	noexcept
	 : _d(d)
	{ }

	constexpr
	translation(T dx, T dy, T dz)
	noexcept
	 : _d{dx, dy, dz}
	{ }

	constexpr inline
	matrix<T,4,4,false,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{ T(1), T(0), T(0), T(0)},
			{ T(0), T(1), T(0), T(0)},
			{ T(0), T(0), T(1), T(0)},
			{_d[0],_d[1],_d[2], T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,false,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// translation * T
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
translation<matrix<T,R,C,RM,V>>
operator * (const translation<matrix<T,R,C,RM,V>>& c, T t)
noexcept
{
	return {c._d*vect::fill<T,R-1,V>::apply(t)};
}

// translation + translation
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
translation<matrix<T,R,C,RM,V>>
operator * (
	const translation<matrix<T,R,C,RM,V>>& c1,
	const translation<matrix<T,R,C,RM,V>>& c2
) noexcept
{
	return {c1._d+c2._d};
}

// reorder_mat_ctr(translation)
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
translation<matrix<T,R,C,!RM,V>>
reorder_mat_ctr(const translation<matrix<T,R,C,RM,V>>& t)
noexcept
{
	return {t._d};
}

// translation_I
template <typename X, unsigned I>
struct translation_I;

// translation along the I-th axis matrix 4x4 row-major
template <typename T, bool V, unsigned I>
struct translation_I<matrix<T,4,4, true,V>, I>
{
	T _d;

	constexpr inline
	T v(unsigned i) const
	noexcept
	{
		return (i == I)?_d:T(0);
	}

	constexpr
	translation_I(T d)
	noexcept
	 : _d(d)
	{ }

	constexpr inline
	matrix<T,4,4, true,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{T(1),T(0),T(0),v(0)},
			{T(0),T(1),T(0),v(1)},
			{T(0),T(0),T(1),v(2)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4, true,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// translation along the I-th axis matrix 4x4 column-major
template <typename T, bool V, unsigned I>
struct translation_I<matrix<T,4,4,false,V>, I>
{
	T _d;

	constexpr inline
	T v(unsigned i) const
	noexcept
	{
		return (i == I)?_d:T(0);
	}

	constexpr
	translation_I(T d)
	noexcept
	 : _d(d)
	{ }

	constexpr inline
	matrix<T,4,4,false,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{T(1),T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{v(0),v(1),v(2),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,false,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// translation_I * T
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,RM,V>, I>
operator * (const translation_I<matrix<T,R,C,RM,V>, I>& c, T t)
noexcept
{
	return {c._d*t};
}

// translation_I * translation_I
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,RM,V>, I>
operator * (
	const translation_I<matrix<T,R,C,RM,V>, I>& c1,
	const translation_I<matrix<T,R,C,RM,V>, I>& c2
) noexcept
{
	return {c1._d+c2._d};
}

// reorder_mat_ctr(translation_I)
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
translation_I<matrix<T,R,C,!RM,V>, I>
reorder_mat_ctr(const translation_I<matrix<T,R,C,RM,V>, I>& t)
noexcept
{
	return {t._d};
}

// translation x
template <typename M>
using translation_x = translation_I<M, 0>;

// is_matrix_constructor<translation_x>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<translation_x<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// translation y
template <typename M>
using translation_y = translation_I<M, 1>;

// is_matrix_constructor<translation_y>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<translation_y<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// translation z
template <typename M>
using translation_z = translation_I<M, 2>;

// is_matrix_constructor<translation_z>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<translation_z<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// rotation_I
template <typename X, unsigned I>
struct rotation_I;

// is_matrix_constructor<rotation_I>
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
struct is_matrix_constructor<rotation_I<matrix<T,R,C,RM,V>, I>>
 : meta::true_type
{ };

// rotation around I-th-axis matrix 4x4
template <typename T, bool RM, bool V, unsigned I>
struct rotation_I<matrix<T,4,4,RM,V>, I>
{
	angle<T> _a;

	constexpr
	rotation_I(angle<T> a)
	noexcept
	 : _a(a)
	{ }

	typedef meta::unsigned_constant<0> _x;
	typedef meta::unsigned_constant<1> _y;
	typedef meta::unsigned_constant<2> _z;

	static constexpr inline
	matrix<T,4,4,RM,V> _make(T cx, T sx, _x)
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{T(1),T(0),T(0),T(0)},
			{T(0),  cx, -sx,T(0)},
			{T(0),  sx,  cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	static constexpr inline
	matrix<T,4,4,RM,V> _make(T cx, T sx, _y)
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{  cx,T(0),  sx,T(0)},
			{T(0),T(1),T(0),T(0)},
			{ -sx,T(0),  cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	static constexpr inline
	matrix<T,4,4,RM,V> _make(T cx, T sx, _z)
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{  cx, -sx,T(0),T(0)},
			{  sx,  cx,T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		typedef meta::unsigned_constant<I> _axis;
		return _make(cos(_a), sin(_a)*(RM?1:-1), _axis());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// rotation_I * rotation_I
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
rotation_I<matrix<T,R,C,RM,V>, I>
operator * (
	const rotation_I<matrix<T,R,C,RM,V>, I>& c1,
	const rotation_I<matrix<T,R,C,RM,V>, I>& c2
) noexcept
{
	return {c1._a+c2._a};
}

// reorder_mat_ctr(rotation_I)
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
rotation_I<matrix<T,R,C,!RM,V>, I>
reorder_mat_ctr(const rotation_I<matrix<T,R,C,RM,V>, I>& r)
noexcept
{
	return {r._a};
}

// rotation x
template <typename M>
using rotation_x = rotation_I<M, 0>;

// is_matrix_constructor<rotation_x>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<rotation_x<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// pitch
template <typename M>
using pitch = rotation_x<M>;

// rotation y
template <typename M>
using rotation_y = rotation_I<M, 1>;

// is_matrix_constructor<rotation_y>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<rotation_y<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// yaw
template <typename M>
using yaw = rotation_y<M>;

// rotation z
template <typename M>
using rotation_z = rotation_I<M, 2>;

// is_matrix_constructor<rotation_z>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<rotation_z<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// roll
template <typename M>
using roll = rotation_z<M>;

// rotation_a
template <typename X>
struct rotation_a;

// is_matrix_constructor<rotation_x>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<rotation_a<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// rotation around arbitrary axis matrix 4x4
template <typename T, bool RM, bool V>
struct rotation_a<matrix<T,4,4,RM,V>>
{
	typedef vector<T,4,V> _vT;

	vector<T,4,V> _v;
	angle<T> _a;

	constexpr
	rotation_a(const vector<T,4,V>& v, angle<T> a)
	noexcept
	 : _v(v)
	 , _a(a)
	{ }

	constexpr
	rotation_a(const vector<T,3,V>& v, angle<T> a)
	noexcept
	 : _v(_vT::from(normalized(v),T(0)))
	 , _a(a)
	{ }

	static constexpr inline
	matrix<T,4,4,RM,V> _make(T ca, T sa, const _vT& v, const _vT& u)
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			(
				_vT::fill(u[0])*v+
				_vT::make( ca*T(1),-sa*v[2], sa*v[1],0)
			)._v,
			(
				_vT::fill(u[1])*v+
				_vT::make( sa*v[2], ca*T(1),-sa*v[0],0)
			)._v,
			(
				_vT::fill(u[2])*v+
				_vT::make(-sa*v[1], sa*v[0], ca*T(1),0)
			)._v,
			(_vT::template axis<3>())._v
		}};
	}

	static constexpr inline
	matrix<T,4,4,RM,V> _make(T ca, T sa, const _vT& v)
	noexcept
	{
		return _make(ca, sa, v, v*(1-ca));
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(cos(_a), sin(_a)*(RM?1:-1), _v);
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(rotation_a)
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
rotation_a<matrix<T,R,C,!RM,V>>
reorder_mat_ctr(const rotation_a<matrix<T,R,C,RM,V>>& r)
noexcept
{
	return {r._v, r._a};
}

// scale
template <typename X>
struct scale;

// is_matrix_constructor<scale>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<scale<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// scale matrix 4x4 row-major
template <typename T, bool RM, bool V>
struct scale<matrix<T,4,4,RM,V>>
{
	typedef typename vect::data<T, 3, V>::type _dT;
	_dT _s;

	constexpr
	scale(_dT s)
	noexcept
	 : _s(s)
	{ }

	constexpr
	scale(T sx, T sy, T sz)
	noexcept
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{_s[0], T(0), T(0), T(0)},
			{ T(0),_s[1], T(0), T(0)},
			{ T(0), T(0),_s[2], T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// scale * T
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
scale<matrix<T,R,C,RM,V>>
operator * (const scale<matrix<T,R,C,RM,V>>& c, T t)
noexcept
{
	return {c._s*vect::fill<T,(R>C?R:C)-1,V>::apply(t)};
}

// scale + scale
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
scale<matrix<T,R,C,RM,V>>
operator * (
	const scale<matrix<T,R,C,RM,V>>& c1,
	const scale<matrix<T,R,C,RM,V>>& c2
) noexcept
{
	return {c1._s*c2._s};
}

// reorder_mat_ctr(scale)
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
scale<matrix<T,R,C,!RM,V>>
reorder_mat_ctr(const scale<matrix<T,R,C,RM,V>>& s)
noexcept
{
	return {s._s};
}

// scale_I
template <typename X, unsigned I>
struct scale_I;

// scale along the I-th axis matrix 4x4
template <typename T, unsigned I, bool RM, bool V>
struct scale_I<matrix<T,4,4,RM,V>, I>
{
	T _s;

	constexpr inline
	T v(unsigned i) const
	noexcept
	{
		return (i == I)?_s:T(1);
	}

	constexpr
	scale_I(T s)
	noexcept
	 : _s(s)
	{ }

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{v(0),T(0),T(0),T(0)},
			{T(0),v(1),T(0),T(0)},
			{T(0),T(0),v(2),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// scale_I * T
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
scale_I<matrix<T,R,C,RM,V>, I>
operator * (const scale_I<matrix<T,R,C,RM,V>, I>& c, T t)
noexcept
{
	return {c._s*t};
}

// scale_I + scale_I
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
scale_I<matrix<T,R,C,RM,V>, I>
operator * (
	const scale_I<matrix<T,R,C,RM,V>, I>& c1,
	const scale_I<matrix<T,R,C,RM,V>, I>& c2
) noexcept
{
	return {c1._s*c2._s};
}

// reorder_mat_ctr(scale_I)
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
scale_I<matrix<T,R,C,!RM,V>, I>
reorder_mat_ctr(const scale_I<matrix<T,R,C,RM,V>, I>& t)
noexcept
{
	return {t._s};
}

// scale x
template <typename M>
using scale_x = scale_I<M, 0>;

// is_matrix_constructor<scale_x>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<scale_x<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// scale y
template <typename M>
using scale_y = scale_I<M, 1>;

// is_matrix_constructor<scale_y>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<scale_y<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// scale z
template <typename M>
using scale_z = scale_I<M, 2>;

// is_matrix_constructor<scale_z>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<scale_z<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };


// uniform_scale
template <typename X>
struct uniform_scale;

// is_matrix_constructor<uniform_scale>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<uniform_scale<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// uniform_scale matrix 4x4 row-major
template <typename T, bool RM, bool V>
struct uniform_scale<matrix<T,4,4,RM,V>>
{
	T _s;

	constexpr
	uniform_scale(T s)
	noexcept
	 : _s(s)
	{ }

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{  _s,T(0),T(0),T(0)},
			{T(0),  _s,T(0),T(0)},
			{T(0),T(0),  _s,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// uniform_scale * T
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
uniform_scale<matrix<T,R,C,RM,V>>
operator * (const uniform_scale<matrix<T,R,C,RM,V>>& c, T t)
noexcept
{
	return {c._s*t};
}

// uniform_scale * uniform_scale 
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
uniform_scale<matrix<T,R,C,RM,V>>
operator * (
	const uniform_scale<matrix<T,R,C,RM,V>>& c1,
	const uniform_scale<matrix<T,R,C,RM,V>>& c2
) noexcept
{
	return {c1._s*c2._s};
}

// reorder_mat_ctr(uniform_scale)
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
uniform_scale<matrix<T,R,C,!RM,V>>
reorder_mat_ctr(const uniform_scale<matrix<T,R,C,RM,V>>& us)
noexcept
{
	return {us._s};
}

// reflection_I
template <typename X, unsigned I>
struct reflection_I;

// is_matrix_constructor<reflection_I>
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
struct is_matrix_constructor<reflection_I<matrix<T,R,C,RM,V>, I>>
 : meta::true_type
{ };

// reflection_I matrix 4x4
template <typename T, bool RM, bool V, unsigned I>
struct reflection_I<matrix<T,4,4,RM,V>, I>
{
	T _r;

	constexpr
	reflection_I(bool r = true)
	noexcept
	 : _r(r?-1:1)
	{ }

	constexpr inline
	T v(unsigned i) const
	noexcept
	{
		return (I == i)?_r:T(1);
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,RM,V>{{
			{v(0),T(0),T(0),T(0)},
			{T(0),v(1),T(0),T(0)},
			{T(0),T(0),v(2),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reflection_I + reflection_I
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
reflection_I<matrix<T,R,C,RM,V>, I>
operator * (
	const reflection_I<matrix<T,R,C,RM,V>, I>& c1,
	const reflection_I<matrix<T,R,C,RM,V>, I>& c2
) noexcept
{
	return {not(c1._r <<equal_to>> c2._r)};
}

// reorder_mat_ctr(reflection_I)
template <typename T, unsigned R, unsigned C, bool RM, bool V, unsigned I>
static constexpr inline
reflection_I<matrix<T,R,C,!RM,V>, I>
reorder_mat_ctr(const reflection_I<matrix<T,R,C,RM,V>, I>& r)
noexcept
{
	return {r._r<T(0)};
}

// reflection x
template <typename M>
using reflection_x = reflection_I<M, 0>;

// is_matrix_constructor<reflection_x>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<reflection_x<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// reflection y
template <typename M>
using reflection_y = reflection_I<M, 1>;

// is_matrix_constructor<reflection_y>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<reflection_y<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// reflection z
template <typename M>
using reflection_z = reflection_I<M, 2>;

// is_matrix_constructor<reflection_z>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<reflection_z<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// shear
template <typename X>
struct shear;

// is_matrix_constructor<shear>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<shear<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// shear matrix 4x4 row-major
template <typename T, bool V>
struct shear<matrix<T,4,4, true,V>>
{
	typedef typename vect::data<T, 3, V>::type _dT;
	_dT _s;

	constexpr
	shear(_dT s)
	noexcept
	 : _s(s)
	{ }

	constexpr
	shear(T sx, T sy, T sz)
	noexcept
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	matrix<T,4,4, true,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{ T(1),_s[0],_s[0], T(0)},
			{_s[1], T(1),_s[1], T(0)},
			{_s[2],_s[2], T(1), T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4, true,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// shear matrix 4x4 column-major
template <typename T, bool V>
struct shear<matrix<T,4,4,false,V>>
{
	typedef typename vect::data<T, 3, V>::type _dT;
	_dT _s;

	constexpr
	shear(_dT s)
	noexcept
	 : _s(s)
	{ }

	constexpr
	shear(T sx, T sy, T sz)
	noexcept
	 : _s{sx, sy, sz}
	{ }

	constexpr inline
	matrix<T,4,4,false,V> operator()(void) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{ T(1),_s[1],_s[2], T(0)},
			{_s[0], T(1),_s[2], T(0)},
			{_s[0],_s[1], T(1), T(0)},
			{ T(0), T(0), T(0), T(1)}
		}};
	}

	constexpr inline
	operator matrix<T,4,4,false,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// shear * shear 
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
shear<matrix<T,R,C,RM,V>>
operator * (
	const shear<matrix<T,R,C,RM,V>>& c1,
	const shear<matrix<T,R,C,RM,V>>& c2
) noexcept
{
	return {c1._s+c2._s};
}

// reorder_mat_ctr(shear)
template <typename T, unsigned R, unsigned C, bool RM, bool V>
static constexpr inline
shear<matrix<T,R,C,!RM,V>>
reorder_mat_ctr(const shear<matrix<T,R,C,RM,V>>& s)
noexcept
{
	return {s._s};
}

// ortho
template <typename X>
struct ortho;

// is_matrix_constructor<ortho>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<ortho<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// ortho matrix 4x4
template <typename T, bool RM, bool V>
struct ortho<matrix<T,4,4,RM,V>>
{
	typedef typename vect::data<T, 6, V>::type _dT;
	_dT _s;

	constexpr
	ortho(const _dT& s)
	noexcept
	 : _s(s)
	{ }

	constexpr ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	) noexcept
	 : _s{x_left, x_right, y_bottom, y_top, z_near, z_far}
	{ }

	constexpr inline T _x_left(void) const { return _s[0]; }
	constexpr inline T _x_right(void) const { return _s[1]; }
	constexpr inline T _y_bottom(void) const { return _s[2]; }
	constexpr inline T _y_top(void) const { return _s[3]; }
	constexpr inline T _z_near(void) const { return _s[4]; }
	constexpr inline T _z_far(void) const { return _s[5]; }

	constexpr inline
	T _m00(void) const
	noexcept
	{
		return T(2) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m11(void) const
	noexcept
	{
		return T(2) / (_y_top() - _y_bottom());
	}

	constexpr inline
	T _m22(void) const
	noexcept
	{
		return -T(2) / (_z_far() - _z_near());
	}

	constexpr inline
	T _m30(void) const
	noexcept
	{
		return -(_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m31(void) const
	noexcept
	{
		return -(_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline
	T _m32(void) const
	noexcept
	{
		return -(_z_far() + _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline
	matrix<T,4,4, true,V> _make(meta::true_type) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{_m00(),   T(0),   T(0), _m30()},
			{  T(0), _m11(),   T(0), _m31()},
			{  T(0),   T(0), _m22(), _m32()},
			{  T(0),   T(0),   T(0),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{  T(0),   T(0), _m22(),   T(0)},
			{_m30(), _m31(), _m32(),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(ortho)
template <typename T, bool RM, bool V>
static constexpr inline
ortho<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const ortho<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._s};
}

// looking_at_y_up
template <typename X>
struct looking_at_y_up;

// is_matrix_constructor<looking_at_y_up>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<looking_at_y_up<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// looking_at_y_up matrix 4x4
template <typename T, bool RM, bool V>
struct looking_at_y_up<matrix<T,4,4,RM,V>>
{
	typedef vector<T,3,V> _dT;

	vector<T,3,V> _e, _t;

	constexpr looking_at_y_up(
		const vector<T, 3, V>& eye,
		const vector<T, 3, V>& target
	) noexcept
	 : _e(eye)
	 , _t(target)
	{ }

	static constexpr inline
	matrix<T,4,4,true,V>
	_make(const _dT& x, const _dT& y, const _dT& z, const _dT& t)
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{x[0],x[1],x[2], -dot(x,t)},
			{y[0],y[1],y[2], -dot(y,t)},
			{z[0],z[1],z[2], -dot(z,t)},
			{T(0), T(0), T(0), T(1)}
		}};
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make(const _dT& y, const _dT& z, const _dT& t)
	noexcept
	{
		return _make(cross(y, z), y, z, t);
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make(const _dT& z, const _dT& t)
	noexcept
	{
		return _make(normalized(cross(z, t)), z, t);
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make(const _dT& z)
	noexcept
	{
		return _make(z, _dT::make(z.z(), T(0),-z.x()));
	}

	constexpr inline
	matrix<T,4,4,true,V> _make(meta::true_type) const
	noexcept
	{
		return _make(normalized(_e-_t));
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return reorder(_make(meta::true_type()));
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(looking_at_y_up)
template <typename T, bool RM, bool V>
static constexpr inline
looking_at_y_up<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const looking_at_y_up<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._e,c._t};
}

// looking_at
template <typename X>
struct looking_at;

// is_matrix_constructor<looking_at>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<looking_at<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// looking_at matrix 4x4
template <typename T, bool RM, bool V>
struct looking_at<matrix<T,4,4,RM,V>>
{
	typedef vector<T,3,V> _dT;

	vector<T,3,V> _e, _t, _u;

	constexpr looking_at(
		const vector<T, 3, V>& eye,
		const vector<T, 3, V>& target,
		const vector<T, 3, V>& up
	) noexcept
	 : _e(eye)
	 , _t(target)
	 , _u(up)
	{ }

	static constexpr inline
	matrix<T,4,4,true,V>
	_make4(const _dT& e, const _dT& x, const _dT& y, const _dT& z)
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{x[0],x[1],x[2], -dot(x,e)},
			{y[0],y[1],y[2], -dot(y,e)},
			{z[0],z[1],z[2], -dot(z,e)},
			{T(0), T(0), T(0), T(1)}
		}};
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make3(const _dT& e, const _dT& y, const _dT& z)
	noexcept
	{
		return _make4(e, cross(y, z), y, z);
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make2(
		const _dT& e,
		const _dT& u,
		const _dT& z,
		const scalar<T,3,V>& dzu
	)
	noexcept
	{
		return _make3(
			e,
			normalized((T(dzu) <<close_to>> T(0))?u-z*dzu:u),
			z
		);
	}

	static constexpr inline
	matrix<T,4,4,true,V>
	_make1(const _dT& e, const _dT& u, const _dT& z)
	noexcept
	{
		return _make2(e, u, z, dot(z,u));
	}

	constexpr inline
	matrix<T,4,4,true,V> _make(meta::true_type) const
	noexcept
	{
		return _make1(_e, _u, normalized(_e-_t));
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return reorder(_make(meta::true_type()));
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(looking_at)
template <typename T, bool RM, bool V>
static constexpr inline
looking_at<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const looking_at<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._e,c._t,c._u};
}

// orbiting_y_up
template <typename X>
struct orbiting_y_up;

// is_matrix_constructor<orbiting_y_up>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<orbiting_y_up<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// orbiting_y_up matrix 4x4
template <typename T, bool RM, bool V>
struct orbiting_y_up<matrix<T,4,4,RM,V>>
{
	vector<T,3,V> _t;
	vector<T,3,V> _x, _z, _y;
	T _r;

	constexpr
	orbiting_y_up(
		const vector<T,3,V>& t,
		const vector<T,3,V>& x,
		const vector<T,3,V>& y,
		const vector<T,3,V>& z,
		T r
	) noexcept
	 : _t(t)
	 , _x(x)
	 , _z(z)
	 , _y(y)
	 , _r(r)
	{ }

	constexpr orbiting_y_up(
		const vector<T, 3, V>& t,
		const T rs,
		const T sa,
		const T ca,
		const T se,
		const T ce
	) noexcept
	 : _t(t)
	 , _x{{-sa, T(0), -ca}}
	 , _z{{ce*ca, se, ce*-sa}}
	 , _y(cross(_z, _x))
	 , _r(rs)
	{ }

	constexpr orbiting_y_up(
		const vector<T, 3, V>& target,
		const T radius,
		angle<T> azimuth,
		angle<T> elevation
	) noexcept
	 : orbiting_y_up(
		target,
		radius,
		sin(azimuth),
		cos(azimuth),
		sin(elevation),
		cos(elevation)
	){ }

	constexpr inline
	matrix<T,4,4,true,V> _make(meta::true_type) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{_x[0],_x[1],_x[2],-_r*dot(_x,_z) - dot(_x,_t)},
			{_y[0],_y[1],_y[2],-_r*dot(_y,_z) - dot(_y,_t)},
			{_z[0],_z[1],_z[2],-_r*dot(_z,_z) - dot(_z,_t)},
			{T(0), T(0), T(0), T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return reorder(_make(meta::true_type()));
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(orbiting_y_up)
template <typename T, bool RM, bool V>
static constexpr inline
orbiting_y_up<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const orbiting_y_up<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._t,c._x,c._y,c._z,c._r};
}

// perspective
template <typename X>
struct perspective;

// is_matrix_constructor<perspective>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<perspective<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// perspective matrix 4x4 row-major
template <typename T, bool RM, bool V>
struct perspective<matrix<T,4,4,RM,V>>
{
	typedef typename vect::data<T, 6, V>::type _dT;
	_dT _s;

	constexpr
	perspective(const _dT& s)
	noexcept
	 : _s(s)
	{ }

	constexpr
	perspective(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	) noexcept
	 : _s{x_left, x_right, y_bottom, y_top, z_near, z_far}
	{ }

	constexpr inline
	T _x_left(void) const
	noexcept
	{ return _s[0]; }

	constexpr inline
	T _x_right(void) const
	noexcept
	{ return _s[1]; }

	constexpr inline
	T _y_bottom(void) const
	noexcept
	{ return _s[2]; }

	constexpr inline
	T _y_top(void) const
	noexcept
	{ return _s[3]; }

	constexpr inline
	T _z_near(void) const
	noexcept
	{ return _s[4]; }

	constexpr inline
	T _z_far(void) const
	noexcept
	{ return _s[5]; }

	static inline
	perspective x(
		angle<T> xfov,
		T aspect,
		T z_near,
		T z_far
	) noexcept
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
	) noexcept
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

	constexpr inline
	T _m00(void) const
	noexcept
	{
		return (T(2) * _z_near()) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m11(void) const
	noexcept
	{
		return (T(2) * _z_near()) / (_y_top() - _y_bottom());
	}

	constexpr inline
	T _m22(void) const
	noexcept
	{
		return -(_z_far() + _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline
	T _m20(void) const
	noexcept
	{
		return (_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m21(void) const
	noexcept
	{
		return (_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline
	T _m23(void) const
	noexcept
	{
		return -T(1);
	}

	constexpr inline
	T _m32(void) const
	noexcept
	{
		return -(T(2) * _z_far() * _z_near()) / (_z_far() - _z_near());
	}

	constexpr inline
	matrix<T,4,4, true,V> _make(meta::true_type) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{_m00(),   T(0), _m20(),   T(0)},
			{  T(0), _m11(), _m21(),   T(0)},
			{  T(0),   T(0), _m22(), _m32()},
			{  T(0),   T(0), _m23(),   T(0)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{_m20(), _m21(), _m22(), _m23()},
			{  T(0),   T(0), _m32(),   T(0)}
		}};
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(perspective)
template <typename T, bool RM, bool V>
static constexpr inline
perspective<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const perspective<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._s};
}

// screen_stretch
template <typename X>
struct screen_stretch;

// is_matrix_constructor<screen_stretch>
template <typename T, unsigned R, unsigned C, bool RM, bool V>
struct is_matrix_constructor<screen_stretch<matrix<T,R,C,RM,V>>>
 : meta::true_type
{ };

// screen_stretch matrix 4x4
template <typename T, bool RM, bool V>
struct screen_stretch<matrix<T,4,4,RM,V>>
{
	typedef typename vect::data<T, 4, V>::type _dT;
	_dT _s;

	constexpr screen_stretch(const _dT& s)
	noexcept
	 : _s(s)
	{ }

	constexpr screen_stretch(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top
	) noexcept
	 : _s{x_left, x_right, y_bottom, y_top}
	{ }

	static constexpr inline
	screen_stretch tile(
		unsigned x,
		unsigned y,
		unsigned nx,
		unsigned ny
	) noexcept
	{
		return screen_stretch(
			-T(1)+T(2*(x+0))/T(nx),
			-T(1)+T(2*(x+1))/T(nx),
			-T(1)+T(2*(y+0))/T(ny),
			-T(1)+T(2*(y+1))/T(ny)
		);
	}

	constexpr inline
	T _x_left(void) const
	noexcept
	{ return _s[0]; }

	constexpr inline
	T _x_right(void) const
	noexcept
	{ return _s[1]; }

	constexpr inline
	T _y_bottom(void) const
	noexcept
	{ return _s[2]; }

	constexpr inline
	T _y_top(void) const
	noexcept
	{ return _s[3]; }

	constexpr inline
	T _m00(void) const
	noexcept
	{
		return T(2) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m11(void) const
	noexcept
	{
		return T(2) / (_y_top() - _y_bottom());
	}

	constexpr inline
	T _m30(void) const
	noexcept
	{
		return -(_x_right() + _x_left()) / (_x_right() - _x_left());
	}

	constexpr inline
	T _m31(void) const
	noexcept
	{
		return -(_y_top() + _y_bottom()) / (_y_top() - _y_bottom());
	}

	constexpr inline
	matrix<T,4,4, true,V> _make(meta::true_type) const
	noexcept
	{
		return matrix<T,4,4, true,V>{{
			{_m00(),   T(0),   T(0), _m30()},
			{  T(0), _m11(),   T(0), _m31()},
			{  T(0),   T(0),   T(1),   T(0)},
			{  T(0),   T(0),   T(0),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,false,V> _make(meta::false_type) const
	noexcept
	{
		return matrix<T,4,4,false,V>{{
			{_m00(),   T(0),   T(0),   T(0)},
			{  T(0), _m11(),   T(0),   T(0)},
			{  T(0),   T(0),   T(1),   T(0)},
			{_m30(), _m31(),   T(0),   T(1)}
		}};
	}

	constexpr inline
	matrix<T,4,4,RM,V> operator()(void) const
	noexcept
	{
		return _make(meta::boolean_constant<RM>());
	}

	constexpr inline
	operator matrix<T,4,4,RM,V> (void) const
	noexcept
	{
		return (*this)();
	}
};

// reorder_mat_ctr(screen_stretch)
template <typename T, bool RM, bool V>
static constexpr inline
screen_stretch<matrix<T,4,4,!RM,V>>
reorder_mat_ctr(const screen_stretch<matrix<T,4,4,RM,V>>& c)
noexcept
{
	return {c._s};
}

} // namespace math
} // namespace eagine

#endif //include guard

