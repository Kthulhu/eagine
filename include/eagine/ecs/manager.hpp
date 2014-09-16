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
#include <eagine/base/array.hpp>
#include <eagine/base/type_name.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/instead_of.hpp>
#include <eagine/ecs/entity.hpp>
#include <eagine/ecs/component.hpp>
#include <eagine/ecs/component_storage.hpp>
#include <map>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Entity>
class manager;

template <typename Entity>
class modifications 
{
private:
	base::vector<base::function<void(manager<Entity>&)>> _ops;
public:
	template <typename Component>
	void add_later(const Entity& e, Component&& c);

	template <typename Component>
	void swap_later(const Entity& e1, const Entity& e2);

	template <typename Component>
	void remove_later(const Entity& e);

	void execute_later(base::function<void(manager<Entity>&)>&& op);

	void commit(manager<Entity>& m);
};

template <typename Entity>
class manager
{
private:
	component_uid_map<
		base::shared_ptr<entity_component_map<Entity>>
	> _eck_maps;

	component_uid_map<
		base::shared_ptr<base_component_storage>
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

	std::size_t _get_cmp_cnt(component_uid cid) const;

	component_key_t _get_cmp_key(const Entity& e, component_uid) const;

	template <typename Component>
	bool _do_add(const Entity& e, Component&& component);

	bool _do_swp(
		const Entity& e1,
		const Entity& e2,
		component_uid,
		base::string(*)(void)
	);

	template <typename Component>
	bool _do_swp(const Entity& e1, const Entity& e2);

	bool _do_rem(const Entity& e, component_uid, base::string(*)(void));

	template <typename Component>
	bool _do_rem(const Entity& e);

	template <typename Component, typename Access>
	typename Access::template result<Component>::type*
	_do_acc(const Entity& e, Access acc);

	template <typename Component, typename Access>
	typename Access::template result<Component>::type*
	_do_acc(
		const Entity& e,
		Access acc,
		base_component_storage* bs,
		component_key_t key
	);

	template <typename Func, typename ... C>
	void _do_call_cr(Func& func, const Entity&, C* ... cps)
	{
		func(*cps...);
	}

	template <typename C0, typename ... Cn, typename Func, typename ... C>
	void _do_call_cr(Func& func, const Entity& e, C* ... cps)
	{
		typedef typename _bare_c<C0>::type adjC0;
		auto* cp = _do_acc<adjC0>(e, typename base::access<C0>::type());
		if(cp) _do_call_cr<Cn...>(func, e, cps..., cp);
	}

	template <typename ... C, typename Func, typename CS, typename CK>
	void _do_call_m_e_cp(
		Func&,
		modifications<Entity>&,
		const Entity&,
		const CS&,
		const CK&
	);
public:
	typedef Entity entity_type;

	template <typename ... P>
	static entity_type make_entity(P&& ... p)
	{
		return entity_type(std::forward<P>(p)...);
	}

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

	template <typename ... C>
	manager& add(const Entity& e, C&& ... components)
	{
		_eat(_do_add(e, std::move(components))...);
		return *this;
	}

	template <typename ... C>
	manager& swap(const Entity& e1, const Entity& e2)
	{
		_eat(_do_swp<C>(e1, e2)...);
		return *this;
	}

	template <typename ... C>
	manager& remove(const Entity& e)
	{
		_eat(_do_rem<C>(e)...);
		return *this;
	}

	manager& remove(const Entity& e, component_uid cid)
	{
		_do_rem(e, cid, nullptr);
		return *this;
	}

	template <typename Component>
	bool has(const Entity& e) const
	{
		return _get_cmp_key(e, get_component_uid<Component>()) !=
			nil_component_key;
	}

	template <typename Component>
	const Component* ro(const Entity& e)
	{
		return _do_acc<Component>(e, base::access_read_only);
	}

	template <typename Component>
	Component* rw(const Entity& e)
	{
		return _do_acc<Component>(e, base::access_read_write);
	}

	template <typename ... C, typename Func>
	manager& for_one_cr(const Entity& e, Func func)
	{
		_do_call_cr<C...>(func, e);
		return *this;
	}

	template <typename ... C>
	manager& for_one(const Entity& e, base::function<void(C...)>& func)
	{
		_do_call_cr<C...>(func, e);
		return *this;
	}

	template <typename ... C, typename Func>
	manager& for_each_m_e_cp(Func func);

	template <typename ... C>
	manager& for_each(
		const base::function<void(
			modifications<Entity>&,
			const Entity&,
			C*...
		)>& func
	);

	template <typename ... C>
	manager& for_each(
		const base::function<void(
			modifications<Entity>&,
			const Entity&,
			C...
		)>& func
	);

	template <typename ... C>
	manager& for_each(const base::function<void(const Entity&, C...)>& func);

	template <typename ... C>
	manager& for_each(const base::function<void(C...)>& func);
};

} // namespace ecs
} // namespace EAGine

#include <eagine/ecs/manager.inl>

#endif //include guard

