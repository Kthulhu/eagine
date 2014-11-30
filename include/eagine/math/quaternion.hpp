/**
 *  @file eagine/math/quaternion.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_QUATERNION_1308281038_HPP
#define EAGINE_MATH_QUATERNION_1308281038_HPP

#include <eagine/math/vector.hpp>

namespace eagine {
namespace math {

template <typename T>
struct quaternion
{
	typedef typename vect::data<T, 4>::type _qT;
	typedef typename vect::data<T, 3>::type _vT;

	typedef const quaternion& _cpT;

	_qT _v;

	static constexpr _vT _sinv(const angle<T>& angle)
	{
		return vect::fill<T,3>::apply(sin(angle));
	}

	static constexpr quaternion _combine(
		const _vT& vec,
		const T& sca
	)
	{
		return {{vec[0], vec[1], vec[2], sca}};
	}

	static constexpr quaternion from_vector(
		const vector<T, 3>& v
	)
	{
		return _combine(v._v, T(0));
	}

	static constexpr quaternion from_scalar_vector(
		const T& s,
		const vector<T, 3>& v
	)
	{
		return _combine(v._v, s);
	}

	static constexpr quaternion from_axis_angle(
		const vector<T,3>& axis,
		const angle<T>& angle
	)
	{
		return _combine(axis._v*_sinv(angle*0.5), cos(angle*0.5));
	}

	friend constexpr bool operator == (_cpT a, _cpT b)
	{
		return a._v == b._v;
	}

	friend constexpr bool operator != (_cpT a, _cpT b)
	{
		return a._v != b._v;
	}

	friend constexpr vector<T, 3> vector_part(_cpT q)
	{
		return {{q._v[0], q._v[1], q._v[2]}};
	}

	friend constexpr T scalar_part(_cpT q)
	{
		return {q._v[3]};
	}

	friend constexpr quaternion conjugate(_cpT q)
	{
		return {{-q._v[0],-q._v[1],-q._v[2], q._v[3]}};
	}

	quaternion operator * (void) const
	{
		return conjugate(*this);
	}

	friend constexpr quaternion inverse(_cpT q)
	{
		return {
			conjugate(q)._v /
			vect::hsum<T, 4>::apply(q._v * q._v)
		};
	}

	friend inline T square_mag(_cpT q)
	{
		return vect::hsum<T, 4>::apply(q._v * q._v)[0];
	}

	friend inline T magnitude(_cpT q)
	{
		using std::sqrt;
		return sqrt(square_mag(q));
	}

	static constexpr inline
	_qT _gp_t1(const _qT& a, const _qT& b)
	{
		return	vect::shuffle<T,4>::template apply<3,3,3,3>(a)*b+
			vect::shuffle<T,4>::template apply<3,3,3,3>(b)*a+
			vect::shuffle<T,4>::template apply<1,2,0,3>(a)*
			vect::shuffle<T,4>::template apply<2,0,1,3>(b)-
			vect::shuffle<T,4>::template apply<2,0,1,3>(a)*
			vect::shuffle<T,4>::template apply<1,2,0,3>(b);
	}

	static constexpr inline
	_qT _gp_t2(const _qT& a, const _qT& b, const _qT& t)
	{
		return	vect::shuffle<T,4>::template apply<3,3,3,3>(a)*
			vect::shuffle<T,4>::template apply<3,3,3,3>(b)-
			vect::shuffle<T,4>::template apply<1,0,0,3>(t)-
			vect::shuffle<T,4>::template apply<2,2,1,3>(t)-
			t;
	}

	friend constexpr quaternion grassman_product(_cpT a, _cpT b)
	{
		return {vect::shuffle2<T,4>::template apply<0,1,2,4>(
			quaternion::_gp_t1(a._v, b._v),
			quaternion::_gp_t2(a._v, b._v, a._v * b._v)
		)};
	}

	friend constexpr quaternion operator * (_cpT a, _cpT b)
	{
		return grassman_product(a, b);
	}

	friend constexpr angle<T> angle_between(_cpT a, _cpT b)
	{
		using std::acos;
		return {acos(vect::hsum<T, 4>::apply(a._v * b._v)[0])};
	}
};

template <typename T>
static constexpr inline vector<T, 3>
rotate(const vector<T, 3>& v, const quaternion<T>& q)
{
	return vector_part(grassman_product(
		grassman_product(q, quaternion<T>::from_vector(v)),
		conjugate(q)
	));
}

} // namespace math
} // namespace eagine

#endif //include guard

