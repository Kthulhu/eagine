/**
 *  @file eagine/ecs/storage_capability.hpp
 *  @brief Component storage capabilities
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_CAPABILITY_1408161720_HPP
#define EAGINE_ECS_STORAGE_CAPABILITY_1408161720_HPP

#include <eagine/base/bitfield.hpp>

namespace eagine {
namespace ecs {

// storage_capability
enum class storage_capability : unsigned short
{
	find = 0x1,
	hide = 0x2,
	copy = 0x4,
	swap = 0x8,
	store = 0x10,
	fetch = 0x20,
	modify = 0x40,
	remove = 0x80,
	reserve = 0x100,
	point_to = 0x200
};

// storage_cap
typedef storage_capability storage_cap;

// storage_traits
typedef base::bitfield<storage_capability> storage_capabilities;

// storage_capability | storage_capability
static constexpr inline
storage_capabilities operator | (storage_capability b1, storage_capability b2)
{
	return storage_capabilities(b1, b2);
}

} // namespace ecs
} // namespace eagine

#endif //include guard

