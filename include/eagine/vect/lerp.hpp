/**
 *  @file eagine/vect/lerp.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_LERP_1308281038_HPP
#define EAGINE_VECT_LERP_1308281038_HPP

#include <eagine/vect/fill.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N, bool V>
struct lerp
{
	typedef typename data<T, N, V>::type _dT;
	typedef typename data_param<T, N, V>::type _dpT;

	_dT operator()(_dpT a, _dpT b, T t) const
	noexcept
	{
		typedef fill<T, N, V> _fill;
		return	a*_fill::apply(1-t)+
			b*_fill::apply(t);
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

