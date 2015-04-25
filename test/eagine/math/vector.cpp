/**
 *  .file test/eagine/math/vector.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_vector
#include <boost/test/unit_test.hpp>

#include <eagine/math/vector.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_vector)

template <typename T, unsigned N, bool V>
bool test_math_vector_close(
	const eagine::math::vector<T, N, V>& a,
	const eagine::math::vector<T, N, V>& b
)
{
	for(unsigned i=0; i<N; ++i)
	{
		if(!test_math_close(a[i], b[i]))
		{
			return false;
		}
	}
	return true;
}

template <typename T, bool V>
void test_math_vector_default_ctr_TV(void)
{
	eagine::math::vector<T, 1, V> v1; (void)v1;
	eagine::math::vector<T, 2, V> v2; (void)v2;
	eagine::math::vector<T, 3, V> v3; (void)v3;
	eagine::math::vector<T, 4, V> v4; (void)v4;
	eagine::math::vector<T, 5, V> v5; (void)v5;
	eagine::math::vector<T, 6, V> v6; (void)v6;
	eagine::math::vector<T, 7, V> v7; (void)v7;
	eagine::math::vector<T, 8, V> v8; (void)v8;
	eagine::math::vector<T,11, V> v11; (void)v11;
	eagine::math::vector<T,17, V> v17; (void)v17;
	eagine::math::vector<T,23, V> v23; (void)v23;

}

template <typename T>
void test_math_vector_default_ctr_T(void)
{
	test_math_vector_default_ctr_TV<T, true>();
	test_math_vector_default_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_default_ctr)
{
	test_math_vector_default_ctr_T<int>();
	test_math_vector_default_ctr_T<float>();
	test_math_vector_default_ctr_T<double>();
}

template <typename T, bool V>
void test_math_vector_init_ctr1_TV(void)
{
	eagine::math::vector<T, 1, V> v1 =
		{{T(1)}};
	(void) v1;
	eagine::math::vector<T, 2, V> v2 =
		{{T(1), T(2)}};
	(void) v2;
	eagine::math::vector<T, 3, V> v3 =
		{{T(1), T(2), T(3)}};
	(void) v3;
	eagine::math::vector<T, 4, V> v4 =
		{{T(1), T(2), T(3), T(4)}};
	(void) v4;
	eagine::math::vector<T, 5, V> v5 =
		{{T(1), T(2), T(3), T(4), T(5)}};
	(void) v5;
	eagine::math::vector<T, 6, V> v6 =
		{{T(1), T(2), T(3), T(4), T(5), T(6)}};
	(void) v6;
	eagine::math::vector<T, 7, V> v7 =
		{{T(1), T(2), T(3), T(4), T(5), T(6), T(7)}};
	(void) v7;
	eagine::math::vector<T, 8, V> v8 =
		{{T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8)}};
	(void) v8;
	eagine::math::vector<T,11, V> v11=
		{{T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8), T(9), T(10), T(11)}};
	(void) v11;
}

template <typename T>
void test_math_vector_init_ctr1_T(void)
{
	test_math_vector_init_ctr1_TV<T, true>();
	test_math_vector_init_ctr1_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_init_ctr1)
{
	test_math_vector_init_ctr1_T<int>();
	test_math_vector_init_ctr1_T<float>();
	test_math_vector_init_ctr1_T<double>();
}

template <typename T, bool V>
void test_math_vector_copy_ctr_TV(void)
{
	eagine::math::vector<T, 1, V> v1 =
		{{T(1)}};
	eagine::math::vector<T, 2, V> v2 =
		{{T(1), T(2)}};
	eagine::math::vector<T, 3, V> v3 =
		{{T(1), T(2), T(3)}};
	eagine::math::vector<T, 4, V> v4 =
		{{T(1), T(2), T(3), T(4)}};
	eagine::math::vector<T, 5, V> v5 =
		{{T(1), T(2), T(3), T(4), T(5)}};
	eagine::math::vector<T, 6, V> v6 =
		{{T(1), T(2), T(3), T(4), T(5), T(6)}};
	eagine::math::vector<T, 7, V> v7 =
		{{T(1), T(2), T(3), T(4), T(5), T(6), T(7)}};
	eagine::math::vector<T, 8, V> v8 =
		{{T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8)}};

	eagine::math::vector<T, 1, V> v1c = v1; (void) v1c;
	eagine::math::vector<T, 2, V> v2c = v2; (void) v2c;
	eagine::math::vector<T, 3, V> v3c = v3; (void) v3c;
	eagine::math::vector<T, 4, V> v4c = v4; (void) v4c;
	eagine::math::vector<T, 5, V> v5c = v5; (void) v5c;
	eagine::math::vector<T, 6, V> v6c = v6; (void) v6c;
	eagine::math::vector<T, 7, V> v7c = v7; (void) v7c;
	eagine::math::vector<T, 8, V> v8c = v8; (void) v8c;
}

template <typename T>
void test_math_vector_copy_ctr_T(void)
{
	test_math_vector_copy_ctr_TV<T, true>();
	test_math_vector_copy_ctr_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_copy_ctr)
{
	test_math_vector_copy_ctr_T<int>();
	test_math_vector_copy_ctr_T<float>();
	test_math_vector_copy_ctr_T<double>();
}

template <typename T, bool V>
void test_math_vector_element_TV(void)
{
	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	eagine::math::vector<T, 1, V> v1 = {{a[0]}};
	eagine::math::vector<T, 2, V> v2 = {{a[0], a[1]}};
	eagine::math::vector<T, 3, V> v3 = {{a[0], a[1], a[2]}};
	eagine::math::vector<T, 4, V> v4 = {{a[0], a[1], a[2], a[3]}};
	eagine::math::vector<T, 5, V> v5 = {{a[0], a[1], a[2], a[3], a[4]}};
	eagine::math::vector<T, 6, V> v6 = {{a[0], a[1], a[2], a[3], a[4], a[5]}};
	eagine::math::vector<T, 7, V> v7 = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6]}};
	eagine::math::vector<T, 8, V> v8 = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}};

	using eagine::math::equal_to;

	BOOST_ASSERT(v1[0] <<equal_to>> a[0]);

	BOOST_ASSERT(v2[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v2[1] <<equal_to>> a[1]);

	BOOST_ASSERT(v3[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v3[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v3[2] <<equal_to>> a[2]);

	BOOST_ASSERT(v4[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v4[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v4[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v4[3] <<equal_to>> a[3]);

	BOOST_ASSERT(v5[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v5[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v5[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v5[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v5[4] <<equal_to>> a[4]);

	BOOST_ASSERT(v6[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v6[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v6[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v6[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v6[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v6[5] <<equal_to>> a[5]);

	BOOST_ASSERT(v7[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v7[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v7[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v7[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v7[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v7[5] <<equal_to>> a[5]);
	BOOST_ASSERT(v7[6] <<equal_to>> a[6]);

	BOOST_ASSERT(v8[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v8[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v8[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v8[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v8[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v8[5] <<equal_to>> a[5]);
	BOOST_ASSERT(v8[6] <<equal_to>> a[6]);
	BOOST_ASSERT(v8[7] <<equal_to>> a[7]);
}

template <typename T>
void test_math_vector_element_T(void)
{
	test_math_vector_element_TV<T, true>();
	test_math_vector_element_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_element)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_vector_element_T<int>();
		test_math_vector_element_T<float>();
		test_math_vector_element_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_x(
	const eagine::math::vector<T, N, V>& v,
	eagine::meta::true_type
)
{
	using eagine::math::equal_to;
	BOOST_ASSERT(v.x() <<equal_to>> v[0]);
}

template <typename T, unsigned N, bool V>
void test_math_vector_x(
	const eagine::math::vector<T, N, V>&,
	eagine::meta::false_type
) { }

template <typename T, unsigned N, bool V>
void test_math_vector_y(
	const eagine::math::vector<T, N, V>& v,
	eagine::meta::true_type
)
{
	using eagine::math::equal_to;
	BOOST_ASSERT(v.y() <<equal_to>> v[1]);
}

template <typename T, unsigned N, bool V>
void test_math_vector_y(
	const eagine::math::vector<T, N, V>&,
	eagine::meta::false_type
) { }

template <typename T, unsigned N, bool V>
void test_math_vector_z(
	const eagine::math::vector<T, N, V>& v,
	eagine::meta::true_type
)
{
	using eagine::math::equal_to;
	BOOST_ASSERT(v.z() <<equal_to>> v[2]);
}

template <typename T, unsigned N, bool V>
void test_math_vector_z(
	const eagine::math::vector<T, N, V>&,
	eagine::meta::false_type
) { }

template <typename T, unsigned N, bool V>
void test_math_vector_w(
	const eagine::math::vector<T, N, V>& v,
	eagine::meta::true_type
)
{
	using eagine::math::equal_to;
	BOOST_ASSERT(v.w() <<equal_to>> v[3]);
}

template <typename T, unsigned N, bool V>
void test_math_vector_w(
	const eagine::math::vector<T, N, V>&,
	eagine::meta::false_type
) { }

template <typename T, unsigned N, bool V>
void test_math_vector_xyzw_TNV(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto v = eagine::math::vector<T, N, V>::from(a, N);

	eagine::meta::integral_constant<bool,(N > 0)> has_x;
	eagine::meta::integral_constant<bool,(N > 1)> has_y;
	eagine::meta::integral_constant<bool,(N > 2)> has_z;
	eagine::meta::integral_constant<bool,(N > 3)> has_w;

	test_math_vector_x<T, N>(v, has_x);
	test_math_vector_y<T, N>(v, has_y);
	test_math_vector_z<T, N>(v, has_z);
	test_math_vector_w<T, N>(v, has_w);
}

template <typename T, bool V>
void test_math_vector_xyzw_TV(void)
{
	test_math_vector_xyzw_TNV<T, 1, V>();
	test_math_vector_xyzw_TNV<T, 2, V>();
	test_math_vector_xyzw_TNV<T, 3, V>();
	test_math_vector_xyzw_TNV<T, 4, V>();
	test_math_vector_xyzw_TNV<T, 5, V>();
	test_math_vector_xyzw_TNV<T, 6, V>();
	test_math_vector_xyzw_TNV<T, 7, V>();
	test_math_vector_xyzw_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_xyzw_T(void)
{
	test_math_vector_xyzw_TV<T, true>();
	test_math_vector_xyzw_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_xyzw)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_xyzw_T<int>();
		test_math_vector_xyzw_T<float>();
		test_math_vector_xyzw_T<double>();
	}
}

template <typename T, bool V>
void test_math_vector_make_TV(void)
{
	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto v1 = eagine::math::vector<T, 1, V>::make(a[0]);
	auto v2 = eagine::math::vector<T, 2, V>::make(a[0], a[1]);
	auto v3 = eagine::math::vector<T, 3, V>::make(a[0], a[1], a[2]);
	auto v4 = eagine::math::vector<T, 4, V>::make(a[0], a[1], a[2], a[3]);
	auto v5 = eagine::math::vector<T, 5, V>::make(a[0], a[1], a[2], a[3], a[4]);
	auto v6 = eagine::math::vector<T, 6, V>::make(a[0], a[1], a[2], a[3], a[4], a[5]);
	auto v7 = eagine::math::vector<T, 7, V>::make(a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
	auto v8 = eagine::math::vector<T, 8, V>::make(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);

	using eagine::math::equal_to;

	BOOST_ASSERT(v1[0] <<equal_to>> a[0]);

	BOOST_ASSERT(v2[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v2[1] <<equal_to>> a[1]);

	BOOST_ASSERT(v3[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v3[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v3[2] <<equal_to>> a[2]);

	BOOST_ASSERT(v4[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v4[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v4[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v4[3] <<equal_to>> a[3]);

	BOOST_ASSERT(v5[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v5[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v5[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v5[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v5[4] <<equal_to>> a[4]);

	BOOST_ASSERT(v6[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v6[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v6[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v6[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v6[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v6[5] <<equal_to>> a[5]);

	BOOST_ASSERT(v7[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v7[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v7[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v7[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v7[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v7[5] <<equal_to>> a[5]);
	BOOST_ASSERT(v7[6] <<equal_to>> a[6]);

	BOOST_ASSERT(v8[0] <<equal_to>> a[0]);
	BOOST_ASSERT(v8[1] <<equal_to>> a[1]);
	BOOST_ASSERT(v8[2] <<equal_to>> a[2]);
	BOOST_ASSERT(v8[3] <<equal_to>> a[3]);
	BOOST_ASSERT(v8[4] <<equal_to>> a[4]);
	BOOST_ASSERT(v8[5] <<equal_to>> a[5]);
	BOOST_ASSERT(v8[6] <<equal_to>> a[6]);
	BOOST_ASSERT(v8[7] <<equal_to>> a[7]);
}

template <typename T>
void test_math_vector_make_T(void)
{
	test_math_vector_make_TV<T, true>();
	test_math_vector_make_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_make)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_vector_make_T<int>();
		test_math_vector_make_T<float>();
		test_math_vector_make_T<double>();
	}
}

template <typename T, bool V>
void test_math_vector_from1_TV(eagine::math::vector<int, 8> x)
{
	auto v8 = eagine::math::vector<T, 8, V>::template from<0,1,2,3,4,5,6,7>(x);
	auto v7 = eagine::math::vector<T, 7, V>::template from<0,1,2,3,4,5,6>(x);
	auto v6 = eagine::math::vector<T, 6, V>::template from<0,1,2,3,4,5>(x);
	auto v5 = eagine::math::vector<T, 5, V>::template from<0,1,2,3,4>(x);
	auto v4 = eagine::math::vector<T, 4, V>::template from<0,1,2,3>(x);
	auto v3 = eagine::math::vector<T, 3, V>::template from<0,1,2>(x);
	auto v2 = eagine::math::vector<T, 2, V>::template from<0,1>(x);
	auto v1 = eagine::math::vector<T, 1, V>::template from<0>(x);

	(void)v1; (void)v2; (void)v3; (void)v4; (void)v5; (void)v6; (void)v7; (void)v8;
}

template <typename T>
void test_math_vector_from1_T(eagine::math::vector<int, 8> x)
{
	test_math_vector_from1_TV<T, true>(x);
	test_math_vector_from1_TV<T,false>(x);
}

BOOST_AUTO_TEST_CASE(math_vector_from1)
{
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	test_math_vector_from1_T<int>(via8);
	test_math_vector_from1_T<float>(via8);
	test_math_vector_from1_T<double>(via8);
}

template <typename T, bool V>
void test_math_vector_from2_TV(void)
{
	eagine::math::vector<T, 1, V> va1 = {{T(1)}};
	eagine::math::vector<T, 2, V> va2 = {{T(1), T(2)}};
	eagine::math::vector<T, 3, V> va3 = {{T(1), T(2), T(3)}};
	eagine::math::vector<T, 4, V> va4 = {{T(1), T(2), T(3), T(4)}};
	eagine::math::vector<T, 5, V> va5 = {{T(1), T(2), T(3), T(4), T(5)}};
	eagine::math::vector<T, 6, V> va6 = {{T(1), T(2), T(3), T(4), T(5), T(6)}};
	eagine::math::vector<T, 7, V> va7 = {{T(1), T(2), T(3), T(4), T(5), T(6), T(7)}};
	eagine::math::vector<T, 8, V> va8 = {{T(1), T(2), T(3), T(4), T(5), T(6), T(7), T(8)}};

	auto vb1 = eagine::math::vector<T, 1, V>::template from<0>(va1);
	auto vb2 = eagine::math::vector<T, 2, V>::template from<1, 0>(va2);
	auto vb3 = eagine::math::vector<T, 3, V>::template from<2, 1, 0>(va3);
	auto vb4 = eagine::math::vector<T, 4, V>::template from<3, 2, 1, 0>(va4);
	auto vb5 = eagine::math::vector<T, 5, V>::template from<4, 3, 2, 1, 0>(va5);
	auto vb6 = eagine::math::vector<T, 6, V>::template from<5, 4, 3, 2, 1, 0>(va6);
	auto vb7 = eagine::math::vector<T, 7, V>::template from<6, 5, 4, 3, 2, 1, 0>(va7);
	auto vb8 = eagine::math::vector<T, 8, V>::template from<7, 6, 5, 4, 3, 2, 1, 0>(va8);

	(void)vb1; (void)vb2; (void)vb3; (void)vb4; (void)vb5; (void)vb6; (void)vb7; (void)vb8;
}

template <typename T>
void test_math_vector_from2_T(void)
{
	test_math_vector_from2_TV<T, true>();
	test_math_vector_from2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_from2)
{
	test_math_vector_from2_T<int>();
	test_math_vector_from2_T<float>();
	test_math_vector_from2_T<double>();
}

#define EAGINE_TEST_RAND_INT(N) \
	(unsigned(( \
		__TIMESTAMP__[__TIMESTAMP__[18+__LINE__%6]%24]^ \
		__TIMESTAMP__[12+__FILE__[__LINE__%10]%12])+ \
		__FILE__[(__TIMESTAMP__[23]+__LINE__)%10]+ \
		__LINE__ \
	) % N)

template <typename T, bool V, unsigned ... I>
void test_math_vector_from3_TVI(void)
{
	static const unsigned M = sizeof...(I);
	unsigned j[M] = {I...};

	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	eagine::math::vector<T, 8, V> v = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}};

	auto u = eagine::math::vector<T, M, V>::template from<I...>(v);

	for(unsigned i=0; i<M; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(u[i] <<equal_to>> v[j[i]]);
	}
}

template <typename T, unsigned ... I>
void test_math_vector_from3_TI(void)
{
	test_math_vector_from3_TVI<T, true, I...>();
	test_math_vector_from3_TVI<T,false, I...>();
}

template <typename T>
void test_math_vector_from3_T(void)
{
	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_TI<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();
}

BOOST_AUTO_TEST_CASE(math_vector_from3)
{
	test_math_vector_from3_T<int>();
	test_math_vector_from3_T<float>();
	test_math_vector_from3_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_from4_TNV(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N];
		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(3);
		}

		auto v = eagine::math::vector<T, N, V>::from(a, N);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;

			BOOST_ASSERT(v[i] <<equal_to>> a[i]);
		}
	}
}

template <typename T, bool V>
void test_math_vector_from4_TV(void)
{
	test_math_vector_from4_TNV<T, 1, V>();
	test_math_vector_from4_TNV<T, 2, V>();
	test_math_vector_from4_TNV<T, 3, V>();
	test_math_vector_from4_TNV<T, 4, V>();
	test_math_vector_from4_TNV<T, 5, V>();
	test_math_vector_from4_TNV<T, 6, V>();
	test_math_vector_from4_TNV<T, 7, V>();
	test_math_vector_from4_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_from4_T(void)
{
	test_math_vector_from4_TV<T, true>();
	test_math_vector_from4_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_from4)
{
	test_math_vector_from4_T<int>();
	test_math_vector_from4_T<float>();
	test_math_vector_from4_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_get_TNV(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(get(va, i) <<equal_to>> va[i]);
	}
}

template <typename T, bool V>
void test_math_vector_get_TV(void)
{
	test_math_vector_get_TNV<T, 1, V>();
	test_math_vector_get_TNV<T, 2, V>();
	test_math_vector_get_TNV<T, 3, V>();
	test_math_vector_get_TNV<T, 4, V>();
	test_math_vector_get_TNV<T, 5, V>();
	test_math_vector_get_TNV<T, 6, V>();
	test_math_vector_get_TNV<T, 7, V>();
	test_math_vector_get_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_get_T(void)
{
	test_math_vector_get_TV<T, true>();
	test_math_vector_get_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_get)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_get_T<int>();
		test_math_vector_get_T<float>();
		test_math_vector_get_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_set_TNV(void)
{
	eagine::math::vector<T, N, V> va;

	for(unsigned k=0; k<10; ++k)
	{
		for(unsigned i=0; i<N; ++i)
		{
			T a = std::rand() / T(3);

			set(va, i, a);

			using eagine::math::equal_to;
			BOOST_ASSERT(get(va, i) <<equal_to>> a);
		}
	}
}

template <typename T, bool V>
void test_math_vector_set_TV(void)
{
	test_math_vector_set_TNV<T, 1, V>();
	test_math_vector_set_TNV<T, 2, V>();
	test_math_vector_set_TNV<T, 3, V>();
	test_math_vector_set_TNV<T, 4, V>();
	test_math_vector_set_TNV<T, 5, V>();
	test_math_vector_set_TNV<T, 6, V>();
	test_math_vector_set_TNV<T, 7, V>();
	test_math_vector_set_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_set_T(void)
{
	test_math_vector_set_TV<T, true>();
	test_math_vector_set_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_set)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_set_T<int>();
		test_math_vector_set_T<float>();
		test_math_vector_set_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_zero_TNV(void)
{
	auto v = eagine::math::vector<T, N, V>::zero();

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
	}
}

template <typename T, bool V>
void test_math_vector_zero_TV(void)
{
	test_math_vector_zero_TNV<T, 1, V>();
	test_math_vector_zero_TNV<T, 2, V>();
	test_math_vector_zero_TNV<T, 3, V>();
	test_math_vector_zero_TNV<T, 4, V>();
	test_math_vector_zero_TNV<T, 5, V>();
	test_math_vector_zero_TNV<T, 6, V>();
	test_math_vector_zero_TNV<T, 7, V>();
	test_math_vector_zero_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_zero_T(void)
{
	test_math_vector_zero_TV<T, true>();
	test_math_vector_zero_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_zero)
{
	test_math_vector_zero_T<int>();
	test_math_vector_zero_T<float>();
	test_math_vector_zero_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_fill_TNV(void)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N, V>::fill(a);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> a);
	}
}

template <typename T, bool V>
void test_math_vector_fill_TV(void)
{
	test_math_vector_fill_TNV<T, 1, V>();
	test_math_vector_fill_TNV<T, 2, V>();
	test_math_vector_fill_TNV<T, 3, V>();
	test_math_vector_fill_TNV<T, 4, V>();
	test_math_vector_fill_TNV<T, 5, V>();
	test_math_vector_fill_TNV<T, 6, V>();
	test_math_vector_fill_TNV<T, 7, V>();
	test_math_vector_fill_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_fill_T(void)
{
	test_math_vector_fill_TV<T, true>();
	test_math_vector_fill_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_fill)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_fill_T<int>();
		test_math_vector_fill_T<float>();
		test_math_vector_fill_T<double>();
	}
}

template <typename T, unsigned N, bool V, unsigned I>
void test_math_vector_axis_TNVI(void)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N, V>::template axis<I>(a);
	auto u = eagine::math::vector<T, N, V>::template axis<I>();

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;

		BOOST_ASSERT(v[i] <<equal_to>> ((i==I)?a:T(0)));
		BOOST_ASSERT(u[i] <<equal_to>> ((i==I)?T(1):T(0)));
	}
}

template <typename T, bool V>
void test_math_vector_axis_TV(void)
{
	test_math_vector_axis_TNVI<T, 1, V, 0>();

	test_math_vector_axis_TNVI<T, 2, V, 0>();
	test_math_vector_axis_TNVI<T, 2, V, 1>();

	test_math_vector_axis_TNVI<T, 3, V, 0>();
	test_math_vector_axis_TNVI<T, 3, V, 1>();
	test_math_vector_axis_TNVI<T, 3, V, 2>();

	test_math_vector_axis_TNVI<T, 4, V, 0>();
	test_math_vector_axis_TNVI<T, 4, V, 1>();
	test_math_vector_axis_TNVI<T, 4, V, 2>();
	test_math_vector_axis_TNVI<T, 4, V, 3>();

	test_math_vector_axis_TNVI<T, 5, V, 0>();
	test_math_vector_axis_TNVI<T, 5, V, 1>();
	test_math_vector_axis_TNVI<T, 5, V, 2>();
	test_math_vector_axis_TNVI<T, 5, V, 3>();
	test_math_vector_axis_TNVI<T, 5, V, 4>();

	test_math_vector_axis_TNVI<T, 6, V, 0>();
	test_math_vector_axis_TNVI<T, 6, V, 1>();
	test_math_vector_axis_TNVI<T, 6, V, 2>();
	test_math_vector_axis_TNVI<T, 6, V, 3>();
	test_math_vector_axis_TNVI<T, 6, V, 4>();
	test_math_vector_axis_TNVI<T, 6, V, 5>();

	test_math_vector_axis_TNVI<T, 7, V, 0>();
	test_math_vector_axis_TNVI<T, 7, V, 1>();
	test_math_vector_axis_TNVI<T, 7, V, 2>();
	test_math_vector_axis_TNVI<T, 7, V, 3>();
	test_math_vector_axis_TNVI<T, 7, V, 4>();
	test_math_vector_axis_TNVI<T, 7, V, 5>();
	test_math_vector_axis_TNVI<T, 7, V, 6>();

	test_math_vector_axis_TNVI<T, 8, V, 0>();
	test_math_vector_axis_TNVI<T, 8, V, 1>();
	test_math_vector_axis_TNVI<T, 8, V, 2>();
	test_math_vector_axis_TNVI<T, 8, V, 3>();
	test_math_vector_axis_TNVI<T, 8, V, 4>();
	test_math_vector_axis_TNVI<T, 8, V, 5>();
	test_math_vector_axis_TNVI<T, 8, V, 6>();
	test_math_vector_axis_TNVI<T, 8, V, 7>();
}

template <typename T>
void test_math_vector_axis_T(void)
{
	test_math_vector_axis_TV<T, true>();
	test_math_vector_axis_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_axis_I)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_axis_T<int>();
		test_math_vector_axis_T<float>();
		test_math_vector_axis_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_axis_TNVi(unsigned i)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N, V>::axis(i, a);

	for(unsigned j=0; j<N; ++j)
	{
		using eagine::math::equal_to;

		BOOST_ASSERT(v[j] <<equal_to>> ((i==j)?a:T(0)));
	}
}

template <typename T, bool V>
void test_math_vector_axis_TVi(void)
{
	test_math_vector_axis_TNVi<T, 1, V>(0);

	test_math_vector_axis_TNVi<T, 2, V>(0);
	test_math_vector_axis_TNVi<T, 2, V>(1);

	test_math_vector_axis_TNVi<T, 3, V>(0);
	test_math_vector_axis_TNVi<T, 3, V>(1);
	test_math_vector_axis_TNVi<T, 3, V>(2);

	test_math_vector_axis_TNVi<T, 4, V>(0);
	test_math_vector_axis_TNVi<T, 4, V>(1);
	test_math_vector_axis_TNVi<T, 4, V>(2);
	test_math_vector_axis_TNVi<T, 4, V>(3);

	test_math_vector_axis_TNVi<T, 5, V>(0);
	test_math_vector_axis_TNVi<T, 5, V>(1);
	test_math_vector_axis_TNVi<T, 5, V>(2);
	test_math_vector_axis_TNVi<T, 5, V>(3);
	test_math_vector_axis_TNVi<T, 5, V>(4);

	test_math_vector_axis_TNVi<T, 6, V>(0);
	test_math_vector_axis_TNVi<T, 6, V>(1);
	test_math_vector_axis_TNVi<T, 6, V>(2);
	test_math_vector_axis_TNVi<T, 6, V>(3);
	test_math_vector_axis_TNVi<T, 6, V>(4);
	test_math_vector_axis_TNVi<T, 6, V>(5);

	test_math_vector_axis_TNVi<T, 7, V>(0);
	test_math_vector_axis_TNVi<T, 7, V>(1);
	test_math_vector_axis_TNVi<T, 7, V>(2);
	test_math_vector_axis_TNVi<T, 7, V>(3);
	test_math_vector_axis_TNVi<T, 7, V>(4);
	test_math_vector_axis_TNVi<T, 7, V>(5);
	test_math_vector_axis_TNVi<T, 7, V>(6);

	test_math_vector_axis_TNVi<T, 8, V>(0);
	test_math_vector_axis_TNVi<T, 8, V>(1);
	test_math_vector_axis_TNVi<T, 8, V>(2);
	test_math_vector_axis_TNVi<T, 8, V>(3);
	test_math_vector_axis_TNVi<T, 8, V>(4);
	test_math_vector_axis_TNVi<T, 8, V>(5);
	test_math_vector_axis_TNVi<T, 8, V>(6);
	test_math_vector_axis_TNVi<T, 8, V>(7);
}

template <typename T>
void test_math_vector_axis_Ti(void)
{
	test_math_vector_axis_TVi<T, true>();
	test_math_vector_axis_TVi<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_axis_Ti)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_axis_Ti<int>();
		test_math_vector_axis_Ti<float>();
		test_math_vector_axis_Ti<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_equal_TNV(void)
{
	T a[N], b[N];

	bool eq = std::rand() % 10 == 1;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		if(eq) b[i] = a[i];
	}

	eq = true;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;

		eq &= (a[i] <<equal_to>> b[i]);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT((va == vb) == eq);
	BOOST_ASSERT((vb == va) == eq);
}

template <typename T, bool V>
void test_math_vector_equal_TV(void)
{
	test_math_vector_equal_TNV<T, 1, V>();
	test_math_vector_equal_TNV<T, 2, V>();
	test_math_vector_equal_TNV<T, 3, V>();
	test_math_vector_equal_TNV<T, 4, V>();
	test_math_vector_equal_TNV<T, 5, V>();
	test_math_vector_equal_TNV<T, 6, V>();
	test_math_vector_equal_TNV<T, 7, V>();
	test_math_vector_equal_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_equal_T(void)
{
	test_math_vector_equal_TV<T, true>();
	test_math_vector_equal_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_equal)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_equal_T<int>();
		test_math_vector_equal_T<float>();
		test_math_vector_equal_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_noteq_TNV(void)
{
	T a[N], b[N];

	bool eq = std::rand() % 10 == 1;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		if(eq) b[i] = a[i];
	}

	eq = true;

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;

		eq &= (a[i] <<equal_to>> b[i]);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT((va != vb) == !eq);
	BOOST_ASSERT((vb != va) == !eq);
}

template <typename T, bool V>
void test_math_vector_noteq_TV(void)
{
	test_math_vector_noteq_TNV<T, 1, V>();
	test_math_vector_noteq_TNV<T, 2, V>();
	test_math_vector_noteq_TNV<T, 3, V>();
	test_math_vector_noteq_TNV<T, 4, V>();
	test_math_vector_noteq_TNV<T, 5, V>();
	test_math_vector_noteq_TNV<T, 6, V>();
	test_math_vector_noteq_TNV<T, 7, V>();
	test_math_vector_noteq_TNV<T, 8, V>();
}

template <typename T>
void test_math_vector_noteq_T(void)
{
	test_math_vector_noteq_TV<T, true>();
	test_math_vector_noteq_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_noteq)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_noteq_T<int>();
		test_math_vector_noteq_T<float>();
		test_math_vector_noteq_T<double>();
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_plus_TNV(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(std::rand()%2?3:-3);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);

	BOOST_ASSERT(test_math_vector_close(va , +va));
}

template <typename T, bool V>
void test_math_vector_plus_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_plus_TNV<T, 1, V>();
		test_math_vector_plus_TNV<T, 2, V>();
		test_math_vector_plus_TNV<T, 3, V>();
		test_math_vector_plus_TNV<T, 4, V>();
		test_math_vector_plus_TNV<T, 5, V>();
		test_math_vector_plus_TNV<T, 6, V>();
		test_math_vector_plus_TNV<T, 7, V>();
		test_math_vector_plus_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_plus_T(void)
{
	test_math_vector_plus_TV<T, true>();
	test_math_vector_plus_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_plus)
{
	test_math_vector_plus_T<int>();
	test_math_vector_plus_T<float>();
	test_math_vector_plus_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_minus_TNV(void)
{
	T a[N], b[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(std::rand()%2?3:-3);
		b[i] = -a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va , -vb));
	BOOST_ASSERT(test_math_vector_close(vb , -va));
}

template <typename T, bool V>
void test_math_vector_minus_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_minus_TNV<T, 1, V>();
		test_math_vector_minus_TNV<T, 2, V>();
		test_math_vector_minus_TNV<T, 3, V>();
		test_math_vector_minus_TNV<T, 4, V>();
		test_math_vector_minus_TNV<T, 5, V>();
		test_math_vector_minus_TNV<T, 6, V>();
		test_math_vector_minus_TNV<T, 7, V>();
		test_math_vector_minus_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_minus_T(void)
{
	test_math_vector_minus_TV<T, true>();
	test_math_vector_minus_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_minus)
{
	test_math_vector_minus_T<int>();
	test_math_vector_minus_T<float>();
	test_math_vector_minus_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_add_TNV(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] + b[i];
		d[i] = b[i] + a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);
	auto vd = eagine::math::vector<T, N, V>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va + vb, vc));
	BOOST_ASSERT(test_math_vector_close(va + vb, vd));
	BOOST_ASSERT(test_math_vector_close(vb + va, vc));
	BOOST_ASSERT(test_math_vector_close(vb + va, vd));
}

template <typename T, bool V>
void test_math_vector_add_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_add_TNV<T, 1, V>();
		test_math_vector_add_TNV<T, 2, V>();
		test_math_vector_add_TNV<T, 3, V>();
		test_math_vector_add_TNV<T, 4, V>();
		test_math_vector_add_TNV<T, 5, V>();
		test_math_vector_add_TNV<T, 6, V>();
		test_math_vector_add_TNV<T, 7, V>();
		test_math_vector_add_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_add_T(void)
{
	test_math_vector_add_TV<T, true>();
	test_math_vector_add_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_add)
{
	test_math_vector_add_T<int>();
	test_math_vector_add_T<float>();
	test_math_vector_add_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_add_2_TNV(void)
{
	T a[N], b[N], c[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] + b[i];
	}

	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);

	va += vb;

	BOOST_ASSERT(test_math_vector_close(va, vc));
}

template <typename T, bool V>
void test_math_vector_add_2_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_add_2_TNV<T, 1, V>();
		test_math_vector_add_2_TNV<T, 2, V>();
		test_math_vector_add_2_TNV<T, 3, V>();
		test_math_vector_add_2_TNV<T, 4, V>();
		test_math_vector_add_2_TNV<T, 5, V>();
		test_math_vector_add_2_TNV<T, 6, V>();
		test_math_vector_add_2_TNV<T, 7, V>();
		test_math_vector_add_2_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_add_2_T(void)
{
	test_math_vector_add_2_TV<T, true>();
	test_math_vector_add_2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_add_2)
{
	test_math_vector_add_2_T<int>();
	test_math_vector_add_2_T<float>();
	test_math_vector_add_2_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_sub_TNV(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] - b[i];
		d[i] = b[i] - a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);
	auto vd = eagine::math::vector<T, N, V>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va - vb, vc));
	BOOST_ASSERT(test_math_vector_close(vb - va, vd));
}

template <typename T, bool V>
void test_math_vector_sub_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_sub_TNV<T, 1, V>();
		test_math_vector_sub_TNV<T, 2, V>();
		test_math_vector_sub_TNV<T, 3, V>();
		test_math_vector_sub_TNV<T, 4, V>();
		test_math_vector_sub_TNV<T, 5, V>();
		test_math_vector_sub_TNV<T, 6, V>();
		test_math_vector_sub_TNV<T, 7, V>();
		test_math_vector_sub_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_sub_T(void)
{
	test_math_vector_sub_TV<T, true>();
	test_math_vector_sub_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_sub)
{
	test_math_vector_sub_T<int>();
	test_math_vector_sub_T<float>();
	test_math_vector_sub_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_mul_TNV(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = std::rand() % 100000;
		c[i] = a[i] * b[i];
		d[i] = b[i] * a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);
	auto vd = eagine::math::vector<T, N, V>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va * vb, vc));
	BOOST_ASSERT(test_math_vector_close(va * vb, vd));
	BOOST_ASSERT(test_math_vector_close(vb * va, vc));
	BOOST_ASSERT(test_math_vector_close(vb * va, vd));
}

template <typename T, bool V>
void test_math_vector_mul_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mul_TNV<T, 1, V>();
		test_math_vector_mul_TNV<T, 2, V>();
		test_math_vector_mul_TNV<T, 3, V>();
		test_math_vector_mul_TNV<T, 4, V>();
		test_math_vector_mul_TNV<T, 5, V>();
		test_math_vector_mul_TNV<T, 6, V>();
		test_math_vector_mul_TNV<T, 7, V>();
		test_math_vector_mul_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_mul_T(void)
{
	test_math_vector_mul_TV<T, true>();
	test_math_vector_mul_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_mul)
{
	test_math_vector_mul_T<int>();
	test_math_vector_mul_T<float>();
	test_math_vector_mul_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_mul_2_TNV(void)
{
	T a[N], b[N], c[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = std::rand() % 100000;
		c[i] = a[i] * b[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);

	va *= vb;

	BOOST_ASSERT(test_math_vector_close(va, vc));
}

template <typename T, bool V>
void test_math_vector_mul_2_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mul_2_TNV<T, 1, V>();
		test_math_vector_mul_2_TNV<T, 2, V>();
		test_math_vector_mul_2_TNV<T, 3, V>();
		test_math_vector_mul_2_TNV<T, 4, V>();
		test_math_vector_mul_2_TNV<T, 5, V>();
		test_math_vector_mul_2_TNV<T, 6, V>();
		test_math_vector_mul_2_TNV<T, 7, V>();
		test_math_vector_mul_2_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_mul_2_T(void)
{
	test_math_vector_mul_2_TV<T, true>();
	test_math_vector_mul_2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_mul_2)
{
	test_math_vector_mul_2_T<int>();
	test_math_vector_mul_2_T<float>();
	test_math_vector_mul_2_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_mulc_TNV(void)
{
	T a[N], b[N], c = std::rand() % 10000;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = a[i] * c;
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va * c, vb));
	BOOST_ASSERT(test_math_vector_close(c * va, vb));
}

template <typename T, bool V>
void test_math_vector_mulc_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mulc_TNV<T, 1, V>();
		test_math_vector_mulc_TNV<T, 2, V>();
		test_math_vector_mulc_TNV<T, 3, V>();
		test_math_vector_mulc_TNV<T, 4, V>();
		test_math_vector_mulc_TNV<T, 5, V>();
		test_math_vector_mulc_TNV<T, 6, V>();
		test_math_vector_mulc_TNV<T, 7, V>();
		test_math_vector_mulc_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_mulc_T(void)
{
	test_math_vector_mulc_TV<T, true>();
	test_math_vector_mulc_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_mulc)
{
	test_math_vector_mulc_T<int>();
	test_math_vector_mulc_T<float>();
	test_math_vector_mulc_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_mulc_2_TNV(void)
{
	T a[N], b[N], c = std::rand() % 10000;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = a[i] * c;
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	va *= c;

	BOOST_ASSERT(test_math_vector_close(va, vb));
}

template <typename T, bool V>
void test_math_vector_mulc_2_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mulc_2_TNV<T, 1, V>();
		test_math_vector_mulc_2_TNV<T, 2, V>();
		test_math_vector_mulc_2_TNV<T, 3, V>();
		test_math_vector_mulc_2_TNV<T, 4, V>();
		test_math_vector_mulc_2_TNV<T, 5, V>();
		test_math_vector_mulc_2_TNV<T, 6, V>();
		test_math_vector_mulc_2_TNV<T, 7, V>();
		test_math_vector_mulc_2_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_mulc_2_T(void)
{
	test_math_vector_mulc_2_TV<T, true>();
	test_math_vector_mulc_2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_mulc_2)
{
	test_math_vector_mulc_2_T<int>();
	test_math_vector_mulc_2_T<float>();
	test_math_vector_mulc_2_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_div_TNV(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = 1 + std::rand() / T(2);
		b[i] = 1 + std::rand() / T(2);
		c[i] = a[i] / b[i];
		d[i] = b[i] / a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);
	auto vc = eagine::math::vector<T, N, V>::from(c, N);
	auto vd = eagine::math::vector<T, N, V>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va / vb, vc));
	BOOST_ASSERT(test_math_vector_close(vb / va, vd));
}

template <typename T, bool V>
void test_math_vector_div_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_div_TNV<T, 1, V>();
		test_math_vector_div_TNV<T, 2, V>();
		test_math_vector_div_TNV<T, 3, V>();
		test_math_vector_div_TNV<T, 4, V>();
		test_math_vector_div_TNV<T, 5, V>();
		test_math_vector_div_TNV<T, 6, V>();
		test_math_vector_div_TNV<T, 7, V>();
		test_math_vector_div_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_div_T(void)
{
	test_math_vector_div_TV<T, true>();
	test_math_vector_div_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_div)
{
	test_math_vector_div_T<int>();
	test_math_vector_div_T<float>();
	test_math_vector_div_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_divc_TNV(void)
{
	T a[N], b[N], c = 1 + std::rand() / T(2);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = 1 + std::rand() / T(2);
		b[i] = a[i] / c;
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va / c, vb));
}

template <typename T, bool V>
void test_math_vector_divc_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_divc_TNV<T, 1, V>();
		test_math_vector_divc_TNV<T, 2, V>();
		test_math_vector_divc_TNV<T, 3, V>();
		test_math_vector_divc_TNV<T, 4, V>();
		test_math_vector_divc_TNV<T, 5, V>();
		test_math_vector_divc_TNV<T, 6, V>();
		test_math_vector_divc_TNV<T, 7, V>();
		test_math_vector_divc_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_divc_T(void)
{
	test_math_vector_divc_TV<T, true>();
	test_math_vector_divc_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_divc)
{
	test_math_vector_divc_T<int>();
	test_math_vector_divc_T<float>();
	test_math_vector_divc_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_hsum_TNV(void)
{
	T a[N];

	T s = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);

		s += a[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vs = hsum(va);

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(test_math_close(vs[i], s));
	}
}

template <typename T, bool V>
void test_math_vector_hsum_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_hsum_TNV<T, 1, V>();
		test_math_vector_hsum_TNV<T, 2, V>();
		test_math_vector_hsum_TNV<T, 3, V>();
		test_math_vector_hsum_TNV<T, 4, V>();
		test_math_vector_hsum_TNV<T, 5, V>();
		test_math_vector_hsum_TNV<T, 6, V>();
		test_math_vector_hsum_TNV<T, 7, V>();
		test_math_vector_hsum_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_hsum_T(void)
{
	test_math_vector_hsum_TV<T, true>();
	test_math_vector_hsum_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_hsum)
{
	test_math_vector_hsum_T<int>();
	test_math_vector_hsum_T<float>();
	test_math_vector_hsum_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_dot_TNV(void)
{
	T a[N], b[N];

	T d = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);
		b[i] = std::rand() / T(N);

		d += a[i]*b[i];
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT(test_math_close(T(dot(va, vb)), d));
}

template <typename T, bool V>
void test_math_vector_dot_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_dot_TNV<T, 1, V>();
		test_math_vector_dot_TNV<T, 2, V>();
		test_math_vector_dot_TNV<T, 3, V>();
		test_math_vector_dot_TNV<T, 4, V>();
		test_math_vector_dot_TNV<T, 5, V>();
		test_math_vector_dot_TNV<T, 6, V>();
		test_math_vector_dot_TNV<T, 7, V>();
		test_math_vector_dot_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_dot_T(void)
{
	test_math_vector_dot_TV<T, true>();
	test_math_vector_dot_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_dot)
{
	test_math_vector_dot_T<int>();
	test_math_vector_dot_T<float>();
	test_math_vector_dot_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_length_TNV(void)
{
	T a[N];

	T l = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);

		l += a[i]*a[i];
	}

	l = T(std::sqrt(l));

	auto va = eagine::math::vector<T, N, V>::from(a, N);

	BOOST_ASSERT(test_math_close(T(length(va)), l));
	BOOST_ASSERT(test_math_close(T(magnitude(va)), l));
}

template <typename T, bool V>
void test_math_vector_length_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_length_TNV<T, 1, V>();
		test_math_vector_length_TNV<T, 2, V>();
		test_math_vector_length_TNV<T, 3, V>();
		test_math_vector_length_TNV<T, 4, V>();
		test_math_vector_length_TNV<T, 5, V>();
		test_math_vector_length_TNV<T, 6, V>();
		test_math_vector_length_TNV<T, 7, V>();
		test_math_vector_length_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_length_T(void)
{
	test_math_vector_length_TV<T, true>();
	test_math_vector_length_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_length)
{
	test_math_vector_length_T<float>();
	test_math_vector_length_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_normalized_TNV(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);

	BOOST_ASSERT(test_math_close(T(length(normalized(va))), T(1)));
}

template <typename T, bool V>
void test_math_vector_normalized_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_normalized_TNV<T, 1, V>();
		test_math_vector_normalized_TNV<T, 2, V>();
		test_math_vector_normalized_TNV<T, 3, V>();
		test_math_vector_normalized_TNV<T, 4, V>();
		test_math_vector_normalized_TNV<T, 5, V>();
		test_math_vector_normalized_TNV<T, 6, V>();
		test_math_vector_normalized_TNV<T, 7, V>();
		test_math_vector_normalized_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_normalized_T(void)
{
	test_math_vector_normalized_TV<T, true>();
	test_math_vector_normalized_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_normalized)
{
	test_math_vector_normalized_T<float>();
	test_math_vector_normalized_T<double>();
}

template <typename T, bool V>
void test_math_vector_perpendicular_TV(void)
{
	for(unsigned n=0; n<1000; ++n)
	{
		T a[2];

		for(unsigned i=0; i<2; ++i)
		{
			a[i] = std::rand() / T(RAND_MAX);
		}

		auto va = normalized(eagine::math::vector<T, 2, V>::from(a, 2));
		auto vb = perpendicular(va);

		BOOST_ASSERT(test_math_close(dot(va, vb)+T(2), T(2)));
	}
}

template <typename T>
void test_math_vector_perpendicular_T(void)
{
	test_math_vector_perpendicular_TV<T, true>();
	test_math_vector_perpendicular_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_perpendicular)
{
	test_math_vector_perpendicular_T<float>();
	test_math_vector_perpendicular_T<double>();
}

template <typename T, bool V>
void test_math_vector_cross_TV(void)
{
	unsigned n = 1000;

	while(n)
	{
		T a[3], b[3];

		for(unsigned i=0; i<3; ++i)
		{
			a[i] = std::rand() / T(RAND_MAX);
			b[i] = std::rand() / T(RAND_MAX);
		}

		auto va = normalized(eagine::math::vector<T, 3, V>::from(a, 3));
		auto vb = normalized(eagine::math::vector<T, 3, V>::from(b, 3));

		if(std::fabs(dot(va, vb)) < T(0.5))
		{
			auto vc = cross(va, vb);
			BOOST_ASSERT(test_math_close(dot(va, vc)+T(1), T(1)));
			BOOST_ASSERT(test_math_close(dot(vb, vc)+T(1), T(1)));
			--n;
		}
	}
}

template <typename T>
void test_math_vector_cross_T(void)
{
	test_math_vector_cross_TV<T, true>();
	test_math_vector_cross_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_cross)
{
	test_math_vector_cross_T<float>();
	test_math_vector_cross_T<double>();
}

template <typename T, unsigned N, bool V>
void test_math_vector_angle_between_TNV(void)
{
	T a[N], b[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
		b[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);
	auto vb = eagine::math::vector<T, N, V>::from(b, N);

	BOOST_ASSERT(test_math_close(
		value(angle_between(va, vb)),
		T(std::acos(dot(normalized(va), normalized(vb))))
	));
}

template <typename T, bool V>
void test_math_vector_angle_between_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_angle_between_TNV<T, 2, V>();
		test_math_vector_angle_between_TNV<T, 3, V>();
		test_math_vector_angle_between_TNV<T, 4, V>();
		test_math_vector_angle_between_TNV<T, 5, V>();
		test_math_vector_angle_between_TNV<T, 6, V>();
		test_math_vector_angle_between_TNV<T, 7, V>();
		test_math_vector_angle_between_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_angle_between_T(void)
{
	test_math_vector_angle_between_TV<T, true>();
	test_math_vector_angle_between_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_angle_between)
{
	test_math_vector_angle_between_T<float>();
	test_math_vector_angle_between_T<double>();
}

template <typename T, unsigned N, typename Range>
void test_math_vector_data_range_T(const T(&a)[N], Range& r)
{

	BOOST_ASSERT(r.addr() != nullptr);
	BOOST_ASSERT(r.size() == N);

	const T* b = r.begin();
	const T* e = r.end();

	BOOST_ASSERT(b != e);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;

		const T* o = r.offs(i);

		BOOST_ASSERT(r[i] <<equal_to>> a[i]);
		BOOST_ASSERT( *o  <<equal_to>> a[i]);
	}

	for(T x : r) { (void)x; }

	for(unsigned i=0; i<N; ++i)
	{
		auto s = r.slice(i);
		BOOST_ASSERT(s.size() == N-i);
	}
}

template <typename T, unsigned N, bool V>
void test_math_vector_data_TNV(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N, V>::from(a, N);

	auto d = data(va);
	eagine::base::typed_memory_range<const T> r = d.range();

	test_math_vector_data_range_T(a, d);
	test_math_vector_data_range_T(a, r);
}

template <typename T, bool V>
void test_math_vector_data_TV(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_data_TNV<T, 2, V>();
		test_math_vector_data_TNV<T, 3, V>();
		test_math_vector_data_TNV<T, 4, V>();
		test_math_vector_data_TNV<T, 5, V>();
		test_math_vector_data_TNV<T, 6, V>();
		test_math_vector_data_TNV<T, 7, V>();
		test_math_vector_data_TNV<T, 8, V>();
	}
}

template <typename T>
void test_math_vector_data_T(void)
{
	test_math_vector_data_TV<T, true>();
	test_math_vector_data_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_vector_data)
{
	test_math_vector_data_T<int>();
	test_math_vector_data_T<float>();
	test_math_vector_data_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
