/**
 *  @file eagine/ecs/posix_fs_storage.inl
 *  @brief Implementation posix_fs_component_storage
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/error.hpp>
#include <cerrno>
#endif

#include <cstdio>
#include <unistd.h>

namespace EAGine {
namespace ecs {
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_opendir_fail(int ec, const base::string& path)
{
	using namespace base;
	throw system_error(std::error_code(errno, std::system_category()), (
		format(translate(
			"POSIX Filesystem component storage failed "
			"to open directory '{1}'."
		)) % path.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_readdir_fail(int ec, const base::string& path)
{
	using namespace base;
	throw system_error(std::error_code(errno, std::system_category()), (
		format(translate(
			"POSIX Filesystem component storage failed "
			"to read directory '{1}'."
		)) % path.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_readdir_fail(int ec)
{
	using namespace base;
	throw system_error(std::error_code(errno, std::system_category()),
		translate(
			"POSIX Filesystem component storage failed "
			"to read directory."
		)
	);
}
//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
void posix_fs_stg_handle_opendir_fail(int ec, const base::string& path);
void posix_fs_stg_handle_readdir_fail(int ec, const base::string& path);
void posix_fs_stg_handle_readdir_fail(int ec);
//------------------------------------------------------------------------------
#endif // LIBRARY
//------------------------------------------------------------------------------
} // namespace detail
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::posix_fs_storage_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
posix_fs_storage_iterator<Entity>::
posix_fs_storage_iterator(posix_fs_base_storage<Entity>& storage)
 : _storage(storage)
 , _dir(::opendir(_storage._prefix.c_str()))
 , _cur_de(nullptr)
{
	if(!_dir)
	{
		detail::posix_fs_stg_handle_opendir_fail(
			errno,
			_storage._prefix
		);
	}
	
	advance();
	skip();
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::get
//------------------------------------------------------------------------------
template <typename Entity>
inline
base::cstrref
posix_fs_storage_iterator<Entity>::
get_name(void)
{
#ifdef _DIRENT_HAVE_D_NAMLEN
	return base::cstrref(
		_pdirent()->d_name,
		_pdirent()->d_namlen
	);
#else
	return base::cstrref(_pdirent()->d_name);
#endif
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::advance
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
advance(void)
{
	if(::readdir_r(_dir, _pdirent(), &_cur_de) != 0)
	{
		detail::posix_fs_stg_handle_readdir_fail(
			errno,
			_storage._prefix
		);
	}
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::skip
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
skip(void)
{
	assert(_dir);
	while(_cur_de)
	{
#ifdef _DIRENT_HAVE_D_TYPE
		if(_cur_de->d_type == DT_REG)
		{
			if(entity_traits<Entity>::is_valid_string(
				base::cstrref(_cur_de->d_name)
			))
			{
				_ent = entity_traits<Entity>::
					from_string(_cur_de->d_name);
				break;
			}
		}
		// TODO symlinks
#else
		// TODO lstat
		static_assert(false, "dirent::d_type is required!");
#endif
		advance();
	}
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::reset
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
reset(void)
{
	assert(_dir);
	::rewinddir(_dir);
	
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::done
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_storage_iterator<Entity>::
done(void)
{
	return _cur_de == nullptr;
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::next
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
next(void)
{
	assert(!done());
	advance();
	skip();
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::current
//------------------------------------------------------------------------------
template <typename Entity>
inline
const Entity&
posix_fs_storage_iterator<Entity>::
current(void)
{
	assert(!done());
	return _ent;
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::new_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_iterator<Entity>*
posix_fs_base_storage<Entity>::
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
// posix_fs_base_storage::delete_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_base_storage<Entity>::
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
// posix_fs_base_storage::_get_path
//------------------------------------------------------------------------------
template <typename Entity>
inline
base::string
posix_fs_base_storage<Entity>::
_get_path(const Entity& ent) const
{
	// TODO custom allocator
	return _prefix+entity_traits<Entity>::to_string(ent);
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::_get_hdn_path
//------------------------------------------------------------------------------
template <typename Entity>
inline
base::string
posix_fs_base_storage<Entity>::
_get_hdn_path(const Entity& ent) const
{
	// TODO custom allocator
	return _prefix+"."+entity_traits<Entity>::to_string(ent);
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::has
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_base_storage<Entity>::
has(const Entity& ent)
{
	base::string filename =
		_prefix+
		entity_traits<Entity>::to_string(ent);

	return ::access(_get_path(ent).c_str(), F_OK) == 0;
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::find
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_base_storage<Entity>::
find(const Entity&, iter_t&)
{
	return false;
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::hidden
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_base_storage<Entity>::
hidden(const Entity& ent, iter_t*)
{
	return	(::access(_get_hdn_path(ent).c_str(), F_OK) == 0) &&
		(::access(_get_path(ent).c_str(), F_OK) != 0);
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::hide
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_base_storage<Entity>::
hide(const Entity& ent, iter_t* pos)
{
	if(!hidden(ent, pos))
	{
		if(!has(ent))
		{
			return false;
		}
		if(int ec = ::std::rename(
			_get_path(ent).c_str(),
			_get_hdn_path(ent).c_str()
		))
		{
			return false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::show
//------------------------------------------------------------------------------
template <typename Entity>
inline
bool
posix_fs_base_storage<Entity>::
show(const Entity& ent, iter_t* pos)
{
	if(hidden(ent, pos))
	{
		if(int ec = ::std::rename(
			_get_hdn_path(ent).c_str(),
			_get_path(ent).c_str()
		))
		{
			return false;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
// posix_fs_base_storage::swap
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_base_storage<Entity>::
swap(const Entity& e1, const Entity& e2)
{
	// TODO
}
//------------------------------------------------------------------------------
// posix_fs_component_storage
//------------------------------------------------------------------------------
// posix_fs_component_storage::_nil_stor_pos
//------------------------------------------------------------------------------
// posix_fs_component_storage::capabilities
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
storage_capabilities
posix_fs_component_storage<Entity, Component>::
capabilities(void) const
{
	storage_capabilities caps = 
		storage_capability::hide|
		storage_capability::copy|
		storage_capability::swap|
		storage_capability::store|
		storage_capability::modify|
		storage_capability::remove;

	if(meta::is_copy_assignable<Component>())
	{
		return caps | storage_capability::fetch;
	}
	return caps;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::reserve
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
reserve(std::size_t count)
{ }
//------------------------------------------------------------------------------
// posix_fs_component_storage::store
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
store(Component&& src, const Entity& ent, iter_t*, iter_t*)
{
	assert(_cmp_io);
	return _cmp_io->write(this->_get_path(ent), src);
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::copy
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
copy(const Entity& to, const Entity& from, iter_t*, iter_t*)
{
	// TODO
	return false;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::remove
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
remove(const Entity& ent, iter_t*)
{
	return ::std::remove(this->_get_path(ent).c_str()) == 0;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::read
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
const Component*
posix_fs_component_storage<Entity, Component>::
read(const Entity& ent, iter_t* pos)
{
	assert(!"Pointing to filesystem-stored components is not supported!");
	return nullptr;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::write
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
Component*
posix_fs_component_storage<Entity, Component>::
write(const Entity& ent, iter_t* pos)
{
	assert(!"Pointing to filesystem-stored components is not supported!");
	return nullptr;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::_fetch - copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t*, meta::true_type)
{
	assert(_cmp_io);
	return _cmp_io->read(this->_get_path(ent), dst);
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::_fetch - non copy assignable
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::false_type)
{
	assert(!"Fetching non assignable components is not supported!");
	return false;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::fetch
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
fetch(Component& dst, const Entity& ent, iter_t* pos)
{
	return _fetch(
		dst, ent, pos,
		typename meta::is_copy_assignable<Component>::type()
	);
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::_for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
template <typename Func, typename IsConst>
inline
bool
posix_fs_component_storage<Entity, Component>::
_for_single(const Func& func, const Entity& ent, iter_t* pos, IsConst)
{
	Component tmp;
	if(this->fetch(tmp, ent, pos))
	{
		func(ent, tmp);
		if(!IsConst())
		{
			this->store(std::move(tmp), ent, pos, nullptr);
		}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
for_single(
	const base::functor_ref<
		void(const Entity&, const Component&)
	>& func,
	const Entity& ent,
	iter_t* pos
)
{
	return _for_single(func, ent, pos, meta::true_type());
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::for_single
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
bool
posix_fs_component_storage<Entity, Component>::
for_single(
	const base::functor_ref<
		void(const Entity&, Component&)
	>& func,
	const Entity& ent,
	iter_t* pos
)
{
	return _for_single(func, ent, pos, meta::false_type());
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
template <typename Func, typename IsConst>
inline
void
posix_fs_component_storage<Entity, Component>::
_for_each(const Func& func, IsConst ic)
{
	posix_fs_storage_iterator<Entity> iter(*this);
	while(!iter.done())
	{
		_for_single(func, iter.current(), &iter, ic);
		iter.next();
	}
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
for_each(const base::functor_ref<void(const Entity&, const Component&) >& func)
{
	_for_each(func, meta::true_type());
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
for_each(const base::functor_ref<void(const Entity&, Component&)>& func)
{
	_for_each(func, meta::false_type());
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace EAGine


