/**
 *  @file eagine/vect/abs.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_ABS_1308281038_HPP
#define EAGINE_VECT_ABS_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct abs
{
	typedef typename data<T, N, V>::type _dT;
	typedef typename data_param<T, N, V>::type _dpT;

	static inline
	_dT _hlp(_dpT a, meta::true_type)
	noexcept
	{
		// TODO
		return _hlp(a, meta::false_type());
	}

	static inline
	_dT _hlp(_dpT a, meta::false_type)
	noexcept
	{
		_dT c = {};
		for(unsigned i=0; i<N; ++i)
		{
			c[i] = a[i]<0?-a[i]:a[i];
		}
		return c;
	}


	static inline
	_dT apply(_dpT a)
	noexcept
	{
		return _hlp(a, has_vect_data<T, N, V>());
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

