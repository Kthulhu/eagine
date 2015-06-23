/**
 *  .file test/eagine/math/close_to.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_close_to
#include <boost/test/unit_test.hpp>

#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>

BOOST_AUTO_TEST_SUITE(math_close_to)

template <typename T>
void test_math_difference_to_1(void)
{
	T a = T(std::rand()-std::rand())/T(11);

	using eagine::math::to;
	using namespace eagine::math::cmp;

	(a <<to>> a <<less_than>> epsilon());
	(a <<to>> T(0) <<less_equal>> exactly(a));
	(a <<to>> T(0) <<less_equal>> relative(1));
}

BOOST_AUTO_TEST_CASE(math_difference_to_1)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_difference_to_1<short>();
		test_math_difference_to_1<int>();
		test_math_difference_to_1<long>();
		test_math_difference_to_1<float>();
		test_math_difference_to_1<double>();
	}
}

template <typename T>
void test_math_difference_to_2(void)
{
	T a = T(std::rand()-std::rand())/T(11);
	T b = T(std::rand()-std::rand())/T(11);

	using std::abs;
	using eagine::math::to;
	using namespace eagine::math::cmp;

	BOOST_ASSERT(not((a <<to>> b) < T(abs(a-b))));
	BOOST_ASSERT(not((a <<to>> b) > T(abs(a-b))));
}

BOOST_AUTO_TEST_CASE(math_difference_to_2)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_difference_to_2<short>();
		test_math_difference_to_2<int>();
		test_math_difference_to_2<long>();
		test_math_difference_to_2<float>();
		test_math_difference_to_2<double>();
	}
}

template <typename T>
void test_math_equal_to_1(void)
{
	T a = T(std::rand());

	using eagine::math::equal_to;
	BOOST_ASSERT((a <<equal_to>> a));
	BOOST_ASSERT(equal_to(a, a));
}

BOOST_AUTO_TEST_CASE(math_equal_to_1)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_equal_to_1<short>();
		test_math_equal_to_1<int>();
		test_math_equal_to_1<long>();
		test_math_equal_to_1<float>();
		test_math_equal_to_1<double>();
	}
}

template <typename T>
void test_math_difference_less_equal_1(void)
{
	T a = T(std::rand() % int(std::numeric_limits<T>::max()/4));
	T b = -a;

	using eagine::math::to;
	using eagine::math::cmp::less_equal;
	using eagine::math::cmp::epsilon;
	using eagine::math::cmp::exactly;
	using eagine::math::cmp::relative;

	BOOST_ASSERT(a <<to>> a <<less_equal>> epsilon());
	BOOST_ASSERT(a <<to>> b <<less_equal>> exactly(3*a));
	BOOST_ASSERT(a <<to>> b <<less_equal>> relative(2));
}

BOOST_AUTO_TEST_CASE(math_difference_less_equal_1)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_difference_less_equal_1<short>();
		test_math_difference_less_equal_1<int>();
		test_math_difference_less_equal_1<long>();
		test_math_difference_less_equal_1<float>();
		test_math_difference_less_equal_1<double>();
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
