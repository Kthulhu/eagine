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
#include <eagine/math/angle.hpp>

namespace EAGine {
namespace math {

template <typename T>
struct quaternion
{
	typedef typename vect::data<T, 4>::type _qT;
	typedef typename vect::data<T, 3>::type _vT;

	typedef const quaternion& _cpT;

	_qT _q;

	static constexpr _vT _sinv(const angle<T>& angle)
	{
		return vect::fill<T,3>::apply(sin(angle));
	}

	static constexpr quaternion _combine(
		const _vT& vec,
		const T& sca
	)
	{
		return {vec[0], vec[1], vec[2], sca};
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
		return a._q == b._q;
	}

	friend constexpr bool operator != (_cpT a, _cpT b)
	{
		return a._q != b._q;
	}

	friend constexpr vector<T, 3> vector_part(_cpT q)
	{
		return {_vT(q._q)};
	}

	friend constexpr T scalar_part(_cpT q)
	{
		return {q._q[3]};
	}

	friend constexpr quaternion conjugate(_cpT q)
	{
		return {-q._q[0],-q._q[1],-q._q[2], q._q[3]};
	}

	friend constexpr quaternion inverse(_cpT q)
	{
		return {
			conjugate(q)._q /
			vect::hsum<T, 4>::apply(q._q * q._q)
		};
	}

	friend inline T magnitude(_cpT q)
	{
		using std::sqrt;
		return sqrt(vect::hsum<T, 4>::apply(q._q * q._q)[0]);
	}

	friend quaternion grassman_product(_cpT a, _cpT b)
	{
		_qT t = a._q * b._q;

		_qT t1 =vect::shuffle<T,4>::template apply<3,3,3,3>(a._q)*b._q+
			vect::shuffle<T,4>::template apply<3,3,3,3>(b._q)*a._q+
			vect::shuffle<T,4>::template apply<1,2,0,3>(a._q)*
			vect::shuffle<T,4>::template apply<2,0,1,3>(b._q)-
			vect::shuffle<T,4>::template apply<2,0,1,3>(a._q)*
			vect::shuffle<T,4>::template apply<1,2,0,3>(b._q);

		_qT t2 =vect::shuffle<T,4>::template apply<3,3,3,3>(a._q)*
			vect::shuffle<T,4>::template apply<3,3,3,3>(b._q)-
			vect::shuffle<T,4>::template apply<1,0,0,3>(t)-
			vect::shuffle<T,4>::template apply<2,2,1,3>(t)-
			t;

		return {vect::shuffle2<T,4>::template apply<0,1,2,4>(t1, t2)};
	}
};

} // namespace math
} // namespace EAGine

#endif //include guard

