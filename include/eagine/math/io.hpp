/**
 *  @file eagine/math/io.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_IO_1308281038_HPP
#define EAGINE_MATH_IO_1308281038_HPP

#include <eagine/math/vector.hpp>
#include <eagine/math/angle.hpp>
#include <eagine/math/quaternion.hpp>
#include <iostream>

namespace EAGine {
namespace math {

template <typename T, unsigned N>
inline
std::ostream&
operator << (std::ostream& o, const vector<T,N>& v)
{
	o << "[" << v._v[0];
	for(unsigned i=1; i<N; ++i)
	{
		o << ", " << v._v[i];
	}
	return o << "]";
}

template <typename T>
inline
std::ostream&
operator << (std::ostream& o, const quaternion<T>& q)
{
	o << "{" << q._v[0];
	for(unsigned i=1; i<4; ++i)
	{
		o << ", " << q._v[i];
	}
	return o << "}";
}

template <typename T>
inline
std::ostream&
operator << (std::ostream& o, const angle<T>& v)
{
	return o << "<" << v._v << "> rad";
}

} // namespace math
} // namespace EAGine

#endif //include guard

