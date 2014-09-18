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
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
// mgr_handle_cmp_is_reg
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void mgr_handle_cmp_is_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is already registered"))
		% c_name.c_str()
	).str());
}
//------------------------------------------------------------------------------
// mgr_handle_cmp_not_reg
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void mgr_handle_cmp_not_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is not registered"))
		% c_name.c_str()
	).str());
}
//------------------------------------------------------------------------------
#else
void mgr_handle_cmp_is_reg(const base::string&);
void mgr_handle_cmp_not_reg(const base::string&);
#endif
//------------------------------------------------------------------------------
// mgr_adder
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
} // namespace detail
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// modifications::add_later
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// modifications::copy_later
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline void
modifications<Entity>::
copy_later(const Entity& from, const Entity& to)
{
	_ops.emplace_back(
		[=](manager<Entity>& m) -> void
		{
			m.template copy<Component>(from, to);
		}
	);
}
//------------------------------------------------------------------------------
// modifications::swap_later
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// modifications::remove_later
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// modifications::execute_later
//------------------------------------------------------------------------------
template <typename Entity>
inline void
modifications<Entity>::
execute_later(base::function<void(manager<Entity>&)>&& op)
{
	_ops.push_back(std::move(op));
}
//------------------------------------------------------------------------------
// modifications::commit
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_reg_cmp_type
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_unr_cmp_type
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_does_know_cmp_type
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_get_cmp_cnt
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_get_cmp_key
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_add
//------------------------------------------------------------------------------
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

			assert(dynamic_cast<cs_t*>(base_storage.get()));

			cs_t* storage = static_cast<cs_t*>(base_storage.get());

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
//------------------------------------------------------------------------------
// manager::_do_cpy
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_cpy(
	const Entity& e1, // from
	const Entity& e2, // to
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
//------------------------------------------------------------------------------
// manager::_do_cpy
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_cpy(const Entity& e1, const Entity& e2)
{
	component_uid cid = get_component_uid<Component>();
	return _do_cpy(e1, e2, cid, &base::type_name<Component>);
}
//------------------------------------------------------------------------------
// manager::_do_swp
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_swp
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_swp(const Entity& e1, const Entity& e2)
{
	component_uid cid = get_component_uid<Component>();
	return _do_swp(e1, e2, cid, &base::type_name<Component>);
}
//------------------------------------------------------------------------------
// manager::_do_rem
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_rem
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_rem(const Entity& e)
{
	component_uid cid = get_component_uid<Component>();
	return _do_rem(e, cid, &base::type_name<Component>);
}
//------------------------------------------------------------------------------
// manager::_do_acc
//------------------------------------------------------------------------------
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

		assert(dynamic_cast<cs_t*>(bs.get()));

		cs_t* storage = static_cast<cs_t*>(bs.get());

		return storage->access(key, acc);
	}
	return nullptr;
}
//------------------------------------------------------------------------------
// manager::_do_acc
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// manager::_do_call_m_e_cp
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func, typename IterStatusData>
inline void 
manager<Entity>::
_do_call_m_e_cp(
	Func& func,
	IterStatusData& isd,
	modifications<Entity>& mods
)
{
	func(
		mods,
		isd._ent,
		_do_acc<
			typename meta::remove_const<
				typename meta::remove_reference<C>::type
			>::type
		>(
			isd._ent,
			typename base::access<C>::type(),
			isd._stgs.template ref<C>(),
			isd._keys.template ref<C>()
		)...
	);
}
//------------------------------------------------------------------------------
// manager::_make_isd
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline iter_status_data<Entity, C...>
manager<Entity>::
_make_isd(void)
{
	return {
		nil_entity<Entity>(),
		{{meta::instead_of<C, std::size_t>::value(0)...}},
		{{_get_cmp_cnt(get_component_uid<C>())...}},
		{{_eck_maps.find(get_component_uid<C>())->get()...}},
		{{_storages.find(get_component_uid<C>())->get()}...},
		{{meta::instead_of<C, component_key_t>::value(nil_component_key)}...}
	};
}
//------------------------------------------------------------------------------
// iter_status_data::_first
//------------------------------------------------------------------------------
template <typename Entity, typename ... C>
inline bool
iter_status_data<Entity, C...>::
_first(void)
{
	std::size_t c = 0;
	for(; c<N; ++c)
	{
		if(_poss[c] < _sizs[c])
		{
			_ent = _ecks[c]->entity(_poss[c]);
			_keys[c] = _ecks[c]->key(_poss[c]);
			break;
		}
		else
		{
			_keys[c] = nil_component_key;
		}
	}

	assert(!(c > N));
	if(c == N)
	{
		return false;
	}

	for(; c<N; ++c)
	{
		if(_poss[c] < _sizs[c])
		{
			const Entity& etmp = _ecks[c]->entity(_poss[c]);
			if(_ent > etmp)
			{
				_ent = etmp;
				_keys[c] = _ecks[c]->key(_poss[c]);
				for(std::size_t pc=0; pc<c; ++pc)
				{
					_keys[pc] = nil_component_key;
				}
			}
			else if(_ent == etmp)
			{
				_keys[c] = _ecks[c]->key(_poss[c]);
			}
			else
			{
				_keys[c] = nil_component_key;
			}
		}
		else
		{
			_keys[c] = nil_component_key;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
// iter_status_data::_next
//------------------------------------------------------------------------------
template <typename Entity, typename ... C>
inline bool
iter_status_data<Entity, C...>::
_next(void)
{
	Entity emin = _ent;

	std::size_t c = 0;
	for(; c<N; ++c)
	{
		if(_poss[c] < _sizs[c])
		{
			if(_ent >= _ecks[c]->entity(_poss[c]))
			{
				++_poss[c];
			}
			if(_poss[c] < _sizs[c])
			{
				emin = _ecks[c]->entity(_poss[c]);
				_keys[c] = _ecks[c]->key(_poss[c]);
				break;
			}
			else
			{
				_keys[c] = nil_component_key;
			}
		}
		else
		{
			_keys[c] = nil_component_key;
		}
	}

	assert(!(c > N));
	if(c == N)
	{
		return false;
	}

	for(; c<N; ++c)
	{
		if(_poss[c] < _sizs[c])
		{
			if(_ent >= _ecks[c]->entity(_poss[c]))
			{
				++_poss[c];
			}
			if(_poss[c] < _sizs[c])
			{
				const Entity& etmp = _ecks[c]->entity(_poss[c]);
				if(emin > etmp)
				{
					emin = _ecks[c]->entity(_poss[c]);
					_keys[c] = _ecks[c]->key(_poss[c]);

					for(std::size_t pc=0; pc<c; ++pc)
					{
						_keys[pc] = nil_component_key;
					}
				}
				else if(emin == etmp)
				{
					_keys[c] = _ecks[c]->key(_poss[c]);
				}
				else
				{
					_keys[c] = nil_component_key;
				}
			}
			else
			{
				_keys[c] = nil_component_key;
			}
		}
		else
		{
			_keys[c] = nil_component_key;
		}
	}

	_ent = emin;

	return true;
}
//------------------------------------------------------------------------------
// manager::adapt_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
adapt_func_e_cp(const Func& func)
{
	return [=](
			modifications<Entity>&,
			const Entity& ent, 
			C* ... cp
		) -> void
		{
			func(ent, *cp...);
		};
}
//------------------------------------------------------------------------------
// manager::wrap_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
wrap_func_e_cp(const Func& func)
{
	return base::function<void(
		modifications<Entity>&,
		const Entity&,
		C*...
	)>(adapt_func_e_cp<C...>(func));
}
//------------------------------------------------------------------------------
// manager::adapt_func
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline auto
manager<Entity>::
adapt_func(const base::function<void(const Entity&, C*...)>& func)
{
	return wrap_func_e_cp<C...>(func);
}
//------------------------------------------------------------------------------
// manager::adapt_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
adapt_func_m_e_c(const Func& func)
{
	return [=](
			modifications<Entity>& mod,
			const Entity& ent, 
			typename meta::remove_reference<C>::type* ... cp
		) -> void
		{
			if(_count_true(cp...) == sizeof...(C))
			{
				func(mod, ent, *cp...);
			}
		};
}
//------------------------------------------------------------------------------
// manager::wrap_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
wrap_func_m_e_c(const Func& func)
{
	return base::function<void(
		modifications<Entity>&,
		const Entity&,
		typename meta::remove_reference<C>::type*...
	)>(adapt_func_m_e_c<C...>(func));
}
//------------------------------------------------------------------------------
// manager::adapt_func
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline auto
manager<Entity>::
adapt_func(
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		C...
	)>& func
)
{
	return wrap_func_m_e_c<C...>(func);
}
//------------------------------------------------------------------------------
// manager::adapt_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
adapt_func_e_c(const Func& func)
{
	return [=](
			modifications<Entity>&,
			const Entity& ent, 
			typename meta::remove_reference<C>::type* ... cp
		) -> void
		{
			if(_count_true(cp...) == sizeof...(C))
			{
				func(ent, *cp...);
			}
		};
}
//------------------------------------------------------------------------------
// manager_wrap_func_e_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
wrap_func_e_c(const Func& func)
{
	return base::function<void(
		modifications<Entity>&,
		const Entity&,
		typename meta::remove_reference<C>::type*...
	)>(adapt_func_e_c<C...>(func));
}
//------------------------------------------------------------------------------
// manager::adapt_func
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline auto
manager<Entity>::
adapt_func(const base::function<void(const Entity&, C...)>& func)
{
	return wrap_func_e_c<C...>(func);
}
//------------------------------------------------------------------------------
// manager::adapt_func_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
adapt_func_c(const Func& func)
{
	return [=](
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
}
//------------------------------------------------------------------------------
// manager::wrap_func_c
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline auto
manager<Entity>::
wrap_func_c(const Func& func)
{
	return base::function<void(
		modifications<Entity>&,
		const Entity&,
		typename meta::remove_reference<C>::type*...
	)>(adapt_func_c<C...>(func));
}
//------------------------------------------------------------------------------
// manager::adapt_func
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline auto
manager<Entity>::
adapt_func(const base::function<void(C...)>& func)
{
	return wrap_func_c<C...>(func);
}
//------------------------------------------------------------------------------
// manager::for_each_m_e_cp
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline manager<Entity>&
manager<Entity>::
for_each_m_e_cp(Func func)
{
	iter_status_data<Entity, C...> isd = _make_isd<C...>();

	if(isd._first())
	{
		modifications<Entity> mods;

		_do_call_m_e_cp<C...>(func, isd, mods);

		while(true)
		{
			if(!isd._next())
			{
				break;
			}
			_do_call_m_e_cp<C...>(func, isd, mods);
		}
		mods.commit(*this);
	}
	return *this;
}
//------------------------------------------------------------------------------
// manager::for_each
//------------------------------------------------------------------------------
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
			C, C&
		>::type...
	>(func);
	return *this;
}
//------------------------------------------------------------------------------
// manager::make_iteration_status
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline auto
manager<Entity>::
make_iteration_status(
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		C*...
	)>&
)
{
	return iteration_status<
		Entity,
		typename meta::conditional<
			meta::is_const<C>::value,
			C, C&
		>::type...
	>();
}
//------------------------------------------------------------------------------
// manager::start_traversal_m_e_cp
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline bool
manager<Entity>::
start_traversal_m_e_cp(iteration_status<Entity, C...>& is, Func& func)
{
	is._data = _make_isd<C...>();
	if(is._data._first())
	{
		_do_call_m_e_cp<C...>(func, is._data, is._mods);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// manager::start_traversal
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... CS, typename ... CF>
inline bool
manager<Entity>::
start_traversal(
	iteration_status<Entity, CS...>& iter_status,
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		CF*...
	)>& func
)
{
	return start_traversal_m_e_cp<
		typename meta::conditional<
			meta::is_const<CF>::value,
			CF, CF&
		>::type...
	>(iter_status, func);
}
//------------------------------------------------------------------------------
// manager::continue_traversal_m_e_cp
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C, typename Func>
inline bool
manager<Entity>::
continue_traversal_m_e_cp(iteration_status<Entity, C...>& is, Func& func)
{
	if(is._data._next())
	{
		_do_call_m_e_cp<C...>(func, is._data, is._mods);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// manager::continue_traversal
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... CS, typename ... CF>
inline bool
manager<Entity>::
continue_traversal(
	iteration_status<Entity, CS...>& iter_status,
	const base::function<void(
		modifications<Entity>&,
		const Entity&,
		CF*...
	)>& func
)
{
	return continue_traversal_m_e_cp<
		typename meta::conditional<
			meta::is_const<CF>::value,
			CF, CF&
		>::type...
	>(iter_status, func);
}
//------------------------------------------------------------------------------
// manager::finish_traversal
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... C>
inline void
manager<Entity>::
finish_traversal(iteration_status<Entity, C...>& is)
{
	is._mods.commit(*this);
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace EAGine


