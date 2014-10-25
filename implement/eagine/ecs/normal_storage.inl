/**
 *  @file eagine/ecs/normal_storage.inl
 *  @brief Implementation normal_component_storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

namespace EAGine {
namespace ecs {
//------------------------------------------------------------------------------
// normal_storage_iterator::set
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_storage_iterator<Entity>::
set(std::size_t pos)
{
	_pos = pos;
}
//------------------------------------------------------------------------------
// normal_storage_iterator::reset
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_storage_iterator<Entity>::
reset(void)
{
	set(0);
}
//------------------------------------------------------------------------------
// normal_storage_iterator::done
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_storage_iterator<Entity>::
done(void)
{
	return _pos >= _storage._index.size();
}
//------------------------------------------------------------------------------
// normal_storage_iterator::next
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_storage_iterator<Entity>::
next(void)
{
	assert(!done());
	++_pos;
}
//------------------------------------------------------------------------------
// normal_storage_iterator::current
//------------------------------------------------------------------------------
template <typename Entity>
inline
const Entity&
normal_storage_iterator<Entity>::
current(void)
{
	assert(!done());
	return _storage._index.key_at(_pos);
}
//------------------------------------------------------------------------------
// normal_base_storage::traits
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_traits
normal_base_storage<Entity>::
traits(void) const
{
	return	//storage_bits::can_hide| // TODO or decorator?
		storage_bits::can_copy|
		storage_bits::can_swap|
		storage_bits::can_store|
		storage_bits::can_fetch|
		storage_bits::can_modify|
		storage_bits::can_remove|
		storage_bits::can_reserve|
		storage_bits::can_point_to;
}
//------------------------------------------------------------------------------
// normal_base_storage::new_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_iterator<Entity>*
normal_base_storage<Entity>::
new_iterator(void)
{
	if(_iter_taken)
	{
		return new _ns_iter_t(*this);
	}
	else
	{
		_iter_taken = true;
		_iter.reset();
		return &_iter;
	}
}
//------------------------------------------------------------------------------
// normal_base_storage::delete_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_base_storage<Entity>::
delete_iterator(iter_t* iter)
{
	assert(dynamic_cast<_ns_iter_t*>(iter));
	if(iter == &_iter)
	{
		_iter_taken = false;
	}
	else delete *iter;
}
//------------------------------------------------------------------------------
// normal_base_storage::has
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_base_storage<Entity>::
has(const Entity& ent)
{
	return _index.contains(ent);
}
//------------------------------------------------------------------------------
// normal_base_storage::find
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_base_storage<Entity>::
find(const Entity& ent, iter_t& pos)
{
	auto epos = _index.pos_of(ent);

	if(epos < 0) return false;

	assert(dynamic_cast<_ns_iter_t*>(&pos));

	_ns_iter_t* iter = static_cast<_ns_iter_t*>(&pos);
	iter->set(epos);
	return true;
}
//------------------------------------------------------------------------------
// normal_base_storage::hide
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_base_storage<Entity>::
hide(const Entity& ent, iter_t* pos)
{
	assert(!"Hiding currently not supported!"); // TODO
}
//------------------------------------------------------------------------------
// normal_base_storage::show
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_base_storage<Entity>::
show(const Entity& ent, iter_t* pos)
{
	assert(!"Showing currently not supported!"); // TODO
}
//------------------------------------------------------------------------------
// normal_base_storage::swap
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
normal_base_storage<Entity>::
swap(const Entity& e1, const Entity& e2)
{
	_index.swap(e1, e2);
}
//------------------------------------------------------------------------------
// normal_component_storage::reserve
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
normal_component_storage<Entity, Component>::
reserve(std::size_t count)
{
	this->_index.reserve(count);
	// TODO
}
//------------------------------------------------------------------------------
// normal_component_storage::store
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
storage_iterator<Entity>*
normal_component_storage<Entity, Component>::
store(Component&& src, const Entity& ent, iter_t* pos, iter_t* res)
{
	// TODO
}
//------------------------------------------------------------------------------
// normal_component_storage::copy
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
storage_iterator<Entity>*
normal_component_storage<Entity, Component>::
copy(const Entity& to, const Entity& from, iter_t* pos, iter_t* res)
{
	// TODO
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace EAGine


