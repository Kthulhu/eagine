/**
 *  .file test/eagine/math/matrix4.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix4
#include <boost/test/unit_test.hpp>

#include <eagine/meta/int_sequence.hpp>
#include <eagine/math/matrix.hpp>
#include <eagine/math/inverse.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix4)

template <typename ... X>
void test_eat(X...){ }

template <typename T, unsigned R, unsigned C, bool RM, unsigned I, unsigned J>
bool test_math_matrix_from_TRCIJ(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(1111);
	}

	eagine::math::matrix<T,R,C,RM> src =
		eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	eagine::math::matrix<T,I+1,J+1,RM> dst =
		eagine::math::matrix<T,I+1,J+1,RM>::from(src);

	for(unsigned i=0; i<=I; ++i)
	for(unsigned j=0; j<=J; ++j)
	{
		BOOST_ASSERT(get(src,i,j) == get(dst,i,j));
	}

	return true;
}

template <typename T, unsigned R, unsigned C, bool RM, unsigned I, unsigned ... J>
bool test_math_matrix_from_TRCIJ(eagine::meta::unsigned_sequence<J...>)
{
	test_eat(test_math_matrix_from_TRCIJ<T,R,C,RM,I,J>()...);
	return true;
}

template <typename T, unsigned R, unsigned C, bool RM, unsigned ... I>
void test_math_matrix_from_TRCI(eagine::meta::unsigned_sequence<I...>)
{
	test_eat(test_math_matrix_from_TRCIJ<T,R,C,RM,I>(
		eagine::meta::make_unsigned_sequence<C>()
	)...);
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_from_TRC(void)
{
	test_math_matrix_from_TRCI<T,R,C,RM>(
		eagine::meta::make_unsigned_sequence<R>()
	);
}

template <typename T, bool RM>
void test_math_matrix_from(void)
{
	test_math_matrix_from_TRC<T, 2, 2, RM>();
	test_math_matrix_from_TRC<T, 2, 3, RM>();
	test_math_matrix_from_TRC<T, 2, 4, RM>();
	test_math_matrix_from_TRC<T, 2, 8, RM>();

	test_math_matrix_from_TRC<T, 3, 2, RM>();
	test_math_matrix_from_TRC<T, 3, 3, RM>();
	test_math_matrix_from_TRC<T, 3, 4, RM>();
	test_math_matrix_from_TRC<T, 3, 8, RM>();

	test_math_matrix_from_TRC<T, 4, 2, RM>();
	test_math_matrix_from_TRC<T, 4, 3, RM>();
	test_math_matrix_from_TRC<T, 4, 4, RM>();
	test_math_matrix_from_TRC<T, 4, 8, RM>();

	test_math_matrix_from_TRC<T, 8, 2, RM>();
	test_math_matrix_from_TRC<T, 8, 3, RM>();
	test_math_matrix_from_TRC<T, 8, 4, RM>();
	test_math_matrix_from_TRC<T, 8, 8, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_from)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_from<float, true>();
		test_math_matrix_from<float,false>();
		test_math_matrix_from<double, true>();
		test_math_matrix_from<double,false>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
