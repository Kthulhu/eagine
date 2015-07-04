/**
 *  .file test/eagine/math/plane.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_plane
#include <boost/test/unit_test.hpp>

#include <eagine/math/plane.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_plane)

template <typename T, bool V>
void test_math_plane_construct_1_TV(void)
{
	T x = T(std::rand());
	T y = T(std::rand());
	T z = T(std::rand());
	T w = T(std::rand());

	eagine::math::plane<T, V> p{x,y,z,w};

	BOOST_ASSERT((test_math_close(p.equation().x(), x)));
	BOOST_ASSERT((test_math_close(p.equation().y(), y)));
	BOOST_ASSERT((test_math_close(p.equation().z(), z)));
	BOOST_ASSERT((test_math_close(p.equation().w(), w)));
}

template <typename T>
void test_math_plane_construct_1_T(void)
{
	test_math_plane_construct_1_TV<T, true>();
	test_math_plane_construct_1_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_1)
{
	test_math_plane_construct_1_T<float>();
	test_math_plane_construct_1_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
