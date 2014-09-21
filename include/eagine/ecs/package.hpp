/**
 *  @file eagine/ecs/package.hpp
 *  @brief Interface for entity/component key map and storage package
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_PACKAGE_1408161720_HPP
#define EAGINE_ECS_PACKAGE_1408161720_HPP

namespace EAGine {
namespace ecs {

template <typename Entity>
class manager;

template <typename Entity>
struct component_package
{
	virtual ~component_package(void) { }

	virtual void register_with(manager<Entity>&) = 0;
	virtual void unregister_from(manager<Entity>&) = 0;
};

template <typename Entity, typename Component>
struct default_component_package
 : component_package<Entity>
{
	virtual void unregister_from(manager<Entity>& m)
	{
		m.template unregister_component_type<Component>();
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

