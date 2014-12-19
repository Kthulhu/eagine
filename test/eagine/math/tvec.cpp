/**
 *  .file test/eagine/math/tvec.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_tvec
#include <boost/test/unit_test.hpp>

#include <eagine/math/tvec.hpp>
#include <type_traits>
#include <cstdlib>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_tvec)

template <typename T>
void test_math_tvec_default_ctr(void)
{
	eagine::math::tvec<float, 2> v2;
	eagine::math::tvec<float, 3> v3;
	eagine::math::tvec<float, 4> v4;
	eagine::math::tvec<float, 5> v5;
	eagine::math::tvec<float, 6> v6;
	eagine::math::tvec<float, 7> v7;
	eagine::math::tvec<float, 8> v8;
	eagine::math::tvec<float, 9> v9;

	(void)v2; (void)v3; (void)v4; (void)v5;
	(void)v6; (void)v7; (void)v8; (void)v9;
}

BOOST_AUTO_TEST_CASE(math_tvec_default_ctr)
{
	test_math_tvec_default_ctr<int>();
	test_math_tvec_default_ctr<float>();
	test_math_tvec_default_ctr<double>();
}

template <typename T>
void test_math_tvec_copy_ctr(void)
{
	eagine::math::tvec<float, 2> v2a;
	eagine::math::tvec<float, 3> v3a;
	eagine::math::tvec<float, 4> v4a;
	eagine::math::tvec<float, 5> v5a;
	eagine::math::tvec<float, 6> v6a;
	eagine::math::tvec<float, 7> v7a;
	eagine::math::tvec<float, 8> v8a;
	eagine::math::tvec<float, 9> v9a;

	eagine::math::tvec<float, 2> v2(v2a);
	eagine::math::tvec<float, 3> v3(v3a);
	eagine::math::tvec<float, 4> v4(v4a);
	eagine::math::tvec<float, 5> v5(v5a);
	eagine::math::tvec<float, 6> v6(v6a);
	eagine::math::tvec<float, 7> v7(v7a);
	eagine::math::tvec<float, 8> v8(v8a);
	eagine::math::tvec<float, 9> v9(v9a);

	(void)v2; (void)v3; (void)v4; (void)v5;
	(void)v6; (void)v7; (void)v8; (void)v9;
}

BOOST_AUTO_TEST_CASE(math_tvec_copy_ctr)
{
	test_math_tvec_copy_ctr<int>();
	test_math_tvec_copy_ctr<float>();
	test_math_tvec_copy_ctr<double>();
}

template <typename T>
void test_math_tvec_init_ctr(void)
{
	eagine::math::tvec<float, 2> v2(1,2);
	eagine::math::tvec<float, 3> v3(1,2,3);
	eagine::math::tvec<float, 4> v4(1,2,3,4);
	eagine::math::tvec<float, 5> v5(1,2,3,4,5);
	eagine::math::tvec<float, 6> v6(1,2,3,4,5,6);
	eagine::math::tvec<float, 7> v7(1,2,3,4,5,6,7);
	eagine::math::tvec<float, 8> v8(1,2,3,4,5,6,7,8);
	eagine::math::tvec<float, 9> v9(1,2,3,4,5,6,7,8,9);

	(void)v2; (void)v3; (void)v4; (void)v5;
	(void)v6; (void)v7; (void)v8; (void)v9;
}

BOOST_AUTO_TEST_CASE(math_tvec_init_ctr)
{
	test_math_tvec_init_ctr<int>();
	test_math_tvec_init_ctr<float>();
	test_math_tvec_init_ctr<double>();
}

template <typename T>
void test_math_tvec_conv_ctr1(void)
{
	eagine::math::tvec<float, 2> v2(1,2);
	eagine::math::tvec<float, 3> v3(v2,3);
	eagine::math::tvec<float, 4> v4(v3,4);
	eagine::math::tvec<float, 5> v5(v4,5);
	eagine::math::tvec<float, 6> v6(v5,6);
	eagine::math::tvec<float, 7> v7(v6,7);
	eagine::math::tvec<float, 8> v8(v7,8);
	eagine::math::tvec<float, 9> v9(v8,9);

	(void)v2; (void)v3; (void)v4; (void)v5;
	(void)v6; (void)v7; (void)v8; (void)v9;
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr1)
{
	test_math_tvec_conv_ctr1<int>();
	test_math_tvec_conv_ctr1<float>();
	test_math_tvec_conv_ctr1<double>();
}

template <typename T, unsigned N>
void test_math_tvec_conv_ctr2_T(void)
{
	eagine::math::tvec<T, N+0> vN0;
	eagine::math::tvec<T, N+1> vN1(vN0,1);
	eagine::math::tvec<T, N+2> vN2(vN0,1,2);
	eagine::math::tvec<T, N+3> vN3(vN0,1,2,3);
	eagine::math::tvec<T, N+4> vN4(vN0,1,2,3,4);
	eagine::math::tvec<T, N+5> vN5(vN0,1,2,3,4,5);
	eagine::math::tvec<T, N+6> vN6(vN0,1,2,3,4,5,6);
}

template <typename T>
void test_math_tvec_conv_ctr2(void)
{
	test_math_tvec_conv_ctr2_T<T, 2>();
	test_math_tvec_conv_ctr2_T<T, 3>();
	test_math_tvec_conv_ctr2_T<T, 4>();
	test_math_tvec_conv_ctr2_T<T, 5>();
	test_math_tvec_conv_ctr2_T<T, 6>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr2)
{
	test_math_tvec_conv_ctr2<int>();
	test_math_tvec_conv_ctr2<float>();
	test_math_tvec_conv_ctr2<double>();
}

template <typename T, unsigned N>
void test_math_taxis_default_ctr_T_N(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0> ax;
}

template <typename T, unsigned N, unsigned I>
void test_math_taxis_default_ctr_T_N(std::integral_constant<unsigned, I>)
{
	test_math_taxis_default_ctr_T_N<T, N>(
		std::integral_constant<unsigned, I-1>()
	);
	eagine::math::taxis<T, N, I> ax;
}

template <typename T, unsigned N>
void test_math_taxis_default_ctr_T(void)
{
	test_math_taxis_default_ctr_T_N<T, N>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T>
void test_math_taxis_default_ctr(void)
{
	test_math_taxis_default_ctr_T<T, 2>();
	test_math_taxis_default_ctr_T<T, 3>();
	test_math_taxis_default_ctr_T<T, 4>();
	test_math_taxis_default_ctr_T<T, 5>();
	test_math_taxis_default_ctr_T<T, 6>();
	test_math_taxis_default_ctr_T<T, 7>();
	test_math_taxis_default_ctr_T<T, 8>();
	test_math_taxis_default_ctr_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_taxis_default_ctr)
{
	test_math_taxis_default_ctr<int>();
	test_math_taxis_default_ctr<float>();
	test_math_taxis_default_ctr<double>();
}

template <typename T, unsigned N>
void test_math_tvec_conv_ctr3_T(void)
{
	eagine::math::tvec<T, N+0> vN0;
	eagine::math::tvec<T, N+1> vN1(vN0,eagine::math::taxis<T,1,0>());
	eagine::math::tvec<T, N+2> vN2(vN0,eagine::math::taxis<T,2,1>());
	eagine::math::tvec<T, N+3> vN3(vN0,eagine::math::taxis<T,3,2>());
	eagine::math::tvec<T, N+4> vN4(vN0,eagine::math::taxis<T,4,3>());
	eagine::math::tvec<T, N+5> vN5(vN0,eagine::math::taxis<T,5,4>());
	eagine::math::tvec<T, N+6> vN6(vN0,eagine::math::taxis<T,6,5>());
}

template <typename T>
void test_math_tvec_conv_ctr3(void)
{
	test_math_tvec_conv_ctr3_T<T, 2>();
	test_math_tvec_conv_ctr3_T<T, 3>();
	test_math_tvec_conv_ctr3_T<T, 4>();
	test_math_tvec_conv_ctr3_T<T, 5>();
	test_math_tvec_conv_ctr3_T<T, 6>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr3)
{
	test_math_tvec_conv_ctr3<int>();
	test_math_tvec_conv_ctr3<float>();
	test_math_tvec_conv_ctr3<double>();
}

template <typename T, unsigned N>
void test_math_tvec_elem1_T(void)
{
	eagine::math::tvec<T, N> vN;

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(vN[i] == T(0));
	}
}

template <typename T>
void test_math_tvec_elem1(void)
{
	test_math_tvec_elem1_T<T, 2>();
	test_math_tvec_elem1_T<T, 3>();
	test_math_tvec_elem1_T<T, 4>();
	test_math_tvec_elem1_T<T, 5>();
	test_math_tvec_elem1_T<T, 6>();
	test_math_tvec_elem1_T<T, 7>();
	test_math_tvec_elem1_T<T, 8>();
	test_math_tvec_elem1_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_tvec_elem1)
{
	test_math_tvec_elem1<int>();
	test_math_tvec_elem1<float>();
	test_math_tvec_elem1<double>();
}

template <typename T, unsigned N>
void test_math_tvec_elem2_T(void)
{
	eagine::math::tvec<T, N+0> vN0;
	eagine::math::tvec<T, N+1> vN1(vN0,1);
	eagine::math::tvec<T, N+2> vN2(vN0,1,2);
	eagine::math::tvec<T, N+3> vN3(vN0,1,2,3);
	eagine::math::tvec<T, N+4> vN4(vN0,1,2,3,4);
	eagine::math::tvec<T, N+5> vN5(vN0,1,2,3,4,5);

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(vN0[i] == T(0));
		BOOST_ASSERT(vN1[i] == T(0));
		BOOST_ASSERT(vN2[i] == T(0));
		BOOST_ASSERT(vN3[i] == T(0));
		BOOST_ASSERT(vN4[i] == T(0));
		BOOST_ASSERT(vN5[i] == T(0));
	}

	BOOST_ASSERT(vN1[N+0] == T(1));
	BOOST_ASSERT(vN2[N+0] == T(1));
	BOOST_ASSERT(vN3[N+0] == T(1));
	BOOST_ASSERT(vN4[N+0] == T(1));
	BOOST_ASSERT(vN5[N+0] == T(1));

	BOOST_ASSERT(vN2[N+1] == T(2));
	BOOST_ASSERT(vN3[N+1] == T(2));
	BOOST_ASSERT(vN4[N+1] == T(2));
	BOOST_ASSERT(vN5[N+1] == T(2));

	BOOST_ASSERT(vN3[N+2] == T(3));
	BOOST_ASSERT(vN4[N+2] == T(3));
	BOOST_ASSERT(vN5[N+2] == T(3));

	BOOST_ASSERT(vN4[N+3] == T(4));
	BOOST_ASSERT(vN5[N+3] == T(4));

	BOOST_ASSERT(vN5[N+4] == T(5));
}

template <typename T>
void test_math_tvec_elem2(void)
{
	test_math_tvec_elem2_T<T, 2>();
	test_math_tvec_elem2_T<T, 3>();
	test_math_tvec_elem2_T<T, 4>();
	test_math_tvec_elem2_T<T, 5>();
	test_math_tvec_elem2_T<T, 6>();
}

BOOST_AUTO_TEST_CASE(math_tvec_elem2)
{
	test_math_tvec_elem2<int>();
	test_math_tvec_elem2<float>();
	test_math_tvec_elem2<double>();
}

template <typename T, unsigned N>
void test_math_taxis_elem1_T_N(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0> aN0;

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(aN0[i] == (i==0?T(1):T(0)));
	}
}

template <typename T, unsigned N, unsigned I>
void test_math_taxis_elem1_T_N(std::integral_constant<unsigned, I>)
{
	test_math_taxis_elem1_T_N<T, N>(
		std::integral_constant<unsigned, I-1>()
	);

	eagine::math::taxis<T, N, I> aNI;

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(aNI[i] == (i==I?T(1):T(0)));
	}
}

template <typename T, unsigned N>
void test_math_taxis_elem1_T(void)
{
	test_math_taxis_elem1_T_N<T, N>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T>
void test_math_taxis_elem1(void)
{
	test_math_taxis_elem1_T<T, 2>();
	test_math_taxis_elem1_T<T, 3>();
	test_math_taxis_elem1_T<T, 4>();
	test_math_taxis_elem1_T<T, 5>();
	test_math_taxis_elem1_T<T, 6>();
	test_math_taxis_elem1_T<T, 7>();
	test_math_taxis_elem1_T<T, 8>();
	test_math_taxis_elem1_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_taxis_elem1)
{
	test_math_taxis_elem1<int>();
	test_math_taxis_elem1<float>();
	test_math_taxis_elem1<double>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
