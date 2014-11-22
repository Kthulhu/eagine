/**
 *  .file test/eagine/base/path.cpp
 *  .brief Test case for base::path class and related functionality
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_path
#include <boost/test/unit_test.hpp>

#include <eagine/base/path.hpp>

BOOST_AUTO_TEST_SUITE(base_path)

BOOST_AUTO_TEST_CASE(base_path_default_construction)
{
	eagine::base::path p;
}

BOOST_AUTO_TEST_CASE(base_path_construction_1)
{
	eagine::base::path p = eagine::base::pa::th/"test"/"eagine"/"base"/"path";
}

BOOST_AUTO_TEST_CASE(base_path_construction_2)
{
	using namespace eagine::base;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	path p2 = pa::th/par::ent/"test"/"eagine"/"base"/"path";
}

BOOST_AUTO_TEST_CASE(base_path_copy_construction)
{
	using namespace eagine::base;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	path p2 = p1;
}

BOOST_AUTO_TEST_CASE(base_path_empty)
{
	using namespace eagine::base;
	const path p0;
	const path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	const path p2 = pa::th/par::ent/"test"/"eagine"/"base"/"path";
	const path p3 = pa::th/"test";
	const path p4 = pa::th/par::ent;

	BOOST_ASSERT( p0.empty());
	BOOST_ASSERT(!p1.empty());
	BOOST_ASSERT(!p2.empty());
	BOOST_ASSERT(!p3.empty());
	BOOST_ASSERT(!p4.empty());
}

BOOST_AUTO_TEST_CASE(base_path_size)
{
	using namespace eagine::base;
	const path p0;
	const path p1 = pa::th/"test";
	const path p2 = pa::th/par::ent;
	const path p3 = pa::th/"test"/"eagine"/"base";
	const path p4 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	const path p5 = pa::th/par::ent/"test"/"eagine"/"base"/"path";

	BOOST_ASSERT(p0.size() == 0);
	BOOST_ASSERT(p1.size() == 1);
	BOOST_ASSERT(p2.size() == 1);
	BOOST_ASSERT(p3.size() == 3);
	BOOST_ASSERT(p4.size() == 5);
	BOOST_ASSERT(p5.size() == 5);
}

BOOST_AUTO_TEST_CASE(base_path_clear)
{
	using namespace eagine::base;
	eagine::base::path p0;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";

	BOOST_ASSERT( p0.empty());
	BOOST_ASSERT(!p1.empty());

	p0.clear();
	p1.clear();

	BOOST_ASSERT( p0.empty());
	BOOST_ASSERT( p1.empty());
}

BOOST_AUTO_TEST_CASE(base_path_front_back)
{
	using namespace eagine::base;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	const path p2 = pa::th/par::ent/"test"/"eagine"/"base"/"path";

	p1.front();
	p2.front();

	p1.back();
	p2.back();
}

BOOST_AUTO_TEST_CASE(base_path_front_back_read)
{
	using namespace eagine::base;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	path p2 = pa::th/par::ent/"test"/"eagine"/"base"/"path";

	p1.front() == "test";
	p2.front() == par::ent;

	p1.back() == "path";
	p1.back() == p2.back();
}

BOOST_AUTO_TEST_CASE(base_path_entry_ref_compare_equality)
{
	using namespace eagine::base;
	path p1 = pa::th/"test"/par::ent/"eagine"/"base"/"path";
	path p2 = pa::th/par::ent/"test"/"eagine"/"base"/"path";

	BOOST_ASSERT(p1.front() == p1.front());
	BOOST_ASSERT(p2.front() == p2.front());
	BOOST_ASSERT(p1.front() != p2.front());
	BOOST_ASSERT(p2.front() != p1.front());

	BOOST_ASSERT(p1.front() == "test");
	BOOST_ASSERT(p2.front() == par::ent);
	BOOST_ASSERT(p1.front() != "path");
	BOOST_ASSERT(p1.front() != "");
	BOOST_ASSERT(p2.front() != "test");
	BOOST_ASSERT(p2.front() != "");

	BOOST_ASSERT(!(p1.front() != p1.front()));
	BOOST_ASSERT(!(p2.front() != p2.front()));
	BOOST_ASSERT(!(p1.front() == p2.front()));
	BOOST_ASSERT(!(p2.front() == p1.front()));

	BOOST_ASSERT(!(p1.front() != "test"));
	BOOST_ASSERT(!(p2.front() != par::ent));
	BOOST_ASSERT(!(p1.front() == "path"));
	BOOST_ASSERT(!(p1.front() == ""));
	BOOST_ASSERT(!(p2.front() == "test"));
	BOOST_ASSERT(!(p2.front() == ""));


	BOOST_ASSERT("test" == p1.front());
	BOOST_ASSERT(par::ent == p2.front());
	BOOST_ASSERT("path" != p1.front());
	BOOST_ASSERT("" != p1.front());
	BOOST_ASSERT("test" != p2.front());
	BOOST_ASSERT("" != p2.front());

	BOOST_ASSERT(!("test" != p1.front()));
	BOOST_ASSERT(!(par::ent != p2.front()));
	BOOST_ASSERT(!("path" == p1.front()));
	BOOST_ASSERT(!("" == p1.front()));
	BOOST_ASSERT(!("test" == p2.front()));
	BOOST_ASSERT(!("" == p2.front()));
}

BOOST_AUTO_TEST_SUITE_END()
