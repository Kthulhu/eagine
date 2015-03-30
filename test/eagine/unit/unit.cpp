/**
 *  .file test/eagine/unit/unit.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_unit
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimensionless.hpp>
#include <eagine/unit/dimension.hpp>
#include <eagine/unit/derived.hpp>
#include <eagine/unit/unit.hpp>

BOOST_AUTO_TEST_SUITE(unit_unit)

template <template <class> class Test>
void do_test_unit_unit(void)
{
	using eagine::unit::unit;

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
struct test_unit_unit_is_unit
{
	void operator()(void) const
	{
		BOOST_ASSERT(eagine::unit::is_unit<Unit>());
		BOOST_ASSERT(eagine::unit::is_dimension<typename Unit::dimension>());
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_is_unit)
{
	do_test_unit_unit<test_unit_unit_is_unit>();
}

template <typename Unit>
struct test_unit_unit_default_ctr
{
	void operator()(void) const
	{
		Unit u;
		(void)u;
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_default_ctr)
{
	do_test_unit_unit<test_unit_unit_default_ctr>();
}

template <typename Unit>
struct test_unit_unit_copy_ctr
{
	void operator()(void) const
	{
		Unit u1;
		Unit u2(u1);
		(void)u2;
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_copy_ctr)
{
	do_test_unit_unit<test_unit_unit_copy_ctr>();
}

template <typename Unit>
struct test_unit_unit_copy_assign
{
	void operator()(void) const
	{
		Unit u1;
		Unit u2;
		u2 = u1;
		(void)u2;
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_copy_assign)
{
	do_test_unit_unit<test_unit_unit_copy_assign>();
}

template <typename Unit1>
struct test_unit_unit_assignable
{
	template <typename Unit2>
	struct tester
	{
		void operator()(void) const
		{
			BOOST_ASSERT((
				std::is_assignable<Unit1, Unit2>() ==
				std::is_assignable<Unit2, Unit1>()
			));
			BOOST_ASSERT((
				std::is_assignable<Unit1, Unit2>() ==
				std::is_same<Unit1, Unit2>()
			));
		}
	};

	void operator()(void) const
	{
		do_test_unit_unit<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_assignable)
{
	do_test_unit_unit<test_unit_unit_assignable>();
}

template <typename Unit1>
struct test_unit_unit_add
{
	template <typename Unit2>
	struct tester
	{
		template <typename U1, typename U2>
		static bool are_addable(decltype(U1()+U2())*)
		{
			return true;
		}

		template <typename U1, typename U2>
		static bool are_addable(...)
		{
			return false;
		}

		void operator()(void) const
		{
			BOOST_ASSERT((
				are_addable<Unit1, Unit2>(0) ==
				std::is_same<
					typename Unit1::dimension,
					typename Unit2::dimension
				>()
			));
		}
	};

	void operator()(void) const
	{
		do_test_unit_unit<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_add)
{
	do_test_unit_unit<test_unit_unit_add>();
}

template <typename Unit1>
struct test_unit_unit_subtract
{
	template <typename Unit2>
	struct tester
	{
		template <typename U1, typename U2>
		static bool are_subtractible(decltype(U1()-U2())*)
		{
			return true;
		}

		template <typename U1, typename U2>
		static bool are_subtractible(...)
		{
			return false;
		}

		void operator()(void) const
		{
			BOOST_ASSERT((
				are_subtractible<Unit1, Unit2>(0) ==
				std::is_same<
					typename Unit1::dimension,
					typename Unit2::dimension
				>()
			));
		}
	};

	void operator()(void) const
	{
		do_test_unit_unit<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_subtract)
{
	do_test_unit_unit<test_unit_unit_subtract>();
}

template <typename Unit1>
struct test_unit_unit_multiply
{
	template <typename Unit2>
	struct tester
	{
		void operator()(void) const
		{
			using eagine::unit::operator*;

			Unit1 u1;
			Unit2 u2;

			auto u3 = u1*u2;

			BOOST_ASSERT(eagine::unit::is_unit<decltype(u3)>());
		}
	};

	void operator()(void) const
	{
		do_test_unit_unit<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_multiply)
{
	do_test_unit_unit<test_unit_unit_multiply>();
}

template <typename Unit1>
struct test_unit_unit_divide
{
	template <typename Unit2>
	struct tester
	{
		void operator()(void) const
		{
			using eagine::unit::operator/;

			Unit1 u1;
			Unit2 u2;

			auto u3 = u1/u2;

			BOOST_ASSERT(eagine::unit::is_unit<decltype(u3)>());
		}
	};

	void operator()(void) const
	{
		do_test_unit_unit<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_unit_divide)
{
	do_test_unit_unit<test_unit_unit_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
