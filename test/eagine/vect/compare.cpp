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
#include <eagine/math/difference.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_compare)

template <typename T, unsigned N, bool V>
void test_vect_equal_TNV_1(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N];

		typename eagine::vect::data<T, N, V>::type u = {}, v = {};

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(2);
			u[i] = a[i];
			v[i] = a[i];
		}

		typedef eagine::vect::equal<T, N, V> _equal;

		BOOST_ASSERT(_equal::apply(u, u));
		BOOST_ASSERT(_equal::apply(v, u));
		BOOST_ASSERT(_equal::apply(u, v));
		BOOST_ASSERT(_equal::apply(v, v));
	}
}

template <typename T, bool V>
void test_vect_equal_TV_1(void)
{
	test_vect_equal_TNV_1<T, 2, V>();
	test_vect_equal_TNV_1<T, 3, V>();
	test_vect_equal_TNV_1<T, 4, V>();
	test_vect_equal_TNV_1<T, 5, V>();
	test_vect_equal_TNV_1<T, 7, V>();
	test_vect_equal_TNV_1<T, 8, V>();
	test_vect_equal_TNV_1<T,11, V>();
	test_vect_equal_TNV_1<T,15, V>();
	test_vect_equal_TNV_1<T,19, V>();
}

template <typename T>
void test_vect_equal_T_1(void)
{
	test_vect_equal_TV_1<T, true>();
	test_vect_equal_TV_1<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_data_equal_TNV_1)
{
	test_vect_equal_T_1<int>();
	test_vect_equal_T_1<float>();
	test_vect_equal_T_1<double>();
}

template <typename T, unsigned N, bool V>
void test_vect_equal_TNV_2(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N], b[N];

		typename eagine::vect::data<T, N, V>::type u = {}, v = {};

		bool eq = true;

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand();
			u[i] = a[i];
			b[i] = std::rand();
			v[i] = b[i];

			using eagine::math::equal_to;

			eq &= (a[i] <<equal_to>> b[i]);
		}

		typedef eagine::vect::equal<T, N, V> _equal;

		BOOST_ASSERT(_equal::apply(u, v) == eq);
		BOOST_ASSERT(_equal::apply(v, u) == eq);
	}
}

template <typename T, bool V>
void test_vect_equal_TV_2(void)
{
	test_vect_equal_TNV_2<T, 2, V>();
	test_vect_equal_TNV_2<T, 3, V>();
	test_vect_equal_TNV_2<T, 4, V>();
	test_vect_equal_TNV_2<T, 5, V>();
	test_vect_equal_TNV_2<T, 7, V>();
	test_vect_equal_TNV_2<T, 8, V>();
	test_vect_equal_TNV_2<T,11, V>();
	test_vect_equal_TNV_2<T,15, V>();
	test_vect_equal_TNV_2<T,19, V>();
}

template <typename T>
void test_vect_equal_T_2(void)
{
	test_vect_equal_TV_2<T, true>();
	test_vect_equal_TV_2<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_data_equal_TNV_2)
{
	test_vect_equal_T_2<int>();
	test_vect_equal_T_2<float>();
	test_vect_equal_T_2<double>();
}

BOOST_AUTO_TEST_SUITE_END()
