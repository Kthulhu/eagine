/**
 *  .file test/eagine/unit/dim_derived.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_dim_derived
#include <boost/test/unit_test.hpp>

#include <eagine/unit/derived.hpp>

BOOST_AUTO_TEST_SUITE(unit_dim_derived)

template <template <class> class Test>
void do_test_unit_base_dimension(void)
{
	Test<eagine::unit::base::angle>()();
	Test<eagine::unit::base::mass>()();
	Test<eagine::unit::base::length>()();
	Test<eagine::unit::base::time>()();
	Test<eagine::unit::base::temperature>()();
	Test<eagine::unit::base::electric_current>()();
	Test<eagine::unit::base::number_of_cycles>()();
	Test<eagine::unit::base::number_of_decays>()();
	Test<eagine::unit::base::luminous_intensity>()();
	Test<eagine::unit::base::amount_of_substance>()();
	Test<eagine::unit::base::solid_angle>()();
}

template <template <class> class Test>
void do_test_unit_dim_derived(void)
{
	Test<eagine::unit::acceleration>()();
	Test<eagine::unit::electrical_capacitance>()();
	Test<eagine::unit::electric_charge>()();
	Test<eagine::unit::force>()();
	Test<eagine::unit::magnetic_flux_density>()();
	Test<eagine::unit::momentum>()();
	Test<eagine::unit::radioactivity>()();
	Test<eagine::unit::angular_velocity>()();
	Test<eagine::unit::electrical_conductance>()();
	Test<eagine::unit::electric_tension>()();
	Test<eagine::unit::frequency>()();
	Test<eagine::unit::magnetic_flux>()();
	Test<eagine::unit::power>()();
	Test<eagine::unit::velocity>()();
	Test<eagine::unit::area>()();
	Test<eagine::unit::electrical_resistance>()();
	Test<eagine::unit::energy>()();
	Test<eagine::unit::inductance>()();
	Test<eagine::unit::mass_density>()();
	Test<eagine::unit::pressure>()();
	Test<eagine::unit::volume>()();
}

template <typename Dimension>
struct test_unit_dim_derived_is_dimension
{
	void operator()(void) const
	{
		BOOST_ASSERT(eagine::unit::is_dimension<Dimension>());
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_is_dimension)
{
	do_test_unit_dim_derived<test_unit_dim_derived_is_dimension>();
}

template <typename Dimension>
struct test_unit_dim_derived_default_ctr
{
	void operator()(void) const
	{
		Dimension d;
		(void)d;
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_default_ctr)
{
	do_test_unit_dim_derived<test_unit_dim_derived_default_ctr>();
}

template <typename Dimension>
struct test_unit_dim_derived_copy_ctr
{
	void operator()(void) const
	{
		Dimension d1;
		Dimension d2(d1);
		(void)d2;
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_copy_ctr)
{
	do_test_unit_dim_derived<test_unit_dim_derived_copy_ctr>();
}

template <typename Dimension>
struct test_unit_dim_derived_copy_assign
{
	void operator()(void) const
	{
		Dimension d1;
		Dimension d2;
		d2 = d1;
		(void)d2;
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_copy_assign)
{
	do_test_unit_dim_derived<test_unit_dim_derived_copy_assign>();
}

template <typename Dimension1>
struct test_unit_dim_derived_multiply
{
	template <typename Dimension2>
	struct tester
	{
		template <typename BaseDim>
		struct tester2
		{
			void operator()(void) const
			{
				using eagine::unit::operator*;

				Dimension1 d1;
				Dimension2 d2;

				typedef decltype(d1*d2) Dimension3;

				BOOST_ASSERT((
					eagine::unit::base_dimension_power<
						Dimension1,
						BaseDim
					>() +
					eagine::unit::base_dimension_power<
						Dimension2,
						BaseDim
					>()==
					eagine::unit::base_dimension_power<
						Dimension3,
						BaseDim
					>()
				));
			}
		};

		void operator()(void) const
		{
			using eagine::unit::operator*;

			Dimension1 d1;
			Dimension2 d2;

			typedef decltype(d1*d2) Dimension3;

			BOOST_ASSERT(eagine::unit::is_dimension<Dimension3>());

			do_test_unit_base_dimension<tester2>();
		}
	};

	void operator()(void) const
	{
		do_test_unit_dim_derived<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_multiply)
{
	do_test_unit_dim_derived<test_unit_dim_derived_multiply>();
}

template <typename Dimension1>
struct test_unit_dim_derived_divide
{
	template <typename Dimension2>
	struct tester
	{
		template <typename BaseDim>
		struct tester2
		{
			void operator()(void) const
			{
				using eagine::unit::operator/;

				Dimension1 d1;
				Dimension2 d2;

				typedef decltype(d1/d2) Dimension3;

				BOOST_ASSERT((
					eagine::unit::base_dimension_power<
						Dimension1,
						BaseDim
					>() -
					eagine::unit::base_dimension_power<
						Dimension2,
						BaseDim
					>()==
					eagine::unit::base_dimension_power<
						Dimension3,
						BaseDim
					>()
				));
			}
		};

		void operator()(void) const
		{
			using eagine::unit::operator/;

			Dimension1 d1;
			Dimension2 d2;

			typedef decltype(d1/d2) Dimension3;

			BOOST_ASSERT(eagine::unit::is_dimension<Dimension3>());

			do_test_unit_base_dimension<tester2>();
		}
	};

	void operator()(void) const
	{
		do_test_unit_dim_derived<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_dim_derived_divide)
{
	do_test_unit_dim_derived<test_unit_dim_derived_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
