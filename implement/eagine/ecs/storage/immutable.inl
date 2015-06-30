/**
 *  @file eagine/ecs/storage/immutable.inl
 *  @brief Implementation of immutable_component_storage
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <eagine/base/assert.hpp>

namespace eagine {
namespace ecs {
//------------------------------------------------------------------------------
// immutable_storage_iterator::immutable_storage_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
immutable_storage_iterator<Entity>::
immutable_storage_iterator(immutable_base_storage<Entity>& storage)
 : _storage(storage)
 , _idx(0)
{ }
//------------------------------------------------------------------------------
// immutable_storage_iterator::get
//------------------------------------------------------------------------------
template <typename Entity>
inline
std::size_t
immutable_storage_iterator<Entity>::
get(void) const
{
	return _idx;
}
//------------------------------------------------------------------------------
// immutable_storage_iterator::set
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
immutable_storage_iterator<Entity>::
set(std::size_t idx)
{
	_idx = idx;
}
//------------------------------------------------------------------------------
// immutable_storage_iterator::reset
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
immutable_storage_iterator<Entity>::
reset(void)
{
	_idx = 0;
}
//------------------------------------------------------------------------------
// immutable_storage_iterator::done
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_storage_iterator<Entity>::
done(void)
{
	return _idx >= _storage._entities.size();
}
//------------------------------------------------------------------------------
// immutable_storage_iterator::next
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
immutable_storage_iterator<Entity>::
next(void)
{
	assert(!done());
	++_idx;
}
//------------------------------------------------------------------------------
// immutable_storage_iterator::current
//------------------------------------------------------------------------------
template <typename Entity>
inline
const Entity&
immutable_storage_iterator<Entity>::
current(void)
{
	assert(!done());
	return _storage._entities.at(_idx);
}
//------------------------------------------------------------------------------
// immutable_base_storage::_ib
//------------------------------------------------------------------------------
template <typename Entity>
inline
const typename immutable_base_storage<Entity>::_info_block&
immutable_base_storage<Entity>::
_ib(const base::const_memory_block& block)
{
	assert(!block.empty());
	assert(block.addr());
	return *static_cast<const _info_block*>(block.addr());
}
//------------------------------------------------------------------------------
// immutable_base_storage::immutable_base_storage
//------------------------------------------------------------------------------
template <typename Entity>
inline
immutable_base_storage<Entity>::
immutable_base_storage(const base::const_memory_block& block)
 : _entities(_ib(block)._ent_addr.get(), _ib(block)._ent_count)
 , _keys(_ib(block)._key_addr.get(), _ib(block)._key_count)
 , _component_data(_ib(block)._cmp_addr.get(), _ib(block)._cmp_size)
 , _index(_entities.begin(), _entities.end(), _keys.begin(), _keys.end())
 , _iter(*this)
 , _iter_taken(false)
{ }
//------------------------------------------------------------------------------
// immutable_base_storage::new_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_iterator<Entity>*
immutable_base_storage<Entity>::
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
// immutable_base_storage::clone_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_iterator<Entity>*
immutable_base_storage<Entity>::
clone_iterator(storage_iterator<Entity>* iter)
{
	assert(dynamic_cast<_ns_iter_t*>(iter));
	return new _ns_iter_t(*static_cast<_ns_iter_t*>(iter));
}
//------------------------------------------------------------------------------
// immutable_base_storage::delete_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
immutable_base_storage<Entity>::
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
// immutable_base_storage::has
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_base_storage<Entity>::
has(const Entity& ent)
{
	return _index.contains(ent);
}
//------------------------------------------------------------------------------
// immutable_base_storage::find
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_base_storage<Entity>::
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
// immutable_base_storage::hidden
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_base_storage<Entity>::
hidden(const Entity& ent, iter_t* pos)
{
	return false;
}
//------------------------------------------------------------------------------
// immutable_base_storage::hide
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_base_storage<Entity>::
hide(const Entity& ent, iter_t* pos)
{
	EAGINE_ABORT("Hiding is currently not supported!"); // TODO
	return false;
}
//------------------------------------------------------------------------------
// immutable_base_storage::show
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
immutable_base_storage<Entity>::
show(const Entity& ent, iter_t* pos)
{
	EAGINE_ABORT("Showing is currently not supported!"); // TODO
	return false;
}
//------------------------------------------------------------------------------
// immutable_base_storage::swap
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
immutable_base_storage<Entity>::
swap(const Entity& e1, const Entity& e2)
{
	EAGINE_ABORT("Swap is not supported by this component storage!");
}
//------------------------------------------------------------------------------
// immutable_component_storage
//------------------------------------------------------------------------------
// immutable_component_storage::_nil_stor_pos
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
constexpr inline
std::size_t
immutable_component_storage<Entity, Component>::
_nil_stor_pos(void)
{
	return ~(std::size_t(0));
}
//------------------------------------------------------------------------------
// immutable_component_storage::_stor_pos
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
std::size_t
immutable_component_storage<Entity, Component>::
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
// immutable_component_storage::immutable_component_storage
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
immutable_component_storage<Entity, Component>::
immutable_component_storage(const base::const_memory_block& block)
 : immutable_base_storage<Entity>(block)
{
}
//------------------------------------------------------------------------------
// immutable_component_storage::capabilities
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
storage_capabilities
immutable_component_storage<Entity, Component>::
capabilities(void) const
{
	//storage_capability::hide| TODO or decorator?
	storage_capabilities caps = 
		storage_capability::find|
		storage_capability::point_to;

	if(meta::is_copy_assignable<Component>())
	{
		return caps | storage_capability::fetch;
	}
	return caps;
}
//------------------------------------------------------------------------------
// immutable_component_storage::reserve
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
reserve(std::size_t)
{
	EAGINE_ABORT("Reserve is not supported by this component storage!");
}
//------------------------------------------------------------------------------
// immutable_component_storage::remove_if
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
remove_if(
	const base::callable_ref<
		bool(const Entity&, const Component&)
	>&
)
{
	EAGINE_ABORT("Remove-if is not supported by this component storage!");
}
//------------------------------------------------------------------------------
// immutable_component_storage::store
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
store(Component&&, const Entity&, iter_t*, iter_t*)
{
	EAGINE_ABORT("Store is not supported by this component storage!");
}
//------------------------------------------------------------------------------
// immutable_component_storage::copy
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
copy(const Entity&, const Entity&, iter_t*, iter_t*)
{
	EAGINE_ABORT("Copy is not supported by this component storage!");
	return false;
}
//------------------------------------------------------------------------------
// immutable_component_storage::remove
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
remove(const Entity&, iter_t*)
{
	EAGINE_ABORT("Remove is not supported by this component storage!");
	return false;
}
//------------------------------------------------------------------------------
// immutable_component_storage::read
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
const Component*
immutable_component_storage<Entity, Component>::
read(const Entity& ent, iter_t* pos)
{
	std::size_t spos = _stor_pos(ent, pos);

	if(spos != _nil_stor_pos())
	{
		return static_cast<const Component*>(
			this->_component_data.offs(spos)
		);
	}
	return nullptr;
}
//------------------------------------------------------------------------------
// immutable_component_storage::write
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
Component*
immutable_component_storage<Entity, Component>::
write(const Entity& ent, iter_t* pos)
{
	EAGINE_ABORT("Write is not supported by this component storage!");
	return nullptr;
}
//------------------------------------------------------------------------------
// immutable_component_storage::_fetch - copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::true_type)
{
	std::size_t spos = _stor_pos(ent, pos);

	if(spos != _nil_stor_pos())
	{
		dst = *static_cast<const Component*>(
			this->_component_data.offs(spos)
		);
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// immutable_component_storage::_fetch - non copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::false_type)
{
	EAGINE_ABORT("Fetching non assignable components is not supported!");
	return false;
}
//------------------------------------------------------------------------------
// immutable_component_storage::fetch
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
fetch(Component& dst, const Entity& ent, iter_t* pos)
{
	return _fetch(
		dst, ent, pos,
		typename meta::is_copy_assignable<Component>::type()
	);
}
//------------------------------------------------------------------------------
// immutable_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
for_single(
	const base::callable_ref<
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
// immutable_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
immutable_component_storage<Entity, Component>::
for_single(
	const base::callable_ref<
		void(const Entity&, Component&)
	>& func,
	const Entity& ent,
	iter_t* pos
)
{
	EAGINE_ABORT("for_single with non const components is not supported!");
	return false;
}
//------------------------------------------------------------------------------
// immutable_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
for_each(const base::callable_ref<void(const Entity&, const Component&) >& func)
{
	auto adaptor = [this, &func](
		const Entity& ent,
		std::size_t spos
	) -> void
	{
		const Component* cptr =
			static_cast<const Component*>(
				this->_component_data.offs(spos)
			);
		assert(cptr);
		func(ent, *cptr);
	};
	this->_index.for_each(adaptor);
}
//------------------------------------------------------------------------------
// immutable_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
for_each(const base::callable_ref<void(const Entity&, Component&)>& func)
{
	EAGINE_ABORT("for_each with non const components is not supported!");
}
//------------------------------------------------------------------------------
// immutable_component_storage::parallel_for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
parallel_for_each(
	const base::callable_ref<
		void(const Entity&, const Component&)
	>& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	auto adaptor = [this, &func](
		const Entity& ent,
		std::size_t spos
	) -> void
	{
		const Component* cptr =
			static_cast<const Component*>(
				this->_component_data.offs(spos)
			);
		assert(cptr);
		func(ent, *cptr);
	};
	this->_index.parallel_for_each(adaptor, prlzr, param);
}
//------------------------------------------------------------------------------
// immutable_component_storage::parallel_for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
immutable_component_storage<Entity, Component>::
parallel_for_each(
	const base::callable_ref<
		void(const Entity&, Component&)
	>& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	EAGINE_ABORT(
		"parallel_for_each with non const "
		"components is not supported!"
	);
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace eagine


