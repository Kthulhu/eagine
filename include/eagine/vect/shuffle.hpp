/**
 *  @file eagine/vect/shuffle.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_SHUFFLE_1308281038_HPP
#define EAGINE_VECT_SHUFFLE_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <int ... I>
struct shuffle_mask
{ };

template <typename T, unsigned N>
struct shuffle
{
	typedef typename data<T, N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	template <int ... I>
	static inline
	_dT apply(
		_dpT v,
		shuffle_mask<I...> = {}
	) noexcept
	{
#if defined(__clang__) && __SSE__
		return __builtin_shufflevector(v,v, I...);
#elif defined(__GNUC__) && __SSE__
		typedef typename data<unsigned,N>::type _mT;
		return __builtin_shuffle(v, _mT{I...});
#else
		return typename data<T, N>::type{v[I]...};
#endif
	}
};

template <typename T, unsigned N>
struct shuffle2
{
	typedef typename data<T, N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	template <int ... I>
	static inline
	_dT apply(
		_dpT v1,
		_dpT v2,
		shuffle_mask<I...> = {}
	) noexcept
	{
#if defined(__clang__) && __SSE__
		return __builtin_shufflevector(v1,v2, I...);
#elif defined(__GNUC__) && __SSE__
		typedef typename data<unsigned,N>::type _mT;
		return __builtin_shuffle(v1, v2, _mT{I...});
#else
		return typename data<T, N>::type{
			I<0?T(0):(unsigned(I)<N? v1[I]: v2[I%N])...
		};
#endif
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

