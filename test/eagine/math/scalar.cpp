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
	eagine::math::scalar<T, 1, V> v1; (void)v1;
	eagine::math::scalar<T, 2, V> v2; (void)v2;
	eagine::math::scalar<T, 3, V> v3; (void)v3;
	eagine::math::scalar<T, 4, V> v4; (void)v4;
	eagine::math::scalar<T, 5, V> v5; (void)v5;
	eagine::math::scalar<T, 6, V> v6; (void)v6;
	eagine::math::scalar<T, 7, V> v7; (void)v7;
	eagine::math::scalar<T, 8, V> v8; (void)v8;
	eagine::math::scalar<T,11, V> v11; (void)v11;
	eagine::math::scalar<T,17, V> v17; (void)v17;
	eagine::math::scalar<T,23, V> v23; (void)v23;

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
	eagine::math::scalar<T, 1, V> v1;
	eagine::math::scalar<T, 1, V> v1c = v1; (void)v1c;

	eagine::math::scalar<T, 2, V> v2;
	eagine::math::scalar<T, 2, V> v2c = v2; (void)v2c;

	eagine::math::scalar<T, 3, V> v3;
	eagine::math::scalar<T, 3, V> v3c = v3; (void)v3c;

	eagine::math::scalar<T, 4, V> v4;
	eagine::math::scalar<T, 4, V> v4c = v4; (void)v4c;

	eagine::math::scalar<T, 5, V> v5;
	eagine::math::scalar<T, 5, V> v5c = v5; (void)v5c;

	eagine::math::scalar<T, 6, V> v6;
	eagine::math::scalar<T, 6, V> v6c = v6; (void)v6c;

	eagine::math::scalar<T, 7, V> v7;
	eagine::math::scalar<T, 7, V> v7c = v7; (void)v7c;

	eagine::math::scalar<T, 8, V> v8;
	eagine::math::scalar<T, 8, V> v8c = v8; (void)v8c;

	eagine::math::scalar<T,11, V> v11;
	eagine::math::scalar<T,11, V> v11c = v11; (void)v11c;

	eagine::math::scalar<T,17, V> v17;
	eagine::math::scalar<T,17, V> v17c = v17; (void)v17c;

	eagine::math::scalar<T,23, V> v23;
	eagine::math::scalar<T,23, V> v23c = v23; (void)v23c;


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

BOOST_AUTO_TEST_SUITE_END()
