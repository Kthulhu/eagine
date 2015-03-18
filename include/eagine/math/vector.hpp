/**
 *  @file eagine/math/vector.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_VECTOR_1308281038_HPP
#define EAGINE_MATH_VECTOR_1308281038_HPP

#include <eagine/vect/fill.hpp>
#include <eagine/vect/axis.hpp>
#include <eagine/vect/from.hpp>
#include <eagine/vect/hsum.hpp>
#include <eagine/vect/esum.hpp>
#include <eagine/vect/sdiv.hpp>
#include <eagine/vect/sqrt.hpp>
#include <eagine/vect/cast.hpp>
#include <eagine/vect/compare.hpp>
#include <eagine/vect/array_ref.hpp>
#include <eagine/meta/min_max.hpp>
#include <eagine/meta/identity.hpp>
#include <eagine/math/angle.hpp>
#include <eagine/base/memory_range.hpp>
#include <cmath>

namespace eagine {
namespace math {

template <typename T, unsigned N>
struct scalar
{
	typedef scalar type;
	typedef T value_type;

	typedef typename vect::_has_vec_data<T, N>::type _vdB;

	typedef typename meta::conditional<
		_vdB::value, vect::data<T, N>, meta::identity<T>
	>::type::type data_type;

	typedef typename meta::conditional<
		_vdB::value, const scalar&, scalar
	>::type _cpT;

	data_type _v;

	static constexpr inline
	scalar _make(T v, meta::true_type)
	noexcept
	{
		return scalar{vect::fill<T, N>::apply(v)};
	}

	static constexpr inline
	scalar _make(T v, meta::false_type)
	noexcept
	{
		return scalar{v};
	}

	static constexpr inline
	scalar make(T v)
	noexcept
	{
		return _make(_vdB());
	}

	constexpr inline
	T _get(meta::true_type) const
	noexcept
	{
		return _v[0];
	}

	constexpr inline
	T _get(meta::false_type) const
	noexcept
	{
		return _v;
	}

	constexpr inline
	operator T (void) const
	noexcept
	{
		return _get(_vdB());
	}

	inline
	scalar& operator = (T v)
	noexcept
	{
		return *this = make(v);
	}

	static constexpr inline
	bool _equal(_cpT a, _cpT b, meta::true_type)
	noexcept
	{
		return vect::equal<T,N>::apply(a._v, b._v);
	}

	static constexpr inline
	bool _equal(_cpT a, _cpT b, meta::false_type)
	noexcept
	{
		return a._v == b._v;
	}

	friend
	bool operator == (_cpT a, _cpT b)
	noexcept
	{
		return _equal(a, b, _vdB());
	}

	friend
	bool operator != (_cpT a, _cpT b)
	noexcept
	{
		return !_equal(a, b, _vdB());
	}
};

template <typename T, unsigned N>
struct vector
{
	typedef vector type;
	typedef scalar<T, N> scalar_type;

	typedef T value_type;

	typedef typename vect::data<T, N>::type _vT;
	typedef _vT data_type;

	typedef const vector& _cpT;
	typedef const scalar<T, N>& _cspT;

	_vT _v;

	template <
		typename P,
		typename = typename meta::enable_if<
			(N == 1) && (meta::is_convertible<P, T>::value)
		>::type
	>
	static constexpr inline
	vector make(P&& p)
	noexcept
	{
		return vector{{T(std::forward<P>(p))}};
	}

	template <
		typename ... P,
		typename = typename meta::enable_if<
			(N > 1) && (sizeof...(P) == N)
		>::type
	>
	static constexpr inline
	vector make(P&& ... p)
	noexcept
	{
		return vector{{T(std::forward<P>(p))...}};
	}

	template <
		typename P,
		unsigned M,
		typename = typename meta::enable_if<
			(!meta::is_same<T, P>::value || (N != M))
		>::type
	>
	static constexpr inline
	vector from(const vector<P, M>& v, T d = T(0))
	noexcept
	{
		return vector{vect::cast<P, M, T, N>::apply(v._v, d)};
	}

	template <typename P, unsigned M>
	static constexpr inline
	vector from(const vector<P, M>& v, const vector<T, N-M>& u)
	noexcept
	{
		return vector{vect::cast<P, M, T, N>::apply(v._v, u._v)};
	}

	template <
		unsigned ... I,
		typename P,
		unsigned M,
		typename = typename meta::enable_if<
			(sizeof...(I) == N)
		>::type
	>
	static constexpr inline
	vector from(const vector<P, M>& v)
	noexcept
	{
		return vector{{T(v._v[I])...}};
	}

	static inline
	vector from(const T* dt, std::size_t sz)
	noexcept
	{
		return vector{vect::from_array<T,N>::apply(dt, sz)};
	}

	static inline
	vector from(const T* dt, std::size_t sz, T fv)
	noexcept
	{
		return vector{vect::from_saafv<T,N>::apply(dt, sz, fv)};
	}

	static inline
	vector zero(void)
	noexcept
	{
		return vector{vect::fill<T,N>::apply(T(0))};
	}

	static inline
	vector fill(T v)
	noexcept
	{
		return vector{vect::fill<T,N>::apply(v)};
	}

	template <unsigned I>
	static inline
	vector axis(void)
	noexcept
	{
		return vector{vect::axis<T,N,I>::apply(T(1))};
	}

	template <unsigned I>
	static inline
	vector axis(T v)
	noexcept
	{
		return vector{vect::axis<T,N,I>::apply(v)};
	}

	static inline
	vector axis(unsigned i, T v)
	noexcept
	{
		vector r{vect::fill<T,N>::apply(T(0))};
		r._v[i] = v;
		return r;
	}

	static constexpr inline
	unsigned dimension(void)
	noexcept
	{
		return N;
	}

	constexpr inline
	T operator [] (unsigned pos) const
	noexcept
	{
		return _v[pos];
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 0), T>::type x(void) const
	noexcept
	{
		static_assert(M == N, "");
		return _v[0];
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 1), T>::type y(void) const
	noexcept
	{
		static_assert(M == N, "");
		return _v[1];
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 2), T>::type z(void) const
	noexcept
	{
		static_assert(M == N, "");
		return _v[2];
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 3), T>::type w(void) const
	noexcept
	{
		static_assert(M == N, "");
		return _v[3];
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 1), vector<T,2>>::type xy(void) const
	noexcept
	{
		static_assert(M == N, "");
		return vector<T,2>::template from<0,1>(*this);
	}

	template <unsigned M = N>
	constexpr inline
	typename meta::enable_if<(M > 2), vector<T,3>>::type xyz(void) const
	noexcept
	{
		static_assert(M == N, "");
		return vector<T,3>::template from<0,1,2>(*this);
	}

	friend constexpr
	vector operator + (_cpT a)
	noexcept
	{
		return a;
	}

	friend constexpr
	vector operator - (_cpT a)
	noexcept
	{
		return vector{-a._v};
	}

	friend constexpr
	vector operator + (_cpT a, _cpT b)
	noexcept
	{
		return vector{a._v+b._v};
	}

	vector& operator += (_cpT a)
	noexcept
	{
		_v = _v + a._v;
		return *this;
	}

	friend constexpr
	vector operator - (_cpT a, _cpT b)
	noexcept
	{
		return vector{a._v-b._v};
	}

	vector& operator -= (_cpT a)
	noexcept
	{
		_v = _v - a._v;
		return *this;
	}

	friend constexpr
	vector operator * (_cpT a, _cpT b)
	noexcept
	{
		return vector{a._v*b._v};
	}

	vector& operator *= (_cpT a)
	noexcept
	{
		_v = _v*a._v;
		return *this;
	}

	template <typename V = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::_vdB::value, V>::type
	operator * (_cspT c, _cpT a)
	noexcept
	{
		return vector{c._v*a._v};
	}

	template <typename V = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::_vdB::value, V>::type
	operator * (_cpT a, _cspT c)
	noexcept
	{
		return vector{a._v*c._v};
	}

	template <typename V = vector>
	typename meta::enable_if<scalar_type::_vdB::value, V>::type&
	operator *= (_cspT c)
	noexcept
	{
		_v = _v*c._v;
		return *this;
	}

	friend constexpr
	vector operator * (T c, _cpT a)
	noexcept
	{
		return vector{a._v*vect::fill<T, N>::apply(c)};
	}

	friend constexpr
	vector operator * (_cpT a, T c)
	noexcept
	{
		return vector{a._v*vect::fill<T, N>::apply(c)};
	}

	vector& operator *= (T c)
	noexcept
	{
		_v = _v*vect::fill<T, N>::apply(c);
		return *this;
	}

	friend constexpr
	vector operator / (_cpT a, _cpT b)
	noexcept
	{
		return vector{vect::sdiv<T, N>::apply(a._v, b._v)};
	}

	template <typename V = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::_vdB::value, V>::type
	operator / (_cspT c, _cpT a)
	noexcept
	{
		return vector{vect::sdiv<T, N>::apply(c._v, a._v)};
	}

	template <typename V = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::_vdB::value, V>::type
	operator / (_cpT a, _cspT c)
	noexcept
	{
		return vector{vect::sdiv<T, N>::apply(a._v, c._v)};
	}

	friend constexpr
	vector operator / (_cpT a, T c)
	noexcept
	{
		return vector{vect::sdiv<T, N>::apply(
			a._v,
			vect::fill<T, N>::apply(c)
		)};
	}

	friend constexpr
	vector operator / (T c, _cpT a)
	noexcept
	{
		return vector{vect::sdiv<T, N>::apply(
			vect::fill<T, N>::apply(c),
			a._v
		)};
	}

	friend
	bool operator == (_cpT a, _cpT b)
	noexcept
	{
		return vect::equal<T,N>::apply(a._v, b._v);
	}

	friend
	bool operator != (_cpT a, _cpT b)
	noexcept
	{
		return !vect::equal<T,N>::apply(a._v, b._v);
	}

	friend
	constexpr vector hsum(_cpT a)
	noexcept
	{
		return vector{vect::hsum<T, N>::apply(a._v)};
	}

	friend constexpr
	scalar<T, N> _dot(_cpT a, _cpT b, meta::true_type)
	noexcept
	{
		return scalar<T, N>{vect::hsum<T, N>::apply(a._v * b._v)};
	}

	friend constexpr
	scalar<T, N> _dot(_cpT a, _cpT b, meta::false_type)
	noexcept
	{
		return scalar<T, N>{vect::esum<T, N>::apply(a._v * b._v)};
	}

	friend constexpr
	scalar<T, N> dot(_cpT a, _cpT b)
	noexcept
	{
		return _dot(a, b, typename scalar_type::_vdB());
	}

	friend constexpr
	scalar<T, N> _mag(_cpT a, meta::true_type)
	noexcept
	{
		return scalar<T, N>{
			vect::sqrt<T, N>::apply(
				vect::hsum<T, N>::apply(a._v * a._v)
			)
		};
	}

	friend constexpr
	scalar<T, N> _mag(_cpT a, meta::false_type)
	noexcept
	{
		using std::sqrt;
		return scalar<T, N>
			{T(sqrt(vect::esum<T, N>::apply(a._v * a._v)))};
	}

	friend constexpr
	scalar<T, N> magnitude(_cpT a)
	noexcept
	{
		return _mag(a, typename scalar_type::_vdB());
	}

	friend constexpr
	scalar<T, N> length(_cpT a)
	noexcept
	{
		return magnitude(a);
	}

	friend constexpr
	scalar<T, N> distance(_cpT a, _cpT b)
	noexcept
	{
		return magnitude(a-b);
	}

	friend constexpr
	vector normalized(_cpT a)
	{
		return a / magnitude(a);
	}

	friend constexpr
	angle<T> angle_between_normalized(_cpT a, _cpT b)
	noexcept
	{
		using std::acos;
		return angle<T>
			{T(acos(vect::esum<T, N>::apply(a._v * b._v)))};
	}

	friend constexpr
	angle<T> angle_between(_cpT a, _cpT b)
	{
		return angle_between_normalized(
			normalized(a),
			normalized(b)
		);
	}
};

// get(vector)
template <unsigned I, typename T, unsigned N>
static constexpr inline
typename meta::enable_if<(I<N), T>::type
get(const vector<T,N>& v)
noexcept
{
	return v._v[I];
}

// get(vector) run-time
template <typename T, unsigned N>
static constexpr inline
T get(const vector<T,N>& v, unsigned i)
noexcept
{
	return v._v[i];
}

// set(vector, v)
template <unsigned I, typename T, unsigned N>
static inline
typename meta::enable_if<(I<N)>::type
set(vector<T,N>& v, T e)
noexcept
{
	v._v[I] = e;
}

// set(vector, v) run-time
template <typename T, unsigned N>
static inline
void
set(vector<T,N>& v, unsigned i, T e)
noexcept
{
	v._v[i] = e;
}

// shuffle_mask
using vect::shuffle_mask;

// shuffle
template <int ... I, typename T, unsigned N>
static inline
typename meta::enable_if<
	meta::max_constant<int, I...>::value < N,
	vector<T, N>
>::type
shuffle(
	const vector<T, N>& v,
	shuffle_mask<I...> m = shuffle_mask<I...>()
) noexcept
{
	return {vect::shuffle<T, N>::apply(v._v, m)};
}

// shuffle
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
) noexcept
{
	return {vect::shuffle2<T, N>::apply(v1._v, v2._v, m)};
}

// perpendicular
template <typename T>
static inline
vector<T, 2>
perpendicular(const vector<T, 2>& a)
noexcept
{
	return {-a._v[1], a._v[0]};
}

// cross
template <typename T>
static inline
vector<T, 3>
cross(const vector<T, 3>& a, const vector<T, 3>& b)
noexcept
{
	typedef vect::shuffle<T, 3> _sh;
	return {
		_sh::template apply<1,2,0>(a._v)*
		_sh::template apply<2,0,1>(b._v)-
		_sh::template apply<2,0,1>(a._v)*
		_sh::template apply<1,2,0>(b._v)
	};
}

// vector_data_ref
template <typename Vector>
class vector_data_ref;

// vector_data_ref<vector>
template <typename T, unsigned N>
class vector_data_ref<vector<T, N>>
{
private:
	vect::array_ref<T, N> _ar;
public:
	vector_data_ref(const vector<T, N>& v)
	noexcept
	 : _ar(v._v)
	{ }

	const T* addr(void) const
	noexcept
	{
		return _ar.data();
	}

	std::size_t size(void) const
	noexcept
	{
		return N;
	}

	base::typed_memory_range<const T> range(void) const
	noexcept
	{
		return base::typed_memory_range<const T>(addr(), size());
	}
};

// data
template <typename T, unsigned N>
static inline
vector_data_ref<vector<T, N>> data(const vector<T, N>& v)
noexcept
{
	return v;
}

} // namespace math
} // namespace eagine

#endif //include guard

