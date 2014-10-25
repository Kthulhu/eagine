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
template <typename Entity>
inline bool
manager<Entity>::
_does_have(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		auto& b_storage = *p_storage;
		if(b_storage)
		{
			return b_storage->has(ent);
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name());
	return false;
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
	component_uid_t cid = get_component_uid<Component>();
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		auto& b_storage = *p_storage;
		if(b_storage)
		{
			typedef component_storage<Entity, Component> cs_t;

			cs_t* storage = dynamic_cast<cs_t*>(b_storage.get());

			assert(storage);

			storage->store(std::move(component), ent);

			return true;
		}
	}
	detail::mgr_handle_cmp_not_reg(_cmp_name_getter<Component>()());
	return false;
}
//------------------------------------------------------------------------------
// manager::_do_add
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
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		auto& b_storage = *p_storage;
		if(b_storage)
		{
			return b_storage->remove(ent);
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name());
	return false;
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace EAGine


