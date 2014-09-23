/**
 *  @file eagine/vect/esum.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_VECT_ESUM_1308281038_HPP
#define EAGINE_VECT_ESUM_1308281038_HPP

#include <eagine/vect/shuffle.hpp>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct esum
{
	static
	T apply(const typename data<T,N>::type& v)
	{
		T r(0);
		for(unsigned i=0; i<N; ++i)
		{
			r += v[i];
		}
		return r;
	}
};


template <typename T>
struct esum<T, 1>
{
	static constexpr inline
	T apply(typename data<T,1>::type v)
	{
		return v[0];
	}
};

template <typename T>
struct esum<T, 2>
{
	static constexpr inline
	T apply(const typename data<T,2>::type& v)
	{
		return v[0]+v[1];
	}
};

#if (defined(__GNUC__) || defined(__clang__)) && __SSE__

template <typename T>
struct esum<T, 3>
{
	typedef typename data<T,  3>::type _dT;
	typedef shuffle<T,3> _sh;
	
	static inline
	_dT _hlp(_dT v, _dT t)
	{
		return t + _sh::template apply<2,0,1>(v);
	}

	static constexpr inline
	T apply(const typename data<T,3>::type& v)
	{
		return _hlp(v, v + _sh::template apply<2,0,1>(v))[0];
	}
};

template <typename T>
struct esum<T, 4>
{
	typedef typename data<T,  4>::type _dT;
	typedef shuffle<T,4> _sh;
	
	static inline
	_dT _hlp(_dT v)
	{
		return v + _sh::template apply<2,3,0,1>(v);
	}
	
	static inline
	T apply(_dT v)
	{
		return _hlp(v + _sh::template apply<1,0,3,2>(v))[0];
	}
};
#endif

} // namespace vect
} // namespace EAGine

#endif //include guard

