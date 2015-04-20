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

BOOST_AUTO_TEST_CASE(math_vector_from1)
{
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	auto vi8 = eagine::math::vector<int, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vi7 = eagine::math::vector<int, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vi6 = eagine::math::vector<int, 6>::from<0,1,2,3,4,5>(via8);
	auto vi5 = eagine::math::vector<int, 5>::from<0,1,2,3,4>(via8);
	auto vi4 = eagine::math::vector<int, 4>::from<0,1,2,3>(via8);
	auto vi3 = eagine::math::vector<int, 3>::from<0,1,2>(via8);
	auto vi2 = eagine::math::vector<int, 2>::from<0,1>(via8);
	auto vi1 = eagine::math::vector<int, 1>::from<0>(via8);

	auto vf8 = eagine::math::vector<float, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vf7 = eagine::math::vector<float, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vf6 = eagine::math::vector<float, 6>::from<0,1,2,3,4,5>(via8);
	auto vf5 = eagine::math::vector<float, 5>::from<0,1,2,3,4>(via8);
	auto vf4 = eagine::math::vector<float, 4>::from<0,1,2,3>(via8);
	auto vf3 = eagine::math::vector<float, 3>::from<0,1,2>(via8);
	auto vf2 = eagine::math::vector<float, 2>::from<0,1>(via8);
	auto vf1 = eagine::math::vector<float, 1>::from<0>(via8);

	auto vd8 = eagine::math::vector<double, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vd7 = eagine::math::vector<double, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vd6 = eagine::math::vector<double, 6>::from<0,1,2,3,4,5>(via8);
	auto vd5 = eagine::math::vector<double, 5>::from<0,1,2,3,4>(via8);
	auto vd4 = eagine::math::vector<double, 4>::from<0,1,2,3>(via8);
	auto vd3 = eagine::math::vector<double, 3>::from<0,1,2>(via8);
	auto vd2 = eagine::math::vector<double, 2>::from<0,1>(via8);
	auto vd1 = eagine::math::vector<double, 1>::from<0>(via8);

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_from2)
{
	eagine::math::vector<int, 1> via1 = {{1}};
	eagine::math::vector<int, 2> via2 = {{1, 2}};
	eagine::math::vector<int, 3> via3 = {{1, 2, 3}};
	eagine::math::vector<int, 4> via4 = {{1, 2, 3, 4}};
	eagine::math::vector<int, 5> via5 = {{1, 2, 3, 4, 5}};
	eagine::math::vector<int, 6> via6 = {{1, 2, 3, 4, 5, 6}};
	eagine::math::vector<int, 7> via7 = {{1, 2, 3, 4, 5, 6, 7}};
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	eagine::math::vector<float, 1> vfa1 = {{1.f}};
	eagine::math::vector<float, 2> vfa2 = {{1.f, 2.f}};
	eagine::math::vector<float, 3> vfa3 = {{1.f, 2.f, 3.f}};
	eagine::math::vector<float, 4> vfa4 = {{1.f, 2.f, 3.f, 4.f}};
	eagine::math::vector<float, 5> vfa5 = {{1.f, 2.f, 3.f, 4.f, 5.f}};
	eagine::math::vector<float, 6> vfa6 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
	eagine::math::vector<float, 7> vfa7 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}};
	eagine::math::vector<float, 8> vfa8 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f}};

	eagine::math::vector<double, 1> vda1 = {{1.0}};
	eagine::math::vector<double, 2> vda2 = {{1.0, 2.0}};
	eagine::math::vector<double, 3> vda3 = {{1.0, 2.0, 3.0}};
	eagine::math::vector<double, 4> vda4 = {{1.0, 2.0, 3.0, 4.0}};
	eagine::math::vector<double, 5> vda5 = {{1.0, 2.0, 3.0, 4.0, 5.0}};
	eagine::math::vector<double, 6> vda6 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
	eagine::math::vector<double, 7> vda7 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
	eagine::math::vector<double, 8> vda8 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

	auto vi1 = eagine::math::vector<int, 1>::from<0>(via1);
	auto vi2 = eagine::math::vector<int, 2>::from<1, 0>(via2);
	auto vi3 = eagine::math::vector<int, 3>::from<2, 1, 0>(via3);
	auto vi4 = eagine::math::vector<int, 4>::from<3, 2, 1, 0>(via4);
	auto vi5 = eagine::math::vector<int, 5>::from<4, 3, 2, 1, 0>(via5);
	auto vi6 = eagine::math::vector<int, 6>::from<5, 4, 3, 2, 1, 0>(via6);
	auto vi7 = eagine::math::vector<int, 7>::from<6, 5, 4, 3, 2, 1, 0>(via7);
	auto vi8 = eagine::math::vector<int, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(via8);

	auto vf1 = eagine::math::vector<float, 1>::from<0>(vfa1);
	auto vf2 = eagine::math::vector<float, 2>::from<1, 0>(vfa2);
	auto vf3 = eagine::math::vector<float, 3>::from<2, 1, 0>(vfa3);
	auto vf4 = eagine::math::vector<float, 4>::from<3, 2, 1, 0>(vfa4);
	auto vf5 = eagine::math::vector<float, 5>::from<4, 3, 2, 1, 0>(vfa5);
	auto vf6 = eagine::math::vector<float, 6>::from<5, 4, 3, 2, 1, 0>(vfa6);
	auto vf7 = eagine::math::vector<float, 7>::from<6, 5, 4, 3, 2, 1, 0>(vfa7);
	auto vf8 = eagine::math::vector<float, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(vfa8);

	auto vd1 = eagine::math::vector<double, 1>::from<0>(vda1);
	auto vd2 = eagine::math::vector<double, 2>::from<1, 0>(vda2);
	auto vd3 = eagine::math::vector<double, 3>::from<2, 1, 0>(vda3);
	auto vd4 = eagine::math::vector<double, 4>::from<3, 2, 1, 0>(vda4);
	auto vd5 = eagine::math::vector<double, 5>::from<4, 3, 2, 1, 0>(vda5);
	auto vd6 = eagine::math::vector<double, 6>::from<5, 4, 3, 2, 1, 0>(vda6);
	auto vd7 = eagine::math::vector<double, 7>::from<6, 5, 4, 3, 2, 1, 0>(vda7);
	auto vd8 = eagine::math::vector<double, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(vda8);

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

#define EAGINE_TEST_RAND_INT(N) \
	(unsigned(( \
		__TIMESTAMP__[__TIMESTAMP__[18+__LINE__%6]%24]^ \
		__TIMESTAMP__[12+__FILE__[__LINE__%10]%12])+ \
		__FILE__[(__TIMESTAMP__[23]+__LINE__)%10]+ \
		__LINE__ \
	) % N)

template <typename T, unsigned ... I>
void test_math_vector_from3_T(void)
{
	static const unsigned M = sizeof...(I);
	unsigned j[M] = {I...};

	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	eagine::math::vector<T, 8> v = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}};

	auto u = eagine::math::vector<T, M>::template from<I...>(v);

	for(unsigned i=0; i<M; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(u[i] <<equal_to>> v[j[i]]);
	}
}

template <typename T>
void test_math_vector_from3(void)
{
	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
		T,
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8),
		EAGINE_TEST_RAND_INT(8)
	>();

	test_math_vector_from3_T<
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
	test_math_vector_from3<int>();
	test_math_vector_from3<float>();
	test_math_vector_from3<double>();
}

template <typename T, unsigned N>
void test_math_vector_from4_T(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N];
		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(3);
		}

		auto v = eagine::math::vector<T, N>::from(a, N);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;

			BOOST_ASSERT(v[i] <<equal_to>> a[i]);
		}
	}
}

template <typename T>
void test_math_vector_from4(void)
{
	test_math_vector_from4_T<T, 1>();
	test_math_vector_from4_T<T, 2>();
	test_math_vector_from4_T<T, 3>();
	test_math_vector_from4_T<T, 4>();
	test_math_vector_from4_T<T, 5>();
	test_math_vector_from4_T<T, 6>();
	test_math_vector_from4_T<T, 7>();
	test_math_vector_from4_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_from4)
{
	test_math_vector_from4<int>();
	test_math_vector_from4<float>();
	test_math_vector_from4<double>();
}

template <typename T, unsigned N>
void test_math_vector_get_T(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto va = eagine::math::vector<T, N>::from(a, N);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(get(va, i) <<equal_to>> va[i]);
	}
}

template <typename T>
void test_math_vector_get(void)
{
	test_math_vector_get_T<T, 1>();
	test_math_vector_get_T<T, 2>();
	test_math_vector_get_T<T, 3>();
	test_math_vector_get_T<T, 4>();
	test_math_vector_get_T<T, 5>();
	test_math_vector_get_T<T, 6>();
	test_math_vector_get_T<T, 7>();
	test_math_vector_get_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_get)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_get<int>();
		test_math_vector_get<float>();
		test_math_vector_get<double>();
	}
}

template <typename T, unsigned N>
void test_math_vector_set_T(void)
{
	eagine::math::vector<T, N> va;

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

template <typename T>
void test_math_vector_set(void)
{
	test_math_vector_set_T<T, 1>();
	test_math_vector_set_T<T, 2>();
	test_math_vector_set_T<T, 3>();
	test_math_vector_set_T<T, 4>();
	test_math_vector_set_T<T, 5>();
	test_math_vector_set_T<T, 6>();
	test_math_vector_set_T<T, 7>();
	test_math_vector_set_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_set)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_set<int>();
		test_math_vector_set<float>();
		test_math_vector_set<double>();
	}
}

template <typename T, unsigned N>
void test_math_vector_zero_T(void)
{
	auto v = eagine::math::vector<T, N>::zero();

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> T(0));
	}
}

template <typename T>
void test_math_vector_zero(void)
{
	test_math_vector_zero_T<T, 1>();
	test_math_vector_zero_T<T, 2>();
	test_math_vector_zero_T<T, 3>();
	test_math_vector_zero_T<T, 4>();
	test_math_vector_zero_T<T, 5>();
	test_math_vector_zero_T<T, 6>();
	test_math_vector_zero_T<T, 7>();
	test_math_vector_zero_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_zero)
{
	test_math_vector_zero<int>();
	test_math_vector_zero<float>();
	test_math_vector_zero<double>();
}

template <typename T, unsigned N>
void test_math_vector_fill_T(void)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N>::fill(a);

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(v[i] <<equal_to>> a);
	}
}

template <typename T>
void test_math_vector_fill(void)
{
	test_math_vector_fill_T<T, 1>();
	test_math_vector_fill_T<T, 2>();
	test_math_vector_fill_T<T, 3>();
	test_math_vector_fill_T<T, 4>();
	test_math_vector_fill_T<T, 5>();
	test_math_vector_fill_T<T, 6>();
	test_math_vector_fill_T<T, 7>();
	test_math_vector_fill_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_fill)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_fill<int>();
		test_math_vector_fill<float>();
		test_math_vector_fill<double>();
	}
}

template <typename T, unsigned I, unsigned N>
void test_math_vector_axis_I_T(void)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N>::template axis<I>(a);
	auto u = eagine::math::vector<T, N>::template axis<I>();

	for(unsigned i=0; i<N; ++i)
	{
		using eagine::math::equal_to;

		BOOST_ASSERT(v[i] <<equal_to>> ((i==I)?a:T(0)));
		BOOST_ASSERT(u[i] <<equal_to>> ((i==I)?T(1):T(0)));
	}
}

template <typename T>
void test_math_vector_axis_I(void)
{
	test_math_vector_axis_I_T<T, 0, 1>();

	test_math_vector_axis_I_T<T, 0, 2>();
	test_math_vector_axis_I_T<T, 1, 2>();

	test_math_vector_axis_I_T<T, 0, 3>();
	test_math_vector_axis_I_T<T, 1, 3>();
	test_math_vector_axis_I_T<T, 2, 3>();

	test_math_vector_axis_I_T<T, 0, 4>();
	test_math_vector_axis_I_T<T, 1, 4>();
	test_math_vector_axis_I_T<T, 2, 4>();
	test_math_vector_axis_I_T<T, 3, 4>();

	test_math_vector_axis_I_T<T, 0, 5>();
	test_math_vector_axis_I_T<T, 1, 5>();
	test_math_vector_axis_I_T<T, 2, 5>();
	test_math_vector_axis_I_T<T, 3, 5>();
	test_math_vector_axis_I_T<T, 4, 5>();

	test_math_vector_axis_I_T<T, 0, 6>();
	test_math_vector_axis_I_T<T, 1, 6>();
	test_math_vector_axis_I_T<T, 2, 6>();
	test_math_vector_axis_I_T<T, 3, 6>();
	test_math_vector_axis_I_T<T, 4, 6>();
	test_math_vector_axis_I_T<T, 5, 6>();

	test_math_vector_axis_I_T<T, 0, 7>();
	test_math_vector_axis_I_T<T, 1, 7>();
	test_math_vector_axis_I_T<T, 2, 7>();
	test_math_vector_axis_I_T<T, 3, 7>();
	test_math_vector_axis_I_T<T, 4, 7>();
	test_math_vector_axis_I_T<T, 5, 7>();
	test_math_vector_axis_I_T<T, 6, 7>();

	test_math_vector_axis_I_T<T, 0, 8>();
	test_math_vector_axis_I_T<T, 1, 8>();
	test_math_vector_axis_I_T<T, 2, 8>();
	test_math_vector_axis_I_T<T, 3, 8>();
	test_math_vector_axis_I_T<T, 4, 8>();
	test_math_vector_axis_I_T<T, 5, 8>();
	test_math_vector_axis_I_T<T, 6, 8>();
	test_math_vector_axis_I_T<T, 7, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_axis_I)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_axis_I<int>();
		test_math_vector_axis_I<float>();
		test_math_vector_axis_I<double>();
	}
}

template <typename T, unsigned N>
void test_math_vector_axis_T(unsigned i)
{
	T a = std::rand() / T(3);

	auto v = eagine::math::vector<T, N>::axis(i, a);

	for(unsigned j=0; j<N; ++j)
	{
		using eagine::math::equal_to;

		BOOST_ASSERT(v[j] <<equal_to>> ((i==j)?a:T(0)));
	}
}

template <typename T>
void test_math_vector_axis(void)
{
	test_math_vector_axis_T<T, 1>(0);

	test_math_vector_axis_T<T, 2>(0);
	test_math_vector_axis_T<T, 2>(1);

	test_math_vector_axis_T<T, 3>(0);
	test_math_vector_axis_T<T, 3>(1);
	test_math_vector_axis_T<T, 3>(2);

	test_math_vector_axis_T<T, 4>(0);
	test_math_vector_axis_T<T, 4>(1);
	test_math_vector_axis_T<T, 4>(2);
	test_math_vector_axis_T<T, 4>(3);

	test_math_vector_axis_T<T, 5>(0);
	test_math_vector_axis_T<T, 5>(1);
	test_math_vector_axis_T<T, 5>(2);
	test_math_vector_axis_T<T, 5>(3);
	test_math_vector_axis_T<T, 5>(4);

	test_math_vector_axis_T<T, 6>(0);
	test_math_vector_axis_T<T, 6>(1);
	test_math_vector_axis_T<T, 6>(2);
	test_math_vector_axis_T<T, 6>(3);
	test_math_vector_axis_T<T, 6>(4);
	test_math_vector_axis_T<T, 6>(5);

	test_math_vector_axis_T<T, 7>(0);
	test_math_vector_axis_T<T, 7>(1);
	test_math_vector_axis_T<T, 7>(2);
	test_math_vector_axis_T<T, 7>(3);
	test_math_vector_axis_T<T, 7>(4);
	test_math_vector_axis_T<T, 7>(5);
	test_math_vector_axis_T<T, 7>(6);

	test_math_vector_axis_T<T, 8>(0);
	test_math_vector_axis_T<T, 8>(1);
	test_math_vector_axis_T<T, 8>(2);
	test_math_vector_axis_T<T, 8>(3);
	test_math_vector_axis_T<T, 8>(4);
	test_math_vector_axis_T<T, 8>(5);
	test_math_vector_axis_T<T, 8>(6);
	test_math_vector_axis_T<T, 8>(7);
}

BOOST_AUTO_TEST_CASE(math_vector_axis)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_axis<int>();
		test_math_vector_axis<float>();
		test_math_vector_axis<double>();
	}
}

template <typename T, unsigned N>
void test_math_vector_equal_T(void)
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

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT((va == vb) == eq);
	BOOST_ASSERT((vb == va) == eq);
}

template <typename T>
void test_math_vector_equal(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_equal_T<T, 1>();
		test_math_vector_equal_T<T, 2>();
		test_math_vector_equal_T<T, 3>();
		test_math_vector_equal_T<T, 4>();
		test_math_vector_equal_T<T, 5>();
		test_math_vector_equal_T<T, 6>();
		test_math_vector_equal_T<T, 7>();
		test_math_vector_equal_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_equal)
{
	test_math_vector_equal<int>();
	test_math_vector_equal<float>();
	test_math_vector_equal<double>();
}

template <typename T, unsigned N>
void test_math_vector_noteq_T(void)
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

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT((va != vb) == !eq);
	BOOST_ASSERT((vb != va) == !eq);
}

template <typename T>
void test_math_vector_noteq(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_noteq_T<T, 1>();
		test_math_vector_noteq_T<T, 2>();
		test_math_vector_noteq_T<T, 3>();
		test_math_vector_noteq_T<T, 4>();
		test_math_vector_noteq_T<T, 5>();
		test_math_vector_noteq_T<T, 6>();
		test_math_vector_noteq_T<T, 7>();
		test_math_vector_noteq_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_noteq)
{
	test_math_vector_noteq<int>();
	test_math_vector_noteq<float>();
	test_math_vector_noteq<double>();
}

template <typename T, unsigned N>
void test_math_vector_plus_T(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(std::rand()%2?3:-3);
	}

	auto va = eagine::math::vector<T, N>::from(a, N);

	BOOST_ASSERT(test_math_vector_close(va , +va));
}

template <typename T>
void test_math_vector_plus(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_plus_T<T, 1>();
		test_math_vector_plus_T<T, 2>();
		test_math_vector_plus_T<T, 3>();
		test_math_vector_plus_T<T, 4>();
		test_math_vector_plus_T<T, 5>();
		test_math_vector_plus_T<T, 6>();
		test_math_vector_plus_T<T, 7>();
		test_math_vector_plus_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_plus)
{
	test_math_vector_plus<int>();
	test_math_vector_plus<float>();
	test_math_vector_plus<double>();
}

template <typename T, unsigned N>
void test_math_vector_minus_T(void)
{
	T a[N], b[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(std::rand()%2?3:-3);
		b[i] = -a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va , -vb));
	BOOST_ASSERT(test_math_vector_close(vb , -va));
}

template <typename T>
void test_math_vector_minus(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_minus_T<T, 1>();
		test_math_vector_minus_T<T, 2>();
		test_math_vector_minus_T<T, 3>();
		test_math_vector_minus_T<T, 4>();
		test_math_vector_minus_T<T, 5>();
		test_math_vector_minus_T<T, 6>();
		test_math_vector_minus_T<T, 7>();
		test_math_vector_minus_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_minus)
{
	test_math_vector_minus<int>();
	test_math_vector_minus<float>();
	test_math_vector_minus<double>();
}

template <typename T, unsigned N>
void test_math_vector_add_T(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] + b[i];
		d[i] = b[i] + a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);
	auto vd = eagine::math::vector<T, N>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va + vb, vc));
	BOOST_ASSERT(test_math_vector_close(va + vb, vd));
	BOOST_ASSERT(test_math_vector_close(vb + va, vc));
	BOOST_ASSERT(test_math_vector_close(vb + va, vd));
}

template <typename T>
void test_math_vector_add(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_add_T<T, 1>();
		test_math_vector_add_T<T, 2>();
		test_math_vector_add_T<T, 3>();
		test_math_vector_add_T<T, 4>();
		test_math_vector_add_T<T, 5>();
		test_math_vector_add_T<T, 6>();
		test_math_vector_add_T<T, 7>();
		test_math_vector_add_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_add)
{
	test_math_vector_add<int>();
	test_math_vector_add<float>();
	test_math_vector_add<double>();
}

template <typename T, unsigned N>
void test_math_vector_add_2_T(void)
{
	T a[N], b[N], c[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] + b[i];
	}

	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);

	va += vb;

	BOOST_ASSERT(test_math_vector_close(va, vc));
}

template <typename T>
void test_math_vector_add_2(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_add_2_T<T, 1>();
		test_math_vector_add_2_T<T, 2>();
		test_math_vector_add_2_T<T, 3>();
		test_math_vector_add_2_T<T, 4>();
		test_math_vector_add_2_T<T, 5>();
		test_math_vector_add_2_T<T, 6>();
		test_math_vector_add_2_T<T, 7>();
		test_math_vector_add_2_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_add_2)
{
	test_math_vector_add_2<int>();
	test_math_vector_add_2<float>();
	test_math_vector_add_2<double>();
}

template <typename T, unsigned N>
void test_math_vector_sub_T(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
		b[i] = std::rand() / T(3);
		c[i] = a[i] - b[i];
		d[i] = b[i] - a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);
	auto vd = eagine::math::vector<T, N>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va - vb, vc));
	BOOST_ASSERT(test_math_vector_close(vb - va, vd));
}

template <typename T>
void test_math_vector_sub(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_sub_T<T, 1>();
		test_math_vector_sub_T<T, 2>();
		test_math_vector_sub_T<T, 3>();
		test_math_vector_sub_T<T, 4>();
		test_math_vector_sub_T<T, 5>();
		test_math_vector_sub_T<T, 6>();
		test_math_vector_sub_T<T, 7>();
		test_math_vector_sub_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_sub)
{
	test_math_vector_sub<int>();
	test_math_vector_sub<float>();
	test_math_vector_sub<double>();
}

template <typename T, unsigned N>
void test_math_vector_mul_T(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = std::rand() % 100000;
		c[i] = a[i] * b[i];
		d[i] = b[i] * a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);
	auto vd = eagine::math::vector<T, N>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va * vb, vc));
	BOOST_ASSERT(test_math_vector_close(va * vb, vd));
	BOOST_ASSERT(test_math_vector_close(vb * va, vc));
	BOOST_ASSERT(test_math_vector_close(vb * va, vd));
}

template <typename T>
void test_math_vector_mul(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mul_T<T, 1>();
		test_math_vector_mul_T<T, 2>();
		test_math_vector_mul_T<T, 3>();
		test_math_vector_mul_T<T, 4>();
		test_math_vector_mul_T<T, 5>();
		test_math_vector_mul_T<T, 6>();
		test_math_vector_mul_T<T, 7>();
		test_math_vector_mul_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_mul)
{
	test_math_vector_mul<int>();
	test_math_vector_mul<float>();
	test_math_vector_mul<double>();
}

template <typename T, unsigned N>
void test_math_vector_mul_2_T(void)
{
	T a[N], b[N], c[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = std::rand() % 100000;
		c[i] = a[i] * b[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);

	va *= vb;

	BOOST_ASSERT(test_math_vector_close(va, vc));
}

template <typename T>
void test_math_vector_mul_2(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mul_2_T<T, 1>();
		test_math_vector_mul_2_T<T, 2>();
		test_math_vector_mul_2_T<T, 3>();
		test_math_vector_mul_2_T<T, 4>();
		test_math_vector_mul_2_T<T, 5>();
		test_math_vector_mul_2_T<T, 6>();
		test_math_vector_mul_2_T<T, 7>();
		test_math_vector_mul_2_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_mul_2)
{
	test_math_vector_mul_2<int>();
	test_math_vector_mul_2<float>();
	test_math_vector_mul_2<double>();
}

template <typename T, unsigned N>
void test_math_vector_mulc_T(void)
{
	T a[N], b[N], c = std::rand() % 10000;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = a[i] * c;
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va * c, vb));
	BOOST_ASSERT(test_math_vector_close(c * va, vb));
}

template <typename T>
void test_math_vector_mulc(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mulc_T<T, 1>();
		test_math_vector_mulc_T<T, 2>();
		test_math_vector_mulc_T<T, 3>();
		test_math_vector_mulc_T<T, 4>();
		test_math_vector_mulc_T<T, 5>();
		test_math_vector_mulc_T<T, 6>();
		test_math_vector_mulc_T<T, 7>();
		test_math_vector_mulc_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_mulc)
{
	test_math_vector_mulc<int>();
	test_math_vector_mulc<float>();
	test_math_vector_mulc<double>();
}

template <typename T, unsigned N>
void test_math_vector_mulc_2_T(void)
{
	T a[N], b[N], c = std::rand() % 10000;

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() % 100000;
		b[i] = a[i] * c;
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	va *= c;

	BOOST_ASSERT(test_math_vector_close(va, vb));
}

template <typename T>
void test_math_vector_mulc_2(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_mulc_2_T<T, 1>();
		test_math_vector_mulc_2_T<T, 2>();
		test_math_vector_mulc_2_T<T, 3>();
		test_math_vector_mulc_2_T<T, 4>();
		test_math_vector_mulc_2_T<T, 5>();
		test_math_vector_mulc_2_T<T, 6>();
		test_math_vector_mulc_2_T<T, 7>();
		test_math_vector_mulc_2_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_mulc_2)
{
	test_math_vector_mulc_2<int>();
	test_math_vector_mulc_2<float>();
	test_math_vector_mulc_2<double>();
}

template <typename T, unsigned N>
void test_math_vector_div_T(void)
{
	T a[N], b[N], c[N], d[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = 1 + std::rand() / T(2);
		b[i] = 1 + std::rand() / T(2);
		c[i] = a[i] / b[i];
		d[i] = b[i] / a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);
	auto vc = eagine::math::vector<T, N>::from(c, N);
	auto vd = eagine::math::vector<T, N>::from(d, N);

	BOOST_ASSERT(test_math_vector_close(va / vb, vc));
	BOOST_ASSERT(test_math_vector_close(vb / va, vd));
}

template <typename T>
void test_math_vector_div(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_div_T<T, 1>();
		test_math_vector_div_T<T, 2>();
		test_math_vector_div_T<T, 3>();
		test_math_vector_div_T<T, 4>();
		test_math_vector_div_T<T, 5>();
		test_math_vector_div_T<T, 6>();
		test_math_vector_div_T<T, 7>();
		test_math_vector_div_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_div)
{
	test_math_vector_div<int>();
	test_math_vector_div<float>();
	test_math_vector_div<double>();
}

template <typename T, unsigned N>
void test_math_vector_divc_T(void)
{
	T a[N], b[N], c = 1 + std::rand() / T(2);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = 1 + std::rand() / T(2);
		b[i] = a[i] / c;
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT(test_math_vector_close(va / c, vb));
}

template <typename T>
void test_math_vector_divc(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_divc_T<T, 1>();
		test_math_vector_divc_T<T, 2>();
		test_math_vector_divc_T<T, 3>();
		test_math_vector_divc_T<T, 4>();
		test_math_vector_divc_T<T, 5>();
		test_math_vector_divc_T<T, 6>();
		test_math_vector_divc_T<T, 7>();
		test_math_vector_divc_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_divc)
{
	test_math_vector_divc<int>();
	test_math_vector_divc<float>();
	test_math_vector_divc<double>();
}

template <typename T, unsigned N>
void test_math_vector_hsum_T(void)
{
	T a[N];

	T s = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);

		s += a[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vs = hsum(va);

	for(unsigned i=0; i<N; ++i)
	{
		BOOST_ASSERT(test_math_close(vs[i], s));
	}
}

template <typename T>
void test_math_vector_hsum(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_hsum_T<T, 1>();
		test_math_vector_hsum_T<T, 2>();
		test_math_vector_hsum_T<T, 3>();
		test_math_vector_hsum_T<T, 4>();
		test_math_vector_hsum_T<T, 5>();
		test_math_vector_hsum_T<T, 6>();
		test_math_vector_hsum_T<T, 7>();
		test_math_vector_hsum_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_hsum)
{
	test_math_vector_hsum<int>();
	test_math_vector_hsum<float>();
	test_math_vector_hsum<double>();
}

template <typename T, unsigned N>
void test_math_vector_dot_T(void)
{
	T a[N], b[N];

	T d = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);
		b[i] = std::rand() / T(N);

		d += a[i]*b[i];
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT(test_math_close(T(dot(va, vb)), d));
}

template <typename T>
void test_math_vector_dot(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_dot_T<T, 1>();
		test_math_vector_dot_T<T, 2>();
		test_math_vector_dot_T<T, 3>();
		test_math_vector_dot_T<T, 4>();
		test_math_vector_dot_T<T, 5>();
		test_math_vector_dot_T<T, 6>();
		test_math_vector_dot_T<T, 7>();
		test_math_vector_dot_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_dot)
{
	test_math_vector_dot<int>();
	test_math_vector_dot<float>();
	test_math_vector_dot<double>();
}

template <typename T, unsigned N>
void test_math_vector_length_T(void)
{
	T a[N];

	T l = T(0);

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N);

		l += a[i]*a[i];
	}

	l = T(std::sqrt(l));

	auto va = eagine::math::vector<T, N>::from(a, N);

	BOOST_ASSERT(test_math_close(T(length(va)), l));
	BOOST_ASSERT(test_math_close(T(magnitude(va)), l));
}

template <typename T>
void test_math_vector_length(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_length_T<T, 1>();
		test_math_vector_length_T<T, 2>();
		test_math_vector_length_T<T, 3>();
		test_math_vector_length_T<T, 4>();
		test_math_vector_length_T<T, 5>();
		test_math_vector_length_T<T, 6>();
		test_math_vector_length_T<T, 7>();
		test_math_vector_length_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_length)
{
	test_math_vector_length<float>();
	test_math_vector_length<double>();
}

template <typename T, unsigned N>
void test_math_vector_normalized_T(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N>::from(a, N);

	BOOST_ASSERT(test_math_close(T(length(normalized(va))), T(1)));
}

template <typename T>
void test_math_vector_normalized(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_normalized_T<T, 1>();
		test_math_vector_normalized_T<T, 2>();
		test_math_vector_normalized_T<T, 3>();
		test_math_vector_normalized_T<T, 4>();
		test_math_vector_normalized_T<T, 5>();
		test_math_vector_normalized_T<T, 6>();
		test_math_vector_normalized_T<T, 7>();
		test_math_vector_normalized_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_normalized)
{
	test_math_vector_normalized<float>();
	test_math_vector_normalized<double>();
}

template <typename T>
void test_math_vector_perpendicular(void)
{
	for(unsigned n=0; n<1000; ++n)
	{
		T a[2];

		for(unsigned i=0; i<2; ++i)
		{
			a[i] = std::rand() / T(RAND_MAX);
		}

		auto va = normalized(eagine::math::vector<T, 2>::from(a, 2));
		auto vb = perpendicular(va);

		BOOST_ASSERT(test_math_close(dot(va, vb)+T(2), T(2)));
	}
}

BOOST_AUTO_TEST_CASE(math_vector_perpendicular)
{
	test_math_vector_perpendicular<float>();
	test_math_vector_perpendicular<double>();
}

template <typename T>
void test_math_vector_cross(void)
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

		auto va = normalized(eagine::math::vector<T, 3>::from(a, 3));
		auto vb = normalized(eagine::math::vector<T, 3>::from(b, 3));

		if(std::fabs(dot(va, vb)) < T(0.5))
		{
			auto vc = cross(va, vb);
			BOOST_ASSERT(test_math_close(dot(va, vc)+T(1), T(1)));
			BOOST_ASSERT(test_math_close(dot(vb, vc)+T(1), T(1)));
			--n;
		}
	}
}

BOOST_AUTO_TEST_CASE(math_vector_cross)
{
	test_math_vector_cross<float>();
	test_math_vector_cross<double>();
}

template <typename T, unsigned N>
void test_math_vector_angle_between_T(void)
{
	T a[N], b[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
		b[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N>::from(a, N);
	auto vb = eagine::math::vector<T, N>::from(b, N);

	BOOST_ASSERT(test_math_close(
		value(angle_between(va, vb)),
		T(std::acos(dot(normalized(va), normalized(vb))))
	));
}

template <typename T>
void test_math_vector_angle_between(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_angle_between_T<T, 2>();
		test_math_vector_angle_between_T<T, 3>();
		test_math_vector_angle_between_T<T, 4>();
		test_math_vector_angle_between_T<T, 5>();
		test_math_vector_angle_between_T<T, 6>();
		test_math_vector_angle_between_T<T, 7>();
		test_math_vector_angle_between_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_angle_between)
{
	test_math_vector_angle_between<float>();
	test_math_vector_angle_between<double>();
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

template <typename T, unsigned N>
void test_math_vector_data_T(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(N*N);
	}

	auto va = eagine::math::vector<T, N>::from(a, N);

	auto d = data(va);
	eagine::base::typed_memory_range<const T> r = d.range();

	test_math_vector_data_range_T(a, d);
	test_math_vector_data_range_T(a, r);
}

template <typename T>
void test_math_vector_data(void)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_data_T<T, 2>();
		test_math_vector_data_T<T, 3>();
		test_math_vector_data_T<T, 4>();
		test_math_vector_data_T<T, 5>();
		test_math_vector_data_T<T, 6>();
		test_math_vector_data_T<T, 7>();
		test_math_vector_data_T<T, 8>();
	}
}

BOOST_AUTO_TEST_CASE(math_vector_data)
{
	test_math_vector_data<int>();
	test_math_vector_data<float>();
	test_math_vector_data<double>();
}

BOOST_AUTO_TEST_SUITE_END()
