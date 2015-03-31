/**
 *  .file test/eagine/vect/hsum.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_hsum
#include <boost/test/unit_test.hpp>

#include <eagine/vect/hsum.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_hsum)

template <typename T, unsigned N>
void test_vect_hsum_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		T s = T(0);

		typename eagine::vect::data<T, N>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			T n = std::rand() / T(2);
			v[i] = n;
			s += n;
		}

		typename eagine::vect::data<T, N>::type r =
			eagine::vect::hsum<T, N>::apply(v);

		for(unsigned i=0; i<N; ++i)
		{
			BOOST_ASSERT(test_vect_data_close(s, r[i]));
		}
	}
}

template <typename T>
void test_vect_hsum_apply_t(void)
{
	test_vect_hsum_apply<T, 2>();
	test_vect_hsum_apply<T, 3>();
	test_vect_hsum_apply<T, 4>();
	test_vect_hsum_apply<T, 5>();
	test_vect_hsum_apply<T, 6>();
	test_vect_hsum_apply<T, 7>();
	test_vect_hsum_apply<T, 8>();

	test_vect_hsum_apply<T, 11>();
	test_vect_hsum_apply<T, 17>();
	test_vect_hsum_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_hsum_apply_int)
{
	test_vect_hsum_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_hsum_apply_float)
{
	test_vect_hsum_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_hsum_apply_double)
{
	test_vect_hsum_apply_t<double>();
}

BOOST_AUTO_TEST_SUITE_END()
