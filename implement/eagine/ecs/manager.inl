/**
 *  @file eagine/ecs/manager.inl
 *  @brief Implementation of E/C manager
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/error.hpp>
#include <eagine/base/type_to_value.hpp>

namespace EAGine {
namespace ecs {
namespace detail {
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
EAGINE_LIB_FUNC
void mgr_handle_cmp_is_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is already registered"))
		% c_name.c_str()
	).str());
}

EAGINE_LIB_FUNC
void mgr_handle_cmp_not_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is not registered"))
		% c_name.c_str()
	).str());
}
#else
void mgr_handle_cmp_is_reg(const base::string&);
void mgr_handle_cmp_not_reg(const base::string&);
#endif

template <typename E, typename C>
struct mgr_adder
{
	E _e;
	C _c;

	mgr_adder(const E& e, C&& c)
	 : _e(e)
	 , _c(std::move(c))
	{ }

	void operator () (manager<E>& m)
	{
		m.add(_e, std::move(_c));
	}
};

} // namespace detail

//
// modifications
//
template <typename Entity>
template <typename Component>
inline void
modifications<Entity>::
add_later(const Entity& e, Component&& c)
{
	_ops.emplace_back(
		detail::mgr_adder<Entity, Component>(e, std::move(c))
	);
}

template <typename Entity>
template <typename Component>
inline void
modifications<Entity>::
swap_later(const Entity& e1, const Entity& e2)
{
	_ops.emplace_back(
		[=](manager<Entity>& m) -> void
		{
			m.template swap<Component>(e1, e2);
		}
	);
}

template <typename Entity>
template <typename Component>
inline void
modifications<Entity>::
remove_later(const Entity& e)
{
	_ops.emplace_back(
		[=](manager<Entity>& m) -> void
		{
			m.template remove<Component>(e);
		}
	);
}

template <typename Entity>
inline void
modifications<Entity>::
execute_later(base::function<void(manager<Entity>&)>&& op)
{
	_ops.push_back(std::move(op));
}

template <typename Entity>
inline void
modifications<Entity>::
commit(manager<Entity>& m)
{
	if(!_ops.empty())
	{
		for(auto& op : _ops)
		{
			op(m);
		}
		_ops.clear();
	}
}

//
// manager
//
template <typename Entity>
inline void
manager<Entity>::
_do_reg_cmp_type(
	component_uid cid,
	const base::shared_ptr<entity_component_map<Entity>>& eck_map,
	const base::shared_ptr<base_component_storage>& storage,
	base::string(*get_name)(void)
)
{
	assert(bool(eck_map));
	assert(bool(storage));

	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map == _eck_maps.end())
	{
		assert(_storages.find(cid) == _storages.end());

		_eck_maps[cid] = eck_map;
		_storages[cid] = storage;
	}
	else
	{
		assert(_storages.find(cid) != _storages.end());
		detail::mgr_handle_cmp_is_reg(get_name());
	}
}

template <typename Entity>
inline void
manager<Entity>::
_do_unr_cmp_type(
	component_uid cid,
	base::string(*get_name)(void)
)
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto p_storage = _storages.find(cid);
		assert(p_storage != _storages.end());

		_eck_maps.erase(p_eck_map);
		_storages.erase(p_storage);
	}
	else
	{
		assert(_storages.find(cid) == _storages.end());
		detail::mgr_handle_cmp_not_reg(get_name());
	}
}

template <typename Entity>
inline bool
manager<Entity>::
_does_know_cmp_type(component_uid cid) const
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		assert(_storages.find(cid) != _storages.end());
		return true;
	}
	else
	{
		assert(_storages.find(cid) == _storages.end());
		return false;
	}
}

template <typename Entity>
inline std::size_t
manager<Entity>::
_get_cmp_cnt(component_uid cid) const
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			return eck_map->size();
		}
	}
	return 0;
}

template <typename Entity>
inline component_key_t
manager<Entity>::
_get_cmp_key(const Entity& e, component_uid cid) const
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			return eck_map->find(e);
		}
	}
	return nil_component_key;
}

template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_add(const Entity& e, Component&& component)
{
	component_uid cid = get_component_uid<Component>();
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			auto p_storage = _storages.find(cid);
			assert(p_storage != _storages.end());

			auto& base_storage = *p_storage;
			assert(base_storage);

			typedef component_storage<Component> cs_t;

			assert(base::dynamic_pointer_cast<cs_t>(base_storage));

			base::shared_ptr<cs_t> storage =
				base::static_pointer_cast<cs_t>(base_storage);

			component_key_t key = eck_map->find(e);

			if(key == nil_component_key)
			{
				key = storage->insert(std::move(component));
			}
			else
			{
				storage->replace(key, std::move(component));
			}

			eck_map->store(e, key);
			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(base::type_name<Component>());
	return false;
}

template <typename Entity>
inline bool
manager<Entity>::
_do_cpy(
	const Entity& e1,
	const Entity& e2,
	component_uid cid,
	base::string(*get_name)(void)
)
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			auto p_storage = _storages.find(cid);
			assert(p_storage != _storages.end());

			auto& base_storage = *p_storage;
			assert(base_storage);

			component_key_t k1 = eck_map->find(e1);
			component_key_t k2 = eck_map->remove(e2);

			if(k2 != nil_component_key)
			{
				base_storage->release(k2);
			}

			if(k1 != nil_component_key)
			{
				k2 = base_storage->copy(k1);

				eck_map->store(e2, k2);

			}
			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name?get_name():base::string());
	return false;
}

template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_cpy(const Entity& e1, const Entity& e2)
{
	component_uid cid = get_component_uid<Component>();
	return _do_cpy(e1, e2, cid, &base::type_name<Component>);
}

template <typename Entity>
inline bool
manager<Entity>::
_do_swp(
	const Entity& e1,
	const Entity& e2,
	component_uid cid,
	base::string(*get_name)(void)
)
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			eck_map->swap(e1, e2);
			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name?get_name():base::string());
	return false;
}

template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_swp(const Entity& e1, const Entity& e2)
{
	component_uid cid = get_component_uid<Component>();
	return _do_swp(e1, e2, cid, &base::type_name<Component>);
}

template <typename Entity>
inline bool
manager<Entity>::
_do_rem(
	const Entity& e,
	component_uid cid,
	base::string(*get_name)(void)
)
{
	auto p_eck_map = _eck_maps.find(cid);

	if(p_eck_map != _eck_maps.end())
	{
		auto& eck_map = *p_eck_map;
		if(eck_map)
		{
			component_key_t key = eck_map->remove(e);

			if(key != nil_component_key)
			{
				auto p_storage = _storages.find(cid);
				assert(p_storage != _storages.end());

				auto& base_storage = *p_storage;
				assert(base_storage);

				base_storage->release(key);
			}

			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name?get_name():base::string());
	return false;
}

template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_rem(const Entity& e)
{
	component_uid cid = get_component_uid<Component>();
	return _do_rem(e, cid, &base::type_name<Component>);
}

template <typename Entity>
template <typename Component, typename Access>
inline typename Access::template result<Component>::type*
manager<Entity>::
_do_acc(const Entity& e, Access acc)
{
	component_uid cid = get_component_uid<Component>();
	component_key_t key = _get_cmp_key(e, cid);

	if(key != nil_component_key)
	{
		auto p_storage = _storages.find(cid);
		assert(p_storage != _storages.end());

		auto& bs = *p_storage;
		assert(bs);

		typedef component_storage<Component> cs_t;

		assert(base::dynamic_pointer_cast<cs_t>(bs));

		base::shared_ptr<cs_t> storage =
			base::static_pointer_cast<cs_t>(bs);

		return storage->access(key, acc);
	}
	return nullptr;
}

template <typename Entity>
template <typename Component, typename Access>
inline typename Access::template result<Component>::type*
manager<Entity>::
_do_acc(
	const Entity& e,
	Access acc,
	base_component_storage* bs,
	component_key_t key
)
{
	if(key != nil_component_key)
	{
		assert(bs);

		typedef component_storage<Component> cs_t;

		assert(dynamic_cast<cs_t*>(bs));

		cs_t* storage = static_cast<cs_t*>(bs);

		return storage->access(key, acc);
	}
	return nullptr;
}

template <typename Entity>
template <typename ... C, typename Func, typename CS, typename CK>
inline void 
manager<Entity>::
_do_call_m_e_cp(
	Func& func,
	modifications<Entity>& mods,
	const Entity& entity,
	const CS& stgs,
	const CK& keys
)
{
	func(
		mods,
		entity,
		_do_acc<
			typename meta::remove_const<
				typename meta::remove_reference<C>::type
			>::type
		>(
			entity,
			typename base::access<C>::type(),
			stgs.template ref<C>(),
			keys.template ref<C>()
		)...
	);
}

template <typename Entity>
template <typename ... C, typename Func>
inline manager<Entity>&
manager<Entity>::
for_each_m_e_cp(Func func)
{
	const std::size_t N = sizeof...(C);

	base::array<std::size_t, N> poss = {{
		meta::instead_of<C, std::size_t>::value(0)...
	}};
	const base::array<std::size_t, N> sizs = {{
		_get_cmp_cnt(get_component_uid<C>())...
	}};
	base::array<entity_component_map<Entity>*, N> ecks = {{
		_eck_maps.find(get_component_uid<C>())->get()...
	}};
	base::type_to_value<base_component_storage*, C...> stgs = {
		{_storages.find(get_component_uid<C>())->get()}...
	};
	base::type_to_value<component_key_t, C...> keys;

	modifications<Entity> mods;

	Entity e = nil_entity<Entity>();

	std::size_t c;
	for(c=0; c<N; ++c)
	{
		if(poss[c] < sizs[c])
		{
			e = ecks[c]->entity(poss[c]);
			keys[c] = ecks[c]->key(poss[c]);
			break;
		}
		else
		{
			keys[c] = nil_component_key;
		}
	}

	assert(!(c > N));
	if(c == N) return *this;

	for(; c<N; ++c)
	{
		if(poss[c] < sizs[c])
		{
			const Entity& te = ecks[c]->entity(poss[c]);
			if(e > te)
			{
				e = te;
				keys[c] = ecks[c]->key(poss[c]);
				for(std::size_t pc=0; pc<c; ++pc)
				{
					keys[pc] = nil_component_key;
				}
			}
			else if(e == te)
			{
				keys[c] = ecks[c]->key(poss[c]);
			}
			else
			{
				keys[c] = nil_component_key;
			}
		}
		else
		{
			keys[c] = nil_component_key;
		}
	}

	_do_call_m_e_cp<C...>(func, mods, e, stgs, keys);

	while(true)
	{
		Entity m = e;

		for(c=0; c<N; ++c)
		{
			if(poss[c] < sizs[c])
			{
				if(e >= ecks[c]->entity(poss[c]))
				{
					++poss[c];
				}
				if(poss[c] < sizs[c])
				{
					m = ecks[c]->entity(poss[c]);
					keys[c] = ecks[c]->key(poss[c]);
					break;
				}
				else
				{
					keys[c] = nil_component_key;
				}
			}
			else
			{
				keys[c] = nil_component_key;
			}
		}

		assert(!(c > N));
		if(c == N) break;

		for(; c<N; ++c)
		{
			if(poss[c] < sizs[c])
			{
				if(e >= ecks[c]->entity(poss[c]))
				{
					++poss[c];
				}
				if(poss[c] < sizs[c])
				{
					const Entity& te = ecks[c]->entity(poss[c]);
					if(m > te)
					{
						m = ecks[c]->entity(poss[c]);
						keys[c] = ecks[c]->key(poss[c]);

						for(std::size_t pc=0; pc<c; ++pc)
						{
							keys[pc] =
								nil_component_key;
						}
					}
					else if(m == te)
					{
						keys[c] = ecks[c]->key(poss[c]);
					}
					else
					{
						keys[c] = nil_component_key;
					}
				}
				else
				{
					keys[c] = nil_component_key;
				}
			}
			else
			{
				keys[c] = nil_component_key;
			}
		}

		e = m;

		_do_call_m_e_cp<C...>(func, mods, e, stgs, keys);
	}
	mods.commit(*this);
	return *this;
}

template <typename Entity>
template <typename ... C>
inline manager<Entity>&
manager<Entity>::
for_each(
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		C*...
	)>& func
)
{
	for_each_m_e_cp<
		typename meta::conditional<
			meta::is_const<C>::value,
			const C&, C&
		>::type...
	>(func);
	return *this;
}

template <typename Entity>
template <typename ... C>
inline manager<Entity>&
manager<Entity>::
for_each(
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		C...
	)>& func
)
{
	auto adapted = [&func](
		modifications<Entity>& m,
		const Entity& e, 
		typename meta::remove_reference<C>::type* ... cp
	) -> void
	{
		if(_count_true(cp...) == sizeof...(C))
		{
			func(m, e, *cp...);
		}
	};
	for_each_m_e_cp<C...>(adapted);
	return *this;
}

template <typename Entity>
template <typename ... C>
inline manager<Entity>&
manager<Entity>::
for_each(const base::function<void(const Entity&, C...)>& func)
{
	auto adapted = [&func](
		modifications<Entity>&,
		const Entity& e, 
		typename meta::remove_reference<C>::type* ... cp
	) -> void
	{
		if(_count_true(cp...) == sizeof...(C))
		{
			func(e, *cp...);
		}
	};
	for_each_m_e_cp<C...>(adapted);
	return *this;
}

template <typename Entity>
template <typename ... C>
inline manager<Entity>&
manager<Entity>::
for_each(const base::function<void(C...)>& func)
{
	auto adapted = [&func](
		modifications<Entity>&,
		const Entity&, 
		typename meta::remove_reference<C>::type* ... cp
	) -> void
	{
		if(_count_true(cp...) == sizeof...(C))
		{
			func(*cp...);
		}
	};
	for_each_m_e_cp<C...>(adapted);
	return *this;
}

} // namespace ecs
} // namespace EAGine


