/**
 *  @file eagine/ecs/component_storage.hpp
 *  @brief E/CS component-related types and constants.
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_ECS_COMPONENT_STORAGE_1408161720_HPP
#define EAGINE_ECS_COMPONENT_STORAGE_1408161720_HPP

#include <eagine/ecs/component.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/function.hpp>
#include <cassert>

namespace EAGine {
namespace ecs {

struct base_component_storage
{
	typedef component_key_t key_t;

	virtual ~base_component_storage(void) noexcept { }

	virtual bool read_only(void) const = 0;

	virtual void add_ref(void) = 0;
	virtual void release(void) = 0;

	virtual void add_ref(key_t key) = 0;
	virtual bool release(key_t key) = 0;

	virtual key_t copy(key_t key) = 0;
};

template <typename Component>
struct component_storage : base_component_storage
{
	virtual Component* access(key_t key, base::access_read_write_t) = 0;
	virtual const Component* access(key_t key, base::access_read_only_t)= 0;

	virtual key_t insert(Component&& component) = 0;
	virtual key_t replace(key_t key, Component&& component) = 0;

	virtual void for_each(const base::function<void(Component&)>&) = 0;
	virtual void for_each(const base::function<void(const Component&)>&)= 0;
};

template <typename Component>
struct component_storage_entry
{
	// negative reference count (if < 0)
	// or the next free component entry
	// in the vector
	int _neg_rc_or_nf;
	Component _component;

	component_storage_entry(Component&& component)
	 : _neg_rc_or_nf(0L)
	 , _component(std::move(component))
	{ }
};

template <typename Component>
class component_entry_vector
{
private:
	base::vector<component_storage_entry<Component>> _ents;
	base::vector<component_key_t> _gc_keys;
	int _next_free;
	int _vector_refs;
public:
	typedef component_key_t key_t;

	component_entry_vector(void)
	 : _next_free(-1)
	 , _vector_refs(0)
	{ }

	const Component& at(key_t key) const
	{
		assert(key < _ents.size());
		return _ents.at(key)._component;
	}

	Component* access(key_t key)
	{
		if(key >= _ents.size()) return nullptr;
		return &_ents.at(key)._component;
	}

	const Component* access(key_t key) const
	{
		if(key >= _ents.size()) return nullptr;
		return &_ents.at(key)._component;
	}

	void reserve(std::size_t size)
	{
		_ents.reserve(size);
	}

	key_t insert(Component&& component)
	{
		key_t key;
		if(_next_free >= 0)
		{
			key = key_t(_next_free);
			_ents.at(key)._component = std::move(component);
			_next_free = _ents.at(key)._neg_rc_or_nf;
			_ents.at(key)._neg_rc_or_nf = -1;
		}
		else
		{
			key = _ents.size();
			_ents.push_back(std::move(component));
			_ents.back()._neg_rc_or_nf = -1;
		}
		return key;
	}

	key_t replace(key_t key, Component&& component)
	{
		_ents.at(key)._component = std::move(component);
		return key;
	}

	key_t copy(key_t key)
	{
		return insert(Component(at(key)));
	}

	void add_ref(key_t key)
	{
		assert(_ents.at(key)._neg_rc_or_nf < 0);
		--_ents.at(key)._neg_rc_or_nf;
	}

	void do_release(key_t key)
	{
		_ents.at(key)._neg_rc_or_nf = _next_free;
		_next_free = int(key);
	}

	bool release(key_t key)
	{
		assert(_ents.at(key)._neg_rc_or_nf < 0);
		if(++_ents.at(key)._neg_rc_or_nf == 0)
		{
			if(_vector_refs)
			{
				_gc_keys.push_back(key);
			}
			else do_release(key);
			return true;
		}
		return false;
	}

	template <typename Function>
	void for_each(Function& function)
	{
		for(auto& ent : _ents)
		{
			if(ent._neg_rc_or_nf < 0)
			{
				function(ent._component);
			}
		}
	}

	void gc(void)
	{
		for(auto key: _gc_keys)
		{
			do_release(key);
		}
		_gc_keys.clear();
	}

	void add_ref(void)
	{
		++_vector_refs;
	}

	void release(void)
	{
		if(_vector_refs-- == 0)
		{
			gc();
		}
	}
};


} // namespace ecs
} // namespace EAGine

#endif //include guard

