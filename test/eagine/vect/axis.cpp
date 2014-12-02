/**
 *  .file test/eagine/vect/axis.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_axis
#include <boost/test/unit_test.hpp>

#include <eagine/vect/axis.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_axis)

template <typename T, unsigned I, unsigned N>
void test_vect_axis_apply(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a = std::rand();

		typename eagine::vect::data<T, N>::type v =
			eagine::vect::axis<T, N, I>::apply(a);

		for(unsigned i=0; i<N; ++i)
		{
			BOOST_ASSERT(v[i] == (i==I?a:0));
		}
	}
}

BOOST_AUTO_TEST_CASE(vect_axis_apply)
{

	test_vect_axis_apply<int, 0, 2>();
	test_vect_axis_apply<int, 1, 2>();

	test_vect_axis_apply<int, 0, 3>();
	test_vect_axis_apply<int, 1, 3>();
	test_vect_axis_apply<int, 2, 3>();

	test_vect_axis_apply<int, 0, 4>();
	test_vect_axis_apply<int, 1, 4>();
	test_vect_axis_apply<int, 2, 4>();
	test_vect_axis_apply<int, 3, 4>();

	test_vect_axis_apply<int, 0, 5>();
	test_vect_axis_apply<int, 1, 5>();
	test_vect_axis_apply<int, 2, 5>();
	test_vect_axis_apply<int, 3, 5>();
	test_vect_axis_apply<int, 4, 5>();

	test_vect_axis_apply<int, 0, 8>();
	test_vect_axis_apply<int, 1, 8>();
	test_vect_axis_apply<int, 2, 8>();
	test_vect_axis_apply<int, 3, 8>();
	test_vect_axis_apply<int, 4, 8>();
	test_vect_axis_apply<int, 5, 8>();
	test_vect_axis_apply<int, 6, 8>();
	test_vect_axis_apply<int, 7, 8>();

	test_vect_axis_apply<float, 0, 2>();
	test_vect_axis_apply<float, 1, 2>();

	test_vect_axis_apply<float, 0, 3>();
	test_vect_axis_apply<float, 1, 3>();
	test_vect_axis_apply<float, 2, 3>();

	test_vect_axis_apply<float, 0, 4>();
	test_vect_axis_apply<float, 1, 4>();
	test_vect_axis_apply<float, 2, 4>();
	test_vect_axis_apply<float, 3, 4>();

	test_vect_axis_apply<float, 0, 5>();
	test_vect_axis_apply<float, 1, 5>();
	test_vect_axis_apply<float, 2, 5>();
	test_vect_axis_apply<float, 3, 5>();
	test_vect_axis_apply<float, 4, 5>();

	test_vect_axis_apply<float, 0, 8>();
	test_vect_axis_apply<float, 1, 8>();
	test_vect_axis_apply<float, 2, 8>();
	test_vect_axis_apply<float, 3, 8>();
	test_vect_axis_apply<float, 4, 8>();
	test_vect_axis_apply<float, 5, 8>();
	test_vect_axis_apply<float, 6, 8>();
	test_vect_axis_apply<float, 7, 8>();

	test_vect_axis_apply<double, 0, 2>();
	test_vect_axis_apply<double, 1, 2>();

	test_vect_axis_apply<double, 0, 3>();
	test_vect_axis_apply<double, 1, 3>();
	test_vect_axis_apply<double, 2, 3>();

	test_vect_axis_apply<double, 0, 4>();
	test_vect_axis_apply<double, 1, 4>();
	test_vect_axis_apply<double, 2, 4>();
	test_vect_axis_apply<double, 3, 4>();

	test_vect_axis_apply<double, 0, 5>();
	test_vect_axis_apply<double, 1, 5>();
	test_vect_axis_apply<double, 2, 5>();
	test_vect_axis_apply<double, 3, 5>();
	test_vect_axis_apply<double, 4, 5>();

	test_vect_axis_apply<double, 0, 8>();
	test_vect_axis_apply<double, 1, 8>();
	test_vect_axis_apply<double, 2, 8>();
	test_vect_axis_apply<double, 3, 8>();
	test_vect_axis_apply<double, 4, 8>();
	test_vect_axis_apply<double, 5, 8>();
	test_vect_axis_apply<double, 6, 8>();
	test_vect_axis_apply<double, 7, 8>();
}


BOOST_AUTO_TEST_SUITE_END()
