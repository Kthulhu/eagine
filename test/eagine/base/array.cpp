/**
 *  .file test/eagine/base/array.cpp
 *  .brief Test case for base::array class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_array
#include <boost/test/unit_test.hpp>

#include <eagine/base/array.hpp>

BOOST_AUTO_TEST_SUITE(base_array)

BOOST_AUTO_TEST_CASE(base_array_default_construction)
{
	eagine::base::array<int, 10> a;
}

BOOST_AUTO_TEST_CASE(base_array_copy_construction)
{
	eagine::base::array<int, 10> a1;
	eagine::base::array<int, 10> a2(a1);
}

BOOST_AUTO_TEST_CASE(base_array_brace_initialization)
{
	eagine::base::array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
}

BOOST_AUTO_TEST_CASE(base_array_equality)
{
	eagine::base::array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
	eagine::base::array<int, 10> a2 = {1,2,3,4,5,6,7,8,9,0};
	eagine::base::array<int, 10> a3 = a1;

	BOOST_ASSERT(a1 == a1);
	BOOST_ASSERT(a2 == a2);
	BOOST_ASSERT(a1 != a2);
	BOOST_ASSERT(a1 == a3);
}

BOOST_AUTO_TEST_CASE(base_array_indexing)
{
	eagine::base::array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
	eagine::base::array<int, 10> a2 = a1;

	for(int i=0; i<10; ++i)
	{
		BOOST_ASSERT(a1[i] == i);
		BOOST_ASSERT(a1[i] == a2[i]);
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
