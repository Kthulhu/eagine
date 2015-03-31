/**
 *  .file test/eagine/vect/compare.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_compare
#include <boost/test/unit_test.hpp>

#include <eagine/vect/compare.hpp>
#include <eagine/math/close_to.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_compare)

template <typename T, unsigned N>
void test_vect_equal_apply_1(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N];

		typename eagine::vect::data<T, N>::type u = {}, v = {};

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(2);
			u[i] = a[i];
			v[i] = a[i];
		}

		typedef eagine::vect::equal<T, N> _equal;

		BOOST_ASSERT(_equal::apply(u, u));
		BOOST_ASSERT(_equal::apply(v, u));
		BOOST_ASSERT(_equal::apply(u, v));
		BOOST_ASSERT(_equal::apply(v, v));
	}
}

BOOST_AUTO_TEST_CASE(vect_data_equal_apply_1)
{
	test_vect_equal_apply_1<int, 2>();
	test_vect_equal_apply_1<int, 3>();
	test_vect_equal_apply_1<int, 4>();
	test_vect_equal_apply_1<int, 5>();
	test_vect_equal_apply_1<int, 7>();
	test_vect_equal_apply_1<int, 8>();
	test_vect_equal_apply_1<int,11>();
	test_vect_equal_apply_1<int,15>();
	test_vect_equal_apply_1<int,19>();

	test_vect_equal_apply_1<float, 2>();
	test_vect_equal_apply_1<float, 3>();
	test_vect_equal_apply_1<float, 4>();
	test_vect_equal_apply_1<float, 5>();
	test_vect_equal_apply_1<float, 6>();
	test_vect_equal_apply_1<float, 9>();
	test_vect_equal_apply_1<float,13>();
	test_vect_equal_apply_1<float,17>();
	test_vect_equal_apply_1<float,21>();

	test_vect_equal_apply_1<double, 2>();
	test_vect_equal_apply_1<double, 3>();
	test_vect_equal_apply_1<double, 4>();
	test_vect_equal_apply_1<double, 5>();
	test_vect_equal_apply_1<double, 8>();
	test_vect_equal_apply_1<double, 9>();
	test_vect_equal_apply_1<double,12>();
	test_vect_equal_apply_1<double,16>();
	test_vect_equal_apply_1<double,17>();
}

template <typename T, unsigned N>
void test_vect_equal_apply_2(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N], b[N];

		typename eagine::vect::data<T, N>::type u = {}, v = {};

		bool eq = true;

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand();
			u[i] = a[i];
			b[i] = std::rand();
			v[i] = b[i];

			using eagine::math::close_to;

			eq &= (a[i] <<close_to>> b[i]);
		}

		typedef eagine::vect::equal<T, N> _equal;

		BOOST_ASSERT(_equal::apply(u, v) == eq);
		BOOST_ASSERT(_equal::apply(v, u) == eq);
	}
}

BOOST_AUTO_TEST_CASE(vect_data_equal_apply_2)
{
	test_vect_equal_apply_2<int, 2>();
	test_vect_equal_apply_2<int, 3>();
	test_vect_equal_apply_2<int, 4>();
	test_vect_equal_apply_2<int, 5>();
	test_vect_equal_apply_2<int, 7>();
	test_vect_equal_apply_2<int, 8>();
	test_vect_equal_apply_2<int,11>();
	test_vect_equal_apply_2<int,15>();
	test_vect_equal_apply_2<int,19>();

	test_vect_equal_apply_2<float, 2>();
	test_vect_equal_apply_2<float, 3>();
	test_vect_equal_apply_2<float, 4>();
	test_vect_equal_apply_2<float, 5>();
	test_vect_equal_apply_2<float, 6>();
	test_vect_equal_apply_2<float, 9>();
	test_vect_equal_apply_2<float,13>();
	test_vect_equal_apply_2<float,17>();
	test_vect_equal_apply_2<float,21>();

	test_vect_equal_apply_2<double, 2>();
	test_vect_equal_apply_2<double, 3>();
	test_vect_equal_apply_2<double, 4>();
	test_vect_equal_apply_2<double, 5>();
	test_vect_equal_apply_2<double, 8>();
	test_vect_equal_apply_2<double, 9>();
	test_vect_equal_apply_2<double,12>();
	test_vect_equal_apply_2<double,16>();
	test_vect_equal_apply_2<double,17>();
}

BOOST_AUTO_TEST_SUITE_END()
