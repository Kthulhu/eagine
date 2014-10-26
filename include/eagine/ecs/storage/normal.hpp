/**
 *  @file eagine/ecs/storage/normal.hpp
 *  @brief Basic in-memory R/W component storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_NORMAL_1408161720_HPP
#define EAGINE_ECS_STORAGE_NORMAL_1408161720_HPP

#include <eagine/ecs/storage.hpp>
#include <eagine/ecs/bits/component_store.hpp>
#include <eagine/base/flat_dict.hpp>
#include <eagine/meta/type_traits.hpp>

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

	std::size_t get(void) const;
	void set(std::size_t pos);
	void reset(void);
	bool done(void);
	void next(void);
	const Entity& current(void);
};

// normal_base_storage
template <typename Entity>
class normal_base_storage
 : public virtual base_storage<Entity>
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

	iter_t* new_iterator(void);
	void delete_iterator(iter_t* iter);

	bool has(const Entity& ent);
	bool find(const Entity& ent, iter_t& pos);

	bool hidden(const Entity& ent, iter_t* pos);
	bool hide(const Entity& ent, iter_t* pos);
	bool show(const Entity& ent, iter_t* pos);
	void swap(const Entity& to, const Entity& from);
};

// normal_component_storage
template <typename Entity, typename Component>
class normal_component_storage
 : public normal_base_storage<Entity>
 , public component_storage<Entity, Component>
{
private:
	component_store<Component> _store;

	typedef normal_storage_iterator<Entity> _ns_iter_t;

	static constexpr std::size_t _nil_stor_pos(void);

	std::size_t _stor_pos(
		const Entity& e,
		storage_iterator<Entity>*
	);
	void _set_iter(
		std::size_t,
		storage_iterator<Entity>*
	);
public:
	typedef storage_iterator<Entity> iter_t;

	storage_capabilities capabilities(void) const;

	void reserve(std::size_t count);

	void store(
		Component&& src,
		const Entity& ent,
		iter_t* pos,
		iter_t* res
	);

	bool copy(
		const Entity& to,
		const Entity& from,
		iter_t* pos,
		iter_t* res
	);

	bool remove(const Entity& from, iter_t* pos);

	const Component* read(const Entity& ent, iter_t* pos);

	Component* write(const Entity& ent, iter_t* pos);

	bool _fetch(Component&, const Entity&, iter_t*, meta::true_type);
	bool _fetch(Component&, const Entity&, iter_t*, meta::false_type);
	bool fetch(Component& dst, const Entity& ent, iter_t* pos);

	bool for_single(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func,
		const Entity& ent,
		iter_t* pos
	);

	bool for_single(
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

#include <eagine/ecs/storage/normal.inl>

#endif //include guard

