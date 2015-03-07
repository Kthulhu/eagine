/**
 *  @file eagine/vect/sqrt.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_SQRT_1308281038_HPP
#define EAGINE_VECT_SQRT_1308281038_HPP

#include <eagine/vect/shuffle.hpp>
#include <cmath>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct sqrt
{
	typedef typename data<T, N>::type _dT;

	static
	_dT apply(_dT v)
	noexcept
	{
		using std::sqrt;
		for(unsigned i=0; i<N; ++i)
		{
			v[i] = sqrt(v[i]);
		}
		return v;
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

