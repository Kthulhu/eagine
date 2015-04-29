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

template <typename T, bool RM, bool V>
void test_math_matrix_translation_1_TRMV(void)
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

	eagine::math::vector<T, 4, V> v2 = t*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]+tx));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]+ty));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]+tz));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T>
void test_math_matrix_translation_1_T(void)
{
	test_math_matrix_translation_1_TRMV<T, true, true>();
	test_math_matrix_translation_1_TRMV<T, true,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_translation_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_1_T<float>();
		test_math_matrix_translation_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_translation_2_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	T tx1 = std::rand()%100-50;
	T ty1 = std::rand()%100-50;
	T tz1 = std::rand()%100-50;

	T tx2 = std::rand()%100-50;
	T ty2 = std::rand()%100-50;
	T tz2 = std::rand()%100-50;

	eagine::math::translation<eagine::math::matrix<T,4,4,RM,V>> t1(tx1,ty1,tz1);
	eagine::math::translation<eagine::math::matrix<T,4,4,RM,V>> t2(tx2,ty2,tz2);

	eagine::math::vector<T, 4, V> v2 = t1*t2*v1;
	eagine::math::vector<T, 4, V> v3 = t2*t1*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]+tx1+tx2));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]+ty1+ty2));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]+tz1+tz2));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));

	BOOST_ASSERT(test_math_close(v3[0], v1[0]+tx2+tx1));
	BOOST_ASSERT(test_math_close(v3[1], v1[1]+ty2+ty1));
	BOOST_ASSERT(test_math_close(v3[2], v1[2]+tz2+tz1));
	BOOST_ASSERT(test_math_close(v3[3], v1[3]));
}

template <typename T>
void test_math_matrix_translation_2_T(void)
{
	test_math_matrix_translation_2_TRMV<T, true, true>();
	test_math_matrix_translation_2_TRMV<T,false, true>();
	test_math_matrix_translation_2_TRMV<T, true,false>();
	test_math_matrix_translation_2_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_translation_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_2_T<float>();
		test_math_matrix_translation_2_T<double>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_translation_1_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	T ti = std::rand()%100;

	eagine::math::translation_I<eagine::math::matrix<T,4,4,RM,V>, I> t(ti);

	eagine::math::vector<T, 4, V> v2 = t*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]+(i==I?ti:T(0))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_translation_1_TI(void)
{
	test_math_matrix_translation_1_TRMVI<T, true, true, I>();
	test_math_matrix_translation_1_TRMVI<T,false, true, I>();
	test_math_matrix_translation_1_TRMVI<T, true,false, I>();
	test_math_matrix_translation_1_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_translation_I_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_1_TI<float, 0>();
		test_math_matrix_translation_1_TI<float, 1>();
		test_math_matrix_translation_1_TI<float, 2>();

		test_math_matrix_translation_1_TI<double, 0>();
		test_math_matrix_translation_1_TI<double, 1>();
		test_math_matrix_translation_1_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_translation_2_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		std::rand()/T(1000)-std::rand()/T(1000),
		T(1)
	}};

	T ti1 = std::rand()%100-50;
	T ti2 = std::rand()%100-50;

	eagine::math::translation_I<eagine::math::matrix<T,4,4,RM,V>, I> t1(ti1);
	eagine::math::translation_I<eagine::math::matrix<T,4,4,RM,V>, I> t2(ti2);

	eagine::math::vector<T, 4, V> v2 = t1*t2*v1;
	eagine::math::vector<T, 4, V> v3 = t2*t1*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]+(i==I?(ti1+ti2):T(0))));
		BOOST_ASSERT(test_math_close(v3[i], v1[i]+(i==I?(ti2+ti1):T(0))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
	BOOST_ASSERT(test_math_close(v3[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_translation_2_TI(void)
{
	test_math_matrix_translation_2_TRMVI<T, true, true, I>();
	test_math_matrix_translation_2_TRMVI<T,false, true, I>();
	test_math_matrix_translation_2_TRMVI<T, true,false, I>();
	test_math_matrix_translation_2_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_translation_I_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_translation_2_TI<float, 0>();
		test_math_matrix_translation_2_TI<float, 1>();
		test_math_matrix_translation_2_TI<float, 2>();

		test_math_matrix_translation_2_TI<double, 0>();
		test_math_matrix_translation_2_TI<double, 1>();
		test_math_matrix_translation_2_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_rotation_I_1_TRMVI(void)
{
	auto v1 = eagine::math::vector<T, 4, V>::from(
		eagine::math::vector<T, 3, V>::fill(1)-
		eagine::math::vector<T, 3, V>::template axis<I>(1),
		T(1)
	);

	eagine::math::angle<T> ri((std::rand()%1571)/T(1000));

	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM,V>, I> r(ri);

	eagine::math::vector<T, 4, V> v2 = r*v1;

	eagine::math::angle<T> ab = angle_between(
		eagine::math::vector<T, 3, V>::template from<0,1,2>(v1),
		eagine::math::vector<T, 3, V>::template from<0,1,2>(v2)
	);

	BOOST_ASSERT(test_math_close(value(ri), value(ab)));

	using eagine::math::equal_to;
	BOOST_ASSERT(v2[3] <<equal_to>> v1[3]);
}

template <typename T, unsigned I>
void test_math_matrix_rotation_I_1_TI(void)
{
	test_math_matrix_rotation_I_1_TRMVI<T, true, true, I>();
	test_math_matrix_rotation_I_1_TRMVI<T,false, true, I>();
	test_math_matrix_rotation_I_1_TRMVI<T, true,false, I>();
	test_math_matrix_rotation_I_1_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_rotation_I_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_rotation_I_1_TI<float, 0>();
		test_math_matrix_rotation_I_1_TI<float, 1>();
		test_math_matrix_rotation_I_1_TI<float, 2>();

		test_math_matrix_rotation_I_1_TI<double, 0>();
		test_math_matrix_rotation_I_1_TI<double, 1>();
		test_math_matrix_rotation_I_1_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_rotation_I_2_TRMVI(void)
{
	auto v1 = eagine::math::vector<T, 4, V>::from(
		eagine::math::vector<T, 3, V>::fill(1)-
		eagine::math::vector<T, 3, V>::template axis<I>(1),
		T(1)
	);

	eagine::math::angle<T> ri1((std::rand()%1571)/T(2000));
	eagine::math::angle<T> ri2((std::rand()%1571)/T(2000));
	
	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM,V>, I> r1(ri1);
	eagine::math::rotation_I<eagine::math::matrix<T,4,4,RM,V>, I> r2(ri2);

	eagine::math::vector<T, 4, V> v2 = r1*r2*v1;

	eagine::math::angle<T> ab = angle_between(
		eagine::math::vector<T, 3, V>::template from<0,1,2>(v1),
		eagine::math::vector<T, 3, V>::template from<0,1,2>(v2)
	);

	BOOST_ASSERT(test_math_close(value(ri1) + value(ri2), value(ab)));

	using eagine::math::equal_to;
	BOOST_ASSERT(v2[3] <<equal_to>> v1[3]);
}

template <typename T, unsigned I>
void test_math_matrix_rotation_I_2_TI(void)
{
	test_math_matrix_rotation_I_2_TRMVI<T, true, true, I>();
	test_math_matrix_rotation_I_2_TRMVI<T,false, true, I>();
	test_math_matrix_rotation_I_2_TRMVI<T, true,false, I>();
	test_math_matrix_rotation_I_2_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_rotation_I_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_rotation_I_2_TI<float, 0>();
		test_math_matrix_rotation_I_2_TI<float, 1>();
		test_math_matrix_rotation_I_2_TI<float, 2>();

		test_math_matrix_rotation_I_2_TI<double, 0>();
		test_math_matrix_rotation_I_2_TI<double, 1>();
		test_math_matrix_rotation_I_2_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_rotation_a_1_TRMV(void)
{
	auto rv = eagine::math::vector<T, 3, V>::make(
		std::rand()/T(1111),
		std::rand()/T(1111),
		std::rand()/T(1111)
	);

	auto v1 = eagine::math::vector<T, 4, V>::make(
		std::rand()/T(1111),
		std::rand()/T(1111),
		std::rand()/T(1111),
		T(1)
	);

	eagine::math::angle<T> ra((std::rand()%1571)/T(1000));

	eagine::math::rotation_a<eagine::math::matrix<T,4,4,RM,V>> r(rv, ra);

	eagine::math::vector<T, 4, V> v2 = r*v1;

	(void)v2;
/* TODO
	eagine::math::angle<T> ab = angle_between(
		eagine::math::vector<T, 3>::template from<0,1,2>(v1),
		eagine::math::vector<T, 3>::template from<0,1,2>(v2)
	);

	T diff = fabs(value(ri) - value(ab));
	BOOST_ASSERT(test_math_close(diff+1, T(1)));

	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
*/
}

template <typename T>
void test_math_matrix_rotation_a_1_T(void)
{
	test_math_matrix_rotation_a_1_TRMV<T, true, true>();
	test_math_matrix_rotation_a_1_TRMV<T,false, true>();
	test_math_matrix_rotation_a_1_TRMV<T, true,false>();
	test_math_matrix_rotation_a_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_rotation_a_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_rotation_a_1_T<float>();
		test_math_matrix_rotation_a_1_T<float>();

		test_math_matrix_rotation_a_1_T<double>();
		test_math_matrix_rotation_a_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_scale_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T sx = std::rand()%100;
	T sy = std::rand()%100;
	T sz = std::rand()%100;

	eagine::math::scale<eagine::math::matrix<T,4,4,RM,V>> s(sx,sy,sz);

	eagine::math::vector<T, 4, V> v2 = s*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]*sx));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]*sy));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]*sz));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T>
void test_math_matrix_scale_1_T(void)
{
	test_math_matrix_scale_1_TRMV<T, true, true>();
	test_math_matrix_scale_1_TRMV<T,false, true>();
	test_math_matrix_scale_1_TRMV<T, true,false>();
	test_math_matrix_scale_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_scale_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_1_T<float>();
		test_math_matrix_scale_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_scale_2_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T sx1 = std::rand()%10;
	T sy1 = std::rand()%10;
	T sz1 = std::rand()%10;

	T sx2 = std::rand()%10;
	T sy2 = std::rand()%10;
	T sz2 = std::rand()%10;

	eagine::math::scale<eagine::math::matrix<T,4,4,RM,V>> s1(sx1,sy1,sz1);
	eagine::math::scale<eagine::math::matrix<T,4,4,RM,V>> s2(sx2,sy2,sz2);

	eagine::math::vector<T, 4, V> v2 = s1*s2*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]*sx1*sx2));
	BOOST_ASSERT(test_math_close(v2[1], v1[1]*sy1*sy2));
	BOOST_ASSERT(test_math_close(v2[2], v1[2]*sz1*sz2));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T>
void test_math_matrix_scale_2_T(void)
{
	test_math_matrix_scale_2_TRMV<T, true, true>();
	test_math_matrix_scale_2_TRMV<T,false, true>();
	test_math_matrix_scale_2_TRMV<T, true,false>();
	test_math_matrix_scale_2_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_scale_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_2_T<float>();
		test_math_matrix_scale_2_T<double>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_scale_I_1_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T si = std::rand()%100;

	eagine::math::scale_I<eagine::math::matrix<T,4,4,RM,V>, I> s(si);

	eagine::math::vector<T, 4, V> v2 = s*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*(i==I?si:T(1))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_scale_I_1_TI(void)
{
	test_math_matrix_scale_I_1_TRMVI<T, true, true, I>();
	test_math_matrix_scale_I_1_TRMVI<T,false, true, I>();
	test_math_matrix_scale_I_1_TRMVI<T, true,false, I>();
	test_math_matrix_scale_I_1_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_scale_I_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_I_1_TI<float, 0>();
		test_math_matrix_scale_I_1_TI<float, 1>();
		test_math_matrix_scale_I_1_TI<float, 2>();

		test_math_matrix_scale_I_1_TI<double, 0>();
		test_math_matrix_scale_I_1_TI<double, 1>();
		test_math_matrix_scale_I_1_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_scale_I_2_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T si1 = std::rand()%10;
	T si2 = std::rand()%10;

	eagine::math::scale_I<eagine::math::matrix<T,4,4,RM,V>, I> s1(si1);
	eagine::math::scale_I<eagine::math::matrix<T,4,4,RM,V>, I> s2(si2);

	eagine::math::vector<T, 4, V> v2 = s1*s2*v1;
	eagine::math::vector<T, 4, V> v3 = s2*s1*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*(i==I?(si1*si2):T(1))));
		BOOST_ASSERT(test_math_close(v3[i], v1[i]*(i==I?(si2*si1):T(1))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
	BOOST_ASSERT(test_math_close(v3[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_scale_I_2_TI(void)
{
	test_math_matrix_scale_I_2_TRMVI<T, true, true, I>();
	test_math_matrix_scale_I_2_TRMVI<T,false, true, I>();
	test_math_matrix_scale_I_2_TRMVI<T, true,false, I>();
	test_math_matrix_scale_I_2_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_scale_I_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_scale_I_2_TI<float, 0>();
		test_math_matrix_scale_I_2_TI<float, 1>();
		test_math_matrix_scale_I_2_TI<float, 2>();

		test_math_matrix_scale_I_2_TI<double, 0>();
		test_math_matrix_scale_I_2_TI<double, 1>();
		test_math_matrix_scale_I_2_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_uniform_scale_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T si = std::rand()%100;

	eagine::math::uniform_scale<eagine::math::matrix<T,4,4,RM,V>> s(si);

	eagine::math::vector<T, 4, V> v2 = s*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*si));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T>
void test_math_matrix_uniform_scale_1_T(void)
{
	test_math_matrix_uniform_scale_1_TRMV<T, true, true>();
	test_math_matrix_uniform_scale_1_TRMV<T,false, true>();
	test_math_matrix_uniform_scale_1_TRMV<T, true,false>();
	test_math_matrix_uniform_scale_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_uniform_scale_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_uniform_scale_1_T<float>();
		test_math_matrix_uniform_scale_1_T<double>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_uniform_scale_2_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T si1 = std::rand()%100;
	T si2 = std::rand()%100;

	eagine::math::uniform_scale<eagine::math::matrix<T,4,4,RM,V>> s1(si1);
	eagine::math::uniform_scale<eagine::math::matrix<T,4,4,RM,V>> s2(si2);

	eagine::math::vector<T, 4, V> v2 = s1*s2*v1;
	eagine::math::vector<T, 4, V> v3 = s2*s1*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*si1*si2));
		BOOST_ASSERT(test_math_close(v3[i], v1[i]*si2*si1));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
	BOOST_ASSERT(test_math_close(v3[3], v1[3]));
}

template <typename T>
void test_math_matrix_uniform_scale_2_T(void)
{
	test_math_matrix_uniform_scale_2_TRMV<T, true, true>();
	test_math_matrix_uniform_scale_2_TRMV<T,false, true>();
	test_math_matrix_uniform_scale_2_TRMV<T, true,false>();
	test_math_matrix_uniform_scale_2_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_uniform_scale_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_uniform_scale_2_T<float>();
		test_math_matrix_uniform_scale_2_T<double>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_reflection_1_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	bool ri = std::rand()%2==0;

	const eagine::math::reflection_I<eagine::math::matrix<T,4,4,RM,V>, I> r(ri);

	const eagine::math::vector<T, 4, V> v2 = r*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*(((i==I)&&ri)?T(-1):T(1))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_reflection_1_TI(void)
{
	test_math_matrix_reflection_1_TRMVI<T, true, true, I>();
	test_math_matrix_reflection_1_TRMVI<T,false, true, I>();
	test_math_matrix_reflection_1_TRMVI<T, true,false, I>();
	test_math_matrix_reflection_1_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_reflection_I_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_reflection_1_TI<float, 0>();
		test_math_matrix_reflection_1_TI<float, 1>();
		test_math_matrix_reflection_1_TI<float, 2>();

		test_math_matrix_reflection_1_TI<double, 0>();
		test_math_matrix_reflection_1_TI<double, 1>();
		test_math_matrix_reflection_1_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V, unsigned I>
void test_math_matrix_reflection_2_TRMVI(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	bool ri1 = std::rand()%2==0;
	bool ri2 = std::rand()%2==0;

	eagine::math::reflection_I<eagine::math::matrix<T,4,4,RM,V>, I> r1(ri1);
	eagine::math::reflection_I<eagine::math::matrix<T,4,4,RM,V>, I> r2(ri2);

	eagine::math::vector<T, 4, V> v2 = r1*r2*v1;

	for(unsigned i=0; i<3; ++i)
	{
		BOOST_ASSERT(test_math_close(v2[i], v1[i]*(((i==I)&&(ri1!=ri2))?T(-1):T(1))));
	}
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T, unsigned I>
void test_math_matrix_reflection_2_TI(void)
{
	test_math_matrix_reflection_2_TRMVI<T, true, true, I>();
	test_math_matrix_reflection_2_TRMVI<T,false, true, I>();
	test_math_matrix_reflection_2_TRMVI<T, true,false, I>();
	test_math_matrix_reflection_2_TRMVI<T,false,false, I>();
}

BOOST_AUTO_TEST_CASE(math_matrix_reflection_I_2)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_reflection_1_TI<float, 0>();
		test_math_matrix_reflection_1_TI<float, 1>();
		test_math_matrix_reflection_1_TI<float, 2>();

		test_math_matrix_reflection_1_TI<double, 0>();
		test_math_matrix_reflection_1_TI<double, 1>();
		test_math_matrix_reflection_1_TI<double, 2>();
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_shear_1_TRMV(void)
{
	eagine::math::vector<T, 4, V> v1{{
		std::rand()/T(1000),
		std::rand()/T(1000),
		std::rand()/T(1000),
		T(1)
	}};

	T sx = std::rand()%10;
	T sy = std::rand()%10;
	T sz = std::rand()%10;

	eagine::math::shear<eagine::math::matrix<T,4,4,RM,V>> s(sx,sy,sz);

	eagine::math::vector<T, 4, V> v2 = s*v1;

	BOOST_ASSERT(test_math_close(v2[0], v1[0]+v1[1]*sx+v1[2]*sx));
	BOOST_ASSERT(test_math_close(v2[1], v1[0]*sy+v1[1]+v1[2]*sy));
	BOOST_ASSERT(test_math_close(v2[2], v1[0]*sz+v1[1]*sz+v1[2]));
	BOOST_ASSERT(test_math_close(v2[3], v1[3]));
}

template <typename T>
void test_math_matrix_shear_1_T(void)
{
	test_math_matrix_shear_1_TRMV<T, true, true>();
	test_math_matrix_shear_1_TRMV<T,false, true>();
	test_math_matrix_shear_1_TRMV<T, true,false>();
	test_math_matrix_shear_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_shear_1)
{
	for(unsigned k=0; k<1000; ++k)
	{
		test_math_matrix_shear_1_T<float>();
		test_math_matrix_shear_1_T<double>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
