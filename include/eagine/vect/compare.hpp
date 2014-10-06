/**
 *  @file eagine/vect/compare.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_COMPARE_1308281038_HPP
#define EAGINE_VECT_COMPARE_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct equal
{
	typedef typename data<T,  N>::type _dT;

	static bool apply(const _dT& a, const _dT& b)
	{
		for(unsigned i=0; i<N; ++i)
		{
			if(a[i] != b[i])
				return false;
		}
		return true;
	}
};

// TODO: some optimizations ?

} // namespace vect
} // namespace EAGine

#endif //include guard

