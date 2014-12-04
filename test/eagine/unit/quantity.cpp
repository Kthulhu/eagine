/**
 *  .file test/eagine/unit/quantity.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_quantity
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimension.hpp>
#include <eagine/unit/unit.hpp>
#include <eagine/unit/quantity.hpp>
#include <eagine/unit/si.hpp>

BOOST_AUTO_TEST_SUITE(unit_quantity)

BOOST_AUTO_TEST_CASE(unit_quantity_default_ctr1)
{
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::angle>> qa;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::solid_angle>> qsa;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::length>> ql;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::mass>> qm;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::time>> qt;

	eagine::unit::quantity<eagine::unit::unit<eagine::unit::temperature>> qT;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::electric_current>> qC;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::number_of_cycles>> qN;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::number_of_decays>> qD;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::luminous_intensity>> qli;
	eagine::unit::quantity<eagine::unit::unit<eagine::unit::amount_of_substance>> qaos;
}

BOOST_AUTO_TEST_CASE(unit_quantity_default_ctr2)
{
	eagine::unit::quantity<eagine::unit::radian> qrad;
	eagine::unit::quantity<eagine::unit::steradian> qsr;
	eagine::unit::quantity<eagine::unit::meter> qm;
	eagine::unit::quantity<eagine::unit::kilogram> qkg;
	eagine::unit::quantity<eagine::unit::second> qs;

	eagine::unit::quantity<eagine::unit::kelvin> qK;
	eagine::unit::quantity<eagine::unit::ampere> qA;
	eagine::unit::quantity<eagine::unit::hertz> qHz;
	eagine::unit::quantity<eagine::unit::becquerel> qBq;
	eagine::unit::quantity<eagine::unit::candela> qcd;
	eagine::unit::quantity<eagine::unit::mole> qmol;
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
