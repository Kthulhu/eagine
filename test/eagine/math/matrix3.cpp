/**
 *  .file test/eagine/math/matrix3.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix3
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix.hpp>
#include <eagine/math/inverse.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix3)

template <typename T, unsigned R, unsigned C, bool RM, bool V>
bool test_math_matrix_close(
	const eagine::math::matrix<T, R, C, RM, V>& a,
	const eagine::math::matrix<T, R, C, RM, V>& b
)
{
	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		if(!test_math_close(a[RM?i:j][RM?j:i], b[RM?i:j][RM?j:i]))
		{
			return false;
		}
	}
	return true;
}

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

template <typename Tester, typename T, bool RM, bool V>
void do_test_math_matrix_pair_TRMV(void)
{
	Tester::template apply<T, 1, 1, 1, RM, V>();
	Tester::template apply<T, 1, 1, 5, RM, V>();
	Tester::template apply<T, 1, 1, 5, RM, V>();
	Tester::template apply<T, 1, 1, 5, RM, V>();
	Tester::template apply<T, 1, 1, 5, RM, V>();

	Tester::template apply<T, 1, 2, 1, RM, V>();
	Tester::template apply<T, 1, 2, 2, RM, V>();
	Tester::template apply<T, 1, 2, 3, RM, V>();
	Tester::template apply<T, 1, 2, 4, RM, V>();
	Tester::template apply<T, 1, 2, 5, RM, V>();

	Tester::template apply<T, 1, 3, 1, RM, V>();
	Tester::template apply<T, 1, 3, 2, RM, V>();
	Tester::template apply<T, 1, 3, 3, RM, V>();
	Tester::template apply<T, 1, 3, 4, RM, V>();
	Tester::template apply<T, 1, 3, 5, RM, V>();

	Tester::template apply<T, 1, 4, 1, RM, V>();
	Tester::template apply<T, 1, 4, 2, RM, V>();
	Tester::template apply<T, 1, 4, 3, RM, V>();
	Tester::template apply<T, 1, 4, 4, RM, V>();
	Tester::template apply<T, 1, 4, 5, RM, V>();

	Tester::template apply<T, 1, 5, 1, RM, V>();
	Tester::template apply<T, 1, 5, 2, RM, V>();
	Tester::template apply<T, 1, 5, 3, RM, V>();
	Tester::template apply<T, 1, 5, 4, RM, V>();
	Tester::template apply<T, 1, 5, 5, RM, V>();

	Tester::template apply<T, 2, 1, 1, RM, V>();
	Tester::template apply<T, 2, 1, 2, RM, V>();
	Tester::template apply<T, 2, 1, 3, RM, V>();
	Tester::template apply<T, 2, 1, 4, RM, V>();
	Tester::template apply<T, 2, 1, 5, RM, V>();

	Tester::template apply<T, 2, 2, 1, RM, V>();
	Tester::template apply<T, 2, 2, 2, RM, V>();
	Tester::template apply<T, 2, 2, 3, RM, V>();
	Tester::template apply<T, 2, 2, 4, RM, V>();
	Tester::template apply<T, 2, 2, 5, RM, V>();

	Tester::template apply<T, 2, 3, 1, RM, V>();
	Tester::template apply<T, 2, 3, 2, RM, V>();
	Tester::template apply<T, 2, 3, 3, RM, V>();
	Tester::template apply<T, 2, 3, 4, RM, V>();
	Tester::template apply<T, 2, 3, 5, RM, V>();

	Tester::template apply<T, 2, 4, 1, RM, V>();
	Tester::template apply<T, 2, 4, 2, RM, V>();
	Tester::template apply<T, 2, 4, 3, RM, V>();
	Tester::template apply<T, 2, 4, 4, RM, V>();
	Tester::template apply<T, 2, 4, 5, RM, V>();

	Tester::template apply<T, 2, 5, 1, RM, V>();
	Tester::template apply<T, 2, 5, 2, RM, V>();
	Tester::template apply<T, 2, 5, 3, RM, V>();
	Tester::template apply<T, 2, 5, 4, RM, V>();
	Tester::template apply<T, 2, 5, 5, RM, V>();

	Tester::template apply<T, 3, 1, 1, RM, V>();
	Tester::template apply<T, 3, 1, 2, RM, V>();
	Tester::template apply<T, 3, 1, 3, RM, V>();
	Tester::template apply<T, 3, 1, 4, RM, V>();
	Tester::template apply<T, 3, 1, 5, RM, V>();

	Tester::template apply<T, 3, 2, 1, RM, V>();
	Tester::template apply<T, 3, 2, 2, RM, V>();
	Tester::template apply<T, 3, 2, 3, RM, V>();
	Tester::template apply<T, 3, 2, 4, RM, V>();
	Tester::template apply<T, 3, 2, 5, RM, V>();

	Tester::template apply<T, 3, 3, 1, RM, V>();
	Tester::template apply<T, 3, 3, 2, RM, V>();
	Tester::template apply<T, 3, 3, 3, RM, V>();
	Tester::template apply<T, 3, 3, 4, RM, V>();
	Tester::template apply<T, 3, 3, 5, RM, V>();

	Tester::template apply<T, 3, 4, 1, RM, V>();
	Tester::template apply<T, 3, 4, 2, RM, V>();
	Tester::template apply<T, 3, 4, 3, RM, V>();
	Tester::template apply<T, 3, 4, 4, RM, V>();
	Tester::template apply<T, 3, 4, 5, RM, V>();

	Tester::template apply<T, 3, 5, 1, RM, V>();
	Tester::template apply<T, 3, 5, 2, RM, V>();
	Tester::template apply<T, 3, 5, 3, RM, V>();
	Tester::template apply<T, 3, 5, 4, RM, V>();
	Tester::template apply<T, 3, 5, 5, RM, V>();

	Tester::template apply<T, 4, 1, 1, RM, V>();
	Tester::template apply<T, 4, 1, 2, RM, V>();
	Tester::template apply<T, 4, 1, 3, RM, V>();
	Tester::template apply<T, 4, 1, 4, RM, V>();
	Tester::template apply<T, 4, 1, 5, RM, V>();

	Tester::template apply<T, 4, 2, 1, RM, V>();
	Tester::template apply<T, 4, 2, 2, RM, V>();
	Tester::template apply<T, 4, 2, 3, RM, V>();
	Tester::template apply<T, 4, 2, 4, RM, V>();
	Tester::template apply<T, 4, 2, 5, RM, V>();

	Tester::template apply<T, 4, 3, 1, RM, V>();
	Tester::template apply<T, 4, 3, 2, RM, V>();
	Tester::template apply<T, 4, 3, 3, RM, V>();
	Tester::template apply<T, 4, 3, 4, RM, V>();
	Tester::template apply<T, 4, 3, 5, RM, V>();

	Tester::template apply<T, 4, 4, 1, RM, V>();
	Tester::template apply<T, 4, 4, 2, RM, V>();
	Tester::template apply<T, 4, 4, 3, RM, V>();
	Tester::template apply<T, 4, 4, 4, RM, V>();
	Tester::template apply<T, 4, 4, 5, RM, V>();

	Tester::template apply<T, 4, 5, 1, RM, V>();
	Tester::template apply<T, 4, 5, 2, RM, V>();
	Tester::template apply<T, 4, 5, 3, RM, V>();
	Tester::template apply<T, 4, 5, 4, RM, V>();
	Tester::template apply<T, 4, 5, 5, RM, V>();

	Tester::template apply<T, 5, 1, 1, RM, V>();
	Tester::template apply<T, 5, 1, 2, RM, V>();
	Tester::template apply<T, 5, 1, 3, RM, V>();
	Tester::template apply<T, 5, 1, 4, RM, V>();
	Tester::template apply<T, 5, 1, 5, RM, V>();

	Tester::template apply<T, 5, 2, 1, RM, V>();
	Tester::template apply<T, 5, 2, 2, RM, V>();
	Tester::template apply<T, 5, 2, 3, RM, V>();
	Tester::template apply<T, 5, 2, 4, RM, V>();
	Tester::template apply<T, 5, 2, 5, RM, V>();

	Tester::template apply<T, 5, 3, 1, RM, V>();
	Tester::template apply<T, 5, 3, 2, RM, V>();
	Tester::template apply<T, 5, 3, 3, RM, V>();
	Tester::template apply<T, 5, 3, 4, RM, V>();
	Tester::template apply<T, 5, 3, 5, RM, V>();

	Tester::template apply<T, 5, 4, 1, RM, V>();
	Tester::template apply<T, 5, 4, 2, RM, V>();
	Tester::template apply<T, 5, 4, 3, RM, V>();
	Tester::template apply<T, 5, 4, 4, RM, V>();
	Tester::template apply<T, 5, 4, 5, RM, V>();

	Tester::template apply<T, 5, 5, 1, RM, V>();
	Tester::template apply<T, 5, 5, 2, RM, V>();
	Tester::template apply<T, 5, 5, 3, RM, V>();
	Tester::template apply<T, 5, 5, 4, RM, V>();
	Tester::template apply<T, 5, 5, 5, RM, V>();
}

template <typename Tester, typename T>
void do_test_math_matrix_pair_T(void)
{
	do_test_math_matrix_pair_TRMV<Tester, T, true, true>();
	do_test_math_matrix_pair_TRMV<Tester, T,false, true>();
	do_test_math_matrix_pair_TRMV<Tester, T, true,false>();
	do_test_math_matrix_pair_TRMV<Tester, T,false,false>();
}

template <typename Tester>
void do_test_math_matrix_pair(void)
{
	do_test_math_matrix_pair_T<Tester, float>();
	do_test_math_matrix_pair_T<Tester,double>();
}

struct test_math_matrix_data
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

		using eagine::math::data;

		auto dr = data(m);

		BOOST_ASSERT(dr.size() == R*C);

		for(unsigned k=0; k<R*C; ++k)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(dr.addr()[k] <<equal_to>> d[k]);
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_data)
{
	for(unsigned k=0; k<100; ++k)
	{
		do_test_math_matrix<test_math_matrix_data>();
	}
}

struct test_math_matrix_multiply
{
	template <typename T, unsigned P, unsigned Q, unsigned R, bool RM, bool V>
	static void apply(void)
	{
		T d1[P*Q];
		T d2[Q*R];

		for(unsigned k=0; k<P*Q; ++k)
		{
			d1[k] = std::rand() / T(3);
		}

		for(unsigned k=0; k<Q*R; ++k)
		{
			d2[k] = std::rand() / T(3);
		}

		auto m1 = eagine::math::matrix<T,P,Q, true,V>::from(d1, P*Q);
		auto m2 = eagine::math::matrix<T,Q,R,false,V>::from(d2, Q*R);

		eagine::math::matrix<T,P,R,true,V> m3 = m1*m2;
		eagine::math::matrix<T,P,R,true,V> m4 = trivial_multiply(m1, m2);

		for(unsigned i=0; i<P; ++i)
		for(unsigned j=0; j<R; ++j)
		{
			T s = T(0);

			for(unsigned k=0; k<Q; ++k)
			{
				s += m1[i][k]*m2[j][k];
			}
			BOOST_ASSERT(test_math_close(m3[i][j], s));
			BOOST_ASSERT(test_math_close(m4[i][j], s));
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_multiply)
{
	for(int i=0; i<1000; ++i)
	{
		do_test_math_matrix_pair<test_math_matrix_multiply>();
	}
}

struct test_math_matrix_vector_mult
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d1[R*C];
		T d2[C];

		for(unsigned k=0; k<R*C; ++k)
		{
			d1[k] = std::rand() / T(3);
		}

		for(unsigned k=0; k<C; ++k)
		{
			d2[k] = std::rand() / T(3);
		}

		auto m = eagine::math::matrix<T,R,C,true,V>::from(d1, R*C);
		auto v = eagine::math::vector<T,C,V>::from(d2, C);

		eagine::math::vector<T,R,V> u = m*v;


		for(unsigned i=0; i<R; ++i)
		{
			T s = T(0);
			for(unsigned j=0; j<C; ++j)
			{
				s += m[i][j]*v[j];
			}
			BOOST_ASSERT(test_math_close(u[i], s));
		}
	}
};

BOOST_AUTO_TEST_CASE(math_matrix_vector_mult)
{
	for(int i=0; i<1000; ++i)
	{
		do_test_math_matrix<test_math_matrix_vector_mult>();
	}
}

struct test_math_vector_matrix_mult
{
	template <typename T, unsigned R, unsigned C, bool RM, bool V>
	static void apply(void)
	{
		T d1[R*C];
		T d2[R];

		for(unsigned k=0; k<R*C; ++k)
		{
			d1[k] = std::rand() / T(3);
		}

		for(unsigned k=0; k<R; ++k)
		{
			d2[k] = std::rand() / T(3);
		}

		auto m = eagine::math::matrix<T,R,C,false,V>::from(d1, R*C);
		auto v = eagine::math::vector<T,R,V>::from(d2, R);

		eagine::math::vector<T,C,V> u = v*m;


		for(unsigned j=0; j<C; ++j)
		{
			T s = T(0);
			for(unsigned i=0; i<R; ++i)
			{
				s += v[i]*m[j][i];

			}
			BOOST_ASSERT(test_math_close(u[j], s));
		}
	}
};

BOOST_AUTO_TEST_CASE(math_vector_matrix_mult)
{
	for(int i=0; i<1000; ++i)
	{
		do_test_math_matrix<test_math_vector_matrix_mult>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_mult_identity_TPQR(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	auto m1 = eagine::math::matrix<T,R,C,RM>::from(d, R*C);
	eagine::math::identity<eagine::math::matrix<T,R,C,RM>> e;

	auto m2 = e()*m1;

	BOOST_ASSERT(test_math_matrix_close(m2, m1));
}

template <typename T, bool RM>
void test_math_matrix_mult_identity_T(void)
{
	test_math_matrix_mult_identity_TPQR<T, 1, 1, RM>();
	test_math_matrix_mult_identity_TPQR<T, 2, 2, RM>();
	test_math_matrix_mult_identity_TPQR<T, 3, 3, RM>();
	test_math_matrix_mult_identity_TPQR<T, 4, 4, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_mult_identity)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_mult_identity_T<float, true>();
		// TODO
		//test_math_matrix_mult_identity_T<float,false>();
		test_math_matrix_mult_identity_T<double, true>();
		//test_math_matrix_mult_identity_T<double,false>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_mult_inverse_T(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = (std::rand() % 1111) / T(3);
	}

	auto m1 = eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	if(auto om2 = eagine::math::inverse(m1))
	{
		auto m2 = om2.get();

		eagine::math::identity<eagine::math::matrix<T,R,C,RM>> e;

		BOOST_ASSERT(test_math_matrix_close(e(), m1*m2));
	}
}

template <typename T, bool RM>
void test_math_matrix_mult_inverse_T(void)
{
	test_math_matrix_mult_inverse_T<T, 2, 2, RM>();
	test_math_matrix_mult_inverse_T<T, 3, 3, RM>();
	test_math_matrix_mult_inverse_T<T, 4, 4, RM>();
	test_math_matrix_mult_inverse_T<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_mult_inverse)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_mult_inverse_T<float, true>();
		// TODO
		//test_math_matrix_mult_inverse_T<float,false>();
		test_math_matrix_mult_inverse_T<double, true>();
		//test_math_matrix_mult_inverse_T<double,false>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
