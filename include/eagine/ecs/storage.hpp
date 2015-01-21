/**
 *  @file eagine/ecs/storage.hpp
 *  @brief Component storage interface
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_1408161720_HPP
#define EAGINE_ECS_STORAGE_1408161720_HPP

#include <eagine/ecs/storage_capability.hpp>
#include <eagine/base/access_type.hpp>
#include <eagine/base/functor.hpp>
#include <eagine/base/parallel.hpp>

namespace eagine {
namespace ecs {

// storage_iterator
template <typename Entity>
struct storage_iterator
{
	virtual ~storage_iterator(void) { }

	virtual void reset(void) = 0;

	virtual bool done(void) = 0;

	virtual void next(void) = 0;

	virtual const Entity& current(void) = 0;
};

// base_storage
template <typename Entity>
struct base_storage
{
	typedef storage_iterator<Entity> iter_t;

	virtual ~base_storage(void) { }

	virtual storage_capabilities capabilities(void) const = 0;

	bool can_find(void) const
	{
		return bool(capabilities() & storage_capability::find);
	}

	bool can_hide(void) const
	{
		return bool(capabilities() & storage_capability::hide);
	}

	bool can_copy(void) const
	{
		return bool(capabilities() & storage_capability::copy);
	}

	bool can_swap(void) const
	{
		return bool(capabilities() & storage_capability::swap);
	}

	bool can_store(void) const
	{
		return bool(capabilities() & storage_capability::store);
	}

	bool can_fetch(void) const
	{
		return bool(capabilities() & storage_capability::fetch);
	}

	bool can_modify(void) const
	{
		return bool(capabilities() & storage_capability::modify);
	}

	bool can_remove(void) const
	{
		return bool(capabilities() & storage_capability::remove);
	}

	bool can_reserve(void) const
	{
		return bool(capabilities() & storage_capability::reserve);
	}

	bool can_point_to(void) const
	{
		return bool(capabilities() & storage_capability::point_to);
	}

	virtual iter_t* new_iterator(void) = 0;

	virtual iter_t* clone_iterator(iter_t*) = 0;

	virtual void delete_iterator(iter_t*) = 0;

	virtual bool has(const Entity& ent) = 0;

	virtual bool find(const Entity& ent, iter_t& pos) = 0;

	// requires can_reserve
	virtual void reserve(std::size_t count) = 0;

	virtual bool hidden(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_hide
	// result indicates if visilibility has changed.
	// failure to hide existing component is indicated
	// by throwing.
	virtual bool hide(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_hide
	// result indicates if visibility has changed.
	// failure to show existing hidden component is indicated
	// by throwing.
	virtual bool show(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_swap
	// failure to swap is indicated by throwing.
	virtual void swap(
		const Entity& e1,
		const Entity& e2
	) = 0;

	// requires can_copy
	// result indicates if the from entity had the component.
	// failure to copy existing is indicated by throwing.
	virtual bool copy(
		const Entity& to,
		const Entity& from,
		iter_t* pos = nullptr,
		iter_t* res = nullptr
	) = 0;

	// requires can_remove
	// result indicates if the entity had component.
	// failure to remove existing component is indicated
	// by throwing.
	virtual bool remove(
		const Entity& from,
		iter_t* pos = nullptr
	) = 0;
};

// component_storage
template <typename Entity, typename Component>
struct component_storage
 : virtual base_storage<Entity>
{
	typedef storage_iterator<Entity> iter_t;

	// requires can_point_to
	virtual const Component* read(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_point_to && can_modify
	virtual Component* write(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_point_to
	const Component* access(
		base::access_read_only_t,
		const Entity& ent,
		iter_t* pos = nullptr
	)
	{
		return read(ent, pos);
	}

	// requires can_point_to && can_modify
	Component* access(
		base::access_read_write_t,
		const Entity& ent,
		iter_t* pos = nullptr
	)
	{
		return write(ent, pos);
	}

	// requires can_remove
	// result indicates if the entity had component.
	// failure to remove existing component is indicated
	// by throwing.
	virtual void remove_if(
		const base::functor_ref<
			bool(const Entity&, const Component&)
		>& predicate
	) = 0;

	// requires can_store
	// failure to store is indicated by throwing
	virtual void store(
		Component&& src,
		const Entity& ent,
		iter_t* pos = nullptr,
		iter_t* res = nullptr
	) = 0;

	// requires can_fetch
	// result indicates if the entity has the component.
	// failure to fetch exisiting component is indicated
	// by throwing
	virtual bool fetch(
		Component& dst,
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_fetch
	virtual bool for_single(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func,
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_modify
	virtual bool for_single(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func,
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_fetch
	virtual void for_each(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func
	) = 0;

	// requires can_modify
	virtual void for_each(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func
	) = 0;

	// requires can_fetch
	virtual void parallel_for_each(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& kernel,
		base::parallelizer&,
		base::execution_params&
	)
	{
		for_each(kernel);
	}

	// requires can_modify
	virtual void parallel_for_each(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& kernel,
		base::parallelizer&,
		base::execution_params&
	)
	{
		for_each(kernel);
	}
};

} // namespace ecs
} // namespace eagine

#endif //include guard

