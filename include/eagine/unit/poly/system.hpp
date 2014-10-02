/**
 *  @file eagine/unit/poly/system.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_POLY_SYSTEM_1308281038_HPP
#define EAGINE_UNIT_POLY_SYSTEM_1308281038_HPP

namespace EAGine {
namespace unit {

template <typename System>
struct system_id;

namespace poly {

class system
{
private:
	int _id;
public:
	template <typename System>
	system(System)
	 : _id(system_id<System>::value)
	{ }

	friend bool operator == (system a, system b)
	{
		return a._id == b._id;
	}

	friend bool operator != (system a, system b)
	{
		return a._id != b._id;
	}
};

} // namespace poly
} // namespace unit
} // namespace EAGine

#endif //include guard

