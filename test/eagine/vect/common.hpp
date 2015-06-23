/**
 *  .file test/eagine/vect/common.hpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp>
#include <eagine/math/difference.hpp>

template <typename T>
inline
T test_vect_close_eps(T*)
{
	return T(0);
}

inline
float test_vect_close_eps(float*)
{
	return 0.1f;
}

inline
double test_vect_close_eps(double*)
{
	return 0.001;
}

template <typename T>
inline
bool test_vect_data_close(T a, T b)
{
	using eagine::math::to;
	using eagine::math::cmp::less_equal;
	using eagine::math::cmp::relative;
	return (a <<to>> b <<less_equal>> relative(test_vect_close_eps(&a)));
}
