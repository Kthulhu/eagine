/**
 *  @file eagine/math/tvec.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_TVEC_1412182141_HPP
#define EAGINE_MATH_TVEC_1412182141_HPP

#include <eagine/math/vector.hpp>
#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace math {

// tvec
template <typename T, unsigned N, bool V>
struct tvec : vector<T, N, V>
{
	template <typename U, unsigned M, bool W>
	struct rebind
	 : tvec<U,M,W>
	{ };

	typedef vector<T, N, V> _base;

	constexpr inline
	tvec(void)
	noexcept
	 : _base(_base::zero())
	{ }

	constexpr inline
	tvec(T v)
	noexcept
	 : _base(_base::fill(v))
	{ }

	constexpr inline
	tvec(const _base& v)
	noexcept
	 : _base(v)
	{ }

	constexpr inline
	tvec(const scalar<T, N, V>& s)
	noexcept
	 : _base{s._v}
	{ }

	inline
	tvec(const T (&d)[N])
	noexcept
	 : _base(_base::from(d, N))
	{ }

	inline
	tvec(const T* d, unsigned n)
	noexcept
	 : _base(_base::from(d, n))
	{ }

	inline
	tvec(const T* d, unsigned n, T v)
	noexcept
	 : _base(_base::from(d, n, v))
	{ }

	template <
		typename ... P,
		typename = typename meta::enable_if<
			(1+sizeof...(P) == N)
		>::type
	>
	constexpr inline
	tvec(T v, P&& ... p)
	noexcept
	 : _base(_base::make(v, std::forward<P>(p)...))
	{ }

	template <
		typename P,
		unsigned M,
		bool W,
		typename = typename meta::enable_if<
			!meta::is_same<P, T>::value ||
			!(M == N)
		>::type
	>
	constexpr inline
	tvec(const vector<P, M, W>& v)
	noexcept
	 : _base(_base::from(v))
	{ }

	template <typename P, unsigned M, bool W>
	constexpr inline
	tvec(const vector<P, M, W>& v, T d)
	noexcept
	 : _base(_base::from(v, d))
	{ }

	template <
		typename P,
		unsigned M,
		bool W,
		typename ... R,
		typename = typename meta::enable_if<
			(sizeof...(R) > 1) && (M+sizeof...(R) == N)
		>::type
	>
	constexpr inline
	tvec(const vector<P, M, W>& v, R&& ... r)
	noexcept
	 : _base(_base::from(
		v,
		vector<T, N-M, W>::make(std::forward<R>(r)...)
	))
	{ }

	template <typename P, unsigned M, bool W>
	constexpr inline
	tvec(const vector<P, M, W>& v, const vector<T, N-M, W>& w)
	noexcept
	 : _base(_base::from(v, w))
	{ }
};

// vec2
typedef tvec<float, 2> vec2;
// vec3
typedef tvec<float, 3> vec3;
// vec4
typedef tvec<float, 4> vec4;

// taxis
template <typename T, unsigned N, unsigned I, bool V = true>
struct taxis : vector<T, N, V>
{
	typedef vector<T, N, V> _base;

	static_assert(I<N, "");

	constexpr inline
	taxis(void)
	noexcept
	 : _base(_base::template axis<I>())
	{ }

	constexpr inline
	taxis(T v)
	noexcept
	 : _base(_base::template axis<I>(v))
	{ }
};

// axis2
template <unsigned I>
using axis2 = taxis<float, 2, I>;
// axis3
template <unsigned I>
using axis3 = taxis<float, 3, I>;
// axis4
template <unsigned I>
using axis4 = taxis<float, 4, I>;

} // namespace math
} // namespace eagine

#endif //include guard

