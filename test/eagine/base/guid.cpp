/**
 *  .file test/eagine/base/guid.cpp
 *  .brief Test case for base::guid class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_guid
#include <boost/test/unit_test.hpp>

#include <eagine/base/guid.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(base_guid)

BOOST_AUTO_TEST_CASE(base_guid_default_construction)
{
	EAGine::base::guid g;
}

BOOST_AUTO_TEST_CASE(base_guid_copy_construction)
{
	EAGine::base::guid g1;
	EAGine::base::guid g2(g1);
}

BOOST_AUTO_TEST_CASE(base_guid_uniqueness)
{
	std::size_t n = 1000;
	std::vector<EAGine::base::guid> gv(n);
	for(std::size_t i=0; i!=n; ++i)
	{
		for(std::size_t j=i+1; j!=n; ++j)
		{
			BOOST_ASSERT(gv[i] != gv[j]);
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()
