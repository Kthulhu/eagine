/**
 *  @file eagine/ecs/storage/normal.inl
 *  @brief Implementation of normal_component_storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

namespace eagine {
namespace ecs {
//------------------------------------------------------------------------------
// normal_storage_iterator::get
//------------------------------------------------------------------------------
template <typename Entity>
inline
std::size_t
normal_storage_iterator<Entity>::
get(void) const
{
	return _pos;
}
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
	else delete iter;
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
// normal_base_storage::hidden
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_base_storage<Entity>::
hidden(const Entity& ent, iter_t* pos)
{
	return false;
}
//------------------------------------------------------------------------------
// normal_base_storage::hide
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_base_storage<Entity>::
hide(const Entity& ent, iter_t* pos)
{
	assert(!"Hiding is currently not supported!"); // TODO
	return false;
}
//------------------------------------------------------------------------------
// normal_base_storage::show
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
normal_base_storage<Entity>::
show(const Entity& ent, iter_t* pos)
{
	assert(!"Showing is currently not supported!"); // TODO
	return false;
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
// normal_component_storage
//------------------------------------------------------------------------------
// normal_component_storage::_nil_stor_pos
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
constexpr inline
std::size_t
normal_component_storage<Entity, Component>::
_nil_stor_pos(void)
{
	return ~(std::size_t(0));
}
//------------------------------------------------------------------------------
// normal_component_storage::_stor_pos
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
std::size_t
normal_component_storage<Entity, Component>::
_stor_pos(const Entity& ent, iter_t* pos)
{
	// position of the entity record in the index
	std::size_t res = _nil_stor_pos();

	// if we have an iterator
	if(pos)
	{
		assert(dynamic_cast<_ns_iter_t*>(pos));
		_ns_iter_t* iter = static_cast<_ns_iter_t*>(pos);
		res = iter->get();

		// if it does not point to the entity
		// we are looking for
		if(this->_index.key_at(res) != ent)
		{
			res = this->_index.get(ent, _nil_stor_pos());
		}
		else
		{
			res = this->_index.val_at(res);
		}
	}
	else
	{
		// try to get it from the index
		res = this->_index.get(ent, res);
	}
	return res;
}
//------------------------------------------------------------------------------
// normal_component_storage::_set_iter
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
normal_component_storage<Entity, Component>::
_set_iter(std::size_t spos, iter_t* pos)
{
	if(pos)
	{
		assert(dynamic_cast<_ns_iter_t*>(pos));
		_ns_iter_t* iter = static_cast<_ns_iter_t*>(pos);

		iter->set(spos);
	}
}
//------------------------------------------------------------------------------
// normal_component_storage::capabilities
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
storage_capabilities
normal_component_storage<Entity, Component>::
capabilities(void) const
{
	//storage_capability::hide| TODO or decorator?
	storage_capabilities caps = 
		storage_capability::find|
		storage_capability::copy|
		storage_capability::swap|
		storage_capability::store|
		storage_capability::modify|
		storage_capability::remove|
		storage_capability::reserve|
		storage_capability::point_to;

	if(meta::is_copy_assignable<Component>())
	{
		return caps | storage_capability::fetch;
	}
	return caps;
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
	this->_store.reserve(count);
}
//------------------------------------------------------------------------------
// normal_component_storage::store
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
normal_component_storage<Entity, Component>::
store(Component&& src, const Entity& ent, iter_t* pos, iter_t* res)
{
	std::size_t spos = _stor_pos(ent, pos);

	// if we don't have this entity on record yet
	if(spos == _nil_stor_pos())
	{
		// insert the component
		spos = this->_store.insert(std::move(src));
		// and store it's position in the index
		this->_index.store(ent, spos, 0);
	}
	else
	{
		// otherwise replace the component
		this->_store.replace(spos, std::move(src));
	}

	_set_iter(spos, res);
}
//------------------------------------------------------------------------------
// normal_component_storage::copy
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
copy(const Entity& to, const Entity& from, iter_t* pos, iter_t* res)
{
	std::size_t spos = _stor_pos(from, pos);

	if(spos != _nil_stor_pos())
	{
		store(this->_store.copy(spos), to, nullptr, res);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::remove
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
remove(const Entity& from, iter_t* pos)
{
	// position of the entity record in the index
	std::size_t idx = this->_index.size();

	// if we have an iterator
	if(pos)
	{
		assert(dynamic_cast<_ns_iter_t*>(pos));
		_ns_iter_t* iter = static_cast<_ns_iter_t*>(pos);
		std::size_t tmp = iter->get();

		// if it does not point to the entity
		// we are looking for
		if(this->_index.key_at(tmp) == from)
		{
			idx = tmp;
		}
	}

	std::size_t spos = this->_index.remove(idx, from, _nil_stor_pos());

	if(spos != _nil_stor_pos())
	{
		this->_store.release(spos);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::read
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
const Component*
normal_component_storage<Entity, Component>::
read(const Entity& ent, iter_t* pos)
{
	std::size_t spos = _stor_pos(ent, pos);

	if(spos != _nil_stor_pos())
	{
		return this->_store.read(spos);
	}
	return nullptr;
}
//------------------------------------------------------------------------------
// normal_component_storage::write
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
Component*
normal_component_storage<Entity, Component>::
write(const Entity& ent, iter_t* pos)
{
	std::size_t spos = _stor_pos(ent, pos);

	if(spos != _nil_stor_pos())
	{
		return this->_store.write(spos);
	}
	return nullptr;
}
//------------------------------------------------------------------------------
// normal_component_storage::_fetch - copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::true_type)
{
	std::size_t spos = _stor_pos(ent, pos);

	if(spos != _nil_stor_pos())
	{
		dst = this->_store.copy(spos);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::_fetch - non copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::false_type)
{
	assert(!"Fetching non assignable components is not supported!");
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::fetch
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
fetch(Component& dst, const Entity& ent, iter_t* pos)
{
	return _fetch(
		dst, ent, pos,
		typename meta::is_copy_assignable<Component>::type()
	);
}
//------------------------------------------------------------------------------
// normal_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
for_single(
	const base::functor_ref<
		void(const Entity&, const Component&)
	>& func,
	const Entity& ent,
	iter_t* pos
)
{
	if(const Component* cptr = this->read(ent, pos))
	{
		func(ent, *cptr);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
normal_component_storage<Entity, Component>::
for_single(
	const base::functor_ref<
		void(const Entity&, Component&)
	>& func,
	const Entity& ent,
	iter_t* pos
)
{
	if(Component* cptr = this->write(ent, pos))
	{
		func(ent, *cptr);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// normal_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
normal_component_storage<Entity, Component>::
for_each(const base::functor_ref<void(const Entity&, const Component&) >& func)
{
	auto adaptor = [this, &func](
		const Entity& ent,
		std::size_t spos
	) -> void
	{
		const Component* cptr = this->_store.read(spos);
		assert(cptr);
		func(ent, *cptr);
	};
	this->_index.for_each(adaptor);
}
//------------------------------------------------------------------------------
// normal_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
normal_component_storage<Entity, Component>::
for_each(const base::functor_ref<void(const Entity&, Component&)>& func)
{
	auto adaptor = [this, &func](
		const Entity& ent,
		std::size_t spos
	) -> void
	{
		Component* cptr = this->_store.write(spos);
		assert(cptr);
		func(ent, *cptr);
	};
	this->_index.for_each(adaptor);
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace eagine


