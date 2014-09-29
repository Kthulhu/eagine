/**
 *  @file eagine/ecs/storage_immutable.hpp
 *  @brief Immutable in-memory component storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_STORAGE_IMMUTABLE_1408161720_HPP
#define EAGINE_ECS_STORAGE_IMMUTABLE_1408161720_HPP

#include <eagine/base/access_type.hpp>
#include <eagine/base/memory_range.hpp>
#include <eagine/ecs/component.hpp>
#include <eagine/ecs/component_storage.hpp>

namespace EAGine {
namespace ecs {

template <typename Component>
class immutable_component_storage
 : public component_storage<Component>
{
private:
	base::typed_memory_range<const component_key_t> _offs;
	base::const_memory_block _data;
public:
	immutable_component_storage(
		const base::typed_memory_range<const component_key_t>& offs,
		const base::const_memory_block& data
	): _offs(offs)
	 , _data(data)
	{ }

	typedef component_key_t key_t;

	component_storage_traits traits(void) const
	{
		typedef component_storage_bits b;
		return (b::can_read |
			b::can_copy
		);
	}

	void add_ref(void) { } 
	void release(void) { } 
	void add_ref(key_t) { } 
	bool release(key_t) { return false; }

	key_t copy(key_t key)
	{
		return key;
	}

	const Component* read(key_t key)
	{
		return static_cast<const Component*>(_data.offs(key));
	}

	Component* write(key_t)
	{
		assert(!"write access is not supported by immutable storage");
		return nullptr;
	}

	bool fetch(key_t, Component&)
	{
		// TODO support if Component is assignable
		assert(!"fetch is not supported by immutable storage");
		return false;
	}

	key_t insert(Component&&)
	{
		assert(!"insert is not supported by immutable storage");
		return nil_component_key;
	}

	key_t replace(key_t, Component&&)
	{
		assert(!"replace is not supported by immutable storage");
		return nil_component_key;
	}

	void for_each(const base::function<void(Component&)>& function)
	{
		assert(!"write access is not supported by immutable storage");
	}

	void for_each(const base::function<void(const Component&)>& function)
	{
		for(key_t key: _offs)
		{
			function(*read(key));
		}
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

