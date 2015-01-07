/**
 *  .file test/eagine/vect/minmax.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_minmax
#include <boost/test/unit_test.hpp>

#include <eagine/vect/minmax.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_minmax)

template <typename T, unsigned N>
void test_vect_minmax_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N>::type u;
		typename eagine::vect::data<T, N>::type v;

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
			v[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N>::type min =
			eagine::vect::min<T, N>::apply(u, v);
		typename eagine::vect::data<T, N>::type max =
			eagine::vect::max<T, N>::apply(u, v);

		for(unsigned i=0; i<N; ++i)
		{
			BOOST_ASSERT(min[i] == (u[i]<v[i])?u[i]:v[i]);
			BOOST_ASSERT(max[i] == (u[i]>v[i])?u[i]:v[i]);
		}
	}
}

template <typename T>
void test_vect_minmax_apply_t(void)
{
	test_vect_minmax_apply<T, 2>();
	test_vect_minmax_apply<T, 3>();
	test_vect_minmax_apply<T, 4>();
	test_vect_minmax_apply<T, 5>();
	test_vect_minmax_apply<T, 6>();
	test_vect_minmax_apply<T, 7>();
	test_vect_minmax_apply<T, 8>();

	test_vect_minmax_apply<T, 11>();
	test_vect_minmax_apply<T, 17>();
	test_vect_minmax_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_minmax_apply_int)
{
	test_vect_minmax_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_minmax_apply_float)
{
	test_vect_minmax_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_minmax_apply_double)
{
	test_vect_minmax_apply_t<double>();
}

BOOST_AUTO_TEST_SUITE_END()
