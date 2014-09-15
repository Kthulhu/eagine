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
} // namespace detail

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
			component_key_t key = eck_map->find(e);

			auto p_storage = _storages.find(cid);
			assert(p_storage != _storages.end());

			auto& base_storage = *p_storage;
			assert(base_storage);

			typedef component_storage<Component> cs_t;

			assert(base::dynamic_pointer_cast<cs_t>(base_storage));

			base::shared_ptr<cs_t> storage =
				base::static_pointer_cast<cs_t>(base_storage);

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
template <typename Component>
inline bool
manager<Entity>::
_do_rem(const Entity& e)
{
	component_uid cid = get_component_uid<Component>();
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

				auto& bs = *p_storage;
				assert(bs);

				typedef component_storage<Component> cs_t;

				assert(base::dynamic_pointer_cast<cs_t>(bs));

				base::shared_ptr<cs_t> storage =
					base::static_pointer_cast<cs_t>(bs);

				storage->release(key);
			}

			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(base::type_name<Component>());
	return false;
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
template <typename ... C, typename Func>
inline void
manager<Entity>::
_for_each_e_ptr(Func func)
{
	const std::size_t N = sizeof...(C);

	base::array<std::size_t, N> poss = {
		meta::instead_of<C, std::size_t>::value(0)...
	};
	const base::array<std::size_t, N> sizs = {
		_get_cmp_cnt(get_component_uid<C>())...
	};
	base::array<entity_component_map<Entity>*, N> ecks = {
		_eck_maps.find(get_component_uid<C>())->get()...
	};

	Entity e = nil_entity<Entity>();

	std::size_t c;
	for(c=0; c<N; ++c)
	{
		if(poss[c] < sizs[c])
		{
			e = ecks[c]->entity(0);
			break;
		}
	}

	assert(!(c > N));
	if(c == N) return;

	for(; c<N; ++c)
	{
		if(poss[c] < sizs[c])
		{
			if(e >= ecks[c]->entity(0))
			{
				e = ecks[c]->entity(0);
			}
		}
	}

	_do_call_e_ptr<C...>(e, func);

	while(true)
	{
		Entity m = e;

		for(c=0; c<N; ++c)
		{
			if(poss[c] < sizs[c])
			{
				if(ecks[c]->entity(poss[c]) <= m)
				{
					++poss[c];
				}
				if(poss[c] < sizs[c])
				{
					m = ecks[c]->entity(poss[c]);
					break;
				}
			}
		}

		assert(!(c > N));
		if(c == N) break;

		for(; c<N; ++c)
		{
			if(poss[c] < sizs[c])
			{
				if(ecks[c]->entity(poss[c]) <= e)
				{
					++poss[c];
				}
				if(poss[c] < sizs[c])
				{
					if(ecks[c]->entity(poss[c]) < m)
					{
						m = ecks[c]->entity(poss[c]);
					}
				}
			}
		}

		e = m;

		_do_call_e_ptr<C...>(e, func);
	}
}

} // namespace ecs
} // namespace EAGine


