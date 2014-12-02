/**
 *  .file test/eagine/vect/fill.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_fill
#include <boost/test/unit_test.hpp>

#include <eagine/vect/fill.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_fill)

template <typename T, unsigned N>
void test_vect_fill_apply(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a = std::rand();

		typename eagine::vect::data<T, N>::type v =
			eagine::vect::fill<T, N>::apply(a);

		for(unsigned i=0; i<N; ++i)
		{
			BOOST_ASSERT(v[i] == a);
		}
	}
}

BOOST_AUTO_TEST_CASE(vect_fill_apply)
{

	test_vect_fill_apply<int, 2>();
	test_vect_fill_apply<int, 3>();
	test_vect_fill_apply<int, 4>();
	test_vect_fill_apply<int, 5>();
	test_vect_fill_apply<int, 8>();

	test_vect_fill_apply<float, 2>();
	test_vect_fill_apply<float, 3>();
	test_vect_fill_apply<float, 4>();
	test_vect_fill_apply<float, 5>();
	test_vect_fill_apply<float, 8>();

	test_vect_fill_apply<double, 2>();
	test_vect_fill_apply<double, 3>();
	test_vect_fill_apply<double, 4>();
	test_vect_fill_apply<double, 5>();
	test_vect_fill_apply<double, 8>();
}


BOOST_AUTO_TEST_SUITE_END()
