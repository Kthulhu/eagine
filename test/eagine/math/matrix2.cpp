/**
 *  .file test/eagine/math/matrix2.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix2
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix2)

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_rows_TRC(void)
{
	eagine::math::matrix<T,R,C,RM> m;

	using eagine::math::rows;

	BOOST_ASSERT(rows(m) == R);
}

template <typename T, bool RM>
void test_math_matrix_rows(void)
{
	test_math_matrix_rows_TRC<T, 1, 1, RM>();
	test_math_matrix_rows_TRC<T, 1, 2, RM>();
	test_math_matrix_rows_TRC<T, 1, 3, RM>();
	test_math_matrix_rows_TRC<T, 1, 4, RM>();
	test_math_matrix_rows_TRC<T, 1, 5, RM>();

	test_math_matrix_rows_TRC<T, 2, 1, RM>();
	test_math_matrix_rows_TRC<T, 2, 2, RM>();
	test_math_matrix_rows_TRC<T, 2, 3, RM>();
	test_math_matrix_rows_TRC<T, 2, 4, RM>();
	test_math_matrix_rows_TRC<T, 2, 5, RM>();

	test_math_matrix_rows_TRC<T, 3, 1, RM>();
	test_math_matrix_rows_TRC<T, 3, 2, RM>();
	test_math_matrix_rows_TRC<T, 3, 3, RM>();
	test_math_matrix_rows_TRC<T, 3, 4, RM>();
	test_math_matrix_rows_TRC<T, 3, 5, RM>();

	test_math_matrix_rows_TRC<T, 4, 1, RM>();
	test_math_matrix_rows_TRC<T, 4, 2, RM>();
	test_math_matrix_rows_TRC<T, 4, 3, RM>();
	test_math_matrix_rows_TRC<T, 4, 4, RM>();
	test_math_matrix_rows_TRC<T, 4, 5, RM>();

	test_math_matrix_rows_TRC<T, 5, 1, RM>();
	test_math_matrix_rows_TRC<T, 5, 2, RM>();
	test_math_matrix_rows_TRC<T, 5, 3, RM>();
	test_math_matrix_rows_TRC<T, 5, 4, RM>();
	test_math_matrix_rows_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_rows)
{
	test_math_matrix_rows<float, true>();
	test_math_matrix_rows<float,false>();
	test_math_matrix_rows<double, true>();
	test_math_matrix_rows<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_cols_TRC(void)
{
	eagine::math::matrix<T,R,C,RM> m;

	using eagine::math::columns;

	BOOST_ASSERT(columns(m) == C);
}

template <typename T, bool RM>
void test_math_matrix_cols(void)
{
	test_math_matrix_cols_TRC<T, 1, 1, RM>();
	test_math_matrix_cols_TRC<T, 1, 2, RM>();
	test_math_matrix_cols_TRC<T, 1, 3, RM>();
	test_math_matrix_cols_TRC<T, 1, 4, RM>();
	test_math_matrix_cols_TRC<T, 1, 5, RM>();

	test_math_matrix_cols_TRC<T, 2, 1, RM>();
	test_math_matrix_cols_TRC<T, 2, 2, RM>();
	test_math_matrix_cols_TRC<T, 2, 3, RM>();
	test_math_matrix_cols_TRC<T, 2, 4, RM>();
	test_math_matrix_cols_TRC<T, 2, 5, RM>();

	test_math_matrix_cols_TRC<T, 3, 1, RM>();
	test_math_matrix_cols_TRC<T, 3, 2, RM>();
	test_math_matrix_cols_TRC<T, 3, 3, RM>();
	test_math_matrix_cols_TRC<T, 3, 4, RM>();
	test_math_matrix_cols_TRC<T, 3, 5, RM>();

	test_math_matrix_cols_TRC<T, 4, 1, RM>();
	test_math_matrix_cols_TRC<T, 4, 2, RM>();
	test_math_matrix_cols_TRC<T, 4, 3, RM>();
	test_math_matrix_cols_TRC<T, 4, 4, RM>();
	test_math_matrix_cols_TRC<T, 4, 5, RM>();

	test_math_matrix_cols_TRC<T, 5, 1, RM>();
	test_math_matrix_cols_TRC<T, 5, 2, RM>();
	test_math_matrix_cols_TRC<T, 5, 3, RM>();
	test_math_matrix_cols_TRC<T, 5, 4, RM>();
	test_math_matrix_cols_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_cols)
{
	test_math_matrix_cols<float, true>();
	test_math_matrix_cols<float,false>();
	test_math_matrix_cols<double, true>();
	test_math_matrix_cols<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_row_major_TRC(void)
{
	eagine::math::matrix<T,R,C,RM> m;

	using eagine::math::row_major;

	BOOST_ASSERT(row_major(m) == RM);
}

template <typename T, bool RM>
void test_math_matrix_row_major(void)
{
	test_math_matrix_row_major_TRC<T, 1, 1, RM>();
	test_math_matrix_row_major_TRC<T, 1, 2, RM>();
	test_math_matrix_row_major_TRC<T, 1, 3, RM>();
	test_math_matrix_row_major_TRC<T, 1, 4, RM>();
	test_math_matrix_row_major_TRC<T, 1, 5, RM>();

	test_math_matrix_row_major_TRC<T, 2, 1, RM>();
	test_math_matrix_row_major_TRC<T, 2, 2, RM>();
	test_math_matrix_row_major_TRC<T, 2, 3, RM>();
	test_math_matrix_row_major_TRC<T, 2, 4, RM>();
	test_math_matrix_row_major_TRC<T, 2, 5, RM>();

	test_math_matrix_row_major_TRC<T, 3, 1, RM>();
	test_math_matrix_row_major_TRC<T, 3, 2, RM>();
	test_math_matrix_row_major_TRC<T, 3, 3, RM>();
	test_math_matrix_row_major_TRC<T, 3, 4, RM>();
	test_math_matrix_row_major_TRC<T, 3, 5, RM>();

	test_math_matrix_row_major_TRC<T, 4, 1, RM>();
	test_math_matrix_row_major_TRC<T, 4, 2, RM>();
	test_math_matrix_row_major_TRC<T, 4, 3, RM>();
	test_math_matrix_row_major_TRC<T, 4, 4, RM>();
	test_math_matrix_row_major_TRC<T, 4, 5, RM>();

	test_math_matrix_row_major_TRC<T, 5, 1, RM>();
	test_math_matrix_row_major_TRC<T, 5, 2, RM>();
	test_math_matrix_row_major_TRC<T, 5, 3, RM>();
	test_math_matrix_row_major_TRC<T, 5, 4, RM>();
	test_math_matrix_row_major_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_row_major)
{
	test_math_matrix_row_major<float, true>();
	test_math_matrix_row_major<float,false>();
	test_math_matrix_row_major<double, true>();
	test_math_matrix_row_major<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_get_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m = eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	for(unsigned i=0; i<R; ++i)
	{
		for(unsigned j=0; j<C; ++j)
		{
			unsigned k = RM?(i*C+j):(j*R+i);
			BOOST_ASSERT(get(m,i,j) == d[k]);
		}
	}
}

template <typename T, bool RM>
void test_math_matrix_get(void)
{
	test_math_matrix_get_TRC<T, 1, 1, RM>();
	test_math_matrix_get_TRC<T, 1, 2, RM>();
	test_math_matrix_get_TRC<T, 1, 3, RM>();
	test_math_matrix_get_TRC<T, 1, 4, RM>();
	test_math_matrix_get_TRC<T, 1, 5, RM>();

	test_math_matrix_get_TRC<T, 2, 1, RM>();
	test_math_matrix_get_TRC<T, 2, 2, RM>();
	test_math_matrix_get_TRC<T, 2, 3, RM>();
	test_math_matrix_get_TRC<T, 2, 4, RM>();
	test_math_matrix_get_TRC<T, 2, 5, RM>();

	test_math_matrix_get_TRC<T, 3, 1, RM>();
	test_math_matrix_get_TRC<T, 3, 2, RM>();
	test_math_matrix_get_TRC<T, 3, 3, RM>();
	test_math_matrix_get_TRC<T, 3, 4, RM>();
	test_math_matrix_get_TRC<T, 3, 5, RM>();

	test_math_matrix_get_TRC<T, 4, 1, RM>();
	test_math_matrix_get_TRC<T, 4, 2, RM>();
	test_math_matrix_get_TRC<T, 4, 3, RM>();
	test_math_matrix_get_TRC<T, 4, 4, RM>();
	test_math_matrix_get_TRC<T, 4, 5, RM>();

	test_math_matrix_get_TRC<T, 5, 1, RM>();
	test_math_matrix_get_TRC<T, 5, 2, RM>();
	test_math_matrix_get_TRC<T, 5, 3, RM>();
	test_math_matrix_get_TRC<T, 5, 4, RM>();
	test_math_matrix_get_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_get)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_get<float, true>();
		test_math_matrix_get<float,false>();
		test_math_matrix_get<double, true>();
		test_math_matrix_get<double,false>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_reorder_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m1 = eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	using eagine::math::reorder;
	eagine::math::matrix<T,R,C,!RM> m2 = reorder(m1);

	for(unsigned i=0; i<R; ++i)
	{
		for(unsigned j=0; j<C; ++j)
		{
			BOOST_ASSERT(get(m1,i,j) == get(m2,i,j));
		}
	}
}

template <typename T, bool RM>
void test_math_matrix_reorder(void)
{
	test_math_matrix_reorder_TRC<T, 1, 1, RM>();
	test_math_matrix_reorder_TRC<T, 1, 2, RM>();
	test_math_matrix_reorder_TRC<T, 1, 3, RM>();
	test_math_matrix_reorder_TRC<T, 1, 4, RM>();
	test_math_matrix_reorder_TRC<T, 1, 5, RM>();

	test_math_matrix_reorder_TRC<T, 2, 1, RM>();
	test_math_matrix_reorder_TRC<T, 2, 2, RM>();
	test_math_matrix_reorder_TRC<T, 2, 3, RM>();
	test_math_matrix_reorder_TRC<T, 2, 4, RM>();
	test_math_matrix_reorder_TRC<T, 2, 5, RM>();

	test_math_matrix_reorder_TRC<T, 3, 1, RM>();
	test_math_matrix_reorder_TRC<T, 3, 2, RM>();
	test_math_matrix_reorder_TRC<T, 3, 3, RM>();
	test_math_matrix_reorder_TRC<T, 3, 4, RM>();
	test_math_matrix_reorder_TRC<T, 3, 5, RM>();

	test_math_matrix_reorder_TRC<T, 4, 1, RM>();
	test_math_matrix_reorder_TRC<T, 4, 2, RM>();
	test_math_matrix_reorder_TRC<T, 4, 3, RM>();
	test_math_matrix_reorder_TRC<T, 4, 4, RM>();
	test_math_matrix_reorder_TRC<T, 4, 5, RM>();

	test_math_matrix_reorder_TRC<T, 5, 1, RM>();
	test_math_matrix_reorder_TRC<T, 5, 2, RM>();
	test_math_matrix_reorder_TRC<T, 5, 3, RM>();
	test_math_matrix_reorder_TRC<T, 5, 4, RM>();
	test_math_matrix_reorder_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_reorder)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_reorder<float, true>();
		test_math_matrix_reorder<float,false>();
		test_math_matrix_reorder<double, true>();
		test_math_matrix_reorder<double,false>();
	}
}

template <typename T, unsigned M, unsigned N, bool RM>
void test_math_matrix_transpose_TRC(void)
{
	T d[M*N];

	for(unsigned k=0; k<M*N; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m1 = eagine::math::matrix<T,M,N,RM>::from(d, M*N);

	using eagine::math::transpose;
	eagine::math::matrix<T,N,M,RM> m2 = transpose(m1);

	for(unsigned i=0; i<M; ++i)
	{
		for(unsigned j=0; j<N; ++j)
		{
			BOOST_ASSERT(get(m1,i,j) == get(m2,j,i));
		}
	}
}

template <typename T, bool RM>
void test_math_matrix_transpose(void)
{
	test_math_matrix_transpose_TRC<T, 1, 1, RM>();
	test_math_matrix_transpose_TRC<T, 1, 2, RM>();
	test_math_matrix_transpose_TRC<T, 1, 3, RM>();
	test_math_matrix_transpose_TRC<T, 1, 4, RM>();
	test_math_matrix_transpose_TRC<T, 1, 5, RM>();

	test_math_matrix_transpose_TRC<T, 2, 1, RM>();
	test_math_matrix_transpose_TRC<T, 2, 2, RM>();
	test_math_matrix_transpose_TRC<T, 2, 3, RM>();
	test_math_matrix_transpose_TRC<T, 2, 4, RM>();
	test_math_matrix_transpose_TRC<T, 2, 5, RM>();

	test_math_matrix_transpose_TRC<T, 3, 1, RM>();
	test_math_matrix_transpose_TRC<T, 3, 2, RM>();
	test_math_matrix_transpose_TRC<T, 3, 3, RM>();
	test_math_matrix_transpose_TRC<T, 3, 4, RM>();
	test_math_matrix_transpose_TRC<T, 3, 5, RM>();

	test_math_matrix_transpose_TRC<T, 4, 1, RM>();
	test_math_matrix_transpose_TRC<T, 4, 2, RM>();
	test_math_matrix_transpose_TRC<T, 4, 3, RM>();
	test_math_matrix_transpose_TRC<T, 4, 4, RM>();
	test_math_matrix_transpose_TRC<T, 4, 5, RM>();

	test_math_matrix_transpose_TRC<T, 5, 1, RM>();
	test_math_matrix_transpose_TRC<T, 5, 2, RM>();
	test_math_matrix_transpose_TRC<T, 5, 3, RM>();
	test_math_matrix_transpose_TRC<T, 5, 4, RM>();
	test_math_matrix_transpose_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_transpose)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_transpose<float, true>();
		test_math_matrix_transpose<float,false>();
		test_math_matrix_transpose<double, true>();
		test_math_matrix_transpose<double,false>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_row_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m = eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	for(unsigned i=0; i<R; ++i)
	{
		using eagine::math::row;
		eagine::math::vector<T, C> r = row(m, i);

		for(unsigned j=0; j<C; ++j)
		{
			unsigned k = RM?(i*C+j):(j*R+i);
			BOOST_ASSERT(r[j] == d[k]);
			BOOST_ASSERT(r[j] == get(m,i,j));
		}
	}
}

template <typename T, bool RM>
void test_math_matrix_row(void)
{
	test_math_matrix_row_TRC<T, 1, 1, RM>();
	test_math_matrix_row_TRC<T, 1, 2, RM>();
	test_math_matrix_row_TRC<T, 1, 3, RM>();
	test_math_matrix_row_TRC<T, 1, 4, RM>();
	test_math_matrix_row_TRC<T, 1, 5, RM>();

	test_math_matrix_row_TRC<T, 2, 1, RM>();
	test_math_matrix_row_TRC<T, 2, 2, RM>();
	test_math_matrix_row_TRC<T, 2, 3, RM>();
	test_math_matrix_row_TRC<T, 2, 4, RM>();
	test_math_matrix_row_TRC<T, 2, 5, RM>();

	test_math_matrix_row_TRC<T, 3, 1, RM>();
	test_math_matrix_row_TRC<T, 3, 2, RM>();
	test_math_matrix_row_TRC<T, 3, 3, RM>();
	test_math_matrix_row_TRC<T, 3, 4, RM>();
	test_math_matrix_row_TRC<T, 3, 5, RM>();

	test_math_matrix_row_TRC<T, 4, 1, RM>();
	test_math_matrix_row_TRC<T, 4, 2, RM>();
	test_math_matrix_row_TRC<T, 4, 3, RM>();
	test_math_matrix_row_TRC<T, 4, 4, RM>();
	test_math_matrix_row_TRC<T, 4, 5, RM>();

	test_math_matrix_row_TRC<T, 5, 1, RM>();
	test_math_matrix_row_TRC<T, 5, 2, RM>();
	test_math_matrix_row_TRC<T, 5, 3, RM>();
	test_math_matrix_row_TRC<T, 5, 4, RM>();
	test_math_matrix_row_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_row)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_row<float, true>();
		test_math_matrix_row<float,false>();
		test_math_matrix_row<double, true>();
		test_math_matrix_row<double,false>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_col_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m = eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	for(unsigned j=0; j<C; ++j)
	{
		using eagine::math::column;
		eagine::math::vector<T, R> c = column(m, j);

		for(unsigned i=0; i<R; ++i)
		{
			unsigned k = RM?(i*C+j):(j*R+i);
			BOOST_ASSERT(c[i] == d[k]);
			BOOST_ASSERT(c[i] == get(m,i,j));
		}
	}
}

template <typename T, bool RM>
void test_math_matrix_col(void)
{
	test_math_matrix_col_TRC<T, 1, 1, RM>();
	test_math_matrix_col_TRC<T, 1, 2, RM>();
	test_math_matrix_col_TRC<T, 1, 3, RM>();
	test_math_matrix_col_TRC<T, 1, 4, RM>();
	test_math_matrix_col_TRC<T, 1, 5, RM>();

	test_math_matrix_col_TRC<T, 2, 1, RM>();
	test_math_matrix_col_TRC<T, 2, 2, RM>();
	test_math_matrix_col_TRC<T, 2, 3, RM>();
	test_math_matrix_col_TRC<T, 2, 4, RM>();
	test_math_matrix_col_TRC<T, 2, 5, RM>();

	test_math_matrix_col_TRC<T, 3, 1, RM>();
	test_math_matrix_col_TRC<T, 3, 2, RM>();
	test_math_matrix_col_TRC<T, 3, 3, RM>();
	test_math_matrix_col_TRC<T, 3, 4, RM>();
	test_math_matrix_col_TRC<T, 3, 5, RM>();

	test_math_matrix_col_TRC<T, 4, 1, RM>();
	test_math_matrix_col_TRC<T, 4, 2, RM>();
	test_math_matrix_col_TRC<T, 4, 3, RM>();
	test_math_matrix_col_TRC<T, 4, 4, RM>();
	test_math_matrix_col_TRC<T, 4, 5, RM>();

	test_math_matrix_col_TRC<T, 5, 1, RM>();
	test_math_matrix_col_TRC<T, 5, 2, RM>();
	test_math_matrix_col_TRC<T, 5, 3, RM>();
	test_math_matrix_col_TRC<T, 5, 4, RM>();
	test_math_matrix_col_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_col)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_matrix_col<float, true>();
		test_math_matrix_col<float,false>();
		test_math_matrix_col<double, true>();
		test_math_matrix_col<double,false>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
