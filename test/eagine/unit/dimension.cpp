/**
 *  .file test/eagine/unit/dimension.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_dimension
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimension.hpp>

BOOST_AUTO_TEST_SUITE(unit_dimension)

BOOST_AUTO_TEST_CASE(unit_dimension_default_ctr)
{
	eagine::unit::angle a;
	eagine::unit::solid_angle sa;
	eagine::unit::length l;
	eagine::unit::mass m;
	eagine::unit::time t;

	eagine::unit::temperature T;
	eagine::unit::electric_current C;
	eagine::unit::number_of_cycles N;
	eagine::unit::number_of_decays D;
	eagine::unit::luminous_intensity li;
	eagine::unit::amount_of_substance aos;
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
