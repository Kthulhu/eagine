/**
 *  .file test/eagine/math/matrix_ctrs2.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix_ctrs2
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix_ctrs.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix_ctrs2)

template <typename T, bool RM>
void test_math_matrix_ortho_T_1(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::ortho<eagine::math::matrix<T,4,4,RM>> o(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1,
		+std::rand()%100+1,
		+std::rand()%100+101
	);

	eagine::math::vector<T, 4> v2 = o*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_ortho_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_ortho_T_1<float, true>();
		test_math_matrix_ortho_T_1<float,false>();
		test_math_matrix_ortho_T_1<double, true>();
		test_math_matrix_ortho_T_1<double,false>();
	}
}

template <typename T, bool RM>
void test_math_matrix_perspective_T_1(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::perspective<eagine::math::matrix<T,4,4,RM>> p(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1,
		+std::rand()%100+1,
		+std::rand()%100+101
	);

	eagine::math::vector<T, 4> v2 = p*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_perspective_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_perspective_T_1<float, true>();
		test_math_matrix_perspective_T_1<float,false>();
		test_math_matrix_perspective_T_1<double, true>();
		test_math_matrix_perspective_T_1<double,false>();
	}
}

template <typename T, bool RM>
void test_math_matrix_screen_stretch_T_1(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::screen_stretch<eagine::math::matrix<T,4,4,RM>> p(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1
	);

	eagine::math::vector<T, 4> v2 = p*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_screen_stretch_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_screen_stretch_T_1<float, true>();
		test_math_matrix_screen_stretch_T_1<float,false>();
		test_math_matrix_screen_stretch_T_1<double, true>();
		test_math_matrix_screen_stretch_T_1<double,false>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
