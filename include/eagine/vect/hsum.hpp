/**
 *  @file eagine/vect/hsum.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_HSUM_1308281038_HPP
#define EAGINE_VECT_HSUM_1308281038_HPP

#include <eagine/vect/shuffle.hpp>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct hsum
{
	typedef typename data<T,  N>::type _dT;

	static _dT apply(_dT v)
	{
		for(unsigned i=1; i<N; ++i)
		{
			v[i] += v[i-1];
		}
		for(unsigned i=N-1; i>0; --i)
		{
			v[i-1] = v[i];
		}
		return v;
	}
};


template <typename T>
struct hsum<T, 1>
{
	typedef typename data<T,  1>::type _dT;

	static constexpr inline
	_dT apply(_dT v)
	{
		return v;
	}
};

template <typename T>
struct hsum<T, 2>
{
	typedef typename data<T,  2>::type _dT;
	typedef shuffle<T, 2> _sh;

	static constexpr inline
	_dT apply(_dT v)
	{
		return v + _sh::template apply<1,0>(v);
	}
};

#if (defined(__GNUC__) || defined(__clang__)) && __SSE__

template <typename T>
struct hsum<T, 3>
{
	typedef typename data<T,  3>::type _dT;
	typedef shuffle<T, 3> _sh;
	
	static inline
	_dT _hlp(_dT v, _dT t)
	{
		return t + _sh::template apply<2,0,1>(v);
	}

	static constexpr inline
	_dT apply(_dT v)
	{
		return _hlp(v, v + _sh::template apply<2,0,1>(v));
	}
};

template <typename T>
struct hsum<T, 4>
{
	typedef typename data<T,  4>::type _dT;
	typedef shuffle<T, 4> _sh;
	
	static constexpr inline
	_dT _hlp(_dT v)
	{
		return v + _sh::template apply<2,3,0,1>(v);
	}
	
	static constexpr inline
	_dT apply(_dT v)
	{
		return _hlp(v + _sh::template apply<1,0,3,2>(v));
	}
};
#endif

} // namespace vect
} // namespace EAGine

#endif //include guard
