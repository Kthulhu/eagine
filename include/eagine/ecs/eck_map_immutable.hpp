/**
 *  @file eagine/ecs/eck_map_immutable .hpp
 *  @brief Immutable in-memory entity/component key map
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_ECK_MAP_IMMUTABLE_1408161720_HPP
#define EAGINE_ECS_ECK_MAP_IMMUTABLE_1408161720_HPP

#include <eagine/base/flat_dict.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/ecs/component.hpp>

namespace EAGine {
namespace ecs {

template <typename Entity>
class immutable_entity_component_map
 : public entity_component_map<Entity>
{
private:
	base::const_flat_range_dict<
		Entity,
		component_key_t,
		const Entity*,
		const component_key_t*
	> _map;
public:
	immutable_entity_component_map(
		const base::typed_memory_range<const Entity>& ents,
		const base::typed_memory_range<const component_key_t>& keys
	): _map(ents.begin(), ents.end(), keys.begin(), keys.end())
	{ }

	typedef component_key_t key_t;

	bool read_only(void) const
	{
		return true;
	}

	std::size_t size(void)
	{
		return _map.size();
	}

	const Entity& entity(std::size_t pos)
	{
		return _map.key_at(pos);
	}

	key_t key(std::size_t pos)
	{
		return _map.val_at(pos);
	}

	key_t find(const Entity& ent)
	{
		return _map.get(ent, nil_component_key);
	}

	void reserve(std::size_t)
	{
		assert(!"reserve is not supported by immutable component map!");
	}

	key_t store(const Entity&, key_t)
	{
		assert(!"store is not supported by immutable component map!");
		return nil_component_key;
	}

	key_t remove(const Entity&)
	{
		assert(!"store is not supported by immutable component map!");
		return nil_component_key;
	}

	void swap(const Entity&, const Entity&)
	{
		assert(!"swap is not supported by immutable component map!");
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

