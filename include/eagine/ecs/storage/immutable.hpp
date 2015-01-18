/**
 *  @file eagine/ecs/storage/immutable.hpp
 *  @brief Basic in-memory immutable component storage
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_IMMUTABLE_1408161720_HPP
#define EAGINE_ECS_STORAGE_IMMUTABLE_1408161720_HPP

#include <eagine/ecs/storage.hpp>
#include <eagine/base/flat_dict.hpp>
#include <eagine/base/offset_ptr.hpp>
#include <eagine/base/memory_block.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/meta/type_traits.hpp>

namespace eagine {
namespace ecs {

// immutable_base_storage - fwd
template <typename Entity>
class immutable_base_storage;

// immutable_storage_iterator
template <typename Entity>
class immutable_storage_iterator
 : public storage_iterator<Entity>
{
protected:
	immutable_base_storage<Entity>& _storage;
private:
	std::size_t _idx;
public:
	immutable_storage_iterator(immutable_base_storage<Entity>&);

	std::size_t get(void) const;
	void set(std::size_t idx);
	void reset(void) override;
	bool done(void) override;
	void next(void) override;
	const Entity& current(void) override;
};

// immutable_base_storage
template <typename Entity>
class immutable_base_storage
 : public virtual base_storage<Entity>
{
protected:
	struct _info_block
	{
		const std::size_t _ent_count;
		const std::size_t _key_count;
		const std::size_t _cmp_size;

		base::offset_ptr<Entity> _ent_addr;
		base::offset_ptr<std::size_t> _key_addr;
		base::offset_ptr<void*> _cmp_addr;
	};

	const _info_block& _ib(const base::const_memory_block&);

	base::typed_memory_range<const Entity> _entities;
	base::typed_memory_range<const std::size_t> _keys;
	base::const_memory_block _component_data;

	base::const_flat_range_dict<
		const Entity,
		const std::size_t,
		const Entity*,
		const std::size_t*
	> _index;

	typedef immutable_storage_iterator<Entity> _ns_iter_t;
	_ns_iter_t _iter;
	bool _iter_taken;

	friend class immutable_storage_iterator<Entity>;

	immutable_base_storage(const immutable_base_storage&) = delete;
public:
	typedef storage_iterator<Entity> iter_t;

	immutable_base_storage(const base::const_memory_block&);

	iter_t* new_iterator(void) override;
	void delete_iterator(iter_t* iter) override;

	bool has(const Entity& ent) override;
	bool find(const Entity& ent, iter_t& pos) override;

	bool hidden(const Entity& ent, iter_t* pos) override;
	bool hide(const Entity& ent, iter_t* pos) override;
	bool show(const Entity& ent, iter_t* pos) override;
	void swap(const Entity& to, const Entity& from) override;
};

// immutable_component_storage
template <typename Entity, typename Component>
class immutable_component_storage
 : public immutable_base_storage<Entity>
 , public component_storage<Entity, Component>
{
private:
	typedef immutable_storage_iterator<Entity> _ns_iter_t;

	static constexpr std::size_t _nil_stor_pos(void);

	std::size_t _stor_pos(
		const Entity& e,
		storage_iterator<Entity>*
	);
public:
	typedef storage_iterator<Entity> iter_t;

	immutable_component_storage(const base::const_memory_block&);

	storage_capabilities capabilities(void) const override;

	void reserve(std::size_t count) override;

	void remove_if(
		const base::functor_ref<
			bool(const Entity&, const Component&)
		>& predicate
	) override;

	void store(
		Component&& src,
		const Entity& ent,
		iter_t* pos,
		iter_t* res
	) override;

	bool copy(
		const Entity& to,
		const Entity& from,
		iter_t* pos,
		iter_t* res
	) override;

	bool remove(const Entity& from, iter_t* pos) override;

	const Component* read(const Entity& ent, iter_t* pos) override;

	Component* write(const Entity& ent, iter_t* pos) override;

	bool _fetch(Component&, const Entity&, iter_t*, meta::true_type);
	bool _fetch(Component&, const Entity&, iter_t*, meta::false_type);
	bool fetch(Component& dst, const Entity& ent, iter_t* pos) override;

	bool for_single(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func,
		const Entity& ent,
		iter_t* pos
	) override;

	bool for_single(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func,
		const Entity& ent,
		iter_t* pos
	) override;

	void for_each(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& func
	) override;

	void for_each(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& func
	) override;

	void parallel_for_each(
		const base::functor_ref<
			void(const Entity&, const Component&)
		>& kernel,
		base::parallelizer&,
		base::execution_params&
	) override;

	void parallel_for_each(
		const base::functor_ref<
			void(const Entity&, Component&)
		>& kernel,
		base::parallelizer&,
		base::execution_params&
	) override;
};

} // namespace ecs
} // namespace eagine

#include <eagine/ecs/storage/immutable.inl>

#endif //include guard

