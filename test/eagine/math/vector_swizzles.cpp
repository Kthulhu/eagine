/**
 *  .file test/eagine/math/vector_swizzles.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_vector_swizzles
#include <boost/test/unit_test.hpp>

#include <eagine/math/tvec.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_vector_swizzles)

template <typename T, bool V>
void test_math_vector_swizzles_1_TV(void)
{
	eagine::math::tvec<T,4,V> v(
		std::rand() / T(111), 
		std::rand() / T(111), 
		std::rand() / T(111), 
		std::rand() / T(111)
	);
	T c = std::rand() / T(111);


#include "vector_swizzles.ipp"
}

template <typename T>
void test_math_vector_swizzles_1_T(void)
{
	test_math_vector_swizzles_1_TV<T, true>();
	test_math_vector_swizzles_1_TV<T,false>();
}

void test_math_vector_swizzles_1(void)
{
	test_math_vector_swizzles_1_T<int>();
	test_math_vector_swizzles_1_T<float>();
	test_math_vector_swizzles_1_T<double>();
}

BOOST_AUTO_TEST_CASE(math_vector_swizzles_1)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_vector_swizzles_1();
	}
}

BOOST_AUTO_TEST_SUITE_END()
