/**
 *  .file test/eagine/math/matrix_ctrs.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix_ctrs
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix_ctrs.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix_ctrs)

template <typename T>
void test_math_matrix_translation_T(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T tx = std::rand()%100;
	T ty = std::rand()%100;
	T tz = std::rand()%100;

	eagine::math::translation<eagine::math::matrix<T,4,4,true>> t(tx,ty,tz);

	eagine::math::vector<T, 4> v2 = t()*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]+tx));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]+ty));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]+tz));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

BOOST_AUTO_TEST_CASE(math_matrix_translation)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_T<float>();
		test_math_matrix_translation_T<double>();
	}
}

template <typename T, unsigned I>
void test_math_matrix_translation_TI(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T ti = std::rand()%100;

	eagine::math::translation_I<eagine::math::matrix<T,4,4,true>, I> t(ti);

	eagine::math::vector<T, 4> v2 = t()*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]+(i==I?ti:T(0))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

BOOST_AUTO_TEST_CASE(math_matrix_translation_I)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_TI<float, 0>();
		test_math_matrix_translation_TI<float, 1>();
		test_math_matrix_translation_TI<float, 2>();
		test_math_matrix_translation_TI<double, 0>();
		test_math_matrix_translation_TI<double, 1>();
		test_math_matrix_translation_TI<double, 2>();
	}
}

template <typename T>
void test_math_matrix_scale_T(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T sx = std::rand()%100;
	T sy = std::rand()%100;
	T sz = std::rand()%100;

	eagine::math::scale<eagine::math::matrix<T,4,4,true>> s(sx,sy,sz);

	eagine::math::vector<T, 4> v2 = s()*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]*sx));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]*sy));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]*sz));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

BOOST_AUTO_TEST_CASE(math_matrix_scale)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_T<float>();
		test_math_matrix_scale_T<double>();
	}
}

template <typename T, unsigned I>
void test_math_matrix_scale_TI(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T si = std::rand()%100;

	eagine::math::scale_I<eagine::math::matrix<T,4,4,true>, I> s(si);

	eagine::math::vector<T, 4> v2 = s()*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*(i==I?si:T(1))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

BOOST_AUTO_TEST_CASE(math_matrix_scale_I)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_TI<float, 0>();
		test_math_matrix_scale_TI<float, 1>();
		test_math_matrix_scale_TI<float, 2>();
		test_math_matrix_scale_TI<double, 0>();
		test_math_matrix_scale_TI<double, 1>();
		test_math_matrix_scale_TI<double, 2>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
