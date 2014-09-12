/**
 *  @file eagine/ecs/eck_map_normal.hpp
 *  @brief Basic in-memory R/W entity/component key map
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_ECK_MAP_NORMAL_1408161720_HPP
#define EAGINE_ECS_ECK_MAP_NORMAL_1408161720_HPP

#include <eagine/base/flat_map.hpp>
#include <eagine/ecs/component.hpp>

namespace EAGine {
namespace ecs {

template <typename Entity>
class normal_entity_component_map
 : public entity_component_map<Entity>
{
private:
	base::flat_map<Entity, component_key_t> _map;
public:
	typedef component_key_t key_t;

	bool read_only(void) const
	{
		return false;
	}

	key_t get(const Entity& entity, key_t nil)
	{
		return _map.get(entity, nil);
	}

	std::size_t size(void)
	{
		return _map.size();
	}

	void reserve(std::size_t count)
	{
		_map.reserve(count);
	}

	key_t store(const Entity& entity, key_t key)
	{
		return _map.store(entity, key, nil_component_key);
	}

	key_t remove(const Entity& entity)
	{
		return _map.remove(entity, nil_component_key);
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

