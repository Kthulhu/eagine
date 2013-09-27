/**
 *  .file test/eagine/base/format.cpp
 *  .brief Test case for base::format class
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_format
#include <boost/test/unit_test.hpp>

#include <eagine/base/format.hpp>
#include <eagine/base/string.hpp>

BOOST_AUTO_TEST_SUITE(base_format)

BOOST_AUTO_TEST_CASE(base_format_construction)
{
	using namespace EAGine::base;
	format f(text_message("a message"));
}

BOOST_AUTO_TEST_CASE(base_format_parameters)
{
	using namespace EAGine::base;
	int a = 1;
	bool b = false;
	float c = 23.45f;
	double d = 67.89;
	string e = "str";
	format(text_message("a message")) % a % b % c % d % e;
}

BOOST_AUTO_TEST_CASE(base_format_str)
{
	using namespace EAGine::base;
	format f(text_message("a message"));
	string s = f.str();
}

BOOST_AUTO_TEST_CASE(base_format_ostream)
{
	using namespace EAGine::base;
	format f(text_message("a message"));

	std::stringstream out;
	out << f;
}

BOOST_AUTO_TEST_SUITE_END()
