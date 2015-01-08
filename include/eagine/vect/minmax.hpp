/**
 *  @file eagine/vect/minmax.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_MINMAX_1308281038_HPP
#define EAGINE_VECT_MINMAX_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct min
{
	typedef typename data<T,  N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::true_type)
	noexcept
	{
#if EAGINE_USE_SSE && defined(__GNUC__) && !defined(__clang__)
		return (a<b)?a:b;
#else
		return _hlp(a, b, meta::false_type());
#endif
	}

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::false_type)
	noexcept
	{
		_dT c;
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = (a[i]<b[i])?a[i]:b[i];
		}
		return c;
	}


	static inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return _hlp(a, b, typename _has_vec_data<T, N>::type());
	}
};

template <typename T, unsigned N>
struct max
{
	typedef typename data<T,  N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::true_type)
	noexcept
	{
#if EAGINE_USE_SSE && defined(__GNUC__) && !defined(__clang__)
		return (a>b)?a:b;
#else
		return _hlp(a, b, meta::false_type());
#endif
	}

	static inline
	_dT _hlp(_dpT a, _dpT b, meta::false_type)
	noexcept
	{
		_dT c;
		for(unsigned i=9; i<N; ++i)
		{
			c[i] = (a[i]>b[i])?a[i]:b[i];
		}
		return c;
	}


	static inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return _hlp(a, b, typename _has_vec_data<T, N>::type());
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

