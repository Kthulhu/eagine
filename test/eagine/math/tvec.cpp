/**
 *  .file test/eagine/math/tvec.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_tvec
#include <boost/test/unit_test.hpp>

#include <eagine/math/tvec.hpp>
#include <eagine/math/difference.hpp>
#include <type_traits>
#include <cstdlib>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_tvec)

template <typename T, unsigned N, bool V>
void test_math_tvec_default_ctr_TNV(void)
{
	eagine::math::tvec<T, N, V> v;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
	}
}

template <typename T, bool V>
void test_math_tvec_default_ctr_TV(void)
{
	test_math_tvec_default_ctr_TNV<T, 2, V>();
	test_math_tvec_default_ctr_TNV<T, 3, V>();
	test_math_tvec_default_ctr_TNV<T, 4, V>();
	test_math_tvec_default_ctr_TNV<T, 5, V>();
	test_math_tvec_default_ctr_TNV<T, 6, V>();
	test_math_tvec_default_ctr_TNV<T, 7, V>();
	test_math_tvec_default_ctr_TNV<T, 8, V>();
	test_math_tvec_default_ctr_TNV<T, 9, V>();
}

template <typename T>
void test_math_tvec_default_ctr_T(void)
{
	test_math_tvec_default_ctr_TV<T, true>();
	test_math_tvec_default_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_default_ctr)
{
	test_math_tvec_default_ctr_T<int>();
	test_math_tvec_default_ctr_T<float>();
	test_math_tvec_default_ctr_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_tvec_copy_ctr_TNV(void)
{
	eagine::math::tvec<T, N, V> u;
	eagine::math::tvec<T, N, V> v(u);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
		BOOST_ASSERT(v[i] <<equal_to>> u[i]);
	}
}

template <typename T, bool V>
void test_math_tvec_copy_ctr_TV(void)
{
	test_math_tvec_copy_ctr_TNV<T, 2, V>();
	test_math_tvec_copy_ctr_TNV<T, 3, V>();
	test_math_tvec_copy_ctr_TNV<T, 4, V>();
	test_math_tvec_copy_ctr_TNV<T, 5, V>();
	test_math_tvec_copy_ctr_TNV<T, 6, V>();
	test_math_tvec_copy_ctr_TNV<T, 7, V>();
	test_math_tvec_copy_ctr_TNV<T, 8, V>();
	test_math_tvec_copy_ctr_TNV<T, 9, V>();
}

template <typename T>
void test_math_tvec_copy_ctr_T(void)
{
	test_math_tvec_copy_ctr_TV<T, true>();
	test_math_tvec_copy_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_copy_ctr)
{
	test_math_tvec_copy_ctr_T<int>();
	test_math_tvec_copy_ctr_T<float>();
	test_math_tvec_copy_ctr_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_tvec_data_ctr_TNV(void)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N, V> u(d, N);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(d[i] <<equal_to>> u[i]);
	}
}

template <typename T, bool V>
void test_math_tvec_data_ctr_TV(void)
{
	test_math_tvec_data_ctr_TNV<T, 2, V>();
	test_math_tvec_data_ctr_TNV<T, 3, V>();
	test_math_tvec_data_ctr_TNV<T, 4, V>();
	test_math_tvec_data_ctr_TNV<T, 5, V>();
	test_math_tvec_data_ctr_TNV<T, 6, V>();
	test_math_tvec_data_ctr_TNV<T, 7, V>();
	test_math_tvec_data_ctr_TNV<T, 8, V>();
	test_math_tvec_data_ctr_TNV<T, 9, V>();
}

template <typename T>
void test_math_tvec_data_ctr_T(void)
{
	test_math_tvec_data_ctr_TV<T, true>();
	test_math_tvec_data_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_data_ctr)
{
	test_math_tvec_data_ctr_T<int>();
	test_math_tvec_data_ctr_T<float>();
	test_math_tvec_data_ctr_T<double>();
}

template <typename T, unsigned N, unsigned M, bool V>
void test_math_tvec_data_ctr_2_TNMV(void)
{
	static_assert(M <= N, "");

	T d[M];

	for(unsigned i=0; i<M; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	T f = std::rand() / T(11);

	eagine::math::tvec<T, N, V> u(d, M, f);

	for(unsigned i=0; i<M; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(d[i] <<equal_to>> u[i]);
	}

	for(unsigned i=M; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(f <<equal_to>> u[i]);
	}
}

template <typename T, bool V>
void test_math_tvec_data_ctr_2_TV(void)
{
	test_math_tvec_data_ctr_2_TNMV<T, 2,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 2,2,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 3,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 3,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 3,3,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 4,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 4,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 4,3,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 4,4,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 5,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 5,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 5,3,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 5,4,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 5,5,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 6,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 6,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 6,3,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 6,4,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 6,5,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 6,6,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 7,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,3,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,4,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,5,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,6,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 7,7,V>();

	test_math_tvec_data_ctr_2_TNMV<T, 8,1,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,2,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,3,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,4,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,5,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,6,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,7,V>();
	test_math_tvec_data_ctr_2_TNMV<T, 8,8,V>();
}

template <typename T>
void test_math_tvec_data_ctr_2_T(void)
{
	test_math_tvec_data_ctr_2_TV<T, true>();
	test_math_tvec_data_ctr_2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_data_ctr_2)
{
	test_math_tvec_data_ctr_2_T<int>();
	test_math_tvec_data_ctr_2_T<float>();
	test_math_tvec_data_ctr_2_T<double>();
}

template <typename T, bool V, typename ... P>
void test_math_tvec_init_ctr_TVP(P ... p)
{
	T d[sizeof...(P)] = {T(p)...};
	eagine::math::tvec<T, sizeof...(P), V> v(p...);

	for(unsigned i=0; i<sizeof...(P); ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(d[i] <<equal_to>> v[i]);
	}
}

template <typename T, bool V>
void test_math_tvec_init_ctr_TV(void)
{
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_TVP<T, V>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
}

template <typename T>
void test_math_tvec_init_ctr_T(void)
{
	test_math_tvec_init_ctr_TV<T, true>();
	test_math_tvec_init_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_init_ctr)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_init_ctr_T<int>();
		test_math_tvec_init_ctr_T<float>();
		test_math_tvec_init_ctr_T<double>();
	}
}

template <typename T, unsigned M, bool V>
void test_math_tvec_conv_ctr1_TMNV(const eagine::math::tvec<T, M, V>&)
{
}

template <typename T, unsigned M, unsigned N, bool V>
void test_math_tvec_conv_ctr1_TMNV(const eagine::math::tvec<T, (M>N?N:0), V>& v1)
{
	T x = std::rand() / T(11);
	eagine::math::tvec<T, N+1, V> v2(v1, x);

	using eagine::math::equal_to;
	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(v1[i] <<equal_to>> v2[i]);
	}
	BOOST_ASSERT(x <<equal_to>> v2[N]);

	test_math_tvec_conv_ctr1_TMNV<T, M, V>(v2);
}

template <typename T, bool V>
void test_math_tvec_conv_ctr1_TV(void)
{
	test_math_tvec_conv_ctr1_TMNV<T, 10, V>(
		eagine::math::tvec<T, 1, V>(std::rand()/T(11))
	);
}

template <typename T>
void test_math_tvec_conv_ctr1_T(void)
{
	test_math_tvec_conv_ctr1_TV<T, true>();
	test_math_tvec_conv_ctr1_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr1)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr1_T<int>();
		test_math_tvec_conv_ctr1_T<float>();
		test_math_tvec_conv_ctr1_T<double>();
	}
}

template <typename T, unsigned N, bool V, typename ... P>
void test_math_tvec_conv_ctr2_TNVP(
	const eagine::math::tvec<T, N, V>& v1,
	P ... p
)
{
	T d[sizeof...(P)] = {T(p)...};
	eagine::math::tvec<T, N+sizeof...(P), V> v2(v1, p...);

	using eagine::math::equal_to;
	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(v1[i] <<equal_to>> v2[i]);
	}

	for(unsigned i=0; i<sizeof...(P); ++i)
	{
		BOOST_ASSERT(d[i] <<equal_to>> v2[N+i]);
	}
}

template <typename T, unsigned N, bool V, typename ... P>
void test_math_tvec_conv_ctr2_TNVP(P ... p)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N, V> v(d, N);
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(v, p...);
}

template <typename T, unsigned N, bool V>
void test_math_tvec_conv_ctr2_TNV(void)
{
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
}

template <typename T, bool V>
void test_math_tvec_conv_ctr2_TV(void)
{
	test_math_tvec_conv_ctr2_TNV<T, 2, V>();
	test_math_tvec_conv_ctr2_TNV<T, 3, V>();
	test_math_tvec_conv_ctr2_TNV<T, 4, V>();
	test_math_tvec_conv_ctr2_TNV<T, 5, V>();
	test_math_tvec_conv_ctr2_TNV<T, 6, V>();
	test_math_tvec_conv_ctr2_TNV<T, 7, V>();
}

template <typename T>
void test_math_tvec_conv_ctr2_T(void)
{
	test_math_tvec_conv_ctr2_TV<T, true>();
	test_math_tvec_conv_ctr2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr2_T<int>();
		test_math_tvec_conv_ctr2_T<float>();
		test_math_tvec_conv_ctr2_T<double>();
	}
}

template <typename T, unsigned N, bool V, typename ... P>
void test_math_tvec_conv_ctr3_TNVP(P ... p)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N, V> v(d, N);
	eagine::math::tvec<T, sizeof...(P), V> u(p...);
	eagine::math::tvec<T, N+sizeof...(P), V> w(v, u);

	using eagine::math::equal_to;
	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(v[i] <<equal_to>> w[i]);
	}

	for(unsigned i=0; i<sizeof...(P); ++i)
	{
		BOOST_ASSERT(u[i] <<equal_to>> w[N+i]);
	}
}

template <typename T, unsigned N, bool V>
void test_math_tvec_conv_ctr3_TNV(void)
{
	test_math_tvec_conv_ctr3_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TNVP<T, N, V>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
}

template <typename T, bool V>
void test_math_tvec_conv_ctr3_TV(void)
{
	test_math_tvec_conv_ctr3_TNV<T, 2, V>();
	test_math_tvec_conv_ctr3_TNV<T, 3, V>();
	test_math_tvec_conv_ctr3_TNV<T, 4, V>();
	test_math_tvec_conv_ctr3_TNV<T, 5, V>();
	test_math_tvec_conv_ctr3_TNV<T, 6, V>();
	test_math_tvec_conv_ctr3_TNV<T, 7, V>();
}

template <typename T>
void test_math_tvec_conv_ctr3_T(void)
{
	test_math_tvec_conv_ctr3_TV<T, true>();
	test_math_tvec_conv_ctr3_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr3)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr3_T<int>();
		test_math_tvec_conv_ctr3_T<float>();
		test_math_tvec_conv_ctr3_T<double>();
	}
}

template <typename T, unsigned N, unsigned M, bool V>
void test_math_tvec_conv_ctr4_TNMV(void)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N, V> v(d, N);
	eagine::math::tvec<T, M, V> u(v);

	using eagine::math::equal_to;
	for(unsigned i=0; i<M; ++i)
	{
		BOOST_ASSERT(v[i] <<equal_to>> u[i]);
	}
}

template <typename T, unsigned N, bool V>
void test_math_tvec_conv_ctr4_TNV(std::integral_constant<unsigned, 0>)
{
}

template <typename T, unsigned N, bool V, unsigned M = N>
void test_math_tvec_conv_ctr4_TNV(std::integral_constant<unsigned, M> = {})
{
	test_math_tvec_conv_ctr4_TNMV<T, N, M, V>();
	test_math_tvec_conv_ctr4_TNV<T, N, V>(
		std::integral_constant<unsigned, M-1>()
	);
}

template <typename T, bool V>
void test_math_tvec_conv_ctr4_TV(void)
{
	test_math_tvec_conv_ctr4_TNV<T, 2, V>();
	test_math_tvec_conv_ctr4_TNV<T, 3, V>();
	test_math_tvec_conv_ctr4_TNV<T, 4, V>();
	test_math_tvec_conv_ctr4_TNV<T, 5, V>();
	test_math_tvec_conv_ctr4_TNV<T, 6, V>();
	test_math_tvec_conv_ctr4_TNV<T, 7, V>();
	test_math_tvec_conv_ctr4_TNV<T, 8, V>();
	test_math_tvec_conv_ctr4_TNV<T, 9, V>();
}

template <typename T>
void test_math_tvec_conv_ctr4_T(void)
{
	test_math_tvec_conv_ctr4_TV<T, true>();
	test_math_tvec_conv_ctr4_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr4)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr4_T<int>();
		test_math_tvec_conv_ctr4_T<float>();
		test_math_tvec_conv_ctr4_T<double>();
	}
}


template <typename T, unsigned N, bool V>
void test_math_taxis_default_ctr_TNVI(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0> ax;
}

template <typename T, unsigned N, bool V, unsigned I>
void test_math_taxis_default_ctr_TNVI(std::integral_constant<unsigned, I>)
{
	test_math_taxis_default_ctr_TNVI<T, N, V>(
		std::integral_constant<unsigned, I-1>()
	);
	eagine::math::taxis<T, N, I, V> ax;
}

template <typename T, unsigned N, bool V>
void test_math_taxis_default_ctr_TNV(void)
{
	test_math_taxis_default_ctr_TNVI<T, N, V>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T, bool V>
void test_math_taxis_default_ctr_TV(void)
{
	test_math_taxis_default_ctr_TNV<T, 2, V>();
	test_math_taxis_default_ctr_TNV<T, 3, V>();
	test_math_taxis_default_ctr_TNV<T, 4, V>();
	test_math_taxis_default_ctr_TNV<T, 5, V>();
	test_math_taxis_default_ctr_TNV<T, 6, V>();
	test_math_taxis_default_ctr_TNV<T, 7, V>();
	test_math_taxis_default_ctr_TNV<T, 8, V>();
	test_math_taxis_default_ctr_TNV<T, 9, V>();
}

template <typename T>
void test_math_taxis_default_ctr_T(void)
{
	test_math_taxis_default_ctr_TV<T, true>();
	test_math_taxis_default_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_taxis_default_ctr)
{
	test_math_taxis_default_ctr_T<int>();
	test_math_taxis_default_ctr_T<float>();
	test_math_taxis_default_ctr_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_taxis_elem1_TNVI(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0, V> aN0;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(aN0[i] <<equal_to>> (i==0?T(1):T(0)));
	}
}

template <typename T, unsigned N, bool V, unsigned I>
void test_math_taxis_elem1_TNVI(std::integral_constant<unsigned, I>)
{
	test_math_taxis_elem1_TNVI<T, N, V>(
		std::integral_constant<unsigned, I-1>()
	);

	eagine::math::taxis<T, N, I, V> aNI;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(aNI[i] <<equal_to>> (i==I?T(1):T(0)));
	}
}

template <typename T, unsigned N, bool V>
void test_math_taxis_elem1_TNV(void)
{
	test_math_taxis_elem1_TNVI<T, N, V>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T, bool V>
void test_math_taxis_elem1_TV(void)
{
	test_math_taxis_elem1_TNV<T, 2, V>();
	test_math_taxis_elem1_TNV<T, 3, V>();
	test_math_taxis_elem1_TNV<T, 4, V>();
	test_math_taxis_elem1_TNV<T, 5, V>();
	test_math_taxis_elem1_TNV<T, 6, V>();
	test_math_taxis_elem1_TNV<T, 7, V>();
	test_math_taxis_elem1_TNV<T, 8, V>();
	test_math_taxis_elem1_TNV<T, 9, V>();
}

template <typename T>
void test_math_taxis_elem1_T(void)
{
	test_math_taxis_elem1_TV<T, true>();
	test_math_taxis_elem1_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_taxis_elem1)
{
	test_math_taxis_elem1_T<int>();
	test_math_taxis_elem1_T<float>();
	test_math_taxis_elem1_T<double>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
