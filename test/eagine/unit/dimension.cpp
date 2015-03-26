/**
 *  .file test/eagine/unit/dimension.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_dimension
#include <boost/test/unit_test.hpp>

#include <eagine/unit/dimension.hpp>

BOOST_AUTO_TEST_SUITE(unit_dimension)

template <template <class> class Test>
void do_test_unit_dimension(void)
{
	Test<eagine::unit::angle>()();
	Test<eagine::unit::solid_angle>()();
	Test<eagine::unit::length>()();
	Test<eagine::unit::mass>()();
	Test<eagine::unit::time>()();

	Test<eagine::unit::temperature>()();
	Test<eagine::unit::electric_current>()();
	Test<eagine::unit::number_of_cycles>()();
	Test<eagine::unit::number_of_decays>()();
	Test<eagine::unit::luminous_intensity>()();
	Test<eagine::unit::amount_of_substance>()();
}

template <typename Dimension>
struct test_unit_dimension_is_dimension
{
	void operator()(void) const
	{
		BOOST_ASSERT(eagine::unit::is_dimension<Dimension>());
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_is_dimension)
{
	do_test_unit_dimension<test_unit_dimension_is_dimension>();
}

template <typename Dimension>
struct test_unit_dimension_default_ctr
{
	void operator()(void) const
	{
		Dimension d;
		(void)d;
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_default_ctr)
{
	do_test_unit_dimension<test_unit_dimension_default_ctr>();
}

template <typename Dimension>
struct test_unit_dimension_copy_ctr
{
	void operator()(void) const
	{
		Dimension d1;
		Dimension d2(d1);
		(void)d2;
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_copy_ctr)
{
	do_test_unit_dimension<test_unit_dimension_copy_ctr>();
}

template <typename Dimension>
struct test_unit_dimension_copy_assign
{
	void operator()(void) const
	{
		Dimension d1;
		Dimension d2;
		d2 = d1;
		(void)d2;
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_copy_assign)
{
	do_test_unit_dimension<test_unit_dimension_copy_assign>();
}

template <typename Dimension1>
struct test_unit_dimension_multiply
{
	template <typename Dimension2>
	struct tester
	{
		void operator()(void) const
		{
			using eagine::unit::operator*;

			Dimension1 d1;
			Dimension2 d2;

			typedef decltype(d1*d2) Dimension3;

			BOOST_ASSERT(eagine::unit::is_dimension<Dimension3>());
		}
	};

	void operator()(void) const
	{
		do_test_unit_dimension<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_multiply)
{
	do_test_unit_dimension<test_unit_dimension_multiply>();
}

template <typename Dimension1>
struct test_unit_dimension_divide
{
	template <typename Dimension2>
	struct tester
	{
		void operator()(void) const
		{
			using eagine::unit::operator/;

			Dimension1 d1;
			Dimension2 d2;

			typedef decltype(d1/d2) Dimension3;

			BOOST_ASSERT(eagine::unit::is_dimension<Dimension3>());
		}
	};

	void operator()(void) const
	{
		do_test_unit_dimension<tester>();
	}
};

BOOST_AUTO_TEST_CASE(unit_dimension_divide)
{
	do_test_unit_dimension<test_unit_dimension_divide>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
