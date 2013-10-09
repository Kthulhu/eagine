/**
 *  .file test/eagine/base/sim_clock.cpp
 *  .brief Test case for base::sim_clock class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGine_base_sim_clock
#include <boost/test/unit_test.hpp>

#include <eagine/base/sim_clock.hpp>
#include <cstdlib>
#include <cmath>

BOOST_AUTO_TEST_SUITE(base_sim_clock)

BOOST_AUTO_TEST_CASE(base_sim_clock_default_construction)
{
	EAGine::base::sim_clock c;
}

BOOST_AUTO_TEST_CASE(base_sim_clock_init_construction)
{
	EAGine::base::sim_clock c(1.5);
}

BOOST_AUTO_TEST_CASE(base_sim_clock_copy_construction)
{
	EAGine::base::sim_clock c1;
	EAGine::base::sim_clock c2(c1);
}

BOOST_AUTO_TEST_CASE(base_sim_clock_update_time)
{
	const double irm = 1.0/RAND_MAX;
	double t = 0.0;
	EAGine::base::sim_clock c;

	for(int k=0; k!=100000; ++k)
	{
		t += (10.0*irm*std::rand());
		c.update(t);
		BOOST_ASSERT(c.time() == t);
	}
}

BOOST_AUTO_TEST_CASE(base_sim_clock_advance_time)
{
	const double irm = 1.0/RAND_MAX;
	double t = 0.0;
	EAGine::base::sim_clock c;

	for(int k=0; k!=100000; ++k)
	{
		double i = 10.0*irm*std::rand();
		t += i;
		c.advance(i);
		BOOST_ASSERT(c.time() == t);
	}
}

BOOST_AUTO_TEST_CASE(base_sim_clock_pace_1)
{
	const double irm = 1.0/RAND_MAX;

	for(int j=0; j!=100; ++j)
	{
		double t = 0.0;
		double p = 0.1+4.9*irm*std::rand();

		EAGine::base::sim_clock c;
		c.pace(p);

		for(int k=0; k!=1000; ++k)
		{
			double i = 10.0*irm*std::rand();
			t += i;
			c.advance(i);
			BOOST_ASSERT(std::abs(c.now().seconds()-t*p)<0.000001);
			BOOST_ASSERT(std::abs(c.real_time().seconds()-t)<0.000001);
			BOOST_ASSERT(std::abs(c.interval().seconds()-i*p)<0.000001);
		}
	}
}

BOOST_AUTO_TEST_CASE(base_sim_clock_pace_2)
{
	const double irm = 1.0/RAND_MAX;

	EAGine::base::sim_clock c;

	for(int j=0; j!=100; ++j)
	{
		double t = 0.0, b = c.time();
		double p = 0.4+1.8*irm*std::rand();
		c.pace(p);

		for(int k=0; k!=1000; ++k)
		{
			double i = 10.0*irm*std::rand();
			t += i;
			c.advance(i);
		}

		BOOST_ASSERT(std::abs(c.time() - (b+t*p))<0.00001);
	}
}

BOOST_AUTO_TEST_CASE(base_sim_time_period_1)
{
	EAGine::base::sim_clock c;
	BOOST_ASSERT(c.now().second() == 0);
	BOOST_ASSERT(c.now().minute() == 0);
	BOOST_ASSERT(c.now().hour() == 0);
	BOOST_ASSERT(c.now().day() == 0);

	c.advance(1.0);
	BOOST_ASSERT(c.now().second() == 1);
	BOOST_ASSERT(c.now().minute() == 0);
	BOOST_ASSERT(c.now().hour() == 0);
	BOOST_ASSERT(c.now().day() == 0);

	c.advance(59.0);
	BOOST_ASSERT(c.now().second() == 0);
	BOOST_ASSERT(c.now().minute() == 1);
	BOOST_ASSERT(c.now().hour() == 0);
	BOOST_ASSERT(c.now().day() == 0);

	c.advance(59.0*60.0);
	BOOST_ASSERT(c.now().second() == 0);
	BOOST_ASSERT(c.now().minute() == 0);
	BOOST_ASSERT(c.now().hour() == 1);
	BOOST_ASSERT(c.now().day() == 0);

	c.advance(23.0*60.0*60.0);
	BOOST_ASSERT(c.now().second() == 0);
	BOOST_ASSERT(c.now().minute() == 0);
	BOOST_ASSERT(c.now().hour() == 0);
	BOOST_ASSERT(c.now().day() == 1);

}

BOOST_AUTO_TEST_CASE(base_sim_time_period_2)
{
	const double irm = 1.0/RAND_MAX;
	EAGine::base::sim_clock c;

	for(int j=0; j!=100; ++j)
	{
		c.pace(0.9+0.2*irm*std::rand());
		for(int k=0; k!=1000; ++k)
		{
			double i = 10.0*irm*std::rand();
			c.advance(i);

			BOOST_ASSERT(c.now().millisecond() >= 0);
			BOOST_ASSERT(c.now().millisecond() < 1000);
			BOOST_ASSERT(c.now().second() >= 0);
			BOOST_ASSERT(c.now().second() < 60);
			BOOST_ASSERT(c.now().minute() >= 0);
			BOOST_ASSERT(c.now().minute() < 60);
			BOOST_ASSERT(c.now().hour() >= 0);
			BOOST_ASSERT(c.now().hour() < 24);
			BOOST_ASSERT(c.now().day() >= 0);

			BOOST_ASSERT(c.real_time().millisecond() >= 0);
			BOOST_ASSERT(c.real_time().millisecond() < 1000);
			BOOST_ASSERT(c.real_time().second() >= 0);
			BOOST_ASSERT(c.real_time().second() < 60);
			BOOST_ASSERT(c.real_time().minute() >= 0);
			BOOST_ASSERT(c.real_time().minute() < 60);
			BOOST_ASSERT(c.real_time().hour() >= 0);
			BOOST_ASSERT(c.real_time().hour() < 24);
			BOOST_ASSERT(c.real_time().day() >= 0);
		}
	}
}

BOOST_AUTO_TEST_SUITE_END()
