/**
 *  @file eagine/ecs/manager.hpp
 *  @brief Entity/Component manager
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
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
#include <eagine/base/parallel.hpp>
#include <eagine/meta/type_traits.hpp>
#include <utility>
#include <cassert>

namespace eagine {
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

	template <typename C>
	component_storage<Entity, C>& _find_storage(void);

	void _do_reg_cmp_type(
		const base::shared_ptr<base_storage<Entity>>&,
		component_uid_t,
		base::string(*)(void)
	);

	void _do_unr_cmp_type(component_uid_t, base::string(*)(void));

	bool _does_know_cmp_type(component_uid_t) const;

	template <typename Result, typename Func>
	Result _apply_on_base_stg(
		Result,
		const Func&,
		component_uid_t,
		base::string(*)(void)
	) const;

	template <typename C, typename Result, typename Func>
	Result _apply_on_cmp_stg(Result, const Func&) const;

	storage_capabilities _get_cmp_type_caps(
		component_uid_t,
		base::string(*)(void)
	) const;

	bool _does_have(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	bool _is_hidn(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	bool _do_show(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	bool _do_hide(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	template <typename Component>
	bool _do_add(const Entity&, Component&& component);

	bool _do_cpy(
		const Entity& f,
		const Entity& t,
		component_uid_t,
		base::string(*)(void)
	);

	bool _do_swp(
		const Entity& f,
		const Entity& t,
		component_uid_t,
		base::string(*)(void)
	);

	bool _do_rem(
		const Entity&,
		component_uid_t,
		base::string(*)(void)
	);

	template <typename C, typename Pred>
	std::size_t _call_rem_if(const Pred&);

	template <typename C, typename Func>
	bool _call_for_single(const Func&, const Entity&);

	template <typename C, typename Func>
	void _call_for_each(const Func&);

	template <typename ... C, typename Func>
	void _call_for_each_m(const Func&);

	template <typename C, typename Func>
	void _call_pl_for_each(
		const Func&,
		base::parallelizer&,
		base::execution_params&
	);

	template <typename ... C, typename Func>
	void _call_pl_for_each_m(
		const Func&,
		base::parallelizer&,
		base::execution_params&
	);

	template <typename T, typename C>
	T _do_get(T C::*, const Entity&, T);
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

	template <
		template <class, class> class Storage,
		typename Component,
		typename ... P
	>
	void register_component_storage(P&& ... p)
	{
		register_component_type<Component>(
			base::make_shared<Storage<Entity, Component>>(
				std::forward<P>(p)...
			)
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

	template <typename Component>
	storage_capabilities component_storage_caps(void) const
	{
		return _get_cmp_type_caps(
			get_component_uid<Component>(),
			_cmp_name_getter<Component>()
		);
	}

	template <typename Component>
	bool component_storage_can(storage_capability cap) const
	{
		return _get_cmp_type_caps(
			get_component_uid<Component>(),
			_cmp_name_getter<Component>()
		).is_set(cap);
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

	template <typename C>
	bool hidden(const Entity& ent)
	{
		return _is_hidn(
			ent,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		);
	}

	template <typename ... C>
	manager& show(const Entity& ent)
	{
		_eat(_do_show(
			ent,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		)...);
		return *this;
	}

	template <typename ... C>
	manager& hide(const Entity& ent)
	{
		_eat(_do_hide(
			ent,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		)...);
		return *this;
	}

	template <typename ... C>
	manager& add(const Entity& ent, C&& ... components)
	{
		_eat(_do_add(ent, std::move(components))...);
		return *this;
	}

	template <typename ... C>
	manager& copy(const Entity& from, const Entity& to)
	{
		_eat(_do_cpy(
			from,
			to,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		)...);
		return *this;
	}

	template <typename ... C>
	manager& swap(const Entity& e1, const Entity& e2)
	{
		_eat(_do_swp(
			e1,
			e2,
			get_component_uid<C>(),
			_cmp_name_getter<C>()
		)...);
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

	template <typename C>
	manager& remove_if(
		const base::functor_ref<bool(const Entity&, const C&)>& pred
	)
	{
		_call_rem_if<C>(pred);
		return *this;
	}

	template <typename C>
	manager& for_single(
		const base::functor_ref<void(const Entity&, const C&)>& func,
		const Entity& ent
	)
	{
		_call_for_single<C>(func, ent);
		return *this;
	}

	template <typename C>
	manager& for_single(
		const base::functor_ref<void(const Entity&, C&)>& func,
		const Entity& ent
	)
	{
		_call_for_single<C>(func, ent);
		return *this;
	}

	template <typename C>
	manager& for_each(
		const base::functor_ref<void(const Entity&, const C&)>& func
	)
	{
		_call_for_each<C>(func);
		return *this;
	}

	template <typename C>
	manager& for_each(
		const base::functor_ref<void(const Entity&, C&)>& func
	)
	{
		_call_for_each<C>(func);
		return *this;
	}

	template <typename ... C>
	typename meta::enable_if<
		(sizeof...(C) > 1),
		manager&
	>::type for_each(
		const base::functor_ref<void(const Entity&, C&...)>& func
	)
	{
		_call_for_each_m<C...>(func);
		return *this;
	}

	template <typename ... C, typename Func>
	manager& for_each_with(const Func& func)
	{
		return for_each(
			base::functor_ref<void(const Entity&, C&...)>(func)
		);
	}

	template <typename C>
	manager& parallel_for_each(
		const base::functor_ref<void(const Entity&, const C&)>& func,
		base::parallelizer& prlzr,
		base::execution_params& param
	)
	{
		_call_pl_for_each<C>(func, prlzr, param);
		return *this;
	}

	template <typename C>
	manager& parallel_for_each(
		const base::functor_ref<void(const Entity&, C&)>& func,
		base::parallelizer& prlzr,
		base::execution_params& param
	)
	{
		_call_pl_for_each<C>(func, prlzr, param);
		return *this;
	}

	template <typename ... C>
	typename meta::enable_if<
		(sizeof...(C) > 1),
		manager&
	>::type parallel_for_each(
		const base::functor_ref<void(const Entity&, C&...)>& func,
		base::parallelizer& prlzr,
		base::execution_params& param
	)
	{
		_call_pl_for_each_m<C...>(func, prlzr, param);
		return *this;
	}

	template <typename ... C, typename Func>
	manager& parallel_for_each_with(
		const Func& func,
		base::parallelizer& prlzr,
		base::execution_params& param
	)
	{
		return parallel_for_each(
			base::functor_ref<void(const Entity&, C&...)>(func),
			prlzr,
			param
		);
	}

	template <typename T, typename C>
	T get(T C::*mvp, const Entity& ent, T res = T())
	{
		return _do_get(mvp, ent, res);
	}
};

} // namespace ecs
} // namespace eagine

#include <eagine/ecs/manager.inl>

#endif //include guard

