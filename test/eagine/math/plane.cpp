/**
 *  .file test/eagine/math/plane.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_plane
#include <boost/test/unit_test.hpp>

#include <eagine/math/plane.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_plane)

template <typename T, bool V>
void test_math_plane_construct_1_TV(void)
{
	T x = T(std::rand());
	T y = T(std::rand());
	T z = T(std::rand());
	T w = T(std::rand());

	eagine::math::plane<T, V> p{x,y,z,w};

	BOOST_ASSERT((test_math_close(p.equation().x(), x)));
	BOOST_ASSERT((test_math_close(p.equation().y(), y)));
	BOOST_ASSERT((test_math_close(p.equation().z(), z)));
	BOOST_ASSERT((test_math_close(p.equation().w(), w)));
}

template <typename T>
void test_math_plane_construct_1_T(void)
{
	test_math_plane_construct_1_TV<T, true>();
	test_math_plane_construct_1_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_1)
{
	test_math_plane_construct_1_T<float>();
	test_math_plane_construct_1_T<double>();
}

template <typename T, bool V>
void test_math_plane_construct_2_TV(void)
{
	T x = T(std::rand());
	T y = T(std::rand());
	T z = T(std::rand());
	T w = T(std::rand());

	eagine::math::vector<T, 4, V> v{{x,y,z,w}};

	eagine::math::plane<T, V> p{v};

	BOOST_ASSERT((test_math_close(p.equation().x(), x)));
	BOOST_ASSERT((test_math_close(p.equation().y(), y)));
	BOOST_ASSERT((test_math_close(p.equation().z(), z)));
	BOOST_ASSERT((test_math_close(p.equation().w(), w)));
}

template <typename T>
void test_math_plane_construct_2_T(void)
{
	test_math_plane_construct_2_TV<T, true>();
	test_math_plane_construct_2_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_2)
{
	test_math_plane_construct_2_T<float>();
	test_math_plane_construct_2_T<double>();
}

template <typename T, bool V>
void test_math_plane_construct_fpan_TV(void)
{
	T px = T(std::rand());
	T py = T(std::rand());
	T pz = T(std::rand());

	T nx = T(std::rand());
	T ny = T(std::rand());
	T nz = T(std::rand());

	eagine::math::vector<T, 3, V> p{{px,py,pz}};
	eagine::math::vector<T, 3, V> n{{nx,ny,nz}};

	eagine::math::plane<T, V> pl =
		eagine::math::plane<T, V>::from_point_and_normal(
			p, normalized(n)
		);
	(void)pl;
}

template <typename T>
void test_math_plane_construct_fpan_T(void)
{
	test_math_plane_construct_fpan_TV<T, true>();
	test_math_plane_construct_fpan_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_fpan)
{
	test_math_plane_construct_fpan_T<float>();
	test_math_plane_construct_fpan_T<double>();
}

template <typename T, bool V>
void test_math_plane_construct_ft_TV(void)
{
	T ax = T(std::rand());
	T ay = T(std::rand());
	T az = T(std::rand());

	T bx = T(std::rand());
	T by = T(std::rand());
	T bz = T(std::rand());

	T cx = T(std::rand());
	T cy = T(std::rand());
	T cz = T(std::rand());

	eagine::math::vector<T, 3, V> a{{ax,ay,az}};
	eagine::math::vector<T, 3, V> b{{bx,by,bz}};
	eagine::math::vector<T, 3, V> c{{cx,cy,cz}};

	eagine::math::plane<T, V> pl =
		eagine::math::plane<T, V>::from_triangle(a,b,c);
	(void)pl;
}

template <typename T>
void test_math_plane_construct_ft_T(void)
{
	test_math_plane_construct_ft_TV<T, true>();
	test_math_plane_construct_ft_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_ft)
{
	test_math_plane_construct_ft_T<float>();
	test_math_plane_construct_ft_T<double>();
}

template <typename T, bool V>
void test_math_plane_construct_fpav_TV(void)
{
	T px = T(std::rand());
	T py = T(std::rand());
	T pz = T(std::rand());

	T ux = T(std::rand());
	T uy = T(std::rand());
	T uz = T(std::rand());

	T vx = T(std::rand());
	T vy = T(std::rand());
	T vz = T(std::rand());

	eagine::math::vector<T, 3, V> p{{px,py,pz}};
	eagine::math::vector<T, 3, V> u{{ux,uy,uz}};
	eagine::math::vector<T, 3, V> v{{vx,vy,vz}};

	eagine::math::plane<T, V> pl =
		eagine::math::plane<T, V>::from_point_and_vectors(p, u, v);
	(void)pl;
}

template <typename T>
void test_math_plane_construct_fpav_T(void)
{
	test_math_plane_construct_fpav_TV<T, true>();
	test_math_plane_construct_fpav_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_plane_construct_fpav)
{
	test_math_plane_construct_fpav_T<float>();
	test_math_plane_construct_fpav_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
