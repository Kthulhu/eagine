/**
 *  @file eagine/ecs/manager.hpp
 *  @brief Entity/Component manager
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_MANAGER_1408161720_HPP
#define EAGINE_ECS_MANAGER_1408161720_HPP

#include <eagine/ecs/component.hpp>
#include <eagine/ecs/storage.hpp>
#include <eagine/base/memory.hpp>
#include <eagine/base/type_name.hpp>
#include <eagine/meta/type_traits.hpp>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Entity>
class manager;

template <typename Entity>
class manager
{
private:
	component_uid_map<
		base::shared_ptr<base_storage<Entity>>
	> _storages;

	template <typename C>
	struct _bare_c : meta::remove_const<
		typename meta::remove_reference<C>::type
	>{ };

	template <typename ... P>
	static void _eat(P ...) { }

	static unsigned _count_true(void)
	{
		return 0;
	}

	template <typename T, typename ... P>
	static unsigned _count_true(T v, P ... p)
	{
		return (bool(v)?1:0)+_count_true(p...);
	}

	template <typename C>
	static base::string (*_cmp_name_getter(void))(void)
	{
		return &base::type_name<C>;
	}

	void _do_reg_cmp_type(
		const base::shared_ptr<base_storage<Entity>>&,
		component_uid_t,
		base::string(*)(void)
	);

	void _do_unr_cmp_type(
		component_uid_t,
		base::string(*)(void)
	);

	bool _does_know_cmp_type(component_uid_t) const;

	bool _does_have(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	template <typename Component>
	bool _do_add(const Entity&, Component&& component);

	bool _do_rem(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);
public:
	manager(void) = default;

	template <typename Component>
	void register_component_type(
		const base::shared_ptr<
			component_storage<
				Entity,
				Component
			>
		>& storage
	)
	{
		_do_reg_cmp_type(
			storage,
			get_component_uid<Component>(),
			_cmp_name_getter<Component>()
		);
	}

	template <typename Component>
	void unregister_component_type(void)
	{
		_do_unr_cmp_type(
			get_component_uid<Component>(),
			_cmp_name_getter<Component>()
		);
	}

	template <typename Component>
	bool knows_component_type(void) const
	{
		return _does_know_cmp_type(get_component_uid<Component>());
	}

	template <typename C>
	bool has(const Entity& ent)
	{
		return _does_have(
			ent,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		);
	}

	template <typename ... C>
	bool has_all(const Entity& ent)
	{
		return _count_true(
			_does_have(
				ent,
				get_component_uid<C>(),
				_cmp_name_getter<C>()
			)...
		) == (sizeof...(C));
	}

	template <typename ... C>
	manager& add(const Entity& ent, C&& ... components)
	{
		_eat(_do_add(ent, std::move(components))...);
		return *this;
	}

	template <typename ... C>
	manager& remove(const Entity& ent)
	{
		_eat(_do_rem(
			ent,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		)...);
		return *this;
	}
};

} // namespace ecs
} // namespace EAGine

#include <eagine/ecs/manager.inl>

#endif //include guard

