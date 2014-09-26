/**
 *  @file eagine/unit/scales.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_SCALES_1308281038_HPP
#define EAGINE_UNIT_SCALES_1308281038_HPP

#include <cmath>

namespace EAGine {
namespace unit {
namespace scales {

struct one
{
	typedef one type;

	static constexpr double value = 1;
};

template <int Num, int Den>
struct rational
{
	typedef rational type;

	static constexpr double value = double(Num)/Den;
};

typedef rational<1, 1000000000> nano;
typedef rational<1, 1000000> micro;
typedef rational<1, 1000> milli;
typedef rational<1, 100> centi;
typedef rational<1, 10> deci;
typedef rational<10, 1> deca;
typedef rational<100, 1> hecto;
typedef rational<1000, 1> kilo;
typedef rational<1000000, 1> mega;
typedef rational<1000000000, 1> giga;

struct pi
{
	typedef pi type;

	static constexpr auto value = M_PI;
};

} // namespace scales
} // namespace unit
} // namespace EAGine

#endif //include guard

