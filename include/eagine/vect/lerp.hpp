/**
 *  @file eagine/vect/lerp.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_LERP_1308281038_HPP
#define EAGINE_VECT_LERP_1308281038_HPP

#include <eagine/vect/fill.hpp>

namespace EAGine {
namespace vect {

template <typename T, unsigned N>
struct lerp
{
	typedef typename data<T, N>::type _dT;

	_dT operator()(const _dT& a, const _dT& b, T t) const
	{
		typedef fill<T, N> _fill;
		return	a*_fill::apply(1-t)+
			b*_fill::apply(t);
	}
};

} // namespace vect
} // namespace EAGine

#endif //include guard

