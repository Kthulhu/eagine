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
#include <eagine/math/fwd.hpp>
#include <eagine/math/angle.hpp>
#include <eagine/base/memory_range.hpp>
#include <cmath>

namespace eagine {
namespace math {

// swizzle_mask
template <typename C, unsigned ... I>
struct swizzle_mask
{
	C _c;

	template <typename T, typename V, unsigned J>
	static constexpr inline
	T _get(const V& v, meta::unsigned_constant<J>)
	noexcept
	{
		return v[J-1];
	}

	template <typename T, typename V>
	constexpr inline
	T _get(const V&, meta::unsigned_constant<0>) const
	noexcept
	{
		return T(_c);
	}

	template <unsigned J, typename T, typename V>
	constexpr inline
	T get(const V& v) const
	noexcept
	{
		return _get<T>(v, meta::unsigned_constant<J>());
	}
};

// has_swizzle
template <typename T, unsigned N, bool V, unsigned ...I>
struct has_swizzle<vector<T, N, V>, I...>
 : meta::boolean_constant<meta::max_constant<unsigned, I...>::value<=N>
{ };

template <typename T, unsigned N, bool V, unsigned ...I>
struct has_swizzle<tvec<T, N, V>, I...>
 : meta::boolean_constant<meta::max_constant<unsigned, I...>::value<=N>
{ };

template <typename T, unsigned N, bool V>
struct scalar
{
	template <typename U, unsigned M, bool W>
	struct rebind
	 : scalar<U,M,W>
	{ };

	typedef scalar type;
	typedef T value_type;

	typedef typename vect::has_vect_data<T, N, V>::type
		is_vectorized;

	typedef typename meta::conditional<
		is_vectorized::value,
		vect::data<T, N, V>,
		meta::identity<T>
	>::type::type data_type;

	typedef typename meta::conditional<
		is_vectorized::value,
		const scalar&,
		scalar
	>::type _cpT;

	data_type _v;

	static constexpr inline
	scalar _make(T v, meta::true_type)
	noexcept
	{
		return scalar{vect::fill<T, N, V>::apply(v)};
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
		return _make(v, is_vectorized());
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
		return _get(is_vectorized());
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
		return vect::equal<T,N,V>::apply(a._v, b._v);
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
		return _equal(a, b, is_vectorized());
	}

	friend
	bool operator != (_cpT a, _cpT b)
	noexcept
	{
		return !_equal(a, b, is_vectorized());
	}
};

template <typename T, unsigned N, bool V>
struct vector
{
	template <typename U, unsigned M, bool W>
	struct rebind
	 : vector<U,M,W>
	{ };

	typedef vector type;
	typedef scalar<T, N, V> scalar_type;

	typedef typename vect::has_vect_data<T, N, V>::type
		is_vectorized;

	typedef T value_type;

	typedef typename vect::data<T, N, V>::type _vT;
	typedef _vT data_type;

	typedef const vector& _cpT;
	typedef const scalar<T, N, V>& _cspT;

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
		bool W,
		typename = typename meta::enable_if<
			(!meta::is_same<T, P>::value || (N != M) || (V != W))
		>::type
	>
	static constexpr inline
	vector from(const vector<P, M, W>& v, T d = T(0))
	noexcept
	{
		return vector{vect::cast<P, M, W, T, N, V>::apply(v._v, d)};
	}

	template <typename P, unsigned M, bool W>
	static constexpr inline
	vector from(const vector<P, M, W>& v, const vector<T, N-M, W>& u)
	noexcept
	{
		return vector{vect::cast<P, M, W, T, N, V>::apply(v._v, u._v)};
	}

	template <
		unsigned ... I,
		typename P,
		unsigned M,
		bool W,
		typename = typename meta::enable_if<
			(sizeof...(I) == N)
		>::type
	>
	static constexpr inline
	vector from(const vector<P, M, W>& v)
	noexcept
	{
		return vector{{T(v._v[I])...}};
	}

	static inline
	vector from(const T* dt, std::size_t sz)
	noexcept
	{
		return vector{vect::from_array<T,N,V>::apply(dt, sz)};
	}

	static inline
	vector from(const T* dt, std::size_t sz, T fv)
	noexcept
	{
		return vector{vect::from_saafv<T,N,V>::apply(dt, sz, fv)};
	}

	static inline
	vector zero(void)
	noexcept
	{
		return vector{vect::fill<T,N,V>::apply(T(0))};
	}

	static inline
	vector fill(T v)
	noexcept
	{
		return vector{vect::fill<T,N,V>::apply(v)};
	}

	template <unsigned I>
	static inline
	vector axis(void)
	noexcept
	{
		return vector{vect::axis<T,N,I,V>::apply(T(1))};
	}

	template <unsigned I>
	static inline
	vector axis(T v)
	noexcept
	{
		return vector{vect::axis<T,N,I,V>::apply(v)};
	}

	static inline
	vector axis(unsigned i, T v)
	noexcept
	{
		vector r{vect::fill<T,N,V>::apply(T(0))};
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

	template <
		unsigned M = N,
		typename = typename meta::enable_if<M == 1, void>::type
	>
	constexpr inline
	explicit
	operator T(void) const
	noexcept
	{
		return _v[0];
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

	template <unsigned ... I>
	constexpr inline
	typename meta::enable_if<
		has_swizzle<vector<T,N,V>, I...>::value,
		vector<T, sizeof...(I), V>
	>::type
	swizzle_by(swizzle_mask<T, I...> m) const
	noexcept
	{
		return {{m.template get<I,T>(_v)...}};
	}

	template <unsigned ... I>
	constexpr inline
	typename meta::enable_if<
		has_swizzle<vector<T,N,V>, I...>::value,
		vector<T, sizeof...(I), V>
	>::type
	swizzle(T c = T(0)) const
	noexcept
	{
		return this->swizzle_by(swizzle_mask<T, I...>{c});
	}

#if !defined(EAGINE_NO_MATH_VECTOR_SWIZZLES) || !EAGINE_NO_MATH_VECTOR_SWIZZLES
#include <eagine/math/vector_swizzles.ipp>
#endif

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

	template <typename Vec = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::is_vectorized::value, Vec>::type
	operator * (_cspT c, _cpT a)
	noexcept
	{
		return vector{c._v*a._v};
	}

	template <typename Vec = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::is_vectorized::value, Vec>::type
	operator * (_cpT a, _cspT c)
	noexcept
	{
		return vector{a._v*c._v};
	}

	template <typename Vec = vector>
	typename meta::enable_if<scalar_type::is_vectorized::value, Vec>::type&
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
		return vector{a._v*vect::fill<T, N, V>::apply(c)};
	}

	friend constexpr
	vector operator * (_cpT a, T c)
	noexcept
	{
		return vector{a._v*vect::fill<T, N, V>::apply(c)};
	}

	vector& operator *= (T c)
	noexcept
	{
		_v = _v*vect::fill<T, N, V>::apply(c);
		return *this;
	}

	friend constexpr
	vector operator / (_cpT a, _cpT b)
	noexcept
	{
		return vector{vect::sdiv<T, N, V>::apply(a._v, b._v)};
	}

	template <typename Vec = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::is_vectorized::value, Vec>::type
	operator / (_cspT c, _cpT a)
	noexcept
	{
		return vector{vect::sdiv<T, N, V>::apply(c._v, a._v)};
	}

	template <typename Vec = vector>
	friend constexpr
	typename meta::enable_if<scalar_type::is_vectorized::value, Vec>::type
	operator / (_cpT a, _cspT c)
	noexcept
	{
		return vector{vect::sdiv<T, N, V>::apply(a._v, c._v)};
	}

	friend constexpr
	vector operator / (_cpT a, T c)
	noexcept
	{
		return vector{vect::sdiv<T, N, V>::apply(
			a._v,
			vect::fill<T, N, V>::apply(c)
		)};
	}

	friend constexpr
	vector operator / (T c, _cpT a)
	noexcept
	{
		return vector{vect::sdiv<T, N, V>::apply(
			vect::fill<T, N, V>::apply(c),
			a._v
		)};
	}

	friend
	bool operator == (_cpT a, _cpT b)
	noexcept
	{
		return vect::equal<T,N,V>::apply(a._v, b._v);
	}

	friend
	bool operator != (_cpT a, _cpT b)
	noexcept
	{
		return !vect::equal<T,N,V>::apply(a._v, b._v);
	}

	friend
	constexpr vector hsum(_cpT a)
	noexcept
	{
		return vector{vect::hsum<T, N, V>::apply(a._v)};
	}

	friend constexpr
	scalar<T, N, V> _dot(_cpT a, _cpT b, meta::true_type)
	noexcept
	{
		return scalar<T, N, V>{vect::hsum<T, N, V>::apply(a._v * b._v)};
	}

	friend constexpr
	scalar<T, N, V> _dot(_cpT a, _cpT b, meta::false_type)
	noexcept
	{
		return scalar<T, N, V>{vect::esum<T, N, V>::apply(a._v * b._v)};
	}

	friend constexpr
	scalar<T, N, V> dot(_cpT a, _cpT b)
	noexcept
	{
		return _dot(a, b, is_vectorized());
	}

	friend constexpr
	scalar<T, N, V> _mag(_cpT a, meta::true_type)
	noexcept
	{
		return scalar<T, N, V>{
			vect::sqrt<T, N, V>::apply(
				vect::hsum<T, N, V>::apply(a._v * a._v)
			)
		};
	}

	friend constexpr
	scalar<T, N, V> _mag(_cpT a, meta::false_type)
	noexcept
	{
		using std::sqrt;
		return scalar<T, N, V>
			{T(sqrt(vect::esum<T, N, V>::apply(a._v * a._v)))};
	}

	friend constexpr
	scalar<T, N, V> magnitude(_cpT a)
	noexcept
	{
		return _mag(a, is_vectorized());
	}

	friend constexpr
	scalar<T, N, V> length(_cpT a)
	noexcept
	{
		return magnitude(a);
	}

	friend constexpr
	scalar<T, N, V> distance(_cpT a, _cpT b)
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
			{T(acos(vect::esum<T, N, V>::apply(a._v * b._v)))};
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
template <unsigned I, typename T, unsigned N, bool V>
static constexpr inline
typename meta::enable_if<(I<N), T>::type
get(const vector<T,N,V>& v)
noexcept
{
	return v._v[I];
}

// get(vector) run-time
template <typename T, unsigned N, bool V>
static constexpr inline
T get(const vector<T,N,V>& v, unsigned i)
noexcept
{
	return v._v[i];
}

// set(vector, v)
template <unsigned I, typename T, unsigned N, bool V>
static inline
typename meta::enable_if<(I<N)>::type
set(vector<T,N,V>& v, T e)
noexcept
{
	v._v[I] = e;
}

// set(vector, v) run-time
template <typename T, unsigned N, bool V>
static inline
void
set(vector<T,N,V>& v, unsigned i, T e)
noexcept
{
	v._v[i] = e;
}

// shuffle_mask
using vect::shuffle_mask;

// shuffle
template <int ... I, typename T, unsigned N, bool V>
static inline
typename meta::enable_if<
	meta::max_constant<int, I...>::value < N,
	vector<T, N, V>
>::type
shuffle(
	const vector<T, N, V>& v,
	shuffle_mask<I...> m = shuffle_mask<I...>()
) noexcept
{
	return {vect::shuffle<T, N, V>::apply(v._v, m)};
}

// shuffle
template <int ... I, typename T, unsigned N, bool V>
static inline
typename meta::enable_if<
	meta::max_constant<int, I...>::value < 2*N,
	vector<T, N, V>
>::type
shuffle(
	const vector<T, N, V>& v1,
	const vector<T, N, V>& v2,
	shuffle_mask<I...> m = shuffle_mask<I...>()
) noexcept
{
	return vector<T,N,V>
		{vect::shuffle2<T, N, V>::apply(v1._v, v2._v, m)};
}

// perpendicular
template <typename T, bool V>
static inline
vector<T, 2, V>
perpendicular(const vector<T, 2, V>& a)
noexcept
{
	return vector<T, 2, V>
		{{-a._v[1], a._v[0]}};
}

// cross
template <typename T, bool V>
static inline
vector<T, 3, V>
cross(const vector<T, 3, V>& a, const vector<T, 3, V>& b)
noexcept
{
	typedef vect::shuffle<T, 3, V> _sh;
	return vector<T, 3, V>{
		_sh::template apply<1,2,0>(a._v)*
		_sh::template apply<2,0,1>(b._v)-
		_sh::template apply<2,0,1>(a._v)*
		_sh::template apply<1,2,0>(b._v)
	};
}

// composite_data_ref<vector>
template <typename T, unsigned N, bool V>
class composite_data_ref<vector<T, N, V>>
 : public base::crtp_derived_memory_range<
	composite_data_ref<vector<T, N, V>>,
	base::typed_memory_range<const T>,
	const T
>
{
private:
	vect::array_ref<T, N, V> _ar;
public:
	composite_data_ref(const vector<T, N, V>& v)
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
};

// data
template <typename T, unsigned N, bool V>
static inline
composite_data_ref<vector<T, N, V>> data(const vector<T, N, V>& v)
noexcept
{
	return v;
}

} // namespace math
} // namespace eagine

#endif //include guard

