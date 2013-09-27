/**
 *  .file test/eagine/base/locale.cpp
 *  .brief Test case for the base localization facility
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_locale
#include <boost/test/unit_test.hpp>

#include <eagine/base/locale.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(base_locale)

BOOST_AUTO_TEST_CASE(base_test_message_default_construction)
{
	EAGine::base::text_message m;
}

BOOST_AUTO_TEST_CASE(base_test_message_init_construction)
{
	EAGine::base::text_message m("text message");
}

BOOST_AUTO_TEST_CASE(base_test_message_copy_construction)
{
	EAGine::base::text_message m1("text message");
	EAGine::base::text_message m2(m1);
}

BOOST_AUTO_TEST_CASE(base_test_message_move_construction)
{
	using EAGine::base::text_message;
	text_message m(text_message("text message"));
}

BOOST_AUTO_TEST_CASE(base_test_message_string)
{
	using EAGine::base::text_message;
	text_message m("text message");

	BOOST_ASSERT(m.str() == "text message");
}

BOOST_AUTO_TEST_CASE(base_test_message_stream)
{
	using EAGine::base::text_message;
	text_message m("text message");

	std::stringstream out;
	out << m;

	BOOST_ASSERT(out.str() == m.str());
}

BOOST_AUTO_TEST_CASE(base_test_translate_1)
{
	using EAGine::base::text_message;
	using EAGine::base::translate;

	text_message m = translate("a message");
}

BOOST_AUTO_TEST_CASE(base_test_translate_2)
{
	using EAGine::base::text_message;
	using EAGine::base::translate;

	text_message m = translate("context", "a message");
}

BOOST_AUTO_TEST_CASE(base_test_translate_3)
{
	using EAGine::base::text_message;
	using EAGine::base::translate;

	int n = 123;
	text_message m = translate("single", "plural", n);
}

BOOST_AUTO_TEST_CASE(base_test_translate_4)
{
	using EAGine::base::text_message;
	using EAGine::base::translate;

	int n = 123;
	text_message m = translate("context", "single", "plural", n);
}

BOOST_AUTO_TEST_SUITE_END()
