/**
 *  .file test/eagine/unit/quantity.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_quantity
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimensionless.hpp>
#include <eagine/unit/dimension.hpp>
#include <eagine/unit/derived.hpp>
#include <eagine/unit/unit.hpp>
#include <eagine/unit/quantity.hpp>
#include <eagine/unit/si.hpp>

#include <eagine/unit/si/electric_charge.hpp>
#include <eagine/unit/si/electric_tension.hpp>
#include <eagine/unit/si/electrical_capacitance.hpp>
#include <eagine/unit/si/electrical_conductance.hpp>
#include <eagine/unit/si/electrical_resistance.hpp>
#include <eagine/unit/si/force.hpp>
#include <eagine/unit/si/energy.hpp>
#include <eagine/unit/si/power.hpp>

#include <eagine/math/difference.hpp>

#include <cstdlib>

BOOST_AUTO_TEST_SUITE(unit_quantity)

template <template <class> class Test>
void do_test_unit_quantity(void)
{
	using eagine::unit::unit;
	using eagine::unit::quantity;

	Test<unit<eagine::unit::dimensionless>>()(false);

	Test<unit<eagine::unit::angle>>()(false);
	Test<unit<eagine::unit::solid_angle>>()(false);
	Test<unit<eagine::unit::length>>()(false);
	Test<unit<eagine::unit::mass>>()(false);
	Test<unit<eagine::unit::time>>()(false);

	Test<unit<eagine::unit::temperature>>()(false);
	Test<unit<eagine::unit::electric_current>>()(false);
	Test<unit<eagine::unit::number_of_cycles>>()(false);
	Test<unit<eagine::unit::number_of_decays>>()(false);
	Test<unit<eagine::unit::luminous_intensity>>()(false);
	Test<unit<eagine::unit::amount_of_substance>>()(false);

	Test<unit<eagine::unit::acceleration>>()(false);
	Test<unit<eagine::unit::electrical_capacitance>>()(false);
	Test<unit<eagine::unit::electric_charge>>()(false);
	Test<unit<eagine::unit::force>>()(false);
	Test<unit<eagine::unit::magnetic_flux_density>>()(false);
	Test<unit<eagine::unit::momentum>>()(false);
	Test<unit<eagine::unit::radioactivity>>()(false);
	Test<unit<eagine::unit::angular_velocity>>()(false);
	Test<unit<eagine::unit::electrical_conductance>>()(false);
	Test<unit<eagine::unit::electric_tension>>()(false);
	Test<unit<eagine::unit::frequency>>()(false);
	Test<unit<eagine::unit::magnetic_flux>>()(false);
	Test<unit<eagine::unit::power>>()(false);
	Test<unit<eagine::unit::velocity>>()(false);
	Test<unit<eagine::unit::area>>()(false);
	Test<unit<eagine::unit::electrical_resistance>>()(false);
	Test<unit<eagine::unit::energy>>()(false);
	Test<unit<eagine::unit::inductance>>()(false);
	Test<unit<eagine::unit::mass_density>>()(false);
	Test<unit<eagine::unit::pressure>>()(false);
	Test<unit<eagine::unit::volume>>()(false);
}

template <template <class> class Test>
void do_test_unit_scaled_quantity(void)
{
	using eagine::unit::unit;
	using eagine::unit::quantity;

	Test<unit<eagine::unit::dimensionless>>()(true);

	Test<eagine::unit::radian>()(true);
	Test<eagine::unit::degree>()(true);
	Test<eagine::unit::gradian>()(true);
	Test<eagine::unit::quarter>()(true);
	Test<eagine::unit::turn>()(true);
	Test<eagine::unit::pi_rad>()(true);

	Test<eagine::unit::gram>()(true);
	Test<eagine::unit::milligram>()(true);
	Test<eagine::unit::kilogram>()(true);

	Test<eagine::unit::meter>()(true);
	Test<eagine::unit::millimeter>()(true);
	Test<eagine::unit::kilometer>()(true);

	Test<eagine::unit::second>()(true);
	Test<eagine::unit::minute>()(true);
	Test<eagine::unit::hour>()(true);
	Test<eagine::unit::day>()(true);

	Test<eagine::unit::kelvin>()(true);

	Test<eagine::unit::ampere>()(true);
	Test<eagine::unit::coulomb>()(true);
	Test<eagine::unit::volt>()(true);
	Test<eagine::unit::farad>()(true);
	Test<eagine::unit::siemens>()(true);
	Test<eagine::unit::ohm>()(true);

	Test<eagine::unit::newton>()(true);
	Test<eagine::unit::joule>()(true);
	Test<eagine::unit::watt>()(true);

	Test<eagine::unit::hertz>()(true);
	Test<eagine::unit::becquerel>()(true);

	Test<eagine::unit::candela>()(true);

	Test<eagine::unit::mole>()(true);

	Test<eagine::unit::steradian>()(true);
}

template <typename Unit>
struct test_unit_quantity_default_ctr
{
	void operator()(bool) const
	{
		eagine::unit::quantity<Unit> q;
		(void)q;
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_default_ctr)
{
	do_test_unit_quantity<test_unit_quantity_default_ctr>();
	do_test_unit_scaled_quantity<test_unit_quantity_default_ctr>();
}

template <typename Unit>
struct test_unit_quantity_copy_ctr
{
	void operator()(bool) const
	{
		eagine::unit::quantity<Unit> q1;
		eagine::unit::quantity<Unit> q2(q1);
		(void)q2;
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_copy_ctr)
{
	do_test_unit_quantity<test_unit_quantity_copy_ctr>();
	do_test_unit_scaled_quantity<test_unit_quantity_copy_ctr>();
}

template <typename Unit>
struct test_unit_quantity_copy_assign
{
	void operator()(bool) const
	{
		eagine::unit::quantity<Unit> q1;
		eagine::unit::quantity<Unit> q2;
		q2 = q1;
		(void)q2;
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_copy_assign)
{
	do_test_unit_quantity<test_unit_quantity_copy_assign>();
	do_test_unit_scaled_quantity<test_unit_quantity_copy_assign>();
}

template <typename Unit>
struct test_unit_quantity_add
{
	void operator()(bool scaled) const
	{
		typedef typename eagine::unit::quantity<Unit>::value_type T;

		eagine::unit::quantity<Unit> q1(T(std::rand() % 111));
		eagine::unit::quantity<Unit> q2(T(std::rand() % 111));

		eagine::unit::quantity<Unit> q3 = q1+q2;

		using eagine::math::close_to;

		if(!scaled)
		{
			BOOST_ASSERT((
				value(q3) <<close_to>>
				(value(q1) + value(q2))
			));
			BOOST_ASSERT((q3 <<close_to>> (q1 + q2)));
		}
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_add)
{
	do_test_unit_quantity<test_unit_quantity_add>();
}

template <typename Unit>
struct test_unit_quantity_subtract
{
	void operator()(bool scaled) const
	{
		typedef typename eagine::unit::quantity<Unit>::value_type T;

		eagine::unit::quantity<Unit> q1(T(std::rand() % 111));
		eagine::unit::quantity<Unit> q2(T(std::rand() % 111));

		eagine::unit::quantity<Unit> q3 = q1-q2;

		using eagine::math::close_to;

		if(!scaled)
		{
			BOOST_ASSERT((
				value(q3) <<close_to>>
				(value(q1) - value(q2))
			));
			BOOST_ASSERT((q3 <<close_to>> (q1 - q2)));
		}
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_subtract)
{
	do_test_unit_quantity<test_unit_quantity_subtract>();
}

template <typename Unit1>
struct test_unit_quantity_multiply
{
	template <typename Unit2>
	struct tester
	{
		void operator()(bool scaled) const
		{
			using eagine::unit::operator*;

			typedef typename eagine::unit::quantity<Unit1>::value_type T1;
			typedef typename eagine::unit::quantity<Unit2>::value_type T2;

			eagine::unit::quantity<Unit1> q1(T1(std::rand() % 111));
			eagine::unit::quantity<Unit2> q2(T2(std::rand() % 111));

			typedef decltype(Unit1()*Unit2()) Unit3;

			eagine::unit::quantity<Unit3> q3 = q1*q2;

			using eagine::math::close_to;

			if(!scaled)
			{
				BOOST_ASSERT((
					value(q3) <<close_to>>
					(value(q1) * value(q2))
				));
				BOOST_ASSERT((q3 <<close_to>> (q1 * q2)));
			}
		}
	};

	void operator()(bool scaled) const
	{
		if(scaled)
		{
			do_test_unit_scaled_quantity<tester>();
		}
		else
		{
			do_test_unit_quantity<tester>();
		}
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_multiply)
{
	do_test_unit_quantity<test_unit_quantity_multiply>();
	do_test_unit_scaled_quantity<test_unit_quantity_multiply>();
}

template <typename Unit1>
struct test_unit_quantity_divide
{
	template <typename Unit2>
	struct tester
	{
		void operator()(bool scaled) const
		{
			using eagine::unit::operator/;

			typedef typename eagine::unit::quantity<Unit1>::value_type T1;
			typedef typename eagine::unit::quantity<Unit2>::value_type T2;

			eagine::unit::quantity<Unit1> q1(T1(std::rand() % 111));
			eagine::unit::quantity<Unit2> q2(T2(1+std::rand() % 111));

			typedef decltype(Unit1()/Unit2()) Unit3;

			eagine::unit::quantity<Unit3> q3 = q1/q2;

			using eagine::math::close_to;

			if(!scaled)
			{
				BOOST_ASSERT((
					value(q3) <<close_to>>
					(value(q1) / value(q2))
				));
				BOOST_ASSERT((q3 <<close_to>> (q1 / q2)));
			}
		}
	};

	void operator()(bool scaled) const
	{
		if(scaled)
		{
			do_test_unit_scaled_quantity<tester>();
		}
		else
		{
			do_test_unit_quantity<tester>();
		}
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_divide)
{
	do_test_unit_quantity<test_unit_quantity_divide>();
	do_test_unit_scaled_quantity<test_unit_quantity_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
