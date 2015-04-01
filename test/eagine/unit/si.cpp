/**
 *  .file test/eagine/unit/si.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_si
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimension.hpp>
#include <eagine/unit/derived.hpp>
#include <eagine/unit/si.hpp>
#include <eagine/unit/si/electric_charge.hpp>
#include <eagine/unit/si/electric_tension.hpp>
#include <eagine/unit/si/electrical_capacitance.hpp>
#include <eagine/unit/si/electrical_conductance.hpp>
#include <eagine/unit/si/electrical_resistance.hpp>
#include <eagine/unit/si/force.hpp>
#include <eagine/unit/si/energy.hpp>
#include <eagine/unit/si/power.hpp>

BOOST_AUTO_TEST_SUITE(unit_si)

template <template <class> class Test>
void do_test_unit_si(void)
{
	Test<eagine::unit::radian>()();
	Test<eagine::unit::degree>()();
	Test<eagine::unit::gradian>()();
	Test<eagine::unit::quarter>()();
	Test<eagine::unit::turn>()();
	Test<eagine::unit::pi_rad>()();

	Test<eagine::unit::gram>()();
	Test<eagine::unit::milligram>()();
	Test<eagine::unit::kilogram>()();

	Test<eagine::unit::meter>()();
	Test<eagine::unit::millimeter>()();
	Test<eagine::unit::kilometer>()();

	Test<eagine::unit::second>()();
	Test<eagine::unit::minute>()();
	Test<eagine::unit::hour>()();
	Test<eagine::unit::day>()();

	Test<eagine::unit::kelvin>()();

	Test<eagine::unit::ampere>()();
	Test<eagine::unit::coulomb>()();
	Test<eagine::unit::volt>()();
	Test<eagine::unit::farad>()();
	Test<eagine::unit::siemens>()();
	Test<eagine::unit::ohm>()();

	Test<eagine::unit::newton>()();
	Test<eagine::unit::joule>()();
	Test<eagine::unit::watt>()();

	Test<eagine::unit::hertz>()();
	Test<eagine::unit::becquerel>()();

	Test<eagine::unit::candela>()();

	Test<eagine::unit::mole>()();

	Test<eagine::unit::steradian>()();
}

template <typename Unit>
struct test_unit_si_is_unit
{
	void operator()(void) const
	{
		BOOST_ASSERT(eagine::unit::is_unit<Unit>());
		BOOST_ASSERT(eagine::unit::is_dimension<typename Unit::dimension>());
	}
};

BOOST_AUTO_TEST_CASE(unit_si_is_unit)
{
	do_test_unit_si<test_unit_si_is_unit>();
}

template <typename Unit>
struct test_unit_si_default_ctr
{
	void operator()(void) const
	{
		Unit u;
		(void)u;
	}
};

BOOST_AUTO_TEST_CASE(unit_si_default_ctr)
{
	do_test_unit_si<test_unit_si_default_ctr>();
}

template <typename Unit>
struct test_unit_si_copy_ctr
{
	void operator()(void) const
	{
		Unit u1;
		Unit u2(u1);
		(void)u2;
	}
};

BOOST_AUTO_TEST_CASE(unit_si_copy_ctr)
{
	do_test_unit_si<test_unit_si_copy_ctr>();
}

template <typename Unit>
struct test_unit_si_copy_assign
{
	void operator()(void) const
	{
		Unit u1;
		Unit u2;
		u2 = u1;
		(void)u2;
	}
};

BOOST_AUTO_TEST_CASE(unit_si_copy_assign)
{
	do_test_unit_si<test_unit_si_copy_assign>();
}

template <typename Unit1>
struct test_unit_si_assignable
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
		do_test_unit_si<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_si_assignable)
{
	do_test_unit_si<test_unit_si_assignable>();
}

template <typename Unit1>
struct test_unit_si_add
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
		do_test_unit_si<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_si_add)
{
	do_test_unit_si<test_unit_si_add>();
}

template <typename Unit1>
struct test_unit_si_subtract
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
		do_test_unit_si<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_si_subtract)
{
	do_test_unit_si<test_unit_si_subtract>();
}

template <typename Unit1>
struct test_unit_si_multiply
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
		do_test_unit_si<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_si_multiply)
{
	do_test_unit_si<test_unit_si_multiply>();
}

template <typename Unit1>
struct test_unit_si_divide
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
		do_test_unit_si<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_si_divide)
{
	do_test_unit_si<test_unit_si_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
