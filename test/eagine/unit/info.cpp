/**
 *  .file test/eagine/unit/info.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_info
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimensionless.hpp>
#include <eagine/unit/derived.hpp>
#include <eagine/unit/info.hpp>

#include <cstring>

static const char* test_unit_info_dim_names [] = {
	"dimensionless",
	"angle",
	"mass",
	"length",
	"time",
	"temperature",
	"electric current",
	"number of cycles",
	"number of decays",
	"luminous intensity",
	"amount of substance",
	"solid angle",

	"acceleration",
	"electrical capacitance",
	"electric charge",
	"force",
	"magnetic flux density",
	"momentum",
	"radioactivity",
	"angular velocity",
	"electrical conductance",
	"electric tension",
	"frequency",
	"magnetic flux",
	"power",
	"velocity",
	"area",
	"electrical resistance",
	"energy",
	"inductance",
	"mass density",
	"pressure",
	"volume",
};

BOOST_AUTO_TEST_SUITE(unit_info)

template <template <class> class Test>
void do_test_unit_dimension_info(void)
{
	unsigned i=0;

	Test<eagine::unit::dimensionless>()(i++);

	Test<eagine::unit::angle>()(i++);
	Test<eagine::unit::mass>()(i++);
	Test<eagine::unit::length>()(i++);
	Test<eagine::unit::time>()(i++);
	Test<eagine::unit::temperature>()(i++);
	Test<eagine::unit::electric_current>()(i++);
	Test<eagine::unit::number_of_cycles>()(i++);
	Test<eagine::unit::number_of_decays>()(i++);
	Test<eagine::unit::luminous_intensity>()(i++);
	Test<eagine::unit::amount_of_substance>()(i++);
	Test<eagine::unit::solid_angle>()(i++);

	Test<eagine::unit::acceleration>()(i++);
	Test<eagine::unit::electrical_capacitance>()(i++);
	Test<eagine::unit::electric_charge>()(i++);
	Test<eagine::unit::force>()(i++);
	Test<eagine::unit::magnetic_flux_density>()(i++);
	Test<eagine::unit::momentum>()(i++);
	Test<eagine::unit::radioactivity>()(i++);
	Test<eagine::unit::angular_velocity>()(i++);
	Test<eagine::unit::electrical_conductance>()(i++);
	Test<eagine::unit::electric_tension>()(i++);
	Test<eagine::unit::frequency>()(i++);
	Test<eagine::unit::magnetic_flux>()(i++);
	Test<eagine::unit::power>()(i++);
	Test<eagine::unit::velocity>()(i++);
	Test<eagine::unit::area>()(i++);
	Test<eagine::unit::electrical_resistance>()(i++);
	Test<eagine::unit::energy>()(i++);
	Test<eagine::unit::inductance>()(i++);
	Test<eagine::unit::mass_density>()(i++);
	Test<eagine::unit::pressure>()(i++);
	Test<eagine::unit::volume>()(i++);
}

template <typename Dimension>
struct test_unit_dimension_info
{
	void operator()(unsigned i) const
	{
		BOOST_ASSERT((std::strcmp(
			eagine::meta::c_str<
				typename eagine::unit::info<
					Dimension
				>::name
			>::value,
			test_unit_info_dim_names[i]
		) == 0));
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_info)
{
	do_test_unit_dimension_info<test_unit_dimension_info>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
