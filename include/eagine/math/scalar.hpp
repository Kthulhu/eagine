/**
 *  @file eagine/math/scalar.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_SCALAR_1308281038_HPP
#define EAGINE_MATH_SCALAR_1308281038_HPP

#include <eagine/vect/abs.hpp>
#include <eagine/vect/fill.hpp>
#include <eagine/vect/cast.hpp>
#include <eagine/vect/minmax.hpp>
#include <eagine/vect/compare.hpp>
#include <eagine/meta/identity.hpp>
#include <eagine/math/fwd.hpp>
#include <eagine/math/difference.hpp>
#include <cmath>

namespace eagine {
namespace math {

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

// difference_op
template <typename T, unsigned N, bool V>
struct difference_op<scalar<T, N, V>>
{
	typedef scalar<T, N, V> data_type;
	data_type _l, _r;

	typedef typename scalar<T, N, V>::data_type _vT;

	static constexpr inline
	T _diff(_vT a, meta::false_type)
	noexcept
	{
		return difference_op<T>::_abs(a);
	}

	static constexpr inline
	T _diff(_vT a, meta::true_type)
	noexcept
	{
		return vect::hmax<T, N, V>::apply(
			vect::abs<T, N, V>::apply(a)
		)[0];
	}

	static constexpr inline
	T norm(data_type l, data_type r)
	noexcept
	{
		return difference_op<T>::_max(
			_diff(l._v),
			_diff(r._v)
		);
	}

	constexpr inline
	T get(void) const
	noexcept
	{
		return _diff(
			_l.v-_r._v,
			typename scalar<T, N, V>::is_vectorized()
		);
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

