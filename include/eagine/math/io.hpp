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
#include <eagine/math/matrix.hpp>
#include <iostream>

namespace eagine {
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

template <typename T, unsigned R, unsigned C>
inline
std::ostream&
operator << (std::ostream& o, const matrix<T,R,C,true>& m)
{
	o << "|R0[" << m._v[0][0];

	for(unsigned c=1; c<C; ++c)
	{
		o << ", " << m._v[0][c];
	}
	o << "]";

	for(unsigned r=1; r<R; ++r)
	{
		o << ",R" << r << "[" << m._v[r][0];
		for(unsigned c=1; c<C; ++c)
		{
			o << ", " << m._v[r][c];
		}
		o << "]";
	}
	return o << "|";
}

template <typename T, unsigned R, unsigned C>
inline
std::ostream&
operator << (std::ostream& o, const matrix<T,R,C,false>& m)
{
	o << "|C0[" << m._v[0][0];

	for(unsigned r=1; r<R; ++r)
	{
		o << ", " << m._v[0][r];
	}
	o << "]";

	for(unsigned c=1; c<C; ++c)
	{
		o << ",C" << c << "[" << m._v[c][0];
		for(unsigned r=1; r<R; ++r)
		{
			o << ", " << m._v[c][r];
		}
		o << "]";
	}
	return o << "|";
}

} // namespace math
} // namespace eagine

#endif //include guard

