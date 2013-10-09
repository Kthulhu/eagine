/**
 *  @file eagine/base/sim_clock.hpp
 *  @brief Simulation clock/chronometer with adjustable pace.
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_BASE_SIM_CLOCK_1308281038_HPP
#define EAGINE_BASE_SIM_CLOCK_1308281038_HPP

#include <cassert>

namespace EAGine {
namespace base {

/// A class measuring a simulation time period
class sim_time_period
{
private:
	double _time;
public:
	sim_time_period(double time)
	 : _time(time)
	{ }

	/// The length of the periods in milliseconds
	double milliseconds(void) const
	{
		return _time*1000.0;
	}

	/// The current millisecond of the period <0-1000)
	int millisecond(void) const
	{
		return int(milliseconds()) % 1000;
	}

	/// The length of the periods in seconds
	double seconds(void) const
	{
		return _time;
	}

	/// The current second of the period <0-60)
	int second(void) const
	{
		return int(seconds()) % 60;
	}

	/// The length of the periods in minutes
	double minutes(void) const
	{
		return _time / 60.0;
	}

	/// The current minute of the period <0-60)
	int minute(void) const
	{
		return int(minutes()) % 60;
	}

	/// The length of the periods in hours
	double hours(void) const
	{
		return _time / 3600.0;
	}

	/// The current minute of the period <0-24)
	int hour(void) const
	{
		return int(hours()) % 24;
	}

	/// The length of the period in days
	double days(void) const
	{
		return _time / (24*3600.0);
	}

	/// The current day of the period
	int day(void) const
	{
		return int(days());
	}
};

sim_time_period operator + (sim_time_period a, sim_time_period b)
{
	return sim_time_period(a.seconds() + b.seconds());
}

sim_time_period operator - (sim_time_period a, sim_time_period b)
{
	return sim_time_period(a.seconds() - b.seconds());
}

/// Class measuring the simulation time
class sim_clock
{
private:
	double _start, _past, _real_time, _curr_time, _prev_time; //[s]
	double _pace;
public:
	sim_clock(double start = 0.0)
	 : _start(start)
	 , _past(start)
	 , _real_time(start)
	 , _curr_time(start)
	 , _prev_time(start)
	 , _pace(1.0)
	{ }

	/// Update the clock by providing real time
	void update(double real_time_seconds)
	{
		_prev_time = _curr_time;
		_real_time = real_time_seconds;
		_curr_time = _past + (_real_time - _start) * _pace;
	}

	/// Advances the clock
	void advance(double seconds)
	{
		_prev_time = _curr_time;
		_real_time += seconds;
		_curr_time = _past + (_real_time - _start) * _pace;
	}

	/// Set the pace by which the sim. time advances compared to real-time
	void pace(double pace_coef)
	{
		if(_pace != pace_coef)
		{
			_start = _real_time;
			_past = _curr_time;
			_pace = pace_coef;
		}
	}

	/// Equivalent to now().seconds()
	double time(void) const
	{
		return this->now().seconds();
	}

	/// Returns the real time elapsed since the start of the simulation
	sim_time_period real_time(void) const
	{
		return sim_time_period(_real_time);
	}

	/// Returns the simulation time elapsed since the start of the simulation
	sim_time_period now(void) const
	{
		return sim_time_period(_curr_time);
	}

	/// Returns the time elapsed between the last and the previous update
	sim_time_period interval(void) const
	{
		return sim_time_period(_curr_time-_prev_time);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

