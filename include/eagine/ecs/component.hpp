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
#include <map>

namespace EAGine {
namespace ecs {

// Component access key type
typedef std::size_t component_key_t;

// nil component key value
constexpr component_key_t nil_component_key = ~(component_key_t(0));

template <typename Derived>
class component
{
// TODO
};

// component unique identifier
typedef ::std::type_index component_uid;

template <typename Component>
inline component_uid get_component_uid(void)
{
	return component_uid(typeid(Component));
}

template <typename T>
using component_uid_map = ::std::map<component_uid, T>;

// interface for maps of entities to component access keys
template <typename Entity>
struct entity_component_map
{
	typedef component_key_t key_t;

	constexpr static key_t nil_key = nil_component_key;

	virtual ~entity_component_map(void) noexcept { }

	virtual bool read_only(void) const = 0;

	virtual key_t get(const Entity& entity, key_t nil = nil_key) = 0;

	virtual std::size_t size(void) = 0;

	virtual void reserve(std::size_t count) = 0;

	virtual key_t store(const Entity& entity, key_t key) = 0;

	virtual key_t remove(const Entity& entity) = 0;
};

struct access_read_only
{
	template <typename Component>
	struct result
	{
		typedef const Component type;
	};
};

struct access_read_write
{
	template <typename Component>
	struct result
	{
		typedef Component type;
	};
};

template <typename C>
struct access
{
	typedef access_read_only type;
};

template <typename C>
struct access<const C&>
 : access<C>
{ };

template <typename C>
struct access<C&>
{
	typedef access_read_write type;
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

