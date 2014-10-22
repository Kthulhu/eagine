/**
 *  @file eagine/ecs/storage_bits.hpp
 *  @brief Component storage capabilities
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_BITS_1408161720_HPP
#define EAGINE_ECS_STORAGE_BITS_1408161720_HPP

#include <eagine/base/bitfield.hpp>

namespace EAGine {
namespace ecs {

// storage_bits
enum class storage_bits : unsigned short
{
	can_hide = 0x1,
	can_copy = 0x2,
	can_swap = 0x4,
	can_store = 0x8,
	can_fetch = 0x10,
	can_modify = 0x20,
	can_remove = 0x40,
	can_reserve = 0x80,
	can_point_to = 0x100
};

// storage_traits
typedef base::bitfield<storage_bits> storage_traits;

// storage_bits | storage_bits
static constexpr inline
storage_traits operator | (storage_bits b1, storage_bits b2)
{
	return storage_traits(b1, b2);
}

} // namespace ecs
} // namespace EAGine

#endif //include guard

