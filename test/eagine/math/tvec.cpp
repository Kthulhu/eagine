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

template <typename T, unsigned N>
void test_math_tvec_default_ctr_T(void)
{
	eagine::math::tvec<T, N> v;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
	}
}

template <typename T>
void test_math_tvec_default_ctr(void)
{
	test_math_tvec_default_ctr_T<T, 2>();
	test_math_tvec_default_ctr_T<T, 3>();
	test_math_tvec_default_ctr_T<T, 4>();
	test_math_tvec_default_ctr_T<T, 5>();
	test_math_tvec_default_ctr_T<T, 6>();
	test_math_tvec_default_ctr_T<T, 7>();
	test_math_tvec_default_ctr_T<T, 8>();
	test_math_tvec_default_ctr_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_tvec_default_ctr)
{
	test_math_tvec_default_ctr<int>();
	test_math_tvec_default_ctr<float>();
	test_math_tvec_default_ctr<double>();
}

template <typename T, unsigned N>
void test_math_tvec_copy_ctr_T(void)
{
	eagine::math::tvec<T, N> u;
	eagine::math::tvec<T, N> v(u);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
		BOOST_ASSERT(v[i] <<equal_to>> u[i]);
	}
}

template <typename T>
void test_math_tvec_copy_ctr(void)
{
	test_math_tvec_copy_ctr_T<T, 2>();
	test_math_tvec_copy_ctr_T<T, 3>();
	test_math_tvec_copy_ctr_T<T, 4>();
	test_math_tvec_copy_ctr_T<T, 5>();
	test_math_tvec_copy_ctr_T<T, 6>();
	test_math_tvec_copy_ctr_T<T, 7>();
	test_math_tvec_copy_ctr_T<T, 8>();
	test_math_tvec_copy_ctr_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_tvec_copy_ctr)
{
	test_math_tvec_copy_ctr<int>();
	test_math_tvec_copy_ctr<float>();
	test_math_tvec_copy_ctr<double>();
}

template <typename T, unsigned N>
void test_math_tvec_data_ctr_T(void)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N> u(d, N);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(d[i] <<equal_to>> u[i]);
	}
}

template <typename T>
void test_math_tvec_data_ctr(void)
{
	test_math_tvec_data_ctr_T<T, 2>();
	test_math_tvec_data_ctr_T<T, 3>();
	test_math_tvec_data_ctr_T<T, 4>();
	test_math_tvec_data_ctr_T<T, 5>();
	test_math_tvec_data_ctr_T<T, 6>();
	test_math_tvec_data_ctr_T<T, 7>();
	test_math_tvec_data_ctr_T<T, 8>();
	test_math_tvec_data_ctr_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_tvec_data_ctr)
{
	test_math_tvec_data_ctr<int>();
	test_math_tvec_data_ctr<float>();
	test_math_tvec_data_ctr<double>();
}

template <typename T, unsigned N, unsigned M>
void test_math_tvec_data_ctr_2_T(void)
{
	static_assert(M <= N, "");

	T d[M];

	for(unsigned i=0; i<M; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	T f = std::rand() / T(11);

	eagine::math::tvec<T, N> u(d, M, f);

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

template <typename T>
void test_math_tvec_data_ctr_2(void)
{
	test_math_tvec_data_ctr_2_T<T, 2,1>();
	test_math_tvec_data_ctr_2_T<T, 2,2>();

	test_math_tvec_data_ctr_2_T<T, 3,1>();
	test_math_tvec_data_ctr_2_T<T, 3,2>();
	test_math_tvec_data_ctr_2_T<T, 3,3>();

	test_math_tvec_data_ctr_2_T<T, 4,1>();
	test_math_tvec_data_ctr_2_T<T, 4,2>();
	test_math_tvec_data_ctr_2_T<T, 4,3>();
	test_math_tvec_data_ctr_2_T<T, 4,4>();

	test_math_tvec_data_ctr_2_T<T, 5,1>();
	test_math_tvec_data_ctr_2_T<T, 5,2>();
	test_math_tvec_data_ctr_2_T<T, 5,3>();
	test_math_tvec_data_ctr_2_T<T, 5,4>();
	test_math_tvec_data_ctr_2_T<T, 5,5>();

	test_math_tvec_data_ctr_2_T<T, 6,1>();
	test_math_tvec_data_ctr_2_T<T, 6,2>();
	test_math_tvec_data_ctr_2_T<T, 6,3>();
	test_math_tvec_data_ctr_2_T<T, 6,4>();
	test_math_tvec_data_ctr_2_T<T, 6,5>();
	test_math_tvec_data_ctr_2_T<T, 6,6>();

	test_math_tvec_data_ctr_2_T<T, 7,1>();
	test_math_tvec_data_ctr_2_T<T, 7,2>();
	test_math_tvec_data_ctr_2_T<T, 7,3>();
	test_math_tvec_data_ctr_2_T<T, 7,4>();
	test_math_tvec_data_ctr_2_T<T, 7,5>();
	test_math_tvec_data_ctr_2_T<T, 7,6>();
	test_math_tvec_data_ctr_2_T<T, 7,7>();

	test_math_tvec_data_ctr_2_T<T, 8,1>();
	test_math_tvec_data_ctr_2_T<T, 8,2>();
	test_math_tvec_data_ctr_2_T<T, 8,3>();
	test_math_tvec_data_ctr_2_T<T, 8,4>();
	test_math_tvec_data_ctr_2_T<T, 8,5>();
	test_math_tvec_data_ctr_2_T<T, 8,6>();
	test_math_tvec_data_ctr_2_T<T, 8,7>();
	test_math_tvec_data_ctr_2_T<T, 8,8>();
}

BOOST_AUTO_TEST_CASE(math_tvec_data_ctr_2)
{
	test_math_tvec_data_ctr_2<int>();
	test_math_tvec_data_ctr_2<float>();
	test_math_tvec_data_ctr_2<double>();
}

template <typename T, typename ... P>
void test_math_tvec_init_ctr_T(P ... p)
{
	T d[sizeof...(P)] = {T(p)...};
	eagine::math::tvec<T, sizeof...(P)> v(p...);

	for(unsigned i=0; i<sizeof...(P); ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(d[i] <<equal_to>> v[i]);
	}
}

template <typename T>
void test_math_tvec_init_ctr(void)
{
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000,
		std::rand() % 1000
	);
	test_math_tvec_init_ctr_T<T>(
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

BOOST_AUTO_TEST_CASE(math_tvec_init_ctr)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_init_ctr<int>();
		test_math_tvec_init_ctr<float>();
		test_math_tvec_init_ctr<double>();
	}
}

template <typename T, unsigned M>
void test_math_tvec_conv_ctr1_T(const eagine::math::tvec<T, M>&)
{
}

template <typename T, unsigned M, unsigned N>
void test_math_tvec_conv_ctr1_T(const eagine::math::tvec<T, (M>N?N:0)>& v1)
{
	T x = std::rand() / T(11);
	eagine::math::tvec<T, N+1> v2(v1, x);

	using eagine::math::equal_to;
	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(v1[i] <<equal_to>> v2[i]);
	}
	BOOST_ASSERT(x <<equal_to>> v2[N]);

	test_math_tvec_conv_ctr1_T<T, M>(v2);
}

template <typename T>
void test_math_tvec_conv_ctr1(void)
{
	test_math_tvec_conv_ctr1_T<T, 10>(
		eagine::math::tvec<T, 1>(std::rand()/T(11))
	);
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr1)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr1<int>();
		test_math_tvec_conv_ctr1<float>();
		test_math_tvec_conv_ctr1<double>();
	}
}

template <typename T, unsigned N, typename ... P>
void test_math_tvec_conv_ctr2_TNP(
	const eagine::math::tvec<T, N>& v1,
	P ... p
)
{
	T d[sizeof...(P)] = {T(p)...};
	eagine::math::tvec<T, N+sizeof...(P)> v2(v1, p...);

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

template <typename T, unsigned N, typename ... P>
void test_math_tvec_conv_ctr2_TN(P ... p)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N> v(d, N);
	test_math_tvec_conv_ctr2_TNP<T, N>(v, p...);
}

template <typename T, unsigned N>
void test_math_tvec_conv_ctr2_T(void)
{
	test_math_tvec_conv_ctr2_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr2_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
}

template <typename T>
void test_math_tvec_conv_ctr2(void)
{
	test_math_tvec_conv_ctr2_T<T, 2>();
	test_math_tvec_conv_ctr2_T<T, 3>();
	test_math_tvec_conv_ctr2_T<T, 4>();
	test_math_tvec_conv_ctr2_T<T, 5>();
	test_math_tvec_conv_ctr2_T<T, 6>();
	test_math_tvec_conv_ctr2_T<T, 7>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr2<int>();
		test_math_tvec_conv_ctr2<float>();
		test_math_tvec_conv_ctr2<double>();
	}
}

template <typename T, unsigned N, typename ... P>
void test_math_tvec_conv_ctr3_TN(P ... p)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N> v(d, N);
	eagine::math::tvec<T, sizeof...(P)> u(p...);
	eagine::math::tvec<T, N+sizeof...(P)> w(v, u);

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

template <typename T, unsigned N>
void test_math_tvec_conv_ctr3_T(void)
{
	test_math_tvec_conv_ctr3_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
	test_math_tvec_conv_ctr3_TN<T, N>(
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11),
		std::rand() / T(11)
	);
}

template <typename T>
void test_math_tvec_conv_ctr3(void)
{
	test_math_tvec_conv_ctr3_T<T, 2>();
	test_math_tvec_conv_ctr3_T<T, 3>();
	test_math_tvec_conv_ctr3_T<T, 4>();
	test_math_tvec_conv_ctr3_T<T, 5>();
	test_math_tvec_conv_ctr3_T<T, 6>();
	test_math_tvec_conv_ctr3_T<T, 7>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr3)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr3<int>();
		test_math_tvec_conv_ctr3<float>();
		test_math_tvec_conv_ctr3<double>();
	}
}

template <typename T, unsigned N, unsigned M>
void test_math_tvec_conv_ctr4_TN(void)
{
	T d[N];

	for(unsigned i=0; i<N; ++i)
	{
		d[i] = std::rand() / T(11);
	}

	eagine::math::tvec<T, N> v(d, N);
	eagine::math::tvec<T, M> u(v);

	using eagine::math::equal_to;
	for(unsigned i=0; i<M; ++i)
	{
		BOOST_ASSERT(v[i] <<equal_to>> u[i]);
	}
}

template <typename T, unsigned N>
void test_math_tvec_conv_ctr4_T(std::integral_constant<unsigned, 0>)
{
}

template <typename T, unsigned N, unsigned M = N>
void test_math_tvec_conv_ctr4_T(std::integral_constant<unsigned, M> = {})
{
	test_math_tvec_conv_ctr4_TN<T, N, M>();
	test_math_tvec_conv_ctr4_T<T, N>(
		std::integral_constant<unsigned, M-1>()
	);
	
}

template <typename T>
void test_math_tvec_conv_ctr4(void)
{
	test_math_tvec_conv_ctr4_T<T, 2>();
	test_math_tvec_conv_ctr4_T<T, 3>();
	test_math_tvec_conv_ctr4_T<T, 4>();
	test_math_tvec_conv_ctr4_T<T, 5>();
	test_math_tvec_conv_ctr4_T<T, 6>();
	test_math_tvec_conv_ctr4_T<T, 7>();
	test_math_tvec_conv_ctr4_T<T, 8>();
	test_math_tvec_conv_ctr4_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_tvec_conv_ctr4)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_tvec_conv_ctr4<int>();
		test_math_tvec_conv_ctr4<float>();
		test_math_tvec_conv_ctr4<double>();
	}
}


template <typename T, unsigned N>
void test_math_taxis_default_ctr_T_N(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0> ax;
}

template <typename T, unsigned N, unsigned I>
void test_math_taxis_default_ctr_T_N(std::integral_constant<unsigned, I>)
{
	test_math_taxis_default_ctr_T_N<T, N>(
		std::integral_constant<unsigned, I-1>()
	);
	eagine::math::taxis<T, N, I> ax;
}

template <typename T, unsigned N>
void test_math_taxis_default_ctr_T(void)
{
	test_math_taxis_default_ctr_T_N<T, N>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T>
void test_math_taxis_default_ctr(void)
{
	test_math_taxis_default_ctr_T<T, 2>();
	test_math_taxis_default_ctr_T<T, 3>();
	test_math_taxis_default_ctr_T<T, 4>();
	test_math_taxis_default_ctr_T<T, 5>();
	test_math_taxis_default_ctr_T<T, 6>();
	test_math_taxis_default_ctr_T<T, 7>();
	test_math_taxis_default_ctr_T<T, 8>();
	test_math_taxis_default_ctr_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_taxis_default_ctr)
{
	test_math_taxis_default_ctr<int>();
	test_math_taxis_default_ctr<float>();
	test_math_taxis_default_ctr<double>();
}

template <typename T, unsigned N>
void test_math_taxis_elem1_T_N(std::integral_constant<unsigned, 0>)
{
	eagine::math::taxis<T, N, 0> aN0;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(aN0[i] <<equal_to>> (i==0?T(1):T(0)));
	}
}

template <typename T, unsigned N, unsigned I>
void test_math_taxis_elem1_T_N(std::integral_constant<unsigned, I>)
{
	test_math_taxis_elem1_T_N<T, N>(
		std::integral_constant<unsigned, I-1>()
	);

	eagine::math::taxis<T, N, I> aNI;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(aNI[i] <<equal_to>> (i==I?T(1):T(0)));
	}
}

template <typename T, unsigned N>
void test_math_taxis_elem1_T(void)
{
	test_math_taxis_elem1_T_N<T, N>(
		std::integral_constant<unsigned, N-1>()
	);
}

template <typename T>
void test_math_taxis_elem1(void)
{
	test_math_taxis_elem1_T<T, 2>();
	test_math_taxis_elem1_T<T, 3>();
	test_math_taxis_elem1_T<T, 4>();
	test_math_taxis_elem1_T<T, 5>();
	test_math_taxis_elem1_T<T, 6>();
	test_math_taxis_elem1_T<T, 7>();
	test_math_taxis_elem1_T<T, 8>();
	test_math_taxis_elem1_T<T, 9>();
}

BOOST_AUTO_TEST_CASE(math_taxis_elem1)
{
	test_math_taxis_elem1<int>();
	test_math_taxis_elem1<float>();
	test_math_taxis_elem1<double>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
