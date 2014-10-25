/**
 *  @file eagine/ecs/normal_storage.hpp
 *  @brief Basic in-memory R/W component storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_NORMAL_STORAGE_1408161720_HPP
#define EAGINE_ECS_NORMAL_STORAGE_1408161720_HPP

#include <eagine/ecs/storage.hpp>
#include <eagine/base/flat_dict.hpp>

namespace EAGine {
namespace ecs {

// normal_base_storage - fwd
template <typename Entity>
class normal_base_storage;

// normal_storage_iterator
template <typename Entity>
class normal_storage_iterator
 : public storage_iterator<Entity>
{
private:
	normal_base_storage<Entity>& _storage;
	std::size_t _pos;
public:
	normal_storage_iterator(normal_base_storage<Entity>& storage)
	 : _storage(storage)
	 , _pos(0)
	{ }

	void set(std::size_t pos);
	void reset(void);
	bool done(void);
	void next(void);
	const Entity& current(void);
};

// normal_base_storage
template <typename Entity>
class normal_base_storage
 : public base_storage<Entity>
{
protected:
	base::flat_dict<Entity, std::size_t> _index;

	typedef normal_storage_iterator<Entity> _ns_iter_t;
	_ns_iter_t _iter;
	bool _iter_taken;

	friend class normal_storage_iterator<Entity>;

	normal_base_storage(const normal_base_storage&) = delete;
public:
	typedef storage_iterator<Entity> iter_t;

	normal_base_storage(void)
	 : _iter(*this)
	 , _iter_taken(false)
	{ }

	storage_traits traits(void) const;

	iter_t* new_iterator(void);
	void delete_iterator(iter_t* iter);

	bool has(const Entity& ent);
	bool find(const Entity& ent, iter_t& pos);

	void hide(const Entity& ent, iter_t* pos);
	void show(const Entity& ent, iter_t* pos);
	void swap(const Entity& to, const Entity& from);
};

// normal_component_storage
template <typename Entity, typename Component>
class normal_component_storage
 : public component_storage<Entity, Component>
{
private:

public:
	typedef storage_iterator<Entity> iter_t;

	void reserve(std::size_t count);

	iter_t* store(
		Component&& src,
		const Entity& ent,
		iter_t* pos,
		iter_t* res
	);

	iter_t* copy(
		const Entity& to,
		const Entity& from,
		iter_t* pos,
		iter_t* res
	);

	bool remove(const Entity& from, iter_t* pos);
	const Component* read(const Entity& ent, iter_t* pos);
	Component* write(const Entity& ent, iter_t* pos);

	bool fetch(Component& dst, const Entity& ent, iter_t* pos);

	void for_single(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func,
		const Entity& ent,
		iter_t* pos
	);

	void for_single(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func,
		const Entity& ent,
		iter_t* pos
	);

	void for_each(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func
	);

	void for_each(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func
	);
};

} // namespace ecs
} // namespace EAGine

#include <eagine/ecs/normal_storage.inl>

#endif //include guard

