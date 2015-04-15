/**
 *  .file test/eagine/base/utf8.cpp
 *  .brief Test case for base utf8 functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_utf8
#include <boost/test/unit_test.hpp>

#include <eagine/base/utf8.hpp>

BOOST_AUTO_TEST_SUITE(base_utf8)

BOOST_AUTO_TEST_CASE(base_utf8_1)
{
	char str[128];
	for(unsigned i=0; i<128; ++i)
	{
		str[i] = char(i & 0xFF);
	}

	BOOST_ASSERT(eagine::base::valid_utf8(str+1, str+128));
}

BOOST_AUTO_TEST_SUITE_END()
