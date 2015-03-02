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
#include <type_traits>

template <typename T>
inline
bool test_math_close(T a, T b, std::true_type)
{
	return a == b;
}

inline
bool test_math_close(float a, float b, std::false_type)
{
	using namespace boost::test_tools;

	float ofs = (a==0)?((b<0)?-10:10):((a<0)?-10:10);

	return check_is_close(
		a+ofs, b+ofs,
		percent_tolerance_t<float>(0.1f),
		FPC_STRONG
	);
}

inline
bool test_math_close(double a, double b, std::false_type)
{
	using namespace boost::test_tools;

	double ofs = (a==0)?((b<0)?-10:10):((a<0)?-10:10);

	return check_is_close(
		a+ofs, b+ofs,
		percent_tolerance_t<double>(0.001),
		FPC_STRONG
	);
}

template <typename T>
inline
bool test_math_close(T a, T b)
{
	return test_math_close(
		a, b,
		typename std::is_integral<T>::type()
	);
}

