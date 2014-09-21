/**
 *  @file eagine/ecs/package_normal.hpp
 *  @brief Implementation of normal in-memory component package
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_PACKAGE_NORMAL_1408161720_HPP
#define EAGINE_ECS_PACKAGE_NORMAL_1408161720_HPP

#include <eagine/ecs/component.hpp>
#include <eagine/ecs/package.hpp>
#include <eagine/ecs/eck_map_normal.hpp>
#include <eagine/ecs/storage_normal.hpp>
#include <eagine/base/memory.hpp>

#include <cstddef>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Entity, typename Component>
class normal_component_package
 : public default_component_package<Entity, Component>
{
public:
	void register_with(manager<Entity>& m)
	{
		using base::make_shared;
		m.template register_component_type<Component>(
			make_shared<normal_entity_component_map<Entity>>(),
			make_shared<normal_component_storage<Component>>()
		);
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

