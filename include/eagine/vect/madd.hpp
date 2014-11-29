/**
 *  @file eagine/vect/madd.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_MADD_1308281038_HPP
#define EAGINE_VECT_MADD_1308281038_HPP

#include <eagine/vect/shuffle.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct madd
{
	typedef typename data<T,  N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	static
	_dT apply(_dpT a, _dpT b, _dpT c)
	noexcept
	{
		return a*b+c;
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

