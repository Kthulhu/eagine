/**
 *  @file eagine/math/inverse.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_INVERSE_1308281038_HPP
#define EAGINE_MATH_INVERSE_1308281038_HPP

#include <eagine/math/matrix.hpp>
#include <eagine/base/optional.hpp>
#include <utility>

namespace eagine {
namespace math {

// inverse matrix
template <typename T, unsigned R, unsigned C>
inline
base::optional<matrix<T,R,C,true>>
inverse(matrix<T,R,C,true> m)
{
	base::optional<matrix<T,R,C,true>> r;

	matrix<T,R,C,true> i = identity<matrix<T,R,C,true>>()();
	if(gauss_jordan(m, i))
	{
		r = i;
	}

	return r;
}

} // namespace math
} // namespace eagine

#endif //include guard

