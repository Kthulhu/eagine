/**
 *  .file test/eagine/vect/from.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_from
#include <boost/test/unit_test.hpp>

#include <eagine/vect/from.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_from)

template <typename T, unsigned N>
void test_vect_from_array_apply_T(void)
{
	T a[N];
	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	typename eagine::vect::data<T, N>::type v =
		eagine::vect::from_array<T, N>::apply(a, N);

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(v[i] == a[i]);
	}
}

template <typename T>
void test_vect_from_array_apply(void)
{
	test_vect_from_array_apply_T<T, 2>();
	test_vect_from_array_apply_T<T, 3>();
	test_vect_from_array_apply_T<T, 4>();
	test_vect_from_array_apply_T<T, 5>();
	test_vect_from_array_apply_T<T, 6>();
	test_vect_from_array_apply_T<T, 7>();
	test_vect_from_array_apply_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(vect_from_array_apply)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_vect_from_array_apply<int>();
		test_vect_from_array_apply<float>();
		test_vect_from_array_apply<double>();
	}
}


template <typename T, unsigned N, unsigned M>
void test_vect_from_saafv_apply_T(void)
{
	static_assert(M <= N, "");

	T a[M];
	for(unsigned i=0; i<M; ++i)
	{
		a[i] = std::rand() / T(3);
	}
	T f = std::rand() / T(3);

	typename eagine::vect::data<T, N>::type v =
		eagine::vect::from_saafv<T, N>::apply(a, M, f);

	for(unsigned i=0; i<M; ++i)
	{
		BOOST_ASSERT(v[i] == a[i]);
	}
	for(unsigned i=M; i<N; ++i)
	{
		BOOST_ASSERT(v[i] == f);
	}
}

template <typename T>
void test_vect_from_saafv_apply(void)
{
	test_vect_from_saafv_apply_T<T, 2,1>();
	test_vect_from_saafv_apply_T<T, 2,2>();

	test_vect_from_saafv_apply_T<T, 3,1>();
	test_vect_from_saafv_apply_T<T, 3,2>();
	test_vect_from_saafv_apply_T<T, 3,3>();

	test_vect_from_saafv_apply_T<T, 4,1>();
	test_vect_from_saafv_apply_T<T, 4,2>();
	test_vect_from_saafv_apply_T<T, 4,3>();
	test_vect_from_saafv_apply_T<T, 4,4>();

	test_vect_from_saafv_apply_T<T, 5,1>();
	test_vect_from_saafv_apply_T<T, 5,2>();
	test_vect_from_saafv_apply_T<T, 5,3>();
	test_vect_from_saafv_apply_T<T, 5,4>();
	test_vect_from_saafv_apply_T<T, 5,5>();

	test_vect_from_saafv_apply_T<T, 6,1>();
	test_vect_from_saafv_apply_T<T, 6,2>();
	test_vect_from_saafv_apply_T<T, 6,3>();
	test_vect_from_saafv_apply_T<T, 6,4>();
	test_vect_from_saafv_apply_T<T, 6,5>();
	test_vect_from_saafv_apply_T<T, 6,6>();

	test_vect_from_saafv_apply_T<T, 7,1>();
	test_vect_from_saafv_apply_T<T, 7,2>();
	test_vect_from_saafv_apply_T<T, 7,3>();
	test_vect_from_saafv_apply_T<T, 7,4>();
	test_vect_from_saafv_apply_T<T, 7,5>();
	test_vect_from_saafv_apply_T<T, 7,6>();
	test_vect_from_saafv_apply_T<T, 7,7>();

	test_vect_from_saafv_apply_T<T, 8,1>();
	test_vect_from_saafv_apply_T<T, 8,2>();
	test_vect_from_saafv_apply_T<T, 8,3>();
	test_vect_from_saafv_apply_T<T, 8,4>();
	test_vect_from_saafv_apply_T<T, 8,5>();
	test_vect_from_saafv_apply_T<T, 8,6>();
	test_vect_from_saafv_apply_T<T, 8,7>();
	test_vect_from_saafv_apply_T<T, 8,8>();
}

BOOST_AUTO_TEST_CASE(vect_from_saafv_apply)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_vect_from_saafv_apply<int>();
		test_vect_from_saafv_apply<float>();
		test_vect_from_saafv_apply<double>();
	}
}


BOOST_AUTO_TEST_SUITE_END()
