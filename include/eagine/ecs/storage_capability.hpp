/**
 *  @file eagine/ecs/storage_capability.hpp
 *  @brief Component storage capabilities
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
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

// storage_capabilities
struct storage_capabilities
 : base::bitfield<storage_capability> 
{
	typedef base::bitfield<storage_capability> _base;
	using _base::bitfield;

	storage_capabilities(void) = default;

	storage_capabilities(_base base)
	 : _base(base)
	{ }

	bool can_find(void) const
	{
		return is_set(storage_capability::find);
	}

	bool can_hide(void) const
	{
		return is_set(storage_capability::hide);
	}

	bool can_copy(void) const
	{
		return is_set(storage_capability::copy);
	}

	bool can_swap(void) const
	{
		return is_set(storage_capability::swap);
	}

	bool can_store(void) const
	{
		return is_set(storage_capability::store);
	}

	bool can_fetch(void) const
	{
		return is_set(storage_capability::fetch);
	}

	bool can_modify(void) const
	{
		return is_set(storage_capability::modify);
	}

	bool can_remove(void) const
	{
		return is_set(storage_capability::remove);
	}

	bool can_reserve(void) const
	{
		return is_set(storage_capability::reserve);
	}

	bool can_point_to(void) const
	{
		return is_set(storage_capability::point_to);
	}
};

// storage_capability | storage_capability
static constexpr inline
storage_capabilities operator | (storage_capability b1, storage_capability b2)
{
	return storage_capabilities(b1, b2);
}

} // namespace ecs
} // namespace eagine

#endif //include guard

