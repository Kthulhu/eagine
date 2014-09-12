/**
 *  @file eagine/ecs/storage_normal.hpp
 *  @brief Basic in-memory R/W component storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_STORAGE_BASIC_1408161720_HPP
#define EAGINE_ECS_STORAGE_BASIC_1408161720_HPP

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

	bool read_only(void) const
	{
		return false;
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

	Component* access(key_t key, access_read_write)
	{
		return _ents.access(key);
	}

	const Component* access(key_t key, access_read_only)
	{
		return _ents.access(key);
	}

	key_t insert(Component&& component)
	{
		return _ents.insert(std::move(component));
	}

	key_t replace(key_t key, Component&& component)
	{
		return _ents.replace(key, std::move(component));
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

