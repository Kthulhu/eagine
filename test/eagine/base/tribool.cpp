/**
 *  .file test/eagine/base/tribool.cpp
 *  .brief Test case for base::tribool class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_tribool
#include <boost/test/unit_test.hpp>

#include <eagine/base/tribool.hpp>

BOOST_AUTO_TEST_SUITE(base_tribool)

BOOST_AUTO_TEST_CASE(base_guid_tribool)
{
	EAGine::base::tribool b;
}

BOOST_AUTO_TEST_CASE(base_tribool_copy_construction)
{
	EAGine::base::tribool b1;
	EAGine::base::tribool b2(b1);
}

BOOST_AUTO_TEST_CASE(base_tribool_initialization)
{
	EAGine::base::tribool t(true);
	EAGine::base::tribool f(false);
	EAGine::base::tribool i(EAGine::base::indeterminate);
}

BOOST_AUTO_TEST_CASE(base_tribool_ops)
{
	EAGine::base::tribool a = true;
	EAGine::base::tribool b = false;
	EAGine::base::tribool c = EAGine::base::indeterminate;

	BOOST_ASSERT(a == a);
	BOOST_ASSERT(a == true);
	BOOST_ASSERT(b == b);
	BOOST_ASSERT(b == false);
	BOOST_ASSERT(!(a == b));

	BOOST_ASSERT(a != false);
	BOOST_ASSERT(b != true);
	BOOST_ASSERT(!(b != false));
	BOOST_ASSERT(!(a != a));
	BOOST_ASSERT(!(b != b));
	BOOST_ASSERT(a != b);
	BOOST_ASSERT(b != a);

	BOOST_ASSERT(!!(a == c));
	BOOST_ASSERT(!!(b == c));
	BOOST_ASSERT(!!(c == c));
	BOOST_ASSERT(!!(c == a));
	BOOST_ASSERT(!!(c == b));

	BOOST_ASSERT(~(a == c));
	BOOST_ASSERT(~(b == c));
	BOOST_ASSERT(~(c == c));
	BOOST_ASSERT(~(c == a));
	BOOST_ASSERT(~(c == b));

	BOOST_ASSERT(a && a);
	BOOST_ASSERT(!(a && b));
	BOOST_ASSERT(!(b && a));
	BOOST_ASSERT(!(b && b));
	BOOST_ASSERT(~(a && c));
	BOOST_ASSERT(!(b && c));
	BOOST_ASSERT(~(c && c));
	BOOST_ASSERT(~(c && a));
	BOOST_ASSERT(!(c && b));

	BOOST_ASSERT(a || a);
	BOOST_ASSERT(a || b);
	BOOST_ASSERT(a || c);
	BOOST_ASSERT(b || a);
	BOOST_ASSERT(c || a);
	BOOST_ASSERT(!(b || b));
	BOOST_ASSERT(~(c || b));
	BOOST_ASSERT(~(b || c));
	BOOST_ASSERT(~(c || c));
}

BOOST_AUTO_TEST_SUITE_END()
