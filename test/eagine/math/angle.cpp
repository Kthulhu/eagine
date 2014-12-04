/**
 *  .file test/eagine/math/angle.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_angle
#include <boost/test/unit_test.hpp>

#include <eagine/math/angle.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_angle)

BOOST_AUTO_TEST_CASE(math_angle_default_ctr)
{
	eagine::math::angle<float> af;
	eagine::math::angle<double> ad;

	(void)af;
	(void)ad;
}

BOOST_AUTO_TEST_CASE(math_angle_init_ctr)
{
	eagine::math::angle<float> af(123.456f);
	eagine::math::angle<double> ad(235.567);

	(void)af;
	(void)ad;
}

BOOST_AUTO_TEST_CASE(math_angle_copy_ctr)
{
	eagine::math::angle<float> af1(123.456f);
	eagine::math::angle<double> ad1(234.567);

	eagine::math::angle<float> af2(af1);
	eagine::math::angle<double> ad2(ad1);

	(void)af2;
	(void)ad2;
}

BOOST_AUTO_TEST_CASE(math_angle_ctr_units)
{
	eagine::math::angle<float> af1 = eagine::unit::quantity<eagine::unit::radian, float>(1);
	eagine::math::angle<double> ad1 = eagine::unit::quantity<eagine::unit::radian, double>(2);

	eagine::math::angle<float> af2 = eagine::unit::quantity<eagine::unit::degree, float>(3);
	eagine::math::angle<double> ad2 = eagine::unit::quantity<eagine::unit::degree, double>(4);

	eagine::math::angle<float> af3 = eagine::unit::quantity<eagine::unit::gradian, float>(5);
	eagine::math::angle<double> ad3 = eagine::unit::quantity<eagine::unit::gradian, double>(6);

	eagine::math::angle<float> af4 = eagine::unit::quantity<eagine::unit::quarter, float>(7);
	eagine::math::angle<double> ad4 = eagine::unit::quantity<eagine::unit::quarter, double>(8);

	eagine::math::angle<float> af5 = eagine::unit::quantity<eagine::unit::turn, float>(9);
	eagine::math::angle<double> ad5 = eagine::unit::quantity<eagine::unit::turn, double>(0);

}

BOOST_AUTO_TEST_CASE(math_angle_value1)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		double d = (0.5 - std::rand()/double(RAND_MAX))*std::rand();

		eagine::math::angle<float> af(f);
		eagine::math::angle<double> ad(d);

		BOOST_ASSERT(value(af) == f);
		BOOST_ASSERT(value(ad) == d);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_compare_eq)
{
	for(unsigned i=0; i<10000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		if(std::rand() % 5 == 1) f2 = f1;

		double d1 = (0.5 - std::rand()/double(RAND_MAX))*std::rand();
		double d2 = (0.5 - std::rand()/double(RAND_MAX))*std::rand();
		if(std::rand() % 5 == 1) d2 = d1;

		eagine::math::angle<float> af1(f1);
		eagine::math::angle<float> af2(f2);
		eagine::math::angle<double> ad1(d1);
		eagine::math::angle<double> ad2(d2);

		// ==
		BOOST_ASSERT((af1 == af2) == (af2 == af1));
		BOOST_ASSERT((ad1 == ad2) == (ad2 == ad1));

		BOOST_ASSERT((af1 == af2) == (f1 == f2));
		BOOST_ASSERT((ad1 == ad2) == (d1 == d2));

		// !=
		BOOST_ASSERT((af1 != af2) == (af2 != af1));
		BOOST_ASSERT((ad1 != ad2) == (ad2 != ad1));

		BOOST_ASSERT((af1 != af2) == (f1 != f2));
		BOOST_ASSERT((ad1 != ad2) == (d1 != d2));

		// <
		BOOST_ASSERT((af1 <  af2) == (af2 >  af1));
		BOOST_ASSERT((ad1 <  ad2) == (ad2 >  ad1));

		BOOST_ASSERT((af1 <  af2) == (f1 <  f2));
		BOOST_ASSERT((ad1 <  ad2) == (d1 <  d2));

		// >
		BOOST_ASSERT((af1 >  af2) == (af2 <  af1));
		BOOST_ASSERT((ad1 >  ad2) == (ad2 <  ad1));

		BOOST_ASSERT((af1 >  af2) == (f1 >  f2));
		BOOST_ASSERT((ad1 >  ad2) == (d1 >  d2));

		// <=
		BOOST_ASSERT((af1 <= af2) == (af2 >= af1));
		BOOST_ASSERT((ad1 <= ad2) == (ad2 >= ad1));

		BOOST_ASSERT((af1 <= af2) == (f1 <= f2));
		BOOST_ASSERT((ad1 <= ad2) == (d1 <= d2));

		// >=
		BOOST_ASSERT((af1 >= af2) == (af2 <= af1));
		BOOST_ASSERT((ad1 >= ad2) == (ad2 <= ad1));

		BOOST_ASSERT((af1 >= af2) == (f1 >= f2));
		BOOST_ASSERT((ad1 >= ad2) == (d1 >= d2));
	}
}

BOOST_AUTO_TEST_CASE(math_angle_plus)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();

		eagine::math::angle<float> afa(f1);
		eagine::math::angle<float> afb(f2);
		eagine::math::angle<float> afc(f1+f2);
		
		BOOST_ASSERT(afa+afb == afc);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_minus)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*std::rand();

		eagine::math::angle<float> afa(f1);
		eagine::math::angle<float> afb(f2);
		eagine::math::angle<float> afc(f1-f2);
		eagine::math::angle<float> afd(f2-f1);
		
		BOOST_ASSERT(afa-afb == afc);
		BOOST_ASSERT(afb-afa == afd);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_multiply)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*1000;
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*1000;

		eagine::math::angle<float> afa(f1);
		eagine::math::angle<float> afb(f2);
		eagine::math::angle<float> afc(f1*f2);
		
		BOOST_ASSERT(f2*afa == afc);
		BOOST_ASSERT(f1*afb == afc);
		BOOST_ASSERT(afa*f2 == afc);
		BOOST_ASSERT(afb*f1 == afc);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_divide)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*1000;
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*1000;

		eagine::math::angle<float> afa(f1);
		eagine::math::angle<float> afb(f2);
		eagine::math::angle<float> afc(f1/f2);
		eagine::math::angle<float> afd(f2/f1);
		
		BOOST_ASSERT(afa/f2 == afc);
		BOOST_ASSERT(afb/f1 == afd);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_ratio)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f1 = (0.5f - std::rand()/float(RAND_MAX))*1000;
		float f2 = (0.5f - std::rand()/float(RAND_MAX))*1000;

		eagine::math::angle<float> afa(f1);
		eagine::math::angle<float> afb(f2);

		BOOST_ASSERT(value(afa/afb) == f1/f2);
		BOOST_ASSERT(value(afb/afa) == f2/f1);
	}
}

BOOST_AUTO_TEST_CASE(math_angle_trigonometric1)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f = (0.5f - std::rand()/float(RAND_MAX))*std::rand();
		double d = (0.5 - std::rand()/double(RAND_MAX))*std::rand();

		using eagine::math::sin;
		BOOST_ASSERT((test_math_close(sin(eagine::math::angle<float>(f)), std::sin(f))));
		BOOST_ASSERT((test_math_close(sin(eagine::math::angle<double>(d)), std::sin(d))));

		using eagine::math::cos;
		BOOST_ASSERT((test_math_close(cos(eagine::math::angle<float>(f)), std::cos(f))));
		BOOST_ASSERT((test_math_close(cos(eagine::math::angle<double>(d)), std::cos(d))));
	}

	for(unsigned i=0; i<1000; ++i)
	{
		float f = 1.99f*(0.5f - std::rand()/float(RAND_MAX));
		double d = 1.99*(0.5 - std::rand()/double(RAND_MAX));

		using eagine::math::tan;
		BOOST_ASSERT((test_math_close(tan(eagine::math::angle<float>(f)), std::tan(f))));
		BOOST_ASSERT((test_math_close(tan(eagine::math::angle<double>(d)), std::tan(d))));
	}
}

BOOST_AUTO_TEST_CASE(math_angle_trigonometric2)
{
	for(unsigned i=0; i<1000; ++i)
	{
		float f = 1.99f*(0.5f - std::rand()/float(RAND_MAX));
		double d = 1.99*(0.5 - std::rand()/double(RAND_MAX));

		using eagine::math::sin;
		using eagine::math::asin;
		BOOST_ASSERT((test_math_close(sin(asin(f)), f)));
		BOOST_ASSERT((test_math_close(sin(asin(d)), d)));

		using eagine::math::cos;
		using eagine::math::acos;
		BOOST_ASSERT((test_math_close(cos(acos(f)), f)));
		BOOST_ASSERT((test_math_close(cos(acos(d)), d)));

		using eagine::math::tan;
		using eagine::math::atan;
		BOOST_ASSERT((test_math_close(tan(atan(f)), f)));
		BOOST_ASSERT((test_math_close(tan(atan(d)), d)));
	}
}

// TODO conversions

BOOST_AUTO_TEST_SUITE_END()
