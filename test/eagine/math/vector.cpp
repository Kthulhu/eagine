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

template <typename T, unsigned N>
bool test_math_vector_close(
	const eagine::math::vector<T, N>& a,
	const eagine::math::vector<T, N>& b
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

BOOST_AUTO_TEST_CASE(math_vector_default_ctr)
{
	eagine::math::vector<int, 1> vi1;
	eagine::math::vector<int, 2> vi2;
	eagine::math::vector<int, 3> vi3;
	eagine::math::vector<int, 4> vi4;
	eagine::math::vector<int, 5> vi5;
	eagine::math::vector<int, 6> vi6;
	eagine::math::vector<int, 7> vi7;
	eagine::math::vector<int, 8> vi8;

	eagine::math::vector<float, 1> vf1;
	eagine::math::vector<float, 2> vf2;
	eagine::math::vector<float, 3> vf3;
	eagine::math::vector<float, 4> vf4;
	eagine::math::vector<float, 5> vf5;
	eagine::math::vector<float, 6> vf6;
	eagine::math::vector<float, 7> vf7;
	eagine::math::vector<float, 8> vf8;

	eagine::math::vector<double, 1> vd1;
	eagine::math::vector<double, 2> vd2;
	eagine::math::vector<double, 3> vd3;
	eagine::math::vector<double, 4> vd4;
	eagine::math::vector<double, 5> vd5;
	eagine::math::vector<double, 6> vd6;
	eagine::math::vector<double, 7> vd7;
	eagine::math::vector<double, 8> vd8;

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_init_ctr1)
{
	eagine::math::vector<int, 1> vi1 = {{1}};
	eagine::math::vector<int, 2> vi2 = {{1, 2}};
	eagine::math::vector<int, 3> vi3 = {{1, 2, 3}};
	eagine::math::vector<int, 4> vi4 = {{1, 2, 3, 4}};
	eagine::math::vector<int, 5> vi5 = {{1, 2, 3, 4, 5}};
	eagine::math::vector<int, 6> vi6 = {{1, 2, 3, 4, 5, 6}};
	eagine::math::vector<int, 7> vi7 = {{1, 2, 3, 4, 5, 6, 7}};
	eagine::math::vector<int, 8> vi8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	eagine::math::vector<float, 1> vf1 = {{1.f}};
	eagine::math::vector<float, 2> vf2 = {{1.f, 2.f}};
	eagine::math::vector<float, 3> vf3 = {{1.f, 2.f, 3.f}};
	eagine::math::vector<float, 4> vf4 = {{1.f, 2.f, 3.f, 4.f}};
	eagine::math::vector<float, 5> vf5 = {{1.f, 2.f, 3.f, 4.f, 5.f}};
	eagine::math::vector<float, 6> vf6 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
	eagine::math::vector<float, 7> vf7 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}};
	eagine::math::vector<float, 8> vf8 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f}};

	eagine::math::vector<double, 1> vd1 = {{1.0}};
	eagine::math::vector<double, 2> vd2 = {{1.0, 2.0}};
	eagine::math::vector<double, 3> vd3 = {{1.0, 2.0, 3.0}};
	eagine::math::vector<double, 4> vd4 = {{1.0, 2.0, 3.0, 4.0}};
	eagine::math::vector<double, 5> vd5 = {{1.0, 2.0, 3.0, 4.0, 5.0}};
	eagine::math::vector<double, 6> vd6 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
	eagine::math::vector<double, 7> vd7 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
	eagine::math::vector<double, 8> vd8 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_copy_ctr)
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

	eagine::math::vector<int, 1> vi1 = via1;
	eagine::math::vector<int, 2> vi2 = via2;
	eagine::math::vector<int, 3> vi3 = via3;
	eagine::math::vector<int, 4> vi4 = via4;
	eagine::math::vector<int, 5> vi5 = via5;
	eagine::math::vector<int, 6> vi6 = via6;
	eagine::math::vector<int, 7> vi7 = via7;
	eagine::math::vector<int, 8> vi8 = via8;

	eagine::math::vector<float, 1> vf1 = vfa1;
	eagine::math::vector<float, 2> vf2 = vfa2;
	eagine::math::vector<float, 3> vf3 = vfa3;
	eagine::math::vector<float, 4> vf4 = vfa4;
	eagine::math::vector<float, 5> vf5 = vfa5;
	eagine::math::vector<float, 6> vf6 = vfa6;
	eagine::math::vector<float, 7> vf7 = vfa7;
	eagine::math::vector<float, 8> vf8 = vfa8;

	eagine::math::vector<double, 1> vd1 = vda1;
	eagine::math::vector<double, 2> vd2 = vda2;
	eagine::math::vector<double, 3> vd3 = vda3;
	eagine::math::vector<double, 4> vd4 = vda4;
	eagine::math::vector<double, 5> vd5 = vda5;
	eagine::math::vector<double, 6> vd6 = vda6;
	eagine::math::vector<double, 7> vd7 = vda7;
	eagine::math::vector<double, 8> vd8 = vda8;


	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

template <typename T>
void test_math_vector_element(void)
{
	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	eagine::math::vector<T, 1> v1 = {{a[0]}};
	eagine::math::vector<T, 2> v2 = {{a[0], a[1]}};
	eagine::math::vector<T, 3> v3 = {{a[0], a[1], a[2]}};
	eagine::math::vector<T, 4> v4 = {{a[0], a[1], a[2], a[3]}};
	eagine::math::vector<T, 5> v5 = {{a[0], a[1], a[2], a[3], a[4]}};
	eagine::math::vector<T, 6> v6 = {{a[0], a[1], a[2], a[3], a[4], a[5]}};
	eagine::math::vector<T, 7> v7 = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6]}};
	eagine::math::vector<T, 8> v8 = {{a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]}};

	BOOST_ASSERT(v1[0] == a[0]);

	BOOST_ASSERT(v2[0] == a[0]);
	BOOST_ASSERT(v2[1] == a[1]);

	BOOST_ASSERT(v3[0] == a[0]);
	BOOST_ASSERT(v3[1] == a[1]);
	BOOST_ASSERT(v3[2] == a[2]);

	BOOST_ASSERT(v4[0] == a[0]);
	BOOST_ASSERT(v4[1] == a[1]);
	BOOST_ASSERT(v4[2] == a[2]);
	BOOST_ASSERT(v4[3] == a[3]);

	BOOST_ASSERT(v5[0] == a[0]);
	BOOST_ASSERT(v5[1] == a[1]);
	BOOST_ASSERT(v5[2] == a[2]);
	BOOST_ASSERT(v5[3] == a[3]);
	BOOST_ASSERT(v5[4] == a[4]);

	BOOST_ASSERT(v6[0] == a[0]);
	BOOST_ASSERT(v6[1] == a[1]);
	BOOST_ASSERT(v6[2] == a[2]);
	BOOST_ASSERT(v6[3] == a[3]);
	BOOST_ASSERT(v6[4] == a[4]);
	BOOST_ASSERT(v6[5] == a[5]);

	BOOST_ASSERT(v7[0] == a[0]);
	BOOST_ASSERT(v7[1] == a[1]);
	BOOST_ASSERT(v7[2] == a[2]);
	BOOST_ASSERT(v7[3] == a[3]);
	BOOST_ASSERT(v7[4] == a[4]);
	BOOST_ASSERT(v7[5] == a[5]);
	BOOST_ASSERT(v7[6] == a[6]);

	BOOST_ASSERT(v8[0] == a[0]);
	BOOST_ASSERT(v8[1] == a[1]);
	BOOST_ASSERT(v8[2] == a[2]);
	BOOST_ASSERT(v8[3] == a[3]);
	BOOST_ASSERT(v8[4] == a[4]);
	BOOST_ASSERT(v8[5] == a[5]);
	BOOST_ASSERT(v8[6] == a[6]);
	BOOST_ASSERT(v8[7] == a[7]);
}

BOOST_AUTO_TEST_CASE(math_vector_element)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_vector_element<int>();
		test_math_vector_element<float>();
		test_math_vector_element<double>();
	}
}

template <typename T, unsigned N>
void test_math_vector_x(
	const eagine::math::vector<T, N>& v,
	eagine::meta::true_type
)
{
	BOOST_ASSERT(v.x() == v[0]);
}

template <typename T, unsigned N>
void test_math_vector_x(
	const eagine::math::vector<T, N>& v,
	eagine::meta::false_type
) { }

template <typename T, unsigned N>
void test_math_vector_y(
	const eagine::math::vector<T, N>& v,
	eagine::meta::true_type
)
{
	BOOST_ASSERT(v.y() == v[1]);
}

template <typename T, unsigned N>
void test_math_vector_y(
	const eagine::math::vector<T, N>& v,
	eagine::meta::false_type
) { }

template <typename T, unsigned N>
void test_math_vector_z(
	const eagine::math::vector<T, N>& v,
	eagine::meta::true_type
)
{
	BOOST_ASSERT(v.z() == v[2]);
}

template <typename T, unsigned N>
void test_math_vector_z(
	const eagine::math::vector<T, N>& v,
	eagine::meta::false_type
) { }

template <typename T, unsigned N>
void test_math_vector_w(
	const eagine::math::vector<T, N>& v,
	eagine::meta::true_type
)
{
	BOOST_ASSERT(v.w() == v[3]);
}

template <typename T, unsigned N>
void test_math_vector_w(
	const eagine::math::vector<T, N>& v,
	eagine::meta::false_type
) { }

template <typename T, unsigned N>
void test_math_vector_xyzw_T(void)
{
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto v = eagine::math::vector<T, N>::from(a, N);

	eagine::meta::integral_constant<bool,(N > 0)> has_x;
	eagine::meta::integral_constant<bool,(N > 1)> has_y;
	eagine::meta::integral_constant<bool,(N > 2)> has_z;
	eagine::meta::integral_constant<bool,(N > 3)> has_w;

	test_math_vector_x<T, N>(v, has_x);
	test_math_vector_y<T, N>(v, has_y);
	test_math_vector_z<T, N>(v, has_z);
	test_math_vector_w<T, N>(v, has_w);
}

template <typename T>
void test_math_vector_xyzw(void)
{
	test_math_vector_xyzw_T<T, 1>();
	test_math_vector_xyzw_T<T, 2>();
	test_math_vector_xyzw_T<T, 3>();
	test_math_vector_xyzw_T<T, 4>();
	test_math_vector_xyzw_T<T, 5>();
	test_math_vector_xyzw_T<T, 6>();
	test_math_vector_xyzw_T<T, 7>();
	test_math_vector_xyzw_T<T, 8>();
}

BOOST_AUTO_TEST_CASE(math_vector_xyzw)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_math_vector_xyzw<int>();
		test_math_vector_xyzw<float>();
		test_math_vector_xyzw<double>();
	}
}

template <typename T>
void test_math_vector_make(void)
{
	static const unsigned N = 8;
	T a[N];

	for(unsigned i=0; i<N; ++i)
	{
		a[i] = std::rand() / T(3);
	}

	auto v1 = eagine::math::vector<T, 1>::make(a[0]);
	auto v2 = eagine::math::vector<T, 2>::make(a[0], a[1]);
	auto v3 = eagine::math::vector<T, 3>::make(a[0], a[1], a[2]);
	auto v4 = eagine::math::vector<T, 4>::make(a[0], a[1], a[2], a[3]);
	auto v5 = eagine::math::vector<T, 5>::make(a[0], a[1], a[2], a[3], a[4]);
	auto v6 = eagine::math::vector<T, 6>::make(a[0], a[1], a[2], a[3], a[4], a[5]);
	auto v7 = eagine::math::vector<T, 7>::make(a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
	auto v8 = eagine::math::vector<T, 8>::make(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);

	BOOST_ASSERT(v1[0] == a[0]);

	BOOST_ASSERT(v2[0] == a[0]);
	BOOST_ASSERT(v2[1] == a[1]);

	BOOST_ASSERT(v3[0] == a[0]);
	BOOST_ASSERT(v3[1] == a[1]);
	BOOST_ASSERT(v3[2] == a[2]);

	BOOST_ASSERT(v4[0] == a[0]);
	BOOST_ASSERT(v4[1] == a[1]);
	BOOST_ASSERT(v4[2] == a[2]);
	BOOST_ASSERT(v4[3] == a[3]);

	BOOST_ASSERT(v5[0] == a[0]);
	BOOST_ASSERT(v5[1] == a[1]);
	BOOST_ASSERT(v5[2] == a[2]);
	BOOST_ASSERT(v5[3] == a[3]);
	BOOST_ASSERT(v5[4] == a[4]);

	BOOST_ASSERT(v6[0] == a[0]);
	BOOST_ASSERT(v6[1] == a[1]);
	BOOST_ASSERT(v6[2] == a[2]);
	BOOST_ASSERT(v6[3] == a[3]);
	BOOST_ASSERT(v6[4] == a[4]);
	BOOST_ASSERT(v6[5] == a[5]);

	BOOST_ASSERT(v7[0] == a[0]);
	BOOST_ASSERT(v7[1] == a[1]);
	BOOST_ASSERT(v7[2] == a[2]);
	BOOST_ASSERT(v7[3] == a[3]);
	BOOST_ASSERT(v7[4] == a[4]);
	BOOST_ASSERT(v7[5] == a[5]);
	BOOST_ASSERT(v7[6] == a[6]);

	BOOST_ASSERT(v8[0] == a[0]);
	BOOST_ASSERT(v8[1] == a[1]);
	BOOST_ASSERT(v8[2] == a[2]);
	BOOST_ASSERT(v8[3] == a[3]);
	BOOST_ASSERT(v8[4] == a[4]);
	BOOST_ASSERT(v8[5] == a[5]);
	BOOST_ASSERT(v8[6] == a[6]);
	BOOST_ASSERT(v8[7] == a[7]);
}


BOOST_AUTO_TEST_CASE(math_vector_make)
{
	for(unsigned i=0; i<1000; ++i)
	{
		test_math_vector_make<int>();
		test_math_vector_make<float>();
		test_math_vector_make<double>();
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
		BOOST_ASSERT(u[i] == v[j[i]]);
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
			BOOST_ASSERT(v[i] == a[i]);
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
		BOOST_ASSERT(get(va, i) == va[i]);
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
			BOOST_ASSERT(get(va, i) == a);
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
		BOOST_ASSERT(v[i] == T(0));
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
		BOOST_ASSERT(v[i] == a);
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
		BOOST_ASSERT(v[i] == ((i==I)?a:T(0)));
		BOOST_ASSERT(u[i] == ((i==I)?T(1):T(0)));
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

BOOST_AUTO_TEST_CASE(math_vector_axis)
{
	for(unsigned i=0; i<10; ++i)
	{
		test_math_vector_axis_I<int>();
		test_math_vector_axis_I<float>();
		test_math_vector_axis_I<double>();
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
		eq &= a[i] == b[i];
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
		eq &= a[i] == b[i];
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

	l = std::sqrt(l);

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
	test_math_vector_length<int>();
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

BOOST_AUTO_TEST_SUITE_END()
