/**
 *  .file test/eagine/base/guid.cpp
 *  .brief Test case for base::guid class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_guid
#include <boost/test/unit_test.hpp>

#include <eagine/base/guid.hpp>
#include <vector>
#include <sstream>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(base_guid)

BOOST_AUTO_TEST_CASE(base_guid_default_construction)
{
	eagine::base::guid g;
}

BOOST_AUTO_TEST_CASE(base_guid_copy_construction)
{
	eagine::base::guid g1;
	eagine::base::guid g2(g1);
}

BOOST_AUTO_TEST_CASE(base_guid_uniqueness)
{
	std::size_t n = 1000;
	std::vector<eagine::base::guid> gv(n);
	for(std::size_t i=0; i!=n; ++i)
	{
		for(std::size_t j=i+1; j!=n; ++j)
		{
			BOOST_ASSERT(gv[i] != gv[j]);
		}
	}
}

BOOST_AUTO_TEST_CASE(base_guid_nil)
{
	eagine::base::guid n1 = eagine::base::guid(nullptr);
	BOOST_ASSERT(n1.is_nil());

	eagine::base::guid n2 = eagine::base::guid::nil();
	BOOST_ASSERT(n2.is_nil());

	BOOST_ASSERT(n1 == n2);
}

BOOST_AUTO_TEST_CASE(base_guid_not_nil)
{
	std::size_t n = 1000;
	for(std::size_t i=0; i!=n; ++i)
	{
		eagine::base::guid g;
		BOOST_ASSERT(!g.is_nil());
	}
}

BOOST_AUTO_TEST_CASE(base_guid_string_1)
{
	std::size_t n = 1000;
	for(std::size_t i=0; i!=n; ++i)
	{
		std::stringstream ss;

		eagine::base::guid g1;

		ss << g1;

		eagine::base::guid g2 = eagine::base::guid(ss.str());

		BOOST_ASSERT(g1 == g2);
	}
}

BOOST_AUTO_TEST_CASE(base_guid_from_string)
{
	static const char* hd = "01234567890abcdef";
	std::size_t n = 1000;
	for(std::size_t i=0; i!=n; ++i)
	{
		const char gs[36] = {
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			'-',
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			'-',
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			'-',
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			'-',
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16],
			hd[std::rand()%16]

		};

		eagine::base::guid g(gs);
	}
}

BOOST_AUTO_TEST_SUITE_END()
