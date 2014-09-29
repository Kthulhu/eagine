/**
 *  @file eagine/ecs/storage_normal.hpp
 *  @brief Basic in-memory R/W component storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_NORMAL_1408161720_HPP
#define EAGINE_ECS_STORAGE_NORMAL_1408161720_HPP

#include <eagine/base/access_type.hpp>
#include <eagine/ecs/component.hpp>
#include <eagine/ecs/component_storage.hpp>

namespace EAGine {
namespace ecs {

template <typename Component>
class normal_component_storage
 : public component_storage<Component>
{
private:
	component_entry_vector<Component> _ents;
public:
	typedef component_key_t key_t;

	component_storage_traits traits(void) const
	{
		typedef component_storage_bits b;
		return (b::can_read |
			b::can_write |
			b::can_fetch |
			b::can_replace |
			b::can_copy |
			b::can_insert |
			b::can_remove |
			b::can_reserve
		);
	}

	void add_ref(void)
	{
		_ents.add_ref();
	}

	void release(void)
	{
		_ents.release();
	}

	void add_ref(key_t key)
	{
		_ents.add_ref(key);
	}

	bool release(key_t key)
	{
		return _ents.release(key);
	}

	key_t copy(key_t key)
	{
		return _ents.copy(key);
	}

	const Component* read(key_t key)
	{
		return _ents.access(key);
	}

	Component* write(key_t key)
	{
		return _ents.access(key);
	}

	bool fetch(key_t key, Component& component)
	{
		const Component* ptr = read(key);
		if(!ptr) return false;
		component = *ptr;
		return true;
	}

	key_t insert(Component&& component)
	{
		return _ents.insert(std::move(component));
	}

	key_t replace(key_t key, Component&& component)
	{
		return _ents.replace(key, std::move(component));
	}

	void for_each(const base::function<void(Component&)>& function)
	{
		_ents.for_each(function);
	}

	void for_each(const base::function<void(const Component&)>& function)
	{
		_ents.for_each(function);
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

