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

namespace EAGine {
namespace vect {

template <unsigned ... I>
struct shuffle_mask
{ };

template <typename T, unsigned N>
struct shuffle
{
	typedef typename data<T, N>::type _dT;

	template <unsigned ... I>
	static inline
	_dT apply(
		const _dT& v,
		shuffle_mask<I...> = {}
	)
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

	template <unsigned ... I>
	static inline
	_dT apply(
		const _dT& v1,
		const _dT& v2,
		shuffle_mask<I...> = {}
	)
	{
#if defined(__clang__) && __SSE__
		return __builtin_shufflevector(v1,v2, I...);
#elif defined(__GNUC__) && __SSE__
		typedef typename data<unsigned,N>::type _mT;
		return __builtin_shuffle(v1, v2, _mT{I...});
#else
		return typename data<T, N>::type{
			(I<N? v1[I]: v2[I%N])...
		};
#endif
	}
};

} // namespace vect
} // namespace EAGine

#endif //include guard

