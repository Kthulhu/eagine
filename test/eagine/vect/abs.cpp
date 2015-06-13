/**
 *  .file test/eagine/vect/abs.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_abs
#include <boost/test/unit_test.hpp>

#include <eagine/vect/abs.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_minmax)

template <typename T, unsigned N, bool V>
void test_vect_abs_TNV(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N, V>::type u = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = (std::rand() / T(2)) - (std::rand() / T(1));
		}

		typename eagine::vect::data<T, N, V>::type v =
			eagine::vect::abs<T, N, V>::apply(u);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			using std::abs;
			BOOST_ASSERT(v[i] <<equal_to>> abs(u[i]));
		}
	}
}

template <typename T, bool V>
void test_vect_abs_TV(void)
{
	test_vect_abs_TNV<T, 1, V>();
	test_vect_abs_TNV<T, 2, V>();
	test_vect_abs_TNV<T, 3, V>();
	test_vect_abs_TNV<T, 4, V>();
	test_vect_abs_TNV<T, 5, V>();
	test_vect_abs_TNV<T, 6, V>();
	test_vect_abs_TNV<T, 7, V>();
	test_vect_abs_TNV<T, 8, V>();

	test_vect_abs_TNV<T, 11, V>();
	test_vect_abs_TNV<T, 17, V>();
	test_vect_abs_TNV<T, 23, V>();
}

template <typename T>
void test_vect_abs_T(void)
{
	test_vect_abs_TV<T, true>();
	test_vect_abs_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_abs_int)
{
	test_vect_abs_T<int>();
}

BOOST_AUTO_TEST_CASE(vect_abs_float)
{
	test_vect_abs_T<float>();
}

BOOST_AUTO_TEST_CASE(vect_abs_double)
{
	test_vect_abs_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
