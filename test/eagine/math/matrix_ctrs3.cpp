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

template <typename T, bool RM, bool V>
void test_math_matrix_ortho_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::ortho<eagine::math::matrix<T,4,4,RM,V>> o(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1,
		+std::rand()%100+1,
		+std::rand()%100+101
	);

	eagine::math::vector<T, 4, V> v2 = o*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_ortho_1_T(void)
{
	test_math_matrix_ortho_1_TRMV<T, true, true>();
	test_math_matrix_ortho_1_TRMV<T,false, true>();
	test_math_matrix_ortho_1_TRMV<T, true,false>();
	test_math_matrix_ortho_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_ortho_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_ortho_1_T<float>();
		test_math_matrix_ortho_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_looking_at_y_up_1_TRMV(void)
{
	eagine::math::vector<T, 3, V> e{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3, V> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::looking_at_y_up<eagine::math::matrix<T,4,4,RM,V>> l(
		e, t
	);

	eagine::math::vector<T, 4, V> v2 = l*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_looking_at_y_up_1_T(void)
{
	test_math_matrix_looking_at_y_up_1_TRMV<T, true, true>();
	test_math_matrix_looking_at_y_up_1_TRMV<T,false, true>();
	test_math_matrix_looking_at_y_up_1_TRMV<T, true,false>();
	test_math_matrix_looking_at_y_up_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_looking_at_y_up_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_looking_at_y_up_1_T<float>();
		test_math_matrix_looking_at_y_up_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_looking_at_1_TRMV(void)
{
	eagine::math::vector<T, 3, V> e{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3, V> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};
	eagine::math::vector<T, 3, V> u{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::looking_at<eagine::math::matrix<T,4,4,RM,V>> l(
		e, t, u
	);

	eagine::math::vector<T, 4, V> v2 = l*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_looking_at_1_T(void)
{
	test_math_matrix_looking_at_1_TRMV<T, true, true>();
	test_math_matrix_looking_at_1_TRMV<T,false, true>();
	test_math_matrix_looking_at_1_TRMV<T, true,false>();
	test_math_matrix_looking_at_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_looking_at_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_looking_at_1_T<float>();
		test_math_matrix_looking_at_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_orbiting_y_up_1_TRMV(void)
{
	eagine::math::vector<T, 3, V> t{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000)
	}};

	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::orbiting_y_up<eagine::math::matrix<T,4,4,RM,V>> o(
		t,
		1+std::rand()%100,
		eagine::math::angle<T>((std::rand()%1571)/T(1000)),
		eagine::math::angle<T>((std::rand()%1571)/T(1000))
	);

	eagine::math::vector<T, 4, V> v2 = o*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_orbiting_y_up_1_T(void)
{
	test_math_matrix_orbiting_y_up_1_TRMV<T, true, true>();
	test_math_matrix_orbiting_y_up_1_TRMV<T,false, true>();
	test_math_matrix_orbiting_y_up_1_TRMV<T, true,false>();
	test_math_matrix_orbiting_y_up_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_orbiting_y_up_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_orbiting_y_up_1_T<float>();
		test_math_matrix_orbiting_y_up_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_perspective_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::perspective<eagine::math::matrix<T,4,4,RM,V>> p(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1,
		+std::rand()%100+1,
		+std::rand()%100+101
	);

	eagine::math::vector<T, 4, V> v2 = p*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_perspective_1_T(void)
{
	test_math_matrix_perspective_1_TRMV<T, true, true>();
	test_math_matrix_perspective_1_TRMV<T,false, true>();
	test_math_matrix_perspective_1_TRMV<T, true,false>();
	test_math_matrix_perspective_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_perspective_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_perspective_1_T<float>();
		test_math_matrix_perspective_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_screen_stretch_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	eagine::math::screen_stretch<eagine::math::matrix<T,4,4,RM,V>> p(
		-std::rand()%100-1,
		+std::rand()%100+1,
		-std::rand()%100-1,
		+std::rand()%100+1
	);

	eagine::math::vector<T, 4, V> v2 = p*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_screen_stretch_1_T(void)
{
	test_math_matrix_screen_stretch_1_TRMV<T, true, true>();
	test_math_matrix_screen_stretch_1_TRMV<T,false, true>();
	test_math_matrix_screen_stretch_1_TRMV<T, true,false>();
	test_math_matrix_screen_stretch_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_screen_stretch_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_screen_stretch_1_T<float>();	
		test_math_matrix_screen_stretch_1_T<double>();	
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_screen_tile_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	unsigned m = unsigned(std::rand() % 10 + 1);
	unsigned n = unsigned(std::rand() % 10 + 1);
	unsigned i = unsigned(std::rand()) % m;
	unsigned j = unsigned(std::rand()) % n;

	auto p = eagine::math::screen_stretch<eagine::math::matrix<T,4,4,RM,V>>
		::tile(i, j, m, n);

	eagine::math::vector<T, 4, V> v2 = p*v1;
	(void)v2;
	// TODO
}

template <typename T>
void test_math_matrix_screen_tile_1_T(void)
{
	test_math_matrix_screen_tile_1_TRMV<T, true, true>();
	test_math_matrix_screen_tile_1_TRMV<T,false, true>();
	test_math_matrix_screen_tile_1_TRMV<T, true,false>();
	test_math_matrix_screen_tile_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_screen_tile_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_screen_tile_1_T<float>();
		test_math_matrix_screen_tile_1_T<double>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_trans_rotat_I_1_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	T tx = std::rand()%100-50;
	T ty = std::rand()%100-50;
	T tz = std::rand()%100-50;

	eagine::math::translation<eagine::math::matrix<T,4,4,RM,V>> t(tx,ty,tz);

	eagine::math::angle<T> ri((std::rand()%1571)/T(1000));

	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM,V>, I> r(ri);

	eagine::math::vector<T, 4, V> v2 = t*r*v1;
	(void)v2;
	// TODO
}

template <typename T, unsigned I>
void test_math_matrix_trans_rotat_I_1_T(void)
{
	test_math_matrix_trans_rotat_I_1_TRMVI<T, true, true, I>();
	test_math_matrix_trans_rotat_I_1_TRMVI<T,false, true, I>();
	test_math_matrix_trans_rotat_I_1_TRMVI<T, true,false, I>();
	test_math_matrix_trans_rotat_I_1_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_trans_rotat_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_trans_rotat_I_1_T<float, 0>();
		test_math_matrix_trans_rotat_I_1_T<float, 1>();
		test_math_matrix_trans_rotat_I_1_T<float, 2>();

		test_math_matrix_trans_rotat_I_1_T<double, 0>();
		test_math_matrix_trans_rotat_I_1_T<double, 1>();
		test_math_matrix_trans_rotat_I_1_T<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I, unsigned J>
void test_math_matrix_trans_I_rotat_I_TRMVIJ(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};


	T ti = std::rand()%100;

	eagine::math::translation_I<eagine::math::matrix<T,4,4,RM,V>, I> t(ti);

	eagine::math::angle<T> ri((std::rand()%1571)/T(1000));

	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM,V>, J> r(ri);

	eagine::math::vector<T, 4, V> v2 = t*r*v1;
	(void)v2;
	// TODO
}

template <typename T, unsigned I, unsigned J>
void test_math_matrix_trans_I_rotat_I_TIJ(void)
{
	test_math_matrix_trans_I_rotat_I_TRMVIJ<T, true, true, I, J>();
	test_math_matrix_trans_I_rotat_I_TRMVIJ<T,false, true, I, J>();
	test_math_matrix_trans_I_rotat_I_TRMVIJ<T, true,false, I, J>();
	test_math_matrix_trans_I_rotat_I_TRMVIJ<T,false,false, I, J>();
}

template <typename T>
void test_math_matrix_trans_I_rotat_I_T(void)
{
	test_math_matrix_trans_I_rotat_I_TIJ<T, 0, 0>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 0, 1>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 0, 2>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 1, 0>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 1, 1>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 1, 2>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 2, 0>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 2, 1>();
	test_math_matrix_trans_I_rotat_I_TIJ<T, 2, 2>();
}

BOOST_AUTO_TEST_CASE(math_matrix_trans_I_rotat_I)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_trans_I_rotat_I_T<float>();
		test_math_matrix_trans_I_rotat_I_T<double>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
