/**
 *  @file eagine/math/vector.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_VECTOR_1308281038_HPP
#define EAGINE_MATH_VECTOR_1308281038_HPP

#include <eagine/vect/fill.hpp>
#include <eagine/vect/axis.hpp>
#include <eagine/vect/hsum.hpp>
#include <eagine/vect/compare.hpp>
#include <eagine/meta/min_max.hpp>
#include <eagine/math/angle.hpp>
#include <cmath>

namespace EAGine {
namespace math {

template <typename T, unsigned N>
struct vector
{
	typedef vector type;

	typedef typename vect::data<T, N>::type _vT;

	typedef const vector& _cpT;

	_vT _v;

	template <unsigned ...I, unsigned M>
	static inline vector from(const vector<T, M>& v)
	{
		return {v._v[I]...};
	}

	static inline vector zero(void)
	{
		return {vect::fill<T,N>::apply(T(0))};
	}

	static inline vector fill(T v)
	{
		return {vect::fill<T,N>::apply(v)};
	}

	template <unsigned I>
	static inline vector axis(void)
	{
		return {vect::axis<T,N,I>::apply(T(1))};
	}

	template <unsigned I>
	static inline vector axis(T v)
	{
		return {vect::axis<T,N,I>::apply(v)};
	}

	inline T operator [] (unsigned pos) const
	{
		return _v[pos];
	}

	friend constexpr vector operator + (_cpT a, _cpT b)
	{
		return {a._v+b._v};
	}

	friend constexpr vector operator - (_cpT a, _cpT b)
	{
		return {a._v-b._v};
	}

	friend constexpr vector operator * (_cpT a, _cpT b)
	{
		return {a._v*b._v};
	}

	friend constexpr vector operator * (_cpT a, T c)
	{
		return {a._v*vect::fill<T, N>::apply(c)};
	}

	friend constexpr vector operator / (_cpT a, _cpT b)
	{
		return {a._v/b._v};
	}

	friend constexpr vector operator / (_cpT a, T c)
	{
		return {a._v/vect::fill<T, N>::apply(c)};
	}

	friend bool operator == (_cpT a, _cpT b)
	{
		return vect::equal<T,N>::apply(a, b);
	}

	friend bool operator != (_cpT a, _cpT b)
	{
		return !vect::equal<T,N>::apply(a, b);
	}

	friend constexpr vector hsum(_cpT a, _cpT b)
	{
		return {vect::hsum<T, N>::apply(a._v * b._v)};
	}

	friend constexpr T dot(_cpT a, _cpT b)
	{
		return vect::hsum<T, N>::apply(a._v * b._v)[0];
	}

	friend constexpr T magnitude(_cpT a)
	{
		using std::sqrt;
		return sqrt(dot(a, a));
	}

	friend constexpr T length(_cpT a)
	{
		return magnitude(a);
	}

	friend constexpr T distance(_cpT a, _cpT b)
	{
		return magnitude(a-b);
	}

	friend constexpr vector normalized(_cpT a)
	{
		return a / magnitude(a);
	}

	friend constexpr angle<T> angle_between(_cpT a, _cpT b)
	{
		using std::acos;
		return {T(acos(vect::hsum<T, N>::apply(a._v * b._v)[0]))};
	}
};

// get(vector)
template <unsigned I, typename T, unsigned N>
static constexpr inline
typename meta::enable_if<(I<N), T>::type
get(const vector<T,N>& v)
{
	return v._v[I];
}

// get(vector) run-time
template <typename T, unsigned N>
static constexpr inline
T get(const vector<T,N>& v, unsigned i)
{
	return v._v[i];
}

using vect::shuffle_mask;

template <int ... I, typename T, unsigned N>
static inline
typename meta::enable_if<
	meta::max_constant<int, I...>::value < N,
	vector<T, N>
>::type
shuffle(
	const vector<T, N>& v,
	shuffle_mask<I...> m = shuffle_mask<I...>()
)
{
	return {vect::shuffle<T, N>::apply(v._v, m)};
}

template <int ... I, typename T, unsigned N>
static inline
typename meta::enable_if<
	meta::max_constant<int, I...>::value < 2*N,
	vector<T, N>
>::type
shuffle(
	const vector<T, N>& v1,
	const vector<T, N>& v2,
	shuffle_mask<I...> m = shuffle_mask<I...>()
)
{
	return {vect::shuffle2<T, N>::apply(v1._v, v2._v, m)};
}

template <typename T>
static inline
vector<T, 3>
cross(const vector<T, 3>& a, const vector<T, 3>& b)
{
	typedef vect::shuffle<T, 3> _sh;
	return {
		_sh::template apply<1,2,0>(a._v)*
		_sh::template apply<2,0,1>(b._v)-
		_sh::template apply<2,0,1>(a._v)*
		_sh::template apply<1,2,0>(b._v)
	};
}

} // namespace math
} // namespace EAGine

#endif //include guard

