/**
 *  .file test/eagine/vect/shuffle.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_shuffle
#include <boost/test/unit_test.hpp>

#include <eagine/vect/shuffle.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <array>

BOOST_AUTO_TEST_SUITE(vect_shuffle)

template <typename T, unsigned N, int ... I>
void test_vect_shuffle_apply(void)
{
	std::array<int, N> n = {{I...}};

	for(unsigned k=0; k<10; ++k)
	{
		T a[N];

		typename eagine::vect::data<T, N>::type v = {};
		typename eagine::vect::shuffle_mask<I...> m = {};

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(2);
			v[i] = a[i];
		}

		typename eagine::vect::data<T, N>::type u =
			eagine::vect::shuffle<T, N>::apply(v, m);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(u[i] <<equal_to>> a[n[i]]);
		}
	}
}

template <typename T>
void test_vect_shuffle_apply_t(void)
{
	test_vect_shuffle_apply<T, 2, 0, 0>();
	test_vect_shuffle_apply<T, 2, 0, 1>();
	test_vect_shuffle_apply<T, 2, 1, 0>();
	test_vect_shuffle_apply<T, 2, 1, 1>();

	test_vect_shuffle_apply<T, 3, 0, 1, 2>();
	test_vect_shuffle_apply<T, 3, 1, 0, 2>();
	test_vect_shuffle_apply<T, 3, 1, 2, 0>();
	test_vect_shuffle_apply<T, 3, 0, 2, 1>();
	test_vect_shuffle_apply<T, 3, 2, 0, 1>();
	test_vect_shuffle_apply<T, 3, 2, 1, 0>();

	test_vect_shuffle_apply<T, 4, 0, 1, 2, 3>();
	test_vect_shuffle_apply<T, 4, 1, 0, 2, 3>();
	test_vect_shuffle_apply<T, 4, 1, 2, 0, 3>();
	test_vect_shuffle_apply<T, 4, 1, 2, 3, 0>();
	test_vect_shuffle_apply<T, 4, 0, 2, 1, 3>();
	test_vect_shuffle_apply<T, 4, 2, 0, 1, 3>();
	test_vect_shuffle_apply<T, 4, 2, 1, 0, 3>();
	test_vect_shuffle_apply<T, 4, 2, 1, 3, 0>();
	test_vect_shuffle_apply<T, 4, 0, 2, 3, 1>();
	test_vect_shuffle_apply<T, 4, 2, 0, 3, 1>();
	test_vect_shuffle_apply<T, 4, 2, 3, 0, 1>();
	test_vect_shuffle_apply<T, 4, 2, 3, 1, 0>();
	test_vect_shuffle_apply<T, 4, 0, 1, 3, 2>();
	test_vect_shuffle_apply<T, 4, 1, 0, 3, 2>();
	test_vect_shuffle_apply<T, 4, 1, 3, 0, 2>();
	test_vect_shuffle_apply<T, 4, 1, 3, 2, 0>();
	test_vect_shuffle_apply<T, 4, 0, 3, 1, 2>();
	test_vect_shuffle_apply<T, 4, 3, 0, 1, 2>();
	test_vect_shuffle_apply<T, 4, 3, 1, 0, 2>();
	test_vect_shuffle_apply<T, 4, 3, 1, 2, 0>();
	test_vect_shuffle_apply<T, 4, 0, 3, 2, 1>();
	test_vect_shuffle_apply<T, 4, 3, 0, 2, 1>();
	test_vect_shuffle_apply<T, 4, 3, 2, 0, 1>();
	test_vect_shuffle_apply<T, 4, 3, 2, 1, 0>();

	test_vect_shuffle_apply<T, 5, 0, 1, 2, 3, 4>();
	test_vect_shuffle_apply<T, 5, 1, 0, 2, 3, 4>();
	test_vect_shuffle_apply<T, 5, 1, 2, 0, 3, 4>();
	test_vect_shuffle_apply<T, 5, 1, 2, 3, 0, 4>();
	test_vect_shuffle_apply<T, 5, 1, 2, 3, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 1, 3, 4>();
	test_vect_shuffle_apply<T, 5, 2, 0, 1, 3, 4>();
	test_vect_shuffle_apply<T, 5, 2, 1, 0, 3, 4>();
	test_vect_shuffle_apply<T, 5, 2, 1, 3, 0, 4>();
	test_vect_shuffle_apply<T, 5, 2, 1, 3, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 3, 1, 4>();
	test_vect_shuffle_apply<T, 5, 2, 0, 3, 1, 4>();
	test_vect_shuffle_apply<T, 5, 2, 3, 0, 1, 4>();
	test_vect_shuffle_apply<T, 5, 2, 3, 1, 0, 4>();
	test_vect_shuffle_apply<T, 5, 2, 3, 1, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 3, 4, 1>();
	test_vect_shuffle_apply<T, 5, 2, 0, 3, 4, 1>();
	test_vect_shuffle_apply<T, 5, 2, 3, 0, 4, 1>();
	test_vect_shuffle_apply<T, 5, 2, 3, 4, 0, 1>();
	test_vect_shuffle_apply<T, 5, 2, 3, 4, 1, 0>();
	test_vect_shuffle_apply<T, 5, 0, 1, 3, 2, 4>();
	test_vect_shuffle_apply<T, 5, 1, 0, 3, 2, 4>();
	test_vect_shuffle_apply<T, 5, 1, 3, 0, 2, 4>();
	test_vect_shuffle_apply<T, 5, 1, 3, 2, 0, 4>();
	test_vect_shuffle_apply<T, 5, 1, 3, 2, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 1, 2, 4>();
	test_vect_shuffle_apply<T, 5, 3, 0, 1, 2, 4>();
	test_vect_shuffle_apply<T, 5, 3, 1, 0, 2, 4>();
	test_vect_shuffle_apply<T, 5, 3, 1, 2, 0, 4>();
	test_vect_shuffle_apply<T, 5, 3, 1, 2, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 2, 1, 4>();
	test_vect_shuffle_apply<T, 5, 3, 0, 2, 1, 4>();
	test_vect_shuffle_apply<T, 5, 3, 2, 0, 1, 4>();
	test_vect_shuffle_apply<T, 5, 3, 2, 1, 0, 4>();
	test_vect_shuffle_apply<T, 5, 3, 2, 1, 4, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 2, 4, 1>();
	test_vect_shuffle_apply<T, 5, 3, 0, 2, 4, 1>();
	test_vect_shuffle_apply<T, 5, 3, 2, 0, 4, 1>();
	test_vect_shuffle_apply<T, 5, 3, 2, 4, 0, 1>();
	test_vect_shuffle_apply<T, 5, 3, 2, 4, 1, 0>();
	test_vect_shuffle_apply<T, 5, 0, 1, 3, 4, 2>();
	test_vect_shuffle_apply<T, 5, 1, 0, 3, 4, 2>();
	test_vect_shuffle_apply<T, 5, 1, 3, 0, 4, 2>();
	test_vect_shuffle_apply<T, 5, 1, 3, 4, 0, 2>();
	test_vect_shuffle_apply<T, 5, 1, 3, 4, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 1, 4, 2>();
	test_vect_shuffle_apply<T, 5, 3, 0, 1, 4, 2>();
	test_vect_shuffle_apply<T, 5, 3, 1, 0, 4, 2>();
	test_vect_shuffle_apply<T, 5, 3, 1, 4, 0, 2>();
	test_vect_shuffle_apply<T, 5, 3, 1, 4, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 4, 1, 2>();
	test_vect_shuffle_apply<T, 5, 3, 0, 4, 1, 2>();
	test_vect_shuffle_apply<T, 5, 3, 4, 0, 1, 2>();
	test_vect_shuffle_apply<T, 5, 3, 4, 1, 0, 2>();
	test_vect_shuffle_apply<T, 5, 3, 4, 1, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 3, 4, 2, 1>();
	test_vect_shuffle_apply<T, 5, 3, 0, 4, 2, 1>();
	test_vect_shuffle_apply<T, 5, 3, 4, 0, 2, 1>();
	test_vect_shuffle_apply<T, 5, 3, 4, 2, 0, 1>();
	test_vect_shuffle_apply<T, 5, 3, 4, 2, 1, 0>();
	test_vect_shuffle_apply<T, 5, 0, 1, 2, 4, 3>();
	test_vect_shuffle_apply<T, 5, 1, 0, 2, 4, 3>();
	test_vect_shuffle_apply<T, 5, 1, 2, 0, 4, 3>();
	test_vect_shuffle_apply<T, 5, 1, 2, 4, 0, 3>();
	test_vect_shuffle_apply<T, 5, 1, 2, 4, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 1, 4, 3>();
	test_vect_shuffle_apply<T, 5, 2, 0, 1, 4, 3>();
	test_vect_shuffle_apply<T, 5, 2, 1, 0, 4, 3>();
	test_vect_shuffle_apply<T, 5, 2, 1, 4, 0, 3>();
	test_vect_shuffle_apply<T, 5, 2, 1, 4, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 4, 1, 3>();
	test_vect_shuffle_apply<T, 5, 2, 0, 4, 1, 3>();
	test_vect_shuffle_apply<T, 5, 2, 4, 0, 1, 3>();
	test_vect_shuffle_apply<T, 5, 2, 4, 1, 0, 3>();
	test_vect_shuffle_apply<T, 5, 2, 4, 1, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 2, 4, 3, 1>();
	test_vect_shuffle_apply<T, 5, 2, 0, 4, 3, 1>();
	test_vect_shuffle_apply<T, 5, 2, 4, 0, 3, 1>();
	test_vect_shuffle_apply<T, 5, 2, 4, 3, 0, 1>();
	test_vect_shuffle_apply<T, 5, 2, 4, 3, 1, 0>();
	test_vect_shuffle_apply<T, 5, 0, 1, 4, 2, 3>();
	test_vect_shuffle_apply<T, 5, 1, 0, 4, 2, 3>();
	test_vect_shuffle_apply<T, 5, 1, 4, 0, 2, 3>();
	test_vect_shuffle_apply<T, 5, 1, 4, 2, 0, 3>();
	test_vect_shuffle_apply<T, 5, 1, 4, 2, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 1, 2, 3>();
	test_vect_shuffle_apply<T, 5, 4, 0, 1, 2, 3>();
	test_vect_shuffle_apply<T, 5, 4, 1, 0, 2, 3>();
	test_vect_shuffle_apply<T, 5, 4, 1, 2, 0, 3>();
	test_vect_shuffle_apply<T, 5, 4, 1, 2, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 2, 1, 3>();
	test_vect_shuffle_apply<T, 5, 4, 0, 2, 1, 3>();
	test_vect_shuffle_apply<T, 5, 4, 2, 0, 1, 3>();
	test_vect_shuffle_apply<T, 5, 4, 2, 1, 0, 3>();
	test_vect_shuffle_apply<T, 5, 4, 2, 1, 3, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 2, 3, 1>();
	test_vect_shuffle_apply<T, 5, 4, 0, 2, 3, 1>();
	test_vect_shuffle_apply<T, 5, 4, 2, 0, 3, 1>();
	test_vect_shuffle_apply<T, 5, 4, 2, 3, 0, 1>();
	test_vect_shuffle_apply<T, 5, 4, 2, 3, 1, 0>();
	test_vect_shuffle_apply<T, 5, 0, 1, 4, 3, 2>();
	test_vect_shuffle_apply<T, 5, 1, 0, 4, 3, 2>();
	test_vect_shuffle_apply<T, 5, 1, 4, 0, 3, 2>();
	test_vect_shuffle_apply<T, 5, 1, 4, 3, 0, 2>();
	test_vect_shuffle_apply<T, 5, 1, 4, 3, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 1, 3, 2>();
	test_vect_shuffle_apply<T, 5, 4, 0, 1, 3, 2>();
	test_vect_shuffle_apply<T, 5, 4, 1, 0, 3, 2>();
	test_vect_shuffle_apply<T, 5, 4, 1, 3, 0, 2>();
	test_vect_shuffle_apply<T, 5, 4, 1, 3, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 3, 1, 2>();
	test_vect_shuffle_apply<T, 5, 4, 0, 3, 1, 2>();
	test_vect_shuffle_apply<T, 5, 4, 3, 0, 1, 2>();
	test_vect_shuffle_apply<T, 5, 4, 3, 1, 0, 2>();
	test_vect_shuffle_apply<T, 5, 4, 3, 1, 2, 0>();
	test_vect_shuffle_apply<T, 5, 0, 4, 3, 2, 1>();
	test_vect_shuffle_apply<T, 5, 4, 0, 3, 2, 1>();
	test_vect_shuffle_apply<T, 5, 4, 3, 0, 2, 1>();
	test_vect_shuffle_apply<T, 5, 4, 3, 2, 0, 1>();
	test_vect_shuffle_apply<T, 5, 4, 3, 2, 1, 0>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle_apply_int)
{
	test_vect_shuffle_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle_apply_float)
{
	test_vect_shuffle_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle_apply_double)
{
	test_vect_shuffle_apply_t<double>();
}

template <typename T, unsigned N, int ... I>
void test_vect_shuffle2_apply(void)
{
	std::array<int, N> n = {{I...}};

	for(unsigned k=0; k<10; ++k)
	{
		T a[N*2];

		typename eagine::vect::data<T, N>::type v = {}, u = {};
		typename eagine::vect::shuffle_mask<I...> m = {};

		for(unsigned i=0; i<N*2; ++i)
		{
			a[i] = std::rand() / T(2);
		}
		for(unsigned i=0; i<N; ++i)
		{
			v[i] = a[0+i];
			u[i] = a[N+i];
		}

		typename eagine::vect::data<T, N>::type w =
			eagine::vect::shuffle2<T, N>::apply(v, u, m);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(w[i] <<equal_to>> a[n[i]]);
		}
	}
}

template <typename T>
void test_vect_shuffle2_apply_t(void)
{
	test_vect_shuffle2_apply<T, 2, 0, 2>();
	test_vect_shuffle2_apply<T, 2, 1, 2>();
	test_vect_shuffle2_apply<T, 2, 1, 0>();
	test_vect_shuffle2_apply<T, 2, 1, 3>();
	test_vect_shuffle2_apply<T, 2, 0, 1>();
	test_vect_shuffle2_apply<T, 2, 2, 1>();
	test_vect_shuffle2_apply<T, 2, 2, 0>();
	test_vect_shuffle2_apply<T, 2, 2, 3>();
	test_vect_shuffle2_apply<T, 2, 0, 3>();
	test_vect_shuffle2_apply<T, 2, 2, 3>();
	test_vect_shuffle2_apply<T, 2, 2, 1>();
	test_vect_shuffle2_apply<T, 2, 0, 3>();
	test_vect_shuffle2_apply<T, 2, 1, 3>();
	test_vect_shuffle2_apply<T, 2, 1, 0>();
	test_vect_shuffle2_apply<T, 2, 1, 2>();
	test_vect_shuffle2_apply<T, 2, 0, 1>();
	test_vect_shuffle2_apply<T, 2, 3, 1>();
	test_vect_shuffle2_apply<T, 2, 3, 0>();
	test_vect_shuffle2_apply<T, 2, 3, 2>();
	test_vect_shuffle2_apply<T, 2, 0, 2>();
	test_vect_shuffle2_apply<T, 2, 3, 2>();
	test_vect_shuffle2_apply<T, 2, 3, 0>();
	test_vect_shuffle2_apply<T, 2, 3, 1>();

	test_vect_shuffle2_apply<T, 3, 0, 2, 4>();
	test_vect_shuffle2_apply<T, 3, 1, 3, 5>();
	test_vect_shuffle2_apply<T, 3, 5, 4, 3>();
	test_vect_shuffle2_apply<T, 3, 1, 2, 3>();
	test_vect_shuffle2_apply<T, 3, 1, 1, 1>();
	test_vect_shuffle2_apply<T, 3, 4, 4, 4>();
	test_vect_shuffle2_apply<T, 3, 2, 3, 1>();
	test_vect_shuffle2_apply<T, 3, 0, 1, 2>();
	test_vect_shuffle2_apply<T, 3, 3, 4, 5>();

	test_vect_shuffle2_apply<T, 4, 0, 2, 4, 6>();
	test_vect_shuffle2_apply<T, 4, 1, 3, 5, 7>();
	test_vect_shuffle2_apply<T, 4, 1, 1, 1, 1>();
	test_vect_shuffle2_apply<T, 4, 1, 1, 2, 2>();
	test_vect_shuffle2_apply<T, 4, 4, 4, 5, 5>();
	test_vect_shuffle2_apply<T, 4, 5, 5, 5, 5>();
	test_vect_shuffle2_apply<T, 4, 3, 2, 1, 0>();
	test_vect_shuffle2_apply<T, 4, 7, 6, 5, 4>();
	test_vect_shuffle2_apply<T, 4, 6, 2, 4, 0>();
	test_vect_shuffle2_apply<T, 4, 7, 1, 5, 3>();

	test_vect_shuffle2_apply<T, 5, 0, 2, 4, 6, 8>();
	test_vect_shuffle2_apply<T, 5, 1, 3, 5, 7, 9>();
	test_vect_shuffle2_apply<T, 5, 8, 6, 4, 2, 0>();
	test_vect_shuffle2_apply<T, 5, 9, 7, 5, 3, 1>();
	test_vect_shuffle2_apply<T, 5, 0, 1, 2, 3, 4>();
	test_vect_shuffle2_apply<T, 5, 5, 6, 7, 8, 9>();
	test_vect_shuffle2_apply<T, 5, 2, 3, 4, 5, 6>();
	test_vect_shuffle2_apply<T, 5, 0, 1, 2, 7, 9>();
	test_vect_shuffle2_apply<T, 5, 2, 2, 2, 2, 2>();
	test_vect_shuffle2_apply<T, 5, 7, 7, 7, 7, 7>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle2_apply_int)
{
	test_vect_shuffle2_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle2_apply_float)
{
	test_vect_shuffle2_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_shuffle2_apply_double)
{
	test_vect_shuffle2_apply_t<double>();
}

BOOST_AUTO_TEST_SUITE_END()
