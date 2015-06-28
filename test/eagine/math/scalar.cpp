/**
 *  .file test/eagine/math/scalar.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_scalar
#include <boost/test/unit_test.hpp>

#include <eagine/math/scalar.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_scalar)

template <typename T, unsigned N, bool V>
bool test_math_scalar_close(
	const eagine::math::scalar<T, N, V>& a,
	const eagine::math::scalar<T, N, V>& b
)
{
	for(unsigned i=0; i<N; ++i)
	{
		if(!test_math_close(T(a), T(b)))
		{
			return false;
		}
	}
	return true;
}

template <typename T, bool V>
void test_math_scalar_default_ctr_TV(void)
{
	eagine::math::scalar<T, 1, V> s1; (void)s1;
	eagine::math::scalar<T, 2, V> s2; (void)s2;
	eagine::math::scalar<T, 3, V> s3; (void)s3;
	eagine::math::scalar<T, 4, V> s4; (void)s4;
	eagine::math::scalar<T, 5, V> s5; (void)s5;
	eagine::math::scalar<T, 6, V> s6; (void)s6;
	eagine::math::scalar<T, 7, V> s7; (void)s7;
	eagine::math::scalar<T, 8, V> s8; (void)s8;
	eagine::math::scalar<T,11, V> s11; (void)s11;
	eagine::math::scalar<T,17, V> s17; (void)s17;
	eagine::math::scalar<T,23, V> s23; (void)s23;

}

template <typename T>
void test_math_scalar_default_ctr_T(void)
{
	test_math_scalar_default_ctr_TV<T, true>();
	test_math_scalar_default_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_scalar_default_ctr)
{
	test_math_scalar_default_ctr_T<int>();
	test_math_scalar_default_ctr_T<float>();
	test_math_scalar_default_ctr_T<double>();
}

template <typename T, bool V>
void test_math_scalar_copy_ctr_TV(void)
{
	eagine::math::scalar<T, 1, V> s1;
	eagine::math::scalar<T, 1, V> s1c = s1; (void)s1c;

	eagine::math::scalar<T, 2, V> s2;
	eagine::math::scalar<T, 2, V> s2c = s2; (void)s2c;

	eagine::math::scalar<T, 3, V> s3;
	eagine::math::scalar<T, 3, V> s3c = s3; (void)s3c;

	eagine::math::scalar<T, 4, V> s4;
	eagine::math::scalar<T, 4, V> s4c = s4; (void)s4c;

	eagine::math::scalar<T, 5, V> s5;
	eagine::math::scalar<T, 5, V> s5c = s5; (void)s5c;

	eagine::math::scalar<T, 6, V> s6;
	eagine::math::scalar<T, 6, V> s6c = s6; (void)s6c;

	eagine::math::scalar<T, 7, V> s7;
	eagine::math::scalar<T, 7, V> s7c = s7; (void)s7c;

	eagine::math::scalar<T, 8, V> s8;
	eagine::math::scalar<T, 8, V> s8c = s8; (void)s8c;

	eagine::math::scalar<T,11, V> s11;
	eagine::math::scalar<T,11, V> s11c = s11; (void)s11c;

	eagine::math::scalar<T,17, V> s17;
	eagine::math::scalar<T,17, V> s17c = s17; (void)s17c;

	eagine::math::scalar<T,23, V> s23;
	eagine::math::scalar<T,23, V> s23c = s23; (void)s23c;


}

template <typename T>
void test_math_scalar_copy_ctr_T(void)
{
	test_math_scalar_copy_ctr_TV<T, true>();
	test_math_scalar_copy_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_scalar_copy_ctr)
{
	test_math_scalar_copy_ctr_T<int>();
	test_math_scalar_copy_ctr_T<float>();
	test_math_scalar_copy_ctr_T<double>();
}

template <typename T, bool V>
void test_math_scalar_conversion_TV(void)
{
	eagine::math::scalar<T, 1, V> s1;
	T s1v = T(s1); (void)s1v;

	eagine::math::scalar<T, 2, V> s2;
	T s2v = T(s2); (void)s2v;

	eagine::math::scalar<T, 3, V> s3;
	T s3v = T(s3); (void)s3v;

	eagine::math::scalar<T, 4, V> s4;
	T s4v = T(s4); (void)s4v;

	eagine::math::scalar<T, 5, V> s5;
	T s5v = T(s5); (void)s5v;

	eagine::math::scalar<T, 6, V> s6;
	T s6v = T(s6); (void)s6v;

	eagine::math::scalar<T, 7, V> s7;
	T s7v = T(s7); (void)s7v;

	eagine::math::scalar<T, 8, V> s8;
	T s8v = T(s8); (void)s8v;

	eagine::math::scalar<T, 11, V> s11;
	T s11v = T(s11); (void)s11v;

	eagine::math::scalar<T, 17, V> s17;
	T s17v = T(s17); (void)s17v;

	eagine::math::scalar<T, 23, V> s23;
	T s23v = T(s23); (void)s23v;
}

template <typename T>
void test_math_scalar_conversion_T(void)
{
	test_math_scalar_conversion_TV<T, true>();
	test_math_scalar_conversion_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_scalar_conversion)
{
	test_math_scalar_conversion_T<int>();
	test_math_scalar_conversion_T<float>();
	test_math_scalar_conversion_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
