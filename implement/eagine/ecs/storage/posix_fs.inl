/**
 *  @file eagine/ecs/posix_fs_storage.inl
 *  @brief Implementation posix_fs_component_storage
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <eagine/ecs/entity.hpp>

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/error.hpp>
#include <sys/stat.h>
#include <cerrno>
#endif

#include <cstdio>
#include <unistd.h>

namespace eagine {
namespace ecs {
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_scandir_fail(int ec, const base::cstrref& path)
{
	assert(path.null_terminated());

	using namespace base;
	throw system_error(std::error_code(ec, std::system_category()), (
		format(translate(
			"POSIX filesystem component storage failed "
			"to scan directory '{1}'."
		)) % path.data()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_stat_fail(int ec, const base::cstrref& path)
{
	assert(path.null_terminated());

	using namespace base;
	throw system_error(std::error_code(ec, std::system_category()), (
		format(translate(
			"POSIX filesystem component storage failed "
			"to stat directory entry '{1}'."
		)) % path.data()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_store_fail(const base::string& s)
{
	using namespace base;
	throw runtime_error((
		format(translate(
			"POSIX filesystem component storage failed "
			"to store component for entity '{1}'."
		)) % s.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_fetch_fail(const base::string& s)
{
	using namespace base;
	throw runtime_error((
		format(translate(
			"POSIX filesystem component storage failed "
			"to fetch component for entity '{1}'."
		)) % s.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_swap_fail(const base::string& f, const base::string& t)
{
	using namespace base;
	throw runtime_error((
		format(translate(
			"POSIX filesystem component storage failed "
			"to swap component between entity '{1}' and '{2}'."
		)) % f.c_str() % t.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_copy_fail(const base::string& f, const base::string& t)
{
	using namespace base;
	throw runtime_error((
		format(translate(
			"POSIX filesystem component storage failed "
			"to copy component from entity '{1}' to '{2}'."
		)) % f.c_str() % t.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_handle_rmv_fail(const base::string& path)
{
	using namespace base;
	throw runtime_error((
		format(translate(
			"POSIX filesystem component storage failed "
			"to remove component from entity '{1}'."
		)) % path.c_str()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_do_move(const base::cstrref& f, const base::cstrref& t)
{
	assert(f.null_terminated());
	assert(t.null_terminated());

	int ec = ::std::rename(f.data(), t.data());

	if(ec == 0) return;

	using namespace base;
	throw system_error(std::error_code(ec, std::system_category()), (
		format(translate(
			"POSIX filesystem component storage failed "
			"to rename file '{1}' to '{2}'."
		)) % f.data() % t.data()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
int posix_fs_stg_do_copy_file(::FILE* src, ::FILE* dst)
{
	int ec = 0;
	char buf[BUFSIZ];
	std::size_t size;
	while(std::feof(src) == 0)
	{
		size = std::fread(buf, 1, BUFSIZ, src);
		ec = std::ferror(src);
		if(ec) return ec;

		std::fwrite(buf, 1, size, dst);
		ec = std::ferror(dst);
		if(ec) return ec;
	}
	return 0;
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_do_copy(const base::cstrref& f, const base::cstrref& t)
{
	assert(f.null_terminated());
	assert(t.null_terminated());

	typedef base::unique_ptr< ::FILE, int (*)(::FILE*)> safe_FILE;
	safe_FILE src(std::fopen(f.data(), "rb"), &std::fclose);
	safe_FILE dst(std::fopen(t.data(), "wb"), &std::fclose);

	int ec = posix_fs_stg_do_copy_file(src.get(), dst.get());
	if(ec == 0) return;

	using namespace base;
	throw system_error(std::error_code(ec, std::system_category()), (
		format(translate(
			"POSIX filesystem component storage failed "
			"to copy file '{1}' to '{2}'."
		)) % f.data() % t.data()
	).str());
}
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void posix_fs_stg_do_swap(const base::cstrref& p1, const base::cstrref& p2)
{
	assert(p1.null_terminated());
	assert(p2.null_terminated());

	typedef base::unique_ptr< ::FILE, int (*)(::FILE*)> safe_FILE;
	safe_FILE fp1(std::fopen(p1.data(), "rb"), &std::fclose);
	safe_FILE fp2(std::fopen(p2.data(), "rb"), &std::fclose);
	safe_FILE tmp(std::tmpfile(), &std::fclose);

	int ec = posix_fs_stg_do_copy_file(fp1.get(), tmp.get());
	if(ec == 0)
	{
		std::freopen(p1.data(), "wb", fp1.get());
		ec = posix_fs_stg_do_copy_file(fp2.get(), fp1.get());
		if(ec == 0)
		{
			std::freopen(p2.data(), "wb", fp2.get());
			std::rewind(tmp.get());
			ec = posix_fs_stg_do_copy_file(tmp.get(), fp2.get());
			if(ec == 0) return;
		}
	}

	using namespace base;
	throw system_error(std::error_code(ec, std::system_category()), (
		format(translate(
			"POSIX filesystem component storage failed "
			"to swap files '{1}' and '{2}'."
		)) % p1.data() % p2.data()
	).str());
}
//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
void posix_fs_stg_handle_scandir_fail(int ec, const base::cstrref& path);
void posix_fs_stg_handle_stat_fail(int ec, const base::cstrref& path);
void posix_fs_stg_handle_store_fail(const base::string& s);
void posix_fs_stg_handle_fetch_fail(const base::string& s);
void posix_fs_stg_handle_swap_fail(const base::string& f, const base::string& t);
void posix_fs_stg_handle_copy_fail(const base::string& f, const base::string& t);
void posix_fs_stg_handle_rmv_fail(const base::string& s);
void posix_fs_stg_do_move(const base::cstrref& f, const base::cstrref& t);
void posix_fs_stg_do_copy(const base::cstrref& f, const base::cstrref& t);
void posix_fs_stg_do_swap(const base::cstrref& p1, const base::cstrref& p2);
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
 , _de_pos(0)
 , _de_count(-1)
 , _de_list(nullptr)
{ }
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::posix_fs_storage_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
posix_fs_storage_iterator<Entity>::
posix_fs_storage_iterator(posix_fs_storage_iterator&& tmp)
 : _storage(tmp._storage)
 , _de_pos(tmp._de_pos)
 , _de_count(tmp._de_count)
 , _de_list(tmp._de_list)
{
	tmp._de_count = -1;
	tmp._de_list = nullptr;
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::~posix_fs_storage_iterator
//------------------------------------------------------------------------------
template <typename Entity>
inline
posix_fs_storage_iterator<Entity>::
~posix_fs_storage_iterator(void)
{
	if(_de_list)
	{
		for(int i=0; i<_de_count; ++i)
		{
			::free((void*)_de_list[i]);
		}
		::free((void*)_de_list);
	}
}
//------------------------------------------------------------------------------
// _posix_fs_storage_iterator_get_name
//------------------------------------------------------------------------------
static inline
base::cstrref
_posix_fs_storage_iterator_get_name(const ::dirent* de)
{
#ifdef _DIRENT_HAVE_D_NAMLEN
	return base::cstrref(de->d_name, de->d_namlen);
#else
	return base::cstrref(de->d_name);
#endif
}
//------------------------------------------------------------------------------
// _posix_fs_storage_iterator_filter
//------------------------------------------------------------------------------
template <typename Entity>
static inline
int
_posix_fs_storage_iterator_filter(const ::dirent* de)
{
#ifdef _DIRENT_HAVE_D_TYPE
	if((de->d_type != DT_REG) && (de->d_type != DT_LNK))
	{
		return 0;
	}
#endif
	return entity_traits<Entity>::is_valid_string(
		_posix_fs_storage_iterator_get_name(de)
	)?1:0;
}
//------------------------------------------------------------------------------
// _posix_fs_storage_iterator_compare
//------------------------------------------------------------------------------
template <typename Entity>
static inline
int
_posix_fs_storage_iterator_compare(const ::dirent** a, const ::dirent** b)
{
	Entity ea(entity_traits<Entity>::from_string(
		_posix_fs_storage_iterator_get_name(*a)
	));
	Entity eb(entity_traits<Entity>::from_string(
		_posix_fs_storage_iterator_get_name(*b)
	));

	if(ea == eb) return 0;
	if(ea < eb) return -1;
	return 1;
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::_init
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
_init(bool force_rewind)
{
	if(_de_count < 0)
	{
		_de_count = ::scandir(
			_storage._prefix.c_str(),
			&_de_list,
			&_posix_fs_storage_iterator_filter<Entity>,
			&_posix_fs_storage_iterator_compare<Entity>
		);
		if(_de_count < 0)
		{
			detail::posix_fs_stg_handle_scandir_fail(
				errno,
				_storage._prefix
			);
			force_rewind = false;
		}
		else
		{
			force_rewind = true;
		}
	}
	if(force_rewind)
	{
		_de_pos = 0;
		_skip();
	}
}
//------------------------------------------------------------------------------
// posix_fs_storage_iterator::_skip
//------------------------------------------------------------------------------
template <typename Entity>
inline
void
posix_fs_storage_iterator<Entity>::
_skip(void)
{
	while(_de_pos < _de_count)
	{
		auto path =
			_storage._prefix+
			_posix_fs_storage_iterator_get_name(_de_list[_de_pos]);

		struct ::stat fs;

		if(::stat(base::c_str(path), &fs) != 0)
		{
			detail::posix_fs_stg_handle_stat_fail(
				errno,
				path
			);
		}

		if(S_ISREG(fs.st_mode)) break;

		++_de_pos;
	}
	if(_de_pos < _de_count)
	{
		_ent = entity_traits<Entity>::from_string(
			_posix_fs_storage_iterator_get_name(_de_list[_de_pos])
		);
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
	_init(true);
	assert(_de_list != nullptr);
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
	_init();
	return _de_pos >= _de_count;
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
	_init();
	assert(!done());
	++_de_pos;
	_skip();
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
	_init();
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
typename posix_fs_base_storage<Entity>::_path_str_t
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
typename posix_fs_base_storage<Entity>::_path_str_t
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
_has_file(const base::cstrref& path)
{
	assert(path.null_terminated());
	return ::access(path.data(), F_OK) == 0;
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
	return _has_file(_get_path(ent));
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
	return	_has_file(_get_hdn_path(ent)) && !_has_file(_get_path(ent));
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
	auto p = _get_path(ent);
	auto ph = _get_hdn_path(ent);

	if(!_has_file(ph))
	{
		if(!_has_file(p))
		{
			return false;
		}
		detail::posix_fs_stg_do_move(p, ph);
		return true;
	}
	return false;
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
	auto p = _get_path(ent);
	auto ph = _get_hdn_path(ent);

	if(_has_file(ph))
	{
		detail::posix_fs_stg_do_move(ph, p);
		return true;
	}
	return false;
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
	auto p1 = _get_path(e1);
	auto p2 = _get_path(e2);

	if(_has_file(p1) && _has_file(p2))
	{
		detail::posix_fs_stg_do_swap(p1, p2);
	}
	else if(_has_file(p1))
	{
		detail::posix_fs_stg_do_move(p1, p2);
	}
	else if(_has_file(p2))
	{
		detail::posix_fs_stg_do_move(p2, p1);
	}
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
// posix_fs_component_storage::remove_if
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
remove_if(
	const base::functor_ref<
		bool(const Entity&, const Component&)
	>& predicate
)
{
	posix_fs_storage_iterator<Entity> iter(*this);
	while(!iter.done())
	{
		Entity ent = iter.current();
		Component tmp;
		if(this->fetch(tmp, ent, &iter))
		{
			if(predicate(ent, tmp))
			{
				this->remove(ent, &iter);
			}
		}
		iter.next();
	}
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::store
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
store(Component&& src, const Entity& ent, iter_t*, iter_t*)
{
	assert(_cmp_io);

	auto p = this->_get_path(ent);

	if(!_cmp_io->write(p, src))
	{
		detail::posix_fs_stg_handle_store_fail(
			entity_traits<Entity>::to_string(ent)
		);
	}
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
	auto pf = this->_get_path(from);

	if(this->_has_file(pf))
	{
		auto pt = this->_get_path(to);
		detail::posix_fs_stg_do_copy(pf, pt);
		return true;
	}
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
	auto p = this->_get_path(ent);

	if(!this->_has_file(p))
	{
		return false;
	}
	if(::std::remove(p.c_str()) != 0)
	{
		detail::posix_fs_stg_handle_rmv_fail(
			entity_traits<Entity>::to_string(ent)
		);
	}
	return true;
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
_fetch(Component& dst, const Entity& ent, iter_t* pos, meta::true_type)
{
	assert(_cmp_io);

	auto p = this->_get_path(ent);

	if(!this->_has_file(p))
	{
		return false;
	}
	if(!_cmp_io->read(p, dst))
	{
		detail::posix_fs_stg_handle_fetch_fail(
			entity_traits<Entity>::to_string(ent)
		);
	}
	return true;
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
// posix_fs_component_storage::_for_each
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
// _posix_fs_component_storage_pfe_adaptor
//------------------------------------------------------------------------------
template <typename Entity, typename Component, typename Func, typename IsConst>
struct _posix_fs_component_storage_pfe_adaptor
{
	posix_fs_component_storage<Entity, Component>& _storage;
	posix_fs_storage_iterator<Entity> _iter;
	Func _func;
	std::size_t _prev;

	_posix_fs_component_storage_pfe_adaptor(
		posix_fs_component_storage<Entity, Component>& storage,
		const Func& func
	): _storage(storage)
	 , _iter(_storage)
	 , _func(func)
	 , _prev(0)
	{ }

	_posix_fs_component_storage_pfe_adaptor(
		const _posix_fs_component_storage_pfe_adaptor& that
	): _storage(that._storage)
	 , _iter(_storage)
	 , _func(that._func)
	 , _prev(that._prev)
	{ }

	bool operator()(std::size_t curr)
	{
		while(_prev < curr)
		{
			if(_iter.done())
			{
				return false;
			}
			_iter.next();
			++_prev;
		}
		_storage._for_single(
			_func,
			_iter.current(),
			&_iter,
			IsConst()
		);
		return true;
	}
};
//------------------------------------------------------------------------------
// posix_fs_component_storage::_parallel_for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
template <typename Func, typename IsConst>
inline
void
posix_fs_component_storage<Entity, Component>::
_parallel_for_each(
	const Func& func,
	base::parallelizer& prlzr,
	base::execution_params& param,
	IsConst
)
{
	_posix_fs_component_storage_pfe_adaptor<
		Entity,
		Component,
		Func,
		IsConst
	> adaptor(*this, func);

	prlzr.execute_stateful(adaptor, param).wait();
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::parallel_for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
parallel_for_each(
	const base::functor_ref<
		void(const Entity&, const Component&)
	>& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	_parallel_for_each(func, prlzr, param, meta::true_type());
}
//------------------------------------------------------------------------------
// posix_fs_component_storage::parallel_for_each
//------------------------------------------------------------------------------
template <typename Entity, typename Component>
inline
void
posix_fs_component_storage<Entity, Component>::
parallel_for_each(
	const base::functor_ref<
		void(const Entity&, Component&)
	>& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	_parallel_for_each(func, prlzr, param, meta::false_type());
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace eagine


