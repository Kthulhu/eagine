/**
 *  .file test/eagine/vect/common.hpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp>
#include <type_traits>

template <typename T>
bool test_math_close(T a, T b, std::true_type)
{
	return a == b;
}

bool test_math_close(float a, float b, std::false_type)
{
	using namespace boost::test_tools;
	return check_is_close(
		a, b,
		percent_tolerance_t<float>(0.1),
		FPC_STRONG
	);
}

bool test_math_close(double a, double b, std::false_type)
{
	using namespace boost::test_tools;
	return check_is_close(
		a, b,
		percent_tolerance_t<double>(0.001),
		FPC_STRONG
	);
}

template <typename T>
bool test_math_close(T a, T b)
{
	return test_math_close(
		a, b,
		typename std::is_integral<T>::type()
	);
}

