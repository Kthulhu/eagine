/**
 *  @file eagine/math/quaternion.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_QUATERNION_1308281038_HPP
#define EAGINE_MATH_QUATERNION_1308281038_HPP

#include <eagine/math/vector.hpp>

namespace eagine {
namespace math {

template <typename T, bool V = true>
struct quaternion
{
	typedef typename vect::data<T, 4, V>::type _qT;
	typedef typename vect::data<T, 3, V>::type _vT;

	typedef const quaternion& _cpT;

	typedef _qT data_type;

	data_type _v;

	static constexpr _vT _sinv(const angle<T>& angle)
	{
		return vect::fill<T, 3, V>::apply(sin(angle));
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
			vect::hsum<T, 4, V>::apply(q._v * q._v)
		};
	}

	friend inline T square_mag(_cpT q)
	{
		return vect::esum<T, 4, V>::apply(q._v * q._v);
	}

	friend inline T magnitude(_cpT q)
	{
		using std::sqrt;
		return sqrt(square_mag(q));
	}

	static constexpr inline
	_qT _gp_t1(const _qT& a, const _qT& b)
	{
		return	vect::shuffle<T,4,V>::template apply<3,3,3,3>(a)*b+
			vect::shuffle<T,4,V>::template apply<3,3,3,3>(b)*a+
			vect::shuffle<T,4,V>::template apply<1,2,0,3>(a)*
			vect::shuffle<T,4,V>::template apply<2,0,1,3>(b)-
			vect::shuffle<T,4,V>::template apply<2,0,1,3>(a)*
			vect::shuffle<T,4,V>::template apply<1,2,0,3>(b);
	}

	static constexpr inline
	_qT _gp_t2(const _qT& a, const _qT& b, const _qT& t)
	{
		return	vect::shuffle<T,4,V>::template apply<3,3,3,3>(a)*
			vect::shuffle<T,4,V>::template apply<3,3,3,3>(b)-
			vect::shuffle<T,4,V>::template apply<1,0,0,3>(t)-
			vect::shuffle<T,4,V>::template apply<2,2,1,3>(t)-
			t;
	}

	friend constexpr quaternion grassman_product(_cpT a, _cpT b)
	{
		return {vect::shuffle2<T,4,V>::template apply<0,1,2,4>(
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
		return angle<T>
			{acos(vect::esum<T,4,V>::apply(a._v * b._v))};
	}
};

template <typename T, bool V>
static constexpr inline vector<T, 3, V>
rotate(const vector<T, 3, V>& v, const quaternion<T, V>& q)
{
	return vector_part(grassman_product(
		grassman_product(q, quaternion<T, V>::from_vector(v)),
		conjugate(q)
	));
}

// difference_op
template <typename T, bool V>
struct difference_op<quaternion<T, V>>
{
	quaternion<T, V> _l, _r;

	typedef typename quaternion<T, V>::data_type _vT;

	static constexpr inline
	T _diff(_vT a)
	noexcept
	{
		return vect::hmax<T, 4, V>::apply(
			vect::abs<T, 4, V>::apply(a)
		)[0];
	}

	constexpr inline
	T get(void) const
	noexcept
	{
		return _diff(_l._v-_r._v);
	}

	constexpr inline
	operator T (void) const
	noexcept
	{
		return get();
	}
};

} // namespace math
} // namespace eagine

#endif //include guard

