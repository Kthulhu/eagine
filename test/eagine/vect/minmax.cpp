/**
 *  .file test/eagine/vect/minmax.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_minmax
#include <boost/test/unit_test.hpp>

#include <eagine/vect/minmax.hpp>
#include <eagine/math/close_to.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_minmax)

template <typename T, unsigned N>
void test_vect_min_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N>::type u = {};
		typename eagine::vect::data<T, N>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
			v[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N>::type min =
			eagine::vect::min<T, N>::apply(u, v);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::close_to;
			BOOST_ASSERT(min[i] <<close_to>> ((u[i]<v[i])?u[i]:v[i]));
		}
	}
}

template <typename T>
void test_vect_min_apply_t(void)
{
	test_vect_min_apply<T, 1>();
	test_vect_min_apply<T, 2>();
	test_vect_min_apply<T, 3>();
	test_vect_min_apply<T, 4>();
	test_vect_min_apply<T, 5>();
	test_vect_min_apply<T, 6>();
	test_vect_min_apply<T, 7>();
	test_vect_min_apply<T, 8>();

	test_vect_min_apply<T, 11>();
	test_vect_min_apply<T, 17>();
	test_vect_min_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_min_apply_int)
{
	test_vect_min_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_min_apply_float)
{
	test_vect_min_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_min_apply_double)
{
	test_vect_min_apply_t<double>();
}

template <typename T, unsigned N>
void test_vect_max_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N>::type u = {};
		typename eagine::vect::data<T, N>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
			v[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N>::type max =
			eagine::vect::max<T, N>::apply(u, v);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::close_to;
			BOOST_ASSERT(max[i] <<close_to>> ((u[i]>v[i])?u[i]:v[i]));
		}
	}
}

template <typename T>
void test_vect_max_apply_t(void)
{
	test_vect_max_apply<T, 1>();
	test_vect_max_apply<T, 2>();
	test_vect_max_apply<T, 3>();
	test_vect_max_apply<T, 4>();
	test_vect_max_apply<T, 5>();
	test_vect_max_apply<T, 6>();
	test_vect_max_apply<T, 7>();
	test_vect_max_apply<T, 8>();

	test_vect_max_apply<T, 11>();
	test_vect_max_apply<T, 17>();
	test_vect_max_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_max_apply_int)
{
	test_vect_max_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_max_apply_float)
{
	test_vect_max_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_max_apply_double)
{
	test_vect_max_apply_t<double>();
}

template <typename T, unsigned N>
void test_vect_hmin_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N>::type u = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N>::type min =
			eagine::vect::hmin<T, N>::apply(u);

		for(unsigned i=0; i<N; ++i)
		{
			for(unsigned j=0; i<N; ++i)
			{
				BOOST_ASSERT(min[i] <= u[j]);
			}
			for(unsigned j=i+1; j<N; ++j)
			{
				using eagine::math::close_to;
				BOOST_ASSERT(min[i] <<close_to>> min[j]);
			}
		}
	}
}

template <typename T>
void test_vect_hmin_apply_t(void)
{
	test_vect_hmin_apply<T, 1>();
	test_vect_hmin_apply<T, 2>();
	test_vect_hmin_apply<T, 3>();
	test_vect_hmin_apply<T, 4>();
	test_vect_hmin_apply<T, 5>();
	test_vect_hmin_apply<T, 6>();
	test_vect_hmin_apply<T, 7>();
	test_vect_hmin_apply<T, 8>();

	test_vect_hmin_apply<T, 11>();
	test_vect_hmin_apply<T, 17>();
	test_vect_hmin_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_apply_int)
{
	test_vect_hmin_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_apply_float)
{
	test_vect_hmin_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_apply_double)
{
	test_vect_hmin_apply_t<double>();
}

template <typename T, unsigned N>
void test_vect_hmax_apply(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N>::type u = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N>::type max =
			eagine::vect::hmax<T, N>::apply(u);

		for(unsigned i=0; i<N; ++i)
		{
			for(unsigned j=0; i<N; ++i)
			{
				BOOST_ASSERT(max[i] >= u[j]);
			}
			for(unsigned j=i+1; j<N; ++j)
			{
				using eagine::math::close_to;
				BOOST_ASSERT(max[i] <<close_to>> max[j]);
			}
		}
	}
}

template <typename T>
void test_vect_hmax_apply_t(void)
{
	test_vect_hmax_apply<T, 1>();
	test_vect_hmax_apply<T, 2>();
	test_vect_hmax_apply<T, 3>();
	test_vect_hmax_apply<T, 4>();
	test_vect_hmax_apply<T, 5>();
	test_vect_hmax_apply<T, 6>();
	test_vect_hmax_apply<T, 7>();
	test_vect_hmax_apply<T, 8>();

	test_vect_hmax_apply<T, 11>();
	test_vect_hmax_apply<T, 17>();
	test_vect_hmax_apply<T, 23>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_apply_int)
{
	test_vect_hmax_apply_t<int>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_apply_float)
{
	test_vect_hmax_apply_t<float>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_apply_double)
{
	test_vect_hmax_apply_t<double>();
}

BOOST_AUTO_TEST_SUITE_END()
