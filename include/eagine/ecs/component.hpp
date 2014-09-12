/**
 *  @file eagine/ecs/component.hpp
 *  @brief E/CS component-related types and constants.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_COMPONENT_1408161720_HPP
#define EAGINE_ECS_COMPONENT_1408161720_HPP

#include <cstddef>
#include <typeinfo>
#include <typeindex>

namespace EAGine {
namespace ecs {

typedef std::size_t component_key_t;

constexpr component_key_t nil_component_key = ~(component_key_t(0));

typedef ::std::type_index component_uid;

template <typename Component>
inline component_uid get_component_uid(void)
{
	return component_uid(typeid(Component));
}

template <typename Entity>
struct entity_component_map
{
	typedef component_key_t key_t;

	constexpr static key_t nil_key = nil_component_key;

	virtual ~entity_component_map(void) noexcept { }

	virtual bool read_only(void) const = 0;

	virtual key_t get(const Entity& entity, key_t nil = nil_key) = 0;

	virtual void reserve(std::size_t count) = 0;

	virtual key_t store(const Entity& entity, key_t key) = 0;

	virtual key_t remove(const Entity& entity) = 0;
};

struct base_component_storage
{
	typedef component_key_t key_t;

	virtual ~base_component_storage(void) noexcept { }

	virtual bool read_only(void) const = 0;

	virtual bool remove(key_t key) = 0;

	virtual key_t copy(key_t key) = 0;

	virtual void add_ref(key_t key) = 0;
	virtual bool release(key_t key) = 0;
};

template <typename Component>
struct component_storage : base_component_storage
{
	virtual Component& access_rw(key_t key) = 0;
	virtual const Component& access_ro(key_t key) const = 0;

	virtual key_t store(Component&& component) = 0;
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

