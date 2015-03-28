/**
 *  .file test/eagine/unit/scales.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_unit_scale
#include <boost/test/unit_test.hpp>

#include <eagine/unit/scales.hpp>
#include <eagine/math/close_to.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(unit_scale)

template <template <class> class Test>
void do_test_unit_scale_base(void)
{
	Test<eagine::unit::scales::one>()();

	Test<eagine::unit::scales::nano>()();
	Test<eagine::unit::scales::micro>()();
	Test<eagine::unit::scales::milli>()();
	Test<eagine::unit::scales::centi>()();
	Test<eagine::unit::scales::deci>()();
	Test<eagine::unit::scales::deca>()();
	Test<eagine::unit::scales::hecto>()();
	Test<eagine::unit::scales::kilo>()();
	Test<eagine::unit::scales::mega>()();
	Test<eagine::unit::scales::giga>()();

	Test<eagine::unit::scales::pi>()();
}

template <template <class> class Test>
struct do_test_unit_scale_compound
{
	template <typename Scale1>
	struct tester
	{
		template <typename Scale2>
		struct tester2
		{
			void operator()(void) const
			{
				Test<eagine::unit::scales::multiplied<
					Scale1,
					Scale2
				>>()();
				Test<eagine::unit::scales::divided<
					Scale1,
					Scale2
				>>()();
			}
		};

		void operator()(void) const
		{
			Test<eagine::unit::scales::inverted<Scale1>>()();
			do_test_unit_scale_base<tester2>();
		}
	};
};

template <template <class> class Test>
void do_test_unit_scale(void)
{
	do_test_unit_scale_base<Test>();

	do_test_unit_scale_base<
		do_test_unit_scale_compound<Test>::template tester
	>();
}

template <typename T>
struct test_unit_scale_apply
{
	template <typename Scale>
	struct tester
	{
		void operator()(void) const
		{
			T v = T(1);
			T u = T(v*Scale::value);
			(void)u;
		}
	};
};

BOOST_AUTO_TEST_CASE(unit_scale_apply)
{
	do_test_unit_scale<test_unit_scale_apply<int>::tester>();
	do_test_unit_scale<test_unit_scale_apply<float>::tester>();
	do_test_unit_scale<test_unit_scale_apply<double>::tester>();
}

template <typename T>
struct test_unit_scale_invert
{
	template <typename Scale>
	struct tester
	{
		void operator()(void) const
		{
			T v = T(1);
			T u = T(v/Scale::value);
			(void)u;
		}
	};
};

BOOST_AUTO_TEST_CASE(unit_scale_invert)
{
	do_test_unit_scale<test_unit_scale_invert<int>::tester>();
	do_test_unit_scale<test_unit_scale_invert<float>::tester>();
	do_test_unit_scale<test_unit_scale_invert<double>::tester>();
}

template <typename Scale, typename T>
void test_unit_scale_value(T m)
{
	using eagine::math::not_farther_from;

	T v = T(1);

	BOOST_ASSERT((
		((v * Scale::value) <<not_farther_from>> (v * m))
			.than.rel(1e-6)
	));
	BOOST_ASSERT((
		((v / Scale::value) <<not_farther_from>> (v / m))
			.than.rel(1e-6)
	));
}

BOOST_AUTO_TEST_CASE(unit_scale_value)
{
	test_unit_scale_value<eagine::unit::scales::one>(1.0);

	test_unit_scale_value<eagine::unit::scales::nano>(1e-9);
	test_unit_scale_value<eagine::unit::scales::micro>(1e-6);
	test_unit_scale_value<eagine::unit::scales::milli>(1e-3);
	test_unit_scale_value<eagine::unit::scales::centi>(1e-2);
	test_unit_scale_value<eagine::unit::scales::deci>(1e-1);
	test_unit_scale_value<eagine::unit::scales::deca>(1e+1);
	test_unit_scale_value<eagine::unit::scales::hecto>(1e+2);
	test_unit_scale_value<eagine::unit::scales::kilo>(1e+3);
	test_unit_scale_value<eagine::unit::scales::mega>(1e+6);
	test_unit_scale_value<eagine::unit::scales::giga>(1e+9);
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
