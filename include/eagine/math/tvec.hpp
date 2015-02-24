/**
 *  @file eagine/math/tvec.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
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
template <typename T, unsigned N>
struct tvec : vector<T, N>
{
	typedef vector<T, N> _base;

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

	inline
	tvec(const T* d, unsigned n)
	noexcept
	 : _base(_base::from(d, n))
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

	template <typename P, unsigned M>
	constexpr inline
	tvec(const vector<P, M>& v, T d)
	noexcept
	 : _base(_base::from(v, d))
	{ }

	template <
		typename P,
		unsigned M,
		typename ... R,
		typename = typename meta::enable_if<
			(sizeof...(R) > 1) && (M+sizeof...(R) == N)
		>::type
	>
	constexpr inline
	tvec(const vector<P, M>& v, R&& ... r)
	noexcept
	 : _base(_base::from(
		v,
		vector<T, N-M>::make(std::forward<R>(r)...)
	))
	{ }

	template <typename P, unsigned M>
	constexpr inline
	tvec(const vector<P, M>& v, const vector<T, N-M>& w)
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
template <typename T, unsigned N, unsigned I>
struct taxis : vector<T, N>
{
	typedef vector<T, N> _base;

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

