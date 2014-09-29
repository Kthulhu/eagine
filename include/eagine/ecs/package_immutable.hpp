/**
 *  @file eagine/ecs/package_immutable.hpp
 *  @brief Implementation of immutable component package
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_PACKAGE_IMMUTABLE_1408161720_HPP
#define EAGINE_ECS_PACKAGE_IMMUTABLE_1408161720_HPP

#include <eagine/ecs/component.hpp>
#include <eagine/ecs/package.hpp>
#include <eagine/ecs/eck_map_immutable.hpp>
#include <eagine/ecs/storage_immutable.hpp>
#include <eagine/base/memory.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/base/offset_ptr.hpp>

#include <cstddef>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Entity, typename Component>
class immutable_component_package
 : public default_component_package<Entity, Component>
{
private:
	struct _info_block
	{
		const std::size_t _ent_count;
		const std::size_t _key_count;
		const std::size_t _cmp_size;

		base::offset_ptr<Entity> _ent_addr;
		base::offset_ptr<component_key_t> _key_addr;
		base::offset_ptr<void*> _cmp_addr;

		base::typed_memory_range<const Entity>
		entities(void) const
		{
			return {_ent_addr.get(), _ent_count};
		}

		base::typed_memory_range<const component_key_t>
		keys(void) const
		{
			return {_key_addr.get(), _key_count};
		}

		base::const_memory_block
		component_data(void) const
		{
			return {_cmp_addr.get(), _cmp_size};
		}
	} const * _ib;
public:
	immutable_component_package(const base::const_memory_block& block)
	 : _ib(static_cast<const _info_block*>(block.addr()))
	{
		assert(sizeof(_info_block) <= block.size());
	}

	void register_with(manager<Entity>& m)
	{
		using base::make_shared;
		m.template register_component_type<Component>(
			make_shared<immutable_entity_component_map<Entity>>(
				_ib->entities(),
				_ib->keys()
			),
			make_shared<immutable_component_storage<Component>>(
				_ib->keys(),
				_ib->component_data()
			)
		);
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

