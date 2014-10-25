/**
 *  @file eagine/ecs/storage.hpp
 *  @brief Component storage interface
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_1408161720_HPP
#define EAGINE_ECS_STORAGE_1408161720_HPP

#include <eagine/ecs/storage_bits.hpp>
#include <eagine/base/access_type.hpp>
#include <eagine/base/functor.hpp>

namespace EAGine {
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

	virtual storage_traits traits(void) const = 0;

	virtual iter_t* new_iterator(void) = 0;

	virtual void delete_iterator(iter_t*) = 0;

	virtual bool has(const Entity& ent) = 0;

	virtual bool find(const Entity& ent, iter_t& pos) = 0;

	// requires can_reserve
	virtual void reserve(std::size_t count) = 0;

	// requires can_hide
	virtual void hide(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_hide
	virtual void show(
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_swap
	virtual void swap(
		const Entity& e1,
		const Entity& e2
	) = 0;

	// requires can_copy
	virtual iter_t* copy(
		const Entity& to,
		const Entity& from,
		iter_t* pos = nullptr,
		iter_t* res = nullptr
	) = 0;

	// requires can_remove
	virtual bool remove(
		const Entity& from,
		iter_t* pos = nullptr
	) = 0;
};

// component_storage
template <typename Entity, typename Component>
struct component_storage
 : base_storage<Entity>
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

	// requires can_store
	virtual iter_t* store(
		Component&& src,
		const Entity& ent,
		iter_t* pos = nullptr,
		iter_t* res = nullptr
	) = 0;

	// requires can_fetch
	virtual bool fetch(
		Component& dst,
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_fetch
	virtual void for_single(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func,
		const Entity& ent,
		iter_t* pos = nullptr
	) = 0;

	// requires can_modify
	virtual void for_single(
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
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

