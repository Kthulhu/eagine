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
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reordered_matrix_constructor<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// constructed_matrix<reordered_constructor>
template <typename M>
struct constructed_matrix<reordered_matrix_constructor<M>>
 : reordered_matrix<M>
{ };

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

// reorder_mat_ctr(translation)
template <typename T, bool RM>
static constexpr inline
translation<matrix<T,4,4,!RM>>
reorder_mat_ctr(const translation<matrix<T,4,4,RM>>& t)
{
	return {t._dx, t._dy, t._dz};
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
		return {{
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
		return {{
			{T(1),T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{v(0),v(1),v(2),T(1)}
		}};
	}
};

// reorder_mat_ctr(translation_I)
template <typename T, bool RM, unsigned I>
static constexpr inline
translation_I<matrix<T,4,4,!RM>, I>
reorder_mat_ctr(const translation_I<matrix<T,4,4,RM>, I>& t)
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

// rotation_x
template <typename X>
struct rotation_x;

// is_matrix_constructor<rotation_x>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_x<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation around X-axis matrix 4x4 row-major
template <typename T, bool RM>
struct rotation_x<matrix<T,4,4, RM>>
{
	T _cx, _sx;

	constexpr rotation_x(angle<T> a)
	 : _cx(cos(a))
	 , _sx(sin(a)*(RM?1:-1))
	{ }

	constexpr inline
	operator matrix<T,4,4, RM> (void) const
	{
		return {{
			{T(1),T(0),T(0),T(0)},
			{T(0), _cx,-_sx,T(0)},
			{T(0), _sx, _cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(rotation_x)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
rotation_x<matrix<T,R,C,!RM>>
reorder_mat_ctr(const rotation_x<matrix<T,R,C,RM>>& r)
{
	return {r._cx,-r._sx};
}

// rotation_y
template <typename X>
struct rotation_y;

// is_matrix_constructor<rotation_y>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_y<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation around Y-axis matrix 4x4 row-major
template <typename T, bool RM>
struct rotation_y<matrix<T,4,4, RM>>
{
	T _cx, _sx;

	constexpr rotation_y(angle<T> a)
	 : _cx(cos(a))
	 , _sx(sin(a)*(RM?1:-1))
	{ }

	constexpr inline
	operator matrix<T,4,4, RM> (void) const
	{
		return {{
			{ _cx,T(0), _sx,T(0)},
			{T(0),T(1),T(0),T(0)},
			{-_sx,T(0), _cx,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(rotation_y)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
rotation_y<matrix<T,R,C,!RM>>
reorder_mat_ctr(const rotation_y<matrix<T,R,C,RM>>& r)
{
	return {r._cx,-r._sx};
}

// rotation_z
template <typename X>
struct rotation_z;

// is_matrix_constructor<rotation_z>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<rotation_z<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// rotation around Z-axis matrix 4x4 row-major
template <typename T, bool RM>
struct rotation_z<matrix<T,4,4, RM>>
{
	T _cx, _sx;

	constexpr rotation_z(angle<T> a)
	 : _cx(cos(a))
	 , _sx(sin(a)*(RM?1:-1))
	{ }

	constexpr inline
	operator matrix<T,4,4, RM> (void) const
	{
		return {{
			{ _cx,-_sx,T(0),T(0)},
			{ _sx, _cx,T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(rotation_z)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
rotation_z<matrix<T,R,C,!RM>>
reorder_mat_ctr(const rotation_z<matrix<T,R,C,RM>>& r)
{
	return {r._cx,-r._sx};
}

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

// reorder_mat_ctr(scale)
template <typename T, bool RM>
static constexpr inline
scale<matrix<T,4,4,!RM>>
reorder_mat_ctr(const scale<matrix<T,4,4,RM>>& s)
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

// reorder_mat_ctr(uniform_scale)
template <typename T, bool RM>
static constexpr inline
uniform_scale<matrix<T,4,4,!RM>>
reorder_mat_ctr(const uniform_scale<matrix<T,4,4,RM>>& us)
{
	return {us._s};
}

// reflection_x
template <typename X>
struct reflection_x;

// is_matrix_constructor<reflection_x>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_x<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// reflection_x matrix 4x4
template <typename T, bool RM>
struct reflection_x<matrix<T,4,4,RM>>
{
	T _r;

	constexpr reflection_x(bool r = true)
	 : _r(r?-1:1)
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return {{
			{  _r,T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(reflection_x)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
reflection_x<matrix<T,R,C,!RM>>
reorder_mat_ctr(const reflection_x<matrix<T,R,C,RM>>& r)
{
	return {r._r};
}

// reflection_y
template <typename X>
struct reflection_y;

// is_matrix_constructor<reflection_y>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_y<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// reflection_y matrix 4x4
template <typename T, bool RM>
struct reflection_y<matrix<T,4,4,RM>>
{
	T _r;

	constexpr reflection_y(bool r = true)
	 : _r(r?-1:1)
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return {{
			{T(1),T(0),T(0),T(0)},
			{T(0),  _r,T(0),T(0)},
			{T(0),T(0),T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(reflection_y)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
reflection_y<matrix<T,R,C,!RM>>
reorder_mat_ctr(const reflection_y<matrix<T,R,C,RM>>& r)
{
	return {r._r};
}

// reflection_z
template <typename X>
struct reflection_z;

// is_matrix_constructor<reflection_z>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<reflection_z<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// reflection_z matrix 4x4
template <typename T, bool RM>
struct reflection_z<matrix<T,4,4,RM>>
{
	T _r;

	constexpr reflection_z(bool r = true)
	 : _r(r?-1:1)
	{ }

	constexpr inline
	operator matrix<T,4,4,RM> (void) const
	{
		return {{
			{T(1),T(0),T(0),T(0)},
			{T(0),T(1),T(0),T(0)},
			{T(0),T(0),  _r,T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(reflection_z)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
reflection_z<matrix<T,R,C,!RM>>
reorder_mat_ctr(const reflection_z<matrix<T,R,C,RM>>& r)
{
	return {r._r};
}

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
	T _sx, _sy, _sz;

	constexpr shear(T sx, T sy, T sz)
	 : _sx(sx), _sy(sy), _sz(sz)
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return {{
			{T(1), _sx, _sx,T(0)},
			{ _sy,T(1), _sy,T(0)},
			{ _sz, _sz,T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// shear matrix 4x4 column-major
template <typename T>
struct shear<matrix<T,4,4,false>>
{
	T _sx, _sy, _sz;

	constexpr shear(T sx, T sy, T sz)
	 : _sx(sx), _sy(sy), _sz(sz)
	{ }

	constexpr inline
	operator matrix<T,4,4,false> (void) const
	{
		return {{
			{T(1), _sy, _sz,T(0)},
			{ _sx,T(1), _sz,T(0)},
			{ _sx, _sy,T(1),T(0)},
			{T(0),T(0),T(0),T(1)}
		}};
	}
};

// reorder_mat_ctr(shear)
template <typename T, bool RM>
static constexpr inline
shear<matrix<T,4,4,!RM>>
reorder_mat_ctr(const shear<matrix<T,4,4,RM>>& s)
{
	return {s._sx, s._sy, s._sz};
}

// ortho
template <typename X>
struct ortho;

// is_matrix_constructor<ortho>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<ortho<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// ortho matrix 4x4 row-major
template <typename T>
struct ortho<matrix<T,4,4, true>>
{
	T _m00,_m11,_m22,_m30,_m31,_m32;

	constexpr ortho(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): _m00( T(2) / (x_right - x_left))
	 , _m11( T(2) / (y_top - y_bottom))
	 , _m22(-T(2) / (z_far - z_near))
	 , _m30(-(x_right + x_left) / (x_right - x_left))
	 , _m31(-(y_top + y_bottom) / (y_top - y_bottom))
	 , _m32(-(z_far + z_near)   / (z_far - z_near))
	{ }

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return {{
			{_m00, T(0), T(0), _m30},
			{T(0), _m11, T(0), _m31},
			{T(0), T(0), _m22, _m32},
			{T(0), T(0), T(0), T(1)}
		}};
	}
};

// perspective
template <typename X>
struct perspective;

// is_matrix_constructor<perspective>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<perspective<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// perspective matrix 4x4 row-major
template <typename T>
struct perspective<matrix<T,4,4, true>>
{
	T _m00,_m11,_m22,_m20,_m21,_m23,_m32;

	constexpr perspective(
		T x_left,
		T x_right,
		T y_bottom,
		T y_top,
		T z_near,
		T z_far
	): _m00((T(2) * z_near) / (x_right - x_left))
	 , _m11((T(2) * z_near) / (y_top - y_bottom))
	 , _m22(-(z_far + z_near) / (z_far - z_near))
	 , _m20((x_right + x_left) / (x_right - x_left))
	 , _m21((y_top + y_bottom) / (y_top - y_bottom))
	 , _m23(-T(1))
	 , _m32(-(T(2) * z_far * z_near) / (z_far - z_near))
	{ }

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

	constexpr inline
	operator matrix<T,4,4, true> (void) const
	{
		return {{
			{_m00, T(0), _m20, T(0)},
			{T(0), _m11, _m21, T(0)},
			{T(0), T(0), _m22, _m32},
			{T(0), T(0), _m23, T(0)}
		}};
	}
};

} // namespace math
} // namespace EAGine

#endif //include guard

