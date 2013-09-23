/**
 *  .file test/eagine/base/string.cpp
 *  .brief Test case for base::string class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_string
#include <boost/test/unit_test.hpp>

#include <eagine/base/string.hpp>

BOOST_AUTO_TEST_SUITE(base_string)

BOOST_AUTO_TEST_CASE(base_string_default_construction)
{
	EAGine::base::string s;
}

BOOST_AUTO_TEST_SUITE_END()
