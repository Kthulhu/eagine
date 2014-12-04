/**
 *  .file test/eagine/unit/unit.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_unit
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimension.hpp>
#include <eagine/unit/unit.hpp>

BOOST_AUTO_TEST_SUITE(unit_unit)

BOOST_AUTO_TEST_CASE(unit_unit_default_ctr)
{
	eagine::unit::unit<eagine::unit::angle> ua;
	eagine::unit::unit<eagine::unit::solid_angle> usa;
	eagine::unit::unit<eagine::unit::length> ul;
	eagine::unit::unit<eagine::unit::mass> um;
	eagine::unit::unit<eagine::unit::time> ut;

	eagine::unit::unit<eagine::unit::temperature> uT;
	eagine::unit::unit<eagine::unit::electric_current> uC;
	eagine::unit::unit<eagine::unit::number_of_cycles> uN;
	eagine::unit::unit<eagine::unit::number_of_decays> uD;
	eagine::unit::unit<eagine::unit::luminous_intensity> uli;
	eagine::unit::unit<eagine::unit::amount_of_substance> uaos;
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
