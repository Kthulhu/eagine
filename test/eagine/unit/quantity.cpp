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

#include <eagine/math/close_to.hpp>

#include <cstdlib>

BOOST_AUTO_TEST_SUITE(unit_quantity)

template <template <class> class Test>
void do_test_unit_quantity(void)
{
	using eagine::unit::unit;
	using eagine::unit::quantity;

	Test<unit<eagine::unit::dimensionless>>()();

	Test<unit<eagine::unit::angle>>()();
	Test<unit<eagine::unit::solid_angle>>()();
	Test<unit<eagine::unit::length>>()();
	Test<unit<eagine::unit::mass>>()();
	Test<unit<eagine::unit::time>>()();

	Test<unit<eagine::unit::temperature>>()();
	Test<unit<eagine::unit::electric_current>>()();
	Test<unit<eagine::unit::number_of_cycles>>()();
	Test<unit<eagine::unit::number_of_decays>>()();
	Test<unit<eagine::unit::luminous_intensity>>()();
	Test<unit<eagine::unit::amount_of_substance>>()();

	Test<unit<eagine::unit::acceleration>>()();
	Test<unit<eagine::unit::electrical_capacitance>>()();
	Test<unit<eagine::unit::electric_charge>>()();
	Test<unit<eagine::unit::force>>()();
	Test<unit<eagine::unit::magnetic_flux_density>>()();
	Test<unit<eagine::unit::momentum>>()();
	Test<unit<eagine::unit::radioactivity>>()();
	Test<unit<eagine::unit::angular_velocity>>()();
	Test<unit<eagine::unit::electrical_conductance>>()();
	Test<unit<eagine::unit::electric_tension>>()();
	Test<unit<eagine::unit::frequency>>()();
	Test<unit<eagine::unit::magnetic_flux>>()();
	Test<unit<eagine::unit::power>>()();
	Test<unit<eagine::unit::velocity>>()();
	Test<unit<eagine::unit::area>>()();
	Test<unit<eagine::unit::electrical_resistance>>()();
	Test<unit<eagine::unit::energy>>()();
	Test<unit<eagine::unit::inductance>>()();
	Test<unit<eagine::unit::mass_density>>()();
	Test<unit<eagine::unit::pressure>>()();
	Test<unit<eagine::unit::volume>>()();
}

template <typename Unit>
struct test_unit_quantity_default_ctr
{
	void operator()(void) const
	{
		eagine::unit::quantity<Unit> q;
		(void)q;
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_default_ctr)
{
	do_test_unit_quantity<test_unit_quantity_default_ctr>();
}

template <typename Unit>
struct test_unit_quantity_copy_ctr
{
	void operator()(void) const
	{
		eagine::unit::quantity<Unit> q1;
		eagine::unit::quantity<Unit> q2(q1);
		(void)q2;
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_copy_ctr)
{
	do_test_unit_quantity<test_unit_quantity_copy_ctr>();
}

template <typename Unit>
struct test_unit_quantity_copy_assign
{
	void operator()(void) const
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
}

template <typename Unit>
struct test_unit_quantity_add
{
	void operator()(void) const
	{
		typedef typename eagine::unit::quantity<Unit>::value_type T;

		eagine::unit::quantity<Unit> q1(T(std::rand() % 111));
		eagine::unit::quantity<Unit> q2(T(std::rand() % 111));

		eagine::unit::quantity<Unit> q3 = q1+q2;

		using eagine::math::close_to;

		BOOST_ASSERT((
			value(q3) <<close_to>>
			(value(q1) + value(q2))
		));
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_add)
{
	do_test_unit_quantity<test_unit_quantity_add>();
}

template <typename Unit>
struct test_unit_quantity_subtract
{
	void operator()(void) const
	{
		typedef typename eagine::unit::quantity<Unit>::value_type T;

		eagine::unit::quantity<Unit> q1(T(std::rand() % 111));
		eagine::unit::quantity<Unit> q2(T(std::rand() % 111));

		eagine::unit::quantity<Unit> q3 = q1-q2;

		using eagine::math::close_to;

		BOOST_ASSERT((
			value(q3) <<close_to>>
			(value(q1) - value(q2))
		));
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
		void operator()(void) const
		{
			using eagine::unit::operator*;

			typedef typename eagine::unit::quantity<Unit1>::value_type T1;
			typedef typename eagine::unit::quantity<Unit2>::value_type T2;

			eagine::unit::quantity<Unit1> q1(T1(std::rand() % 111));
			eagine::unit::quantity<Unit2> q2(T2(std::rand() % 111));

			typedef decltype(Unit1()*Unit2()) Unit3;

			eagine::unit::quantity<Unit3> q3 = q1*q2;

			using eagine::math::close_to;

			BOOST_ASSERT((
				value(q3) <<close_to>>
				(value(q1) * value(q2))
			));
		}
	};

	void operator()(void) const
	{
		do_test_unit_quantity<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_multiply)
{
	do_test_unit_quantity<test_unit_quantity_multiply>();
}

template <typename Unit1>
struct test_unit_quantity_divide
{
	template <typename Unit2>
	struct tester
	{
		void operator()(void) const
		{
			using eagine::unit::operator/;

			typedef typename eagine::unit::quantity<Unit1>::value_type T1;
			typedef typename eagine::unit::quantity<Unit2>::value_type T2;

			eagine::unit::quantity<Unit1> q1(T1(std::rand() % 111));
			eagine::unit::quantity<Unit2> q2(T2(1+std::rand() % 111));

			typedef decltype(Unit1()/Unit2()) Unit3;

			eagine::unit::quantity<Unit3> q3 = q1/q2;

			using eagine::math::close_to;

			BOOST_ASSERT((
				value(q3) <<close_to>>
				(value(q1) / value(q2))
			));
		}
	};

	void operator()(void) const
	{
		do_test_unit_quantity<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_quantity_divide)
{
	do_test_unit_quantity<test_unit_quantity_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
