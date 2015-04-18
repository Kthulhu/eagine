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
#include <eagine/math/difference.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_minmax)

template <typename T, unsigned N, bool V>
void test_vect_min_TNV(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N, V>::type u = {};
		typename eagine::vect::data<T, N, V>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
			v[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N, V>::type min =
			eagine::vect::min<T, N, V>::apply(u, v);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(min[i] <<equal_to>> ((u[i]<v[i])?u[i]:v[i]));
		}
	}
}

template <typename T, bool V>
void test_vect_min_TV(void)
{
	test_vect_min_TNV<T, 1, V>();
	test_vect_min_TNV<T, 2, V>();
	test_vect_min_TNV<T, 3, V>();
	test_vect_min_TNV<T, 4, V>();
	test_vect_min_TNV<T, 5, V>();
	test_vect_min_TNV<T, 6, V>();
	test_vect_min_TNV<T, 7, V>();
	test_vect_min_TNV<T, 8, V>();

	test_vect_min_TNV<T, 11, V>();
	test_vect_min_TNV<T, 17, V>();
	test_vect_min_TNV<T, 23, V>();
}

template <typename T>
void test_vect_min_T(void)
{
	test_vect_min_TV<T, true>();
	test_vect_min_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_min_int)
{
	test_vect_min_T<int>();
}

BOOST_AUTO_TEST_CASE(vect_min_float)
{
	test_vect_min_T<float>();
}

BOOST_AUTO_TEST_CASE(vect_min_double)
{
	test_vect_min_T<double>();
}


template <typename T, unsigned N, bool V>
void test_vect_max_TNV(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N, V>::type u = {};
		typename eagine::vect::data<T, N, V>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
			v[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N, V>::type max =
			eagine::vect::max<T, N, V>::apply(u, v);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(max[i] <<equal_to>> ((u[i]>v[i])?u[i]:v[i]));
		}
	}
}

template <typename T, bool V>
void test_vect_max_TV(void)
{
	test_vect_max_TNV<T, 1, V>();
	test_vect_max_TNV<T, 2, V>();
	test_vect_max_TNV<T, 3, V>();
	test_vect_max_TNV<T, 4, V>();
	test_vect_max_TNV<T, 5, V>();
	test_vect_max_TNV<T, 6, V>();
	test_vect_max_TNV<T, 7, V>();
	test_vect_max_TNV<T, 8, V>();

	test_vect_max_TNV<T, 11, V>();
	test_vect_max_TNV<T, 17, V>();
	test_vect_max_TNV<T, 23, V>();
}

template <typename T>
void test_vect_max_T(void)
{
	test_vect_max_TV<T, true>();
	test_vect_max_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_max_int)
{
	test_vect_max_T<int>();
}

BOOST_AUTO_TEST_CASE(vect_max_float)
{
	test_vect_max_T<float>();
}

BOOST_AUTO_TEST_CASE(vect_max_double)
{
	test_vect_max_T<double>();
}


template <typename T, unsigned N, bool V>
void test_vect_hmin_TNV(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N, V>::type u = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N, V>::type min =
			eagine::vect::hmin<T, N, V>::apply(u);

		for(unsigned i=0; i<N; ++i)
		{
			for(unsigned j=0; i<N; ++i)
			{
				BOOST_ASSERT(min[i] <= u[j]);
			}
			for(unsigned j=i+1; j<N; ++j)
			{
				using eagine::math::equal_to;
				BOOST_ASSERT(min[i] <<equal_to>> min[j]);
			}
		}
	}
}

template <typename T, bool V>
void test_vect_hmin_TV(void)
{
	test_vect_hmin_TNV<T, 1, V>();
	test_vect_hmin_TNV<T, 2, V>();
	test_vect_hmin_TNV<T, 3, V>();
	test_vect_hmin_TNV<T, 4, V>();
	test_vect_hmin_TNV<T, 5, V>();
	test_vect_hmin_TNV<T, 6, V>();
	test_vect_hmin_TNV<T, 7, V>();
	test_vect_hmin_TNV<T, 8, V>();

	test_vect_hmin_TNV<T, 11, V>();
	test_vect_hmin_TNV<T, 17, V>();
	test_vect_hmin_TNV<T, 23, V>();
}

template <typename T>
void test_vect_hmin_T(void)
{
	test_vect_hmin_TV<T, true>();
	test_vect_hmin_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_int)
{
	test_vect_hmin_T<int>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_float)
{
	test_vect_hmin_T<float>();
}

BOOST_AUTO_TEST_CASE(vect_hmin_double)
{
	test_vect_hmin_T<double>();
}


template <typename T, unsigned N, bool V>
void test_vect_hmax_TNV(void)
{
	for(unsigned k=0; k<10; ++k)
	{
		typename eagine::vect::data<T, N, V>::type u = {};

		for(unsigned i=0; i<N; ++i)
		{
			u[i] = std::rand() / T(2);
		}

		typename eagine::vect::data<T, N, V>::type max =
			eagine::vect::hmax<T, N, V>::apply(u);

		for(unsigned i=0; i<N; ++i)
		{
			for(unsigned j=0; i<N; ++i)
			{
				BOOST_ASSERT(max[i] >= u[j]);
			}
			for(unsigned j=i+1; j<N; ++j)
			{
				using eagine::math::equal_to;
				BOOST_ASSERT(max[i] <<equal_to>> max[j]);
			}
		}
	}
}

template <typename T, bool V>
void test_vect_hmax_TV(void)
{
	test_vect_hmax_TNV<T, 1, V>();
	test_vect_hmax_TNV<T, 2, V>();
	test_vect_hmax_TNV<T, 3, V>();
	test_vect_hmax_TNV<T, 4, V>();
	test_vect_hmax_TNV<T, 5, V>();
	test_vect_hmax_TNV<T, 6, V>();
	test_vect_hmax_TNV<T, 7, V>();
	test_vect_hmax_TNV<T, 8, V>();

	test_vect_hmax_TNV<T, 11, V>();
	test_vect_hmax_TNV<T, 17, V>();
	test_vect_hmax_TNV<T, 23, V>();
}

template <typename T>
void test_vect_hmax_T(void)
{
	test_vect_hmax_TV<T, true>();
	test_vect_hmax_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_int)
{
	test_vect_hmax_T<int>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_float)
{
	test_vect_hmax_T<float>();
}

BOOST_AUTO_TEST_CASE(vect_hmax_double)
{
	test_vect_hmax_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
