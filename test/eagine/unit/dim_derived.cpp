/**
 *  .file test/eagine/unit/dim_derived.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_dim_derived
#include <boost/test/unit_test.hpp>

#include <eagine/unit/derived.hpp>

BOOST_AUTO_TEST_SUITE(unit_dim_derived)

BOOST_AUTO_TEST_CASE(unit_dim_derived_default_ctr)
{
	eagine::unit::acceleration acc;
	eagine::unit::electrical_capacitance eca;
	eagine::unit::electric_charge ecg;
	eagine::unit::force f;
	eagine::unit::magnetic_flux_density mfd;
	eagine::unit::momentum m;
	eagine::unit::radioactivity ra;
	eagine::unit::angular_velocity av;
	eagine::unit::electrical_conductance ec;
	eagine::unit::electric_tension et;
	eagine::unit::frequency freq;
	eagine::unit::magnetic_flux mf;
	eagine::unit::power p;
	eagine::unit::velocity v;
	eagine::unit::area a;
	eagine::unit::electrical_resistance er;
	eagine::unit::energy e;
	eagine::unit::inductance ind;
	eagine::unit::mass_density md;
	eagine::unit::pressure pse;
	eagine::unit::volume vol;
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
