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

template <typename Tester, typename T, bool RM, bool V>
void do_test_math_matrix_TRMV(void)
{
	Tester::template apply<T, 1, 1, RM, V>();
	Tester::template apply<T, 1, 2, RM, V>();
	Tester::template apply<T, 1, 3, RM, V>();
	Tester::template apply<T, 1, 4, RM, V>();
	Tester::template apply<T, 1, 5, RM, V>();

	Tester::template apply<T, 2, 1, RM, V>();
	Tester::template apply<T, 2, 2, RM, V>();
	Tester::template apply<T, 2, 3, RM, V>();
	Tester::template apply<T, 2, 4, RM, V>();
	Tester::template apply<T, 2, 5, RM, V>();

	Tester::template apply<T, 3, 1, RM, V>();
	Tester::template apply<T, 3, 2, RM, V>();
	Tester::template apply<T, 3, 3, RM, V>();
	Tester::template apply<T, 3, 4, RM, V>();
	Tester::template apply<T, 3, 5, RM, V>();

	Tester::template apply<T, 4, 1, RM, V>();
	Tester::template apply<T, 4, 2, RM, V>();
	Tester::template apply<T, 4, 3, RM, V>();
	Tester::template apply<T, 4, 4, RM, V>();
	Tester::template apply<T, 4, 5, RM, V>();

	Tester::template apply<T, 5, 1, RM, V>();
	Tester::template apply<T, 5, 2, RM, V>();
	Tester::template apply<T, 5, 3, RM, V>();
	Tester::template apply<T, 5, 4, RM, V>();
	Tester::template apply<T, 5, 5, RM, V>();
}

template <typename Tester, typename T>
void do_test_math_matrix_T(void)
{
	do_test_math_matrix_TRMV<Tester, T, true, true>();
	do_test_math_matrix_TRMV<Tester, T,false, true>();
	do_test_math_matrix_TRMV<Tester, T, true,false>();
	do_test_math_matrix_TRMV<Tester, T,false,false>();
}

template <typename Tester>
void do_test_math_matrix(void)
{
	do_test_math_matrix_T<Tester, float>();
	do_test_math_matrix_T<Tester,double>();
}

struct test_math_matrix_rows
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		eagine::math::matrix<T,R,C,RM,V> m;

		using eagine::math::rows;

		BOOST_ASSERT(rows(m) == R);
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_rows)
{
	do_test_math_matrix<test_math_matrix_rows>();
}

struct test_math_matrix_cols
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		eagine::math::matrix<T,R,C,RM,V> m;

		using eagine::math::columns;

		BOOST_ASSERT(columns(m) == C);
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_cols)
{
	do_test_math_matrix<test_math_matrix_cols>();
}

struct test_math_matrix_row_major
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		eagine::math::matrix<T,R,C,RM,V> m;

		using eagine::math::row_major;

		BOOST_ASSERT(row_major(m) == RM);
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_row_major)
{
	do_test_math_matrix<test_math_matrix_row_major>();
}

struct test_math_matrix_get
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d[R*C];

		for(unsigned k=0; k<R*C; ++k)
		{
			d[k] = std::rand() / T(3);
		}

		auto m = eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);

		for(unsigned i=0; i<R; ++i)
		{
			for(unsigned j=0; j<C; ++j)
			{
				unsigned k = RM?(i*C+j):(j*R+i);

				using eagine::math::equal_to;
				BOOST_ASSERT(get(m,i,j) <<equal_to>> d[k]);
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_get)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_get>();
	}
}

struct test_math_matrix_reorder
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d[R*C];

		for(unsigned k=0; k<R*C; ++k)
		{
			d[k] = std::rand() / T(3);
		}

		auto m1 = eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);

		using eagine::math::reorder;
		eagine::math::matrix<T,R,C,!RM,V> m2 = reorder(m1);

		for(unsigned i=0; i<R; ++i)
		{
			for(unsigned j=0; j<C; ++j)
			{
				using eagine::math::equal_to;
				BOOST_ASSERT(get(m1,i,j) <<equal_to>> get(m2,i,j));
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_reorder)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_reorder>();
	}
}

struct test_math_matrix_transpose
{
	template <typename T, unsigned M, unsigned N, bool RM, bool V>
	static void apply(void)
	{
		T d[M*N];

		for(unsigned k=0; k<M*N; ++k)
		{
			d[k] = std::rand() / T(3);
		}

		auto m1 = eagine::math::matrix<T,M,N,RM,V>::from(d, M*N);

		using eagine::math::transpose;
		eagine::math::matrix<T,N,M,RM,V> m2 = transpose(m1);

		for(unsigned i=0; i<M; ++i)
		{
			for(unsigned j=0; j<N; ++j)
			{
				using eagine::math::equal_to;
				BOOST_ASSERT(get(m1,i,j) <<equal_to>> get(m2,j,i));
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_transpose)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_transpose>();
	}
}

struct test_math_matrix_row
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d[R*C];

		for(unsigned k=0; k<R*C; ++k)
		{
			d[k] = std::rand() / T(3);
		}

		auto m = eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);

		for(unsigned i=0; i<R; ++i)
		{
			using eagine::math::row;
			eagine::math::vector<T, C, V> r = row(m, i);

			for(unsigned j=0; j<C; ++j)
			{
				unsigned k = RM?(i*C+j):(j*R+i);

				using eagine::math::equal_to;
				BOOST_ASSERT(r[j] <<equal_to>> d[k]);
				BOOST_ASSERT(r[j] <<equal_to>> get(m,i,j));
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_row)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_row>();
	}
}

struct test_math_matrix_col
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d[R*C];

		for(unsigned k=0; k<R*C; ++k)
		{
			d[k] = std::rand() / T(3);
		}

		auto m = eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);

		for(unsigned j=0; j<C; ++j)
		{
			using eagine::math::column;
			eagine::math::vector<T, R, V> c = column(m, j);

			for(unsigned i=0; i<R; ++i)
			{
				unsigned k = RM?(i*C+j):(j*R+i);

				using eagine::math::equal_to;
				BOOST_ASSERT(c[i] <<equal_to>> d[k]);
				BOOST_ASSERT(c[i] <<equal_to>> get(m,i,j));
			}
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_col)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_col>();
	}
}

struct test_math_matrix_data
{
	template <typename T, unsigned N, typename Range>
	static void test_data_range(const T(&a)[N], Range& r)
	{
		BOOST_ASSERT(r.addr() != nullptr);
		BOOST_ASSERT(r.size() == N);

		const T* b = r.begin();
		const T* e = r.end();

		BOOST_ASSERT(b != e);

		for(unsigned i=0; i<N; ++i)
		{
			const T* o = r.offs(i);

			using eagine::math::equal_to;
			BOOST_ASSERT(r[i] <<equal_to>> a[i]);
			BOOST_ASSERT(*o  <<equal_to>> a[i]);
		}

		for(T x : r) { (void)x; }

		for(unsigned i=0; i<N; ++i)
		{
			auto s = r.slice(i);
			BOOST_ASSERT(s.size() == N-i);
		}
	}

	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T a[R*C];

		for(unsigned i=0; i<R*C; ++i)
		{
			a[i] = std::rand() / T(R*C);
		}

		auto ma = eagine::math::matrix<T, R, C, RM, V>::from(a, R*C);

		auto d = data(ma);
		eagine::base::typed_memory_range<const T> r = d.range();

		test_data_range(a, d);
		test_data_range(a, r);
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_data)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_data>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
