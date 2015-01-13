/**
 *  @file eagine/ecs/manager.inl
 *  @brief Implementation of E/C manager
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/error.hpp>
#endif

namespace eagine {
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
} // namespace detail
//------------------------------------------------------------------------------
// manager::_do_reg_cmp_type
//------------------------------------------------------------------------------
template <typename Entity>
inline void
manager<Entity>::
_do_reg_cmp_type(
	const base::shared_ptr<base_storage<Entity>>& storage,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	assert(bool(storage));

	auto p_storage = _storages.find(cid);

	if(p_storage == _storages.end())
	{
		_storages[cid] = storage;
	}
	else
	{
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
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		_storages.erase(p_storage);
	}
	else
	{
		detail::mgr_handle_cmp_not_reg(get_name());
	}
}
//------------------------------------------------------------------------------
// manager::_does_know_cmp_type
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_does_know_cmp_type(component_uid_t cid) const
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------------------------
// manager::_apply_on_base_stg
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Result, typename Func>
inline
Result
manager<Entity>::
_apply_on_base_stg(
	Result fallback,
	const Func& func,
	component_uid_t cid,
	base::string(*get_name)(void)
) const
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		auto& bs_storage = *p_storage;
		if(bs_storage)
		{
			return func(bs_storage);
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name());
	return fallback;
}
//------------------------------------------------------------------------------
// manager::_apply_on_cmp_stg
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Result, typename Func>
inline
Result
manager<Entity>::
_apply_on_cmp_stg(
	Result fallback,
	const Func& func
) const
{
	return _apply_on_base_stg(
		fallback,
		[&func](auto& b_storage) -> auto
		{
			typedef component_storage<Entity, Component> cs_t;

			cs_t* ct_storage = dynamic_cast<cs_t*>(b_storage.get());

			assert(ct_storage);

			return func(ct_storage);
		},
		get_component_uid<Component>(),
		_cmp_name_getter<Component>()
	);
}
//------------------------------------------------------------------------------
// manager::_get_cmp_type_caps
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_capabilities
manager<Entity>::
_get_cmp_type_caps(
	component_uid_t cid,
	base::string(*get_name)(void)
) const
{
	return _apply_on_base_stg(
		storage_capabilities(),
		[](auto& b_storage) -> auto
		{
			return b_storage->capabilities();
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_does_have
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_does_have(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> auto
		{
			return b_storage->has(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_is_hidn
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_is_hidn(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> auto
		{
			return b_storage->hidden(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_show
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_show(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> auto
		{
			return b_storage->show(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_hide
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_hide(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> auto
		{
			return b_storage->hide(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_add
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_add(const Entity& ent, Component&& component)
{
	return _apply_on_cmp_stg<Component>(
		false,
		[&ent, &component](auto& c_storage) -> auto
		{
			c_storage->store(std::move(component), ent);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// manager::_do_cpy
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_cpy(
	const Entity& from,
	const Entity& to,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&from, &to](auto& b_storage) -> auto
		{
			return b_storage->copy(to, from);
		},
		cid, get_name
	);
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
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&e1, &e2](auto& b_storage) -> auto
		{
			b_storage->swap(e1, e2);
			return true;
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_rem
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_rem(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> auto
		{
			return b_storage->remove(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_call_for_single
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline bool
manager<Entity>::
_call_for_single(const Func& func, const Entity& ent)
{
	return _apply_on_cmp_stg<Component>(
		false,
		[&func, &ent](auto& c_storage) -> auto
		{
			return c_storage->for_single(func, ent);
		}
	);
}
//------------------------------------------------------------------------------
// manager::_call_for_each
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline void
manager<Entity>::
_call_for_each(const Func& func)
{
	_apply_on_cmp_stg<Component>(
		false,
		[&func](auto& c_storage) -> auto
		{
			c_storage->for_each(func);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// manager::_call_pl_for_each
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline void
manager<Entity>::
_call_pl_for_each(
	const Func& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	_apply_on_cmp_stg<Component>(
		false,
		[&func,&prlzr,&param](auto& c_storage) -> auto
		{
			c_storage->for_each(func, prlzr,param);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// manager::_do_get
//------------------------------------------------------------------------------
template <typename Entity>
template <typename T, typename C>
inline T
manager<Entity>::
_do_get(T C::* mvp, const Entity& ent, T res)
{
	assert(mvp);

	auto getter = [mvp, &res](const Entity&, const C& cmp) -> void
	{
		res = cmp.*mvp;
	};
	base::functor<void(const Entity&, const C&)> func(getter);

	_call_for_single<C>(func, ent);
	return res;
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace eagine


