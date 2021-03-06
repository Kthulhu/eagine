/**
 *  @file eagine/vect/compare.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_COMPARE_1308281038_HPP
#define EAGINE_VECT_COMPARE_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct equal
{
	typedef typename data_param<T, N, V>::type _dpT;

	static
	bool apply(_dpT a, _dpT b)
	noexcept
	{
		bool result = true;
		for(unsigned i=0; i<N; ++i)
		{
			result &= (a[i] == b[i]);
		}
		return result;
	}
};

template <typename T, unsigned N, bool V>
struct notequal
{
	typedef typename data_param<T, N, V>::type _dpT;

	static
	bool apply(_dpT a, _dpT b)
	noexcept
	{
		bool result = false;
		for(unsigned i=0; i<N; ++i)
		{
			result |= (a[i] != b[i]);
		}
		return result;
	}
};

// TODO: some optimizations ?
// TODO: math::difference

} // namespace vect
} // namespace eagine

#endif //include guard

