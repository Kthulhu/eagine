/**
 *  @file eagine/vect/esum.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_VECT_ESUM_1308281038_HPP
#define EAGINE_VECT_ESUM_1308281038_HPP

#include <eagine/vect/data.hpp>

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

#if defined(__GNUC__)

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
	T apply(typename data<T,2>::type v)
	{
		return v[0]+v[1];
	}
};

template <typename T>
struct esum<T, 3>
{
	static constexpr inline
	T apply(typename data<T,3>::type v)
	{
		return v[0]+v[1]+v[2];
	}
};

template <typename T>
struct esum<T, 4>
{
	static constexpr inline
	T apply(typename data<T,4>::type v)
	{
		return v[0]+v[1]+v[2]+v[3];
	}
};
#endif

} // namespace vect
} // namespace EAGine

#endif //include guard

