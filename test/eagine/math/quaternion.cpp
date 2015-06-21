/**
 *  .file test/eagine/math/quaternion.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_quaternion
#include <boost/test/unit_test.hpp>

#include <eagine/math/quaternion.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_quaternion)

template <typename T, bool V>
void test_math_quaternion_default_ctr_TV(void)
{
	eagine::math::quaternion<T, V> q;
	(void)q;
}

template <typename T>
void test_math_quaternion_default_ctr_T(void)
{
	test_math_quaternion_default_ctr_TV<T, true>();
	test_math_quaternion_default_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_quaternion_default_ctr)
{
	test_math_quaternion_default_ctr_T<float>();
	test_math_quaternion_default_ctr_T<double>();
}

template <typename T, bool V>
void test_math_quaternion_copy_ctr_TV(void)
{
	eagine::math::quaternion<T, V> q1;
	eagine::math::quaternion<T, V> q2((q1));
	(void)q2;
}

template <typename T>
void test_math_quaternion_copy_ctr_T(void)
{
	test_math_quaternion_copy_ctr_TV<T, true>();
	test_math_quaternion_copy_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_quaternion_copy_ctr)
{
	test_math_quaternion_copy_ctr_T<float>();
	test_math_quaternion_copy_ctr_T<double>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
