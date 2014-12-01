/**
 *  .file test/eagine/vect/data.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_data
#include <boost/test/unit_test.hpp>

#include <eagine/vect/data.hpp>

BOOST_AUTO_TEST_SUITE(vect_data)

BOOST_AUTO_TEST_CASE(vect_data_default_construct)
{
	eagine::vect::data<int, 2>::type v2i;
	eagine::vect::data<int, 3>::type v3i;
	eagine::vect::data<int, 4>::type v4i;
	eagine::vect::data<int, 8>::type v8i;

	eagine::vect::data<float, 2>::type v2f;
	eagine::vect::data<float, 3>::type v3f;
	eagine::vect::data<float, 4>::type v4f;
	eagine::vect::data<float, 8>::type v8f;

	eagine::vect::data<double, 2>::type v2d;
	eagine::vect::data<double, 3>::type v3d;
	eagine::vect::data<double, 4>::type v4d;
	eagine::vect::data<double, 8>::type v8d;
}

BOOST_AUTO_TEST_CASE(vect_data_initialization)
{
	eagine::vect::data<int, 2>::type v2i =
		{1, 2};
	eagine::vect::data<int, 3>::type v3i =
		{1, 2, 3};
	eagine::vect::data<int, 4>::type v4i =
		{1, 2, 3, 4};
	eagine::vect::data<int, 7>::type v7i =
		{1, 2, 3, 4, 5, 6, 7};
	eagine::vect::data<int, 8>::type v8i =
		{1, 2, 3, 4, 5, 6, 7, 8};

	eagine::vect::data<float, 2>::type v2f =
		{1.f, 2.f};
	eagine::vect::data<float, 3>::type v3f =
		{1.f, 2.f, 3.f};
	eagine::vect::data<float, 4>::type v4f =
		{1.f, 2.f, 3.f, 4.f};
	eagine::vect::data<float, 7>::type v7f =
		{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f};
	eagine::vect::data<float, 8>::type v8f =
		{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f};

	eagine::vect::data<double, 2>::type v2d =
		{1.0, 2.0};
	eagine::vect::data<double, 3>::type v3d =
		{1.0, 2.0, 3.0};
	eagine::vect::data<double, 4>::type v4d =
		{1.0, 2.0, 3.0, 4.0};
	eagine::vect::data<double, 7>::type v7d =
		{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
	eagine::vect::data<double, 8>::type v8d =
		{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
}

BOOST_AUTO_TEST_CASE(vect_data_copy_construct)
{
	eagine::vect::data<int, 2>::type v2i;
	eagine::vect::data<int, 2>::type v2ic = v2i;
	eagine::vect::data<int, 3>::type v3i;
	eagine::vect::data<int, 3>::type v3ic = v3i;
	eagine::vect::data<int, 4>::type v4i;
	eagine::vect::data<int, 4>::type v4ic = v4i;
	eagine::vect::data<int, 8>::type v8i;
	eagine::vect::data<int, 8>::type v8ic = v8i;

	eagine::vect::data<float, 2>::type v2f;
	eagine::vect::data<float, 2>::type v2fc = v2f;
	eagine::vect::data<float, 3>::type v3f;
	eagine::vect::data<float, 3>::type v3fc = v3f;
	eagine::vect::data<float, 4>::type v4f;
	eagine::vect::data<float, 4>::type v4fc = v4f;
	eagine::vect::data<float, 8>::type v8f;
	eagine::vect::data<float, 8>::type v8fc = v8f;

	eagine::vect::data<double, 2>::type v2d;
	eagine::vect::data<double, 2>::type v2dc = v2d;
	eagine::vect::data<double, 3>::type v3d;
	eagine::vect::data<double, 3>::type v3dc = v3d;
	eagine::vect::data<double, 4>::type v4d;
	eagine::vect::data<double, 4>::type v4dc = v4d;
	eagine::vect::data<double, 8>::type v8d;
	eagine::vect::data<double, 8>::type v8dc = v8d;
}

BOOST_AUTO_TEST_CASE(vect_data_elements)
{
	eagine::vect::data<int, 2>::type v2i =
		{1, 2};
	BOOST_ASSERT(v2i[0] == 1);
	BOOST_ASSERT(v2i[1] == 2);

	eagine::vect::data<int, 3>::type v3i =
		{2, 3, 4};
	BOOST_ASSERT(v3i[0] == 2);
	BOOST_ASSERT(v3i[1] == 3);
	BOOST_ASSERT(v3i[2] == 4);

	eagine::vect::data<int, 4>::type v4i =
		{3, 4, 5, 6};
	BOOST_ASSERT(v4i[0] == 3);
	BOOST_ASSERT(v4i[1] == 4);
	BOOST_ASSERT(v4i[2] == 5);
	BOOST_ASSERT(v4i[3] == 6);

	eagine::vect::data<int, 7>::type v7i =
		{4, 5, 6, 7, 8, 9, 0};
	BOOST_ASSERT(v7i[0] == 4);
	BOOST_ASSERT(v7i[1] == 5);
	BOOST_ASSERT(v7i[2] == 6);
	BOOST_ASSERT(v7i[3] == 7);
	BOOST_ASSERT(v7i[4] == 8);
	BOOST_ASSERT(v7i[5] == 9);
	BOOST_ASSERT(v7i[6] == 0);

	eagine::vect::data<int, 8>::type v8i =
		{5, 6, 7, 8, 9, 0, 1, 2};
	BOOST_ASSERT(v8i[0] == 5);
	BOOST_ASSERT(v8i[1] == 6);
	BOOST_ASSERT(v8i[2] == 7);
	BOOST_ASSERT(v8i[3] == 8);
	BOOST_ASSERT(v8i[4] == 9);
	BOOST_ASSERT(v8i[5] == 0);
	BOOST_ASSERT(v8i[6] == 1);
	BOOST_ASSERT(v8i[7] == 2);

	eagine::vect::data<float, 2>::type v2f =
		{1.f, 2.f};
	BOOST_ASSERT(v2f[0] == 1.f);
	BOOST_ASSERT(v2f[1] == 2.f);

	eagine::vect::data<float, 3>::type v3f =
		{2.f, 3.f, 4.f};
	BOOST_ASSERT(v3f[0] == 2.f);
	BOOST_ASSERT(v3f[1] == 3.f);
	BOOST_ASSERT(v3f[2] == 4.f);

	eagine::vect::data<float, 4>::type v4f =
		{3.f, 4.f, 5.f, 6.f};
	BOOST_ASSERT(v4f[0] == 3.f);
	BOOST_ASSERT(v4f[1] == 4.f);
	BOOST_ASSERT(v4f[2] == 5.f);
	BOOST_ASSERT(v4f[3] == 6.f);

	eagine::vect::data<float, 8>::type v8f =
		{4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 0.f, 1.f};
	BOOST_ASSERT(v8f[0] == 4.f);
	BOOST_ASSERT(v8f[1] == 5.f);
	BOOST_ASSERT(v8f[2] == 6.f);
	BOOST_ASSERT(v8f[3] == 7.f);
	BOOST_ASSERT(v8f[4] == 8.f);
	BOOST_ASSERT(v8f[5] == 9.f);
	BOOST_ASSERT(v8f[6] == 0.f);
	BOOST_ASSERT(v8f[7] == 1.f);

	eagine::vect::data<double, 2>::type v2d =
		{0.0, 9.0};
	BOOST_ASSERT(v2d[0] == 0.0);
	BOOST_ASSERT(v2d[1] == 9.0);

	eagine::vect::data<double, 3>::type v3d =
		{1.0, 3.0, 5.0};
	BOOST_ASSERT(v3d[0] == 1.0);
	BOOST_ASSERT(v3d[1] == 3.0);
	BOOST_ASSERT(v3d[2] == 5.0);

	eagine::vect::data<double, 4>::type v4d =
		{2.0, 4.0, 6.0, 8.0};
	BOOST_ASSERT(v4d[0] == 2.0);
	BOOST_ASSERT(v4d[1] == 4.0);
	BOOST_ASSERT(v4d[2] == 6.0);
	BOOST_ASSERT(v4d[3] == 8.0);

	eagine::vect::data<double, 8>::type v8d =
		{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	BOOST_ASSERT(v8d[0] == 1.0);
	BOOST_ASSERT(v8d[1] == 2.0);
	BOOST_ASSERT(v8d[2] == 3.0);
	BOOST_ASSERT(v8d[3] == 4.0);
	BOOST_ASSERT(v8d[4] == 5.0);
	BOOST_ASSERT(v8d[5] == 6.0);
	BOOST_ASSERT(v8d[6] == 7.0);
	BOOST_ASSERT(v8d[7] == 8.0);
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
