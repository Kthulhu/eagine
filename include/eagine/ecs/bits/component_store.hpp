/**
 *  @file eagine/ecs/bits/component_store.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_ECS_BITS_COMPONENT_STORE_1408161720_HPP
#define EAGINE_ECS_BITS_COMPONENT_STORE_1408161720_HPP

#include <eagine/base/vector.hpp>
#include <type_traits>
#include <cassert>

namespace EAGine {
namespace ecs {

template <typename Component>
class component_store_entry
{
private:
	// negative reference count (if < 0)
	// or the next free component entry-1
	// in the vector (if > 0)
	std::ptrdiff_t _neg_rc_or_nf;

	typedef typename std::aligned_storage<
		sizeof(Component),
		alignof(Component)
	>::type _cstore_t;
	_cstore_t _cstore;

	static constexpr bool _has_noexcept_move =
		noexcept(Component(std::move(std::declval<Component>())));

	static Component& _cast(_cstore_t& s)
	{
		return *((Component*)(void*)&s);
	}

	static const Component& _cast(const _cstore_t& s)
	{
		return *((const Component*)(const void*)&s);
	}

	static void _move_in(_cstore_t& s, Component&& c)
	noexcept(_has_noexcept_move)
	{
		new (&s) Component(std::move(c));
	}

	static Component _move_out(_cstore_t& s)
	noexcept(_has_noexcept_move)
	{
		return std::move(_cast(s));
	}

	static void _move(_cstore_t& to, _cstore_t& from)
	noexcept(_has_noexcept_move)
	{
		_move_in(to, std::move(_cast(from)));
	}
public:
	component_store_entry(const component_store_entry&) = delete;

	component_store_entry(void)
	noexcept
	 : _neg_rc_or_nf(0)
	{ }

	component_store_entry(Component&& c)
	noexcept(_has_noexcept_move)
	 : _neg_rc_or_nf(0)
	{
		_move_in(_cstore, std::move(c));
		_neg_rc_or_nf = -1;
	}

	component_store_entry(component_store_entry&& tmp)
	noexcept(_has_noexcept_move)
	 : _neg_rc_or_nf(0)
	{
		if(tmp._neg_rc_or_nf < 0)
		{
			_move(_cstore, tmp._cstore);
		}
		_neg_rc_or_nf = tmp._neg_rc_or_nf;
		tmp._neg_rc_or_nf = 0;
	}

	component_store_entry& operator = (component_store_entry&& tmp)
	noexcept(_has_noexcept_move)
	{
		_move(_cstore, tmp._cstore);
		_neg_rc_or_nf = tmp._neg_rc_or_nf;
		tmp._neg_rc_or_nf = 0;
		return *this;
	}
	
	~component_store_entry(void)
	noexcept
	{
		if(_neg_rc_or_nf < 0)
		{
			try { _move_out(_cstore); }
			catch(...) { }
		}
	}

	bool empty(void) const
	noexcept
	{
		return _neg_rc_or_nf >= 0;
	}

	const Component& ro(void) const
	noexcept
	{
		assert(!empty());
		return _cast(_cstore);
	}

	Component& rw(void) const
	noexcept
	{
		assert(!empty());
		return _cast(_cstore);
	}

	std::ptrdiff_t store(Component&& c)
	noexcept(_has_noexcept_move)
	{
		assert(empty());
		_move_in(_cstore, std::move(c));
		std::ptrdiff_t result = _neg_rc_or_nf-1;
		_neg_rc_or_nf = -1;
		return result;
	}

	void add_ref(void)
	noexcept
	{
		assert(_neg_rc_or_nf < 0);
		--_neg_rc_or_nf;
	}

	bool rem_ref(void)
	noexcept
	{
		assert(_neg_rc_or_nf < 0);
		return (++_neg_rc_or_nf == 0);
	}

	Component release(void)
	noexcept(_has_noexcept_move)
	{
		assert(_neg_rc_or_nf == 0);
		return _move_out(_cstore);
	}

	void mark_free(std::ptrdiff_t next_free)
	noexcept
	{
		assert(_neg_rc_or_nf == 0);
		_neg_rc_or_nf = next_free+1;
	}
};

template <typename Component>
class component_store
{
private:
	base::vector<component_store_entry<Component>> _ents;
	std::ptrdiff_t _next_free;
public:
	component_store(void)
	noexcept
	 : _next_free(-1)
	{ }

	Component* access(std::size_t pos)
	{
		if(pos >= _ents.size()) return nullptr;
		return &_ents[pos].rw();
	}

	const Component* access(std::size_t pos) const
	{
		if(pos >= _ents.size()) return nullptr;
		return &_ents[pos].ro();
	}

	void reserve(std::size_t size)
	{
		_ents.reserve(size);
	}

	std::size_t insert(Component&& component)
	{
		std::size_t pos;
		if(_next_free >= 0)
		{
			pos = std::size_t(_next_free);
			assert(pos < _ents.size());
			_next_free = _ents[pos].store(std::move(component));
		}
		else
		{
			pos = _ents.size();
			_ents.emplace_back(std::move(component));
		}
		return pos;
	}

	std::size_t replace(std::size_t pos, Component&& component)
	{
		assert(pos < _ents.size());
		_ents[pos].rw() = std::move(component);
		return pos;
	}

	std::size_t copy(std::size_t pos)
	{
		assert(pos < _ents.size());
		return insert(Component(_ents[pos].ro()));
	}

	void add_ref(std::size_t pos)
	{
		assert(pos < _ents.size());
		_ents[pos].add_ref();
	}

	bool release(std::size_t pos)
	{
		assert(pos < _ents.size());
		if(_ents[pos].rem_ref())
		{
			_ents[pos].release();

			assert((_next_free >= 0) || (_next_free == -1));
			_ents[pos].mark_free(_next_free);
			_next_free = std::ptrdiff_t(pos);
			return true;
		}
		return false;
	}
};

} // namespace ecs
} // namespace EAGine

#endif //include guard

