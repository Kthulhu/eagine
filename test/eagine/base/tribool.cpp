/**
 *  .file test/eagine/base/tribool.cpp
 *  .brief Test case for base::tribool class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_tribool
#include <boost/test/unit_test.hpp>

#include <eagine/base/tribool.hpp>

BOOST_AUTO_TEST_SUITE(base_tribool)

BOOST_AUTO_TEST_CASE(base_guid_tribool)
{
	eagine::base::tribool b;
	(void)b;
}

BOOST_AUTO_TEST_CASE(base_tribool_copy_construction)
{
	eagine::base::tribool b1;
	eagine::base::tribool b2(b1);
	(void)b2;
}

BOOST_AUTO_TEST_CASE(base_tribool_initialization)
{
	eagine::base::tribool t(true);
	eagine::base::tribool f(false);
	eagine::base::tribool i(eagine::base::indeterminate);

	(void)t;
	(void)f;
	(void)i;
}

BOOST_AUTO_TEST_CASE(base_tribool_ops)
{
	eagine::base::tribool a = true;
	eagine::base::tribool b = false;
	eagine::base::tribool c = eagine::base::indeterminate;

	BOOST_ASSERT(bool(a));
	BOOST_ASSERT(!!a);
	BOOST_ASSERT(!*a);
	BOOST_ASSERT(~a);
	BOOST_ASSERT(!!~a);
	BOOST_ASSERT(a == a);
	BOOST_ASSERT(true == a);
	BOOST_ASSERT(!bool(b));
	BOOST_ASSERT(!b);
	BOOST_ASSERT(!*b);
	BOOST_ASSERT(!bool(~b));
	BOOST_ASSERT(!~b);
	BOOST_ASSERT(b == b);
	BOOST_ASSERT(b == false);
	BOOST_ASSERT(false == b);
	BOOST_ASSERT(!(a == b));
	BOOST_ASSERT(!(b == a));
	BOOST_ASSERT(!bool(c));
	BOOST_ASSERT(!!c);
	BOOST_ASSERT(*c);
	BOOST_ASSERT(~c);
	BOOST_ASSERT(!~c);

	BOOST_ASSERT(a != false);
	BOOST_ASSERT(false != a);
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

	BOOST_ASSERT(~(a != c));
	BOOST_ASSERT(~(b != c));
	BOOST_ASSERT(~(c != c));
	BOOST_ASSERT(~(c != a));
	BOOST_ASSERT(~(c != b));

	BOOST_ASSERT(a && a);
	BOOST_ASSERT(!(a && b));
	BOOST_ASSERT(!(b && a));
	BOOST_ASSERT(!(b && b));
	BOOST_ASSERT(*(a && c));
	BOOST_ASSERT(!(b && c));
	BOOST_ASSERT(*(c && c));
	BOOST_ASSERT(*(c && a));
	BOOST_ASSERT(!(c && b));

	BOOST_ASSERT(a || a);
	BOOST_ASSERT(a || b);
	BOOST_ASSERT(a || c);
	BOOST_ASSERT(b || a);
	BOOST_ASSERT(c || a);
	BOOST_ASSERT(!(b || b));
	BOOST_ASSERT(*(c || b));
	BOOST_ASSERT(*(b || c));
	BOOST_ASSERT(*(c || c));
}

BOOST_AUTO_TEST_SUITE_END()
