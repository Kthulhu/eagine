/**
 *  .file test/eagine/math/matrix_ctrs3.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix_ctrs3
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix_ctrs.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix_ctrs3)

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
void test_math_matrix_looking_at_y_up_T_1(void)
{
	eagine::math::vector<T, 3> e{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::looking_at_y_up<eagine::math::matrix<T,4,4,RM>> l(
		e, t
	);

	eagine::math::vector<T, 4> v2 = l*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_looking_at_y_up_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_looking_at_y_up_T_1<float, true>();
		test_math_matrix_looking_at_y_up_T_1<float,false>();
		test_math_matrix_looking_at_y_up_T_1<double, true>();
		test_math_matrix_looking_at_y_up_T_1<double,false>();
	}
}

template <typename T, bool RM>
void test_math_matrix_looking_at_T_1(void)
{
	eagine::math::vector<T, 3> e{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3> u{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::looking_at<eagine::math::matrix<T,4,4,RM>> l(
		e, t, u
	);

	eagine::math::vector<T, 4> v2 = l*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_looking_at_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_looking_at_T_1<float, true>();
		test_math_matrix_looking_at_T_1<float,false>();
		test_math_matrix_looking_at_T_1<double, true>();
		test_math_matrix_looking_at_T_1<double,false>();
	}
}

template <typename T, bool RM>
void test_math_matrix_orbiting_y_up_T_1(void)
{
	eagine::math::vector<T, 3> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::orbiting_y_up<eagine::math::matrix<T,4,4,RM>> o(
		t,
		1+std::rand()%100,
		eagine::math::angle<T>((std::rand()%1571)/T(1000)),
		eagine::math::angle<T>((std::rand()%1571)/T(1000))
	);

	eagine::math::vector<T, 4> v2 = o*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_orbiting_y_up_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_orbiting_y_up_T_1<float, true>();
		test_math_matrix_orbiting_y_up_T_1<float,false>();
		test_math_matrix_orbiting_y_up_T_1<double, true>();
		test_math_matrix_orbiting_y_up_T_1<double,false>();
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

template <typename T, bool RM>
void test_math_matrix_screen_tile_T_1(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	unsigned m = std::rand() % 10 + 1;
	unsigned n = std::rand() % 10 + 1;
	unsigned i = std::rand() % m;
	unsigned j = std::rand() % n;

	auto p = eagine::math::screen_stretch<eagine::math::matrix<T,4,4,RM>>
		::tile(i, j, m, n);

	eagine::math::vector<T, 4> v2 = p*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_screen_tile_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_screen_tile_T_1<float, true>();
		test_math_matrix_screen_tile_T_1<float,false>();
		test_math_matrix_screen_tile_T_1<double, true>();
		test_math_matrix_screen_tile_T_1<double,false>();
	}
}

template <typename T, bool RM, unsigned I>
void test_math_matrix_trans_rotat_T_1(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	T tx = std::rand()%100-50;
	T ty = std::rand()%100-50;
	T tz = std::rand()%100-50;

	eagine::math::translation<eagine::math::matrix<T,4,4,RM>> t(tx,ty,tz);

	eagine::math::angle<T> ri((std::rand()%1571)/T(1000));

	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM>, I> r(ri);

	eagine::math::vector<T, 4> v2 = t*r*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_trans_rotat_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_trans_rotat_T_1<float, true, 0>();
		test_math_matrix_trans_rotat_T_1<float, true, 1>();
		test_math_matrix_trans_rotat_T_1<float, true, 2>();
		test_math_matrix_trans_rotat_T_1<float,false, 0>();
		test_math_matrix_trans_rotat_T_1<float,false, 1>();
		test_math_matrix_trans_rotat_T_1<float,false, 2>();

		test_math_matrix_trans_rotat_T_1<double, true, 0>();
		test_math_matrix_trans_rotat_T_1<double, true, 1>();
		test_math_matrix_trans_rotat_T_1<double, true, 2>();
		test_math_matrix_trans_rotat_T_1<double,false, 0>();
		test_math_matrix_trans_rotat_T_1<double,false, 1>();
		test_math_matrix_trans_rotat_T_1<double,false, 2>();
	}
}

template <typename T, bool RM, unsigned I, unsigned J>
void test_math_matrix_trans_rotat_T_2(void)
{
	eagine::math::vector<T, 4> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};


	T ti = std::rand()%100;

	eagine::math::translation_I<eagine::math::matrix<T,4,4,RM>, I> t(ti);

	eagine::math::angle<T> ri((std::rand()%1571)/T(1000));

	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM>, I> r(ri);

	eagine::math::vector<T, 4> v2 = t*r*v1;
	(void)v2;
	// TODO
}

BOOST_AUTO_TEST_CASE(math_matrix_trans_rotat_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_trans_rotat_T_2<float, true, 0, 0>();
		test_math_matrix_trans_rotat_T_2<float, true, 0, 1>();
		test_math_matrix_trans_rotat_T_2<float, true, 0, 2>();
		test_math_matrix_trans_rotat_T_2<float, true, 1, 0>();
		test_math_matrix_trans_rotat_T_2<float, true, 1, 1>();
		test_math_matrix_trans_rotat_T_2<float, true, 1, 2>();
		test_math_matrix_trans_rotat_T_2<float, true, 2, 0>();
		test_math_matrix_trans_rotat_T_2<float, true, 2, 1>();
		test_math_matrix_trans_rotat_T_2<float, true, 2, 2>();

		test_math_matrix_trans_rotat_T_2<float,false, 0, 0>();
		test_math_matrix_trans_rotat_T_2<float,false, 0, 1>();
		test_math_matrix_trans_rotat_T_2<float,false, 0, 2>();
		test_math_matrix_trans_rotat_T_2<float,false, 1, 0>();
		test_math_matrix_trans_rotat_T_2<float,false, 0, 1>();
		test_math_matrix_trans_rotat_T_2<float,false, 0, 2>();
		test_math_matrix_trans_rotat_T_2<float,false, 2, 0>();
		test_math_matrix_trans_rotat_T_2<float,false, 2, 1>();
		test_math_matrix_trans_rotat_T_2<float,false, 2, 2>();

		test_math_matrix_trans_rotat_T_2<double, true, 0, 0>();
		test_math_matrix_trans_rotat_T_2<double, true, 0, 1>();
		test_math_matrix_trans_rotat_T_2<double, true, 0, 2>();
		test_math_matrix_trans_rotat_T_2<double, true, 1, 0>();
		test_math_matrix_trans_rotat_T_2<double, true, 1, 1>();
		test_math_matrix_trans_rotat_T_2<double, true, 1, 2>();
		test_math_matrix_trans_rotat_T_2<double, true, 2, 0>();
		test_math_matrix_trans_rotat_T_2<double, true, 2, 1>();
		test_math_matrix_trans_rotat_T_2<double, true, 2, 2>();

		test_math_matrix_trans_rotat_T_2<double,false, 0, 0>();
		test_math_matrix_trans_rotat_T_2<double,false, 0, 1>();
		test_math_matrix_trans_rotat_T_2<double,false, 0, 2>();
		test_math_matrix_trans_rotat_T_2<double,false, 1, 0>();
		test_math_matrix_trans_rotat_T_2<double,false, 1, 1>();
		test_math_matrix_trans_rotat_T_2<double,false, 1, 2>();
		test_math_matrix_trans_rotat_T_2<double,false, 2, 0>();
		test_math_matrix_trans_rotat_T_2<double,false, 2, 1>();
		test_math_matrix_trans_rotat_T_2<double,false, 2, 2>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
