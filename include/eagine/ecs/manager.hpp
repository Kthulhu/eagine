/**
 *  @file eagine/ecs/manager.hpp
 *  @brief Entity/Component manager
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_MANAGER_1408161720_HPP
#define EAGINE_ECS_MANAGER_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/string.hpp>
#include <eagine/base/type_name.hpp>
#include <eagine/ecs/component.hpp>
#include <eagine/ecs/component_storage.hpp>
#include <map>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Entity>
class manager
{
private:
	component_uid_map<
		base::shared_ptr<entity_component_map<Entity>>
	> eck_maps;

	component_uid_map<
		base::shared_ptr<base_component_storage>
	> storages;

	void _do_reg_cmp_type(
		component_uid cid,
		const base::shared_ptr<entity_component_map<Entity>>& eck_map,
		const base::shared_ptr<base_component_storage>& storage,
		base::string(*get_name)(void)
	);

	void _do_unr_cmp_type(
		component_uid cid,
		base::string(*get_name)(void)
	);

	bool _does_know_cmp_type(component_uid cid) const;

	component_key_t _get_cmp_key(const Entity& e, component_uid) const;

	template <typename Component>
	component_key_t _req_ck(const Entity& e) const
	{
		component_key_t ck =
			_get_cmp_key(e, get_component_uid<Component>());

 		assert(ck != nil_component_key);
		return ck;
	}
public:
	typedef Entity entity_type;

	template <typename Component>
	void register_component_type(
		const base::shared_ptr<entity_component_map<Entity>>& eck_map,
		const base::shared_ptr<component_storage<Component>>& storage
	)
	{
		_do_reg_cmp_type(
			get_component_uid<Component>(),
			eck_map,
			storage,
			&base::type_name<Component>
		);
	}

	template <typename Component>
	void unregister_component_type(void)
	{
		_do_unr_cmp_type(
			get_component_uid<Component>(),
			&base::type_name<Component>
		);
	}

	template <typename Component>
	void knows_component_type(void) const
	{
		return _does_know_cmp_type(get_component_uid<Component>());
	}

	template <typename ... P>
	static entity_type make_entity(P&& ... p)
	{
		return entity_type(std::forward<P>(p)...);
	}

	template <typename Component>
	bool has(const Entity& e) const
	{
		return _get_cmp_key(e, get_component_uid<Component>()) !=
			nil_component_key;
	}

	template <typename Component>
	const Component& read(const Entity& e) const
	{
		component_key_t ck = _req_ck<Component>(e);
	}
};

} // namespace ecs
} // namespace EAGine

#include <eagine/ecs/manager.inl>

#endif //include guard

