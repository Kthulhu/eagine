/**
 *  @file eagine/ecs/manager.inl
 *  @brief Implementation of E/C manager
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>
#include <eagine/base/array.hpp>

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>
#include <eagine/base/error.hpp>
#endif

namespace eagine {
namespace ecs {
//------------------------------------------------------------------------------
namespace detail {
//------------------------------------------------------------------------------
#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
//------------------------------------------------------------------------------
// mgr_handle_cmp_is_reg
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void mgr_handle_cmp_is_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is already registered"))
		% c_name.c_str()
	).str());
}
//------------------------------------------------------------------------------
// mgr_handle_cmp_not_reg
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void mgr_handle_cmp_not_reg(const base::string& c_name)
{
	using namespace base;
	throw runtime_error((
		format(translate("Component type '{1}' is not registered"))
		% c_name.c_str()
	).str());
}
//------------------------------------------------------------------------------
#else
void mgr_handle_cmp_is_reg(const base::string&);
void mgr_handle_cmp_not_reg(const base::string&);
#endif
//------------------------------------------------------------------------------
} // namespace detail
//------------------------------------------------------------------------------
// manager::_find_storage
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
component_storage<Entity, Component>&
manager<Entity>::
_find_storage(void)
{
	auto p_storage = _storages.find(get_component_uid<Component>());

	typedef component_storage<Entity, Component> cs_t;
	cs_t* ct_storage = nullptr;

	if(p_storage != _storages.end())
	{
		auto& b_storage = *p_storage;
		if(b_storage)
		{
			ct_storage = dynamic_cast<cs_t*>(b_storage.get());
			assert(ct_storage);
		}
	}
	if(!ct_storage)
	{
		base::string(*get_name)(void) = _cmp_name_getter<Component>();
		detail::mgr_handle_cmp_not_reg(get_name());
		assert(!"Logic error!");
	}
	return *ct_storage;
}
//------------------------------------------------------------------------------
// manager::_do_reg_cmp_type
//------------------------------------------------------------------------------
template <typename Entity>
inline void
manager<Entity>::
_do_reg_cmp_type(
	const base::shared_ptr<base_storage<Entity>>& storage,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	assert(bool(storage));

	auto p_storage = _storages.find(cid);

	if(p_storage == _storages.end())
	{
		_storages[cid] = storage;
	}
	else
	{
		detail::mgr_handle_cmp_is_reg(get_name());
	}
}
//------------------------------------------------------------------------------
// manager::_do_unr_cmp_type
//------------------------------------------------------------------------------
template <typename Entity>
inline void
manager<Entity>::
_do_unr_cmp_type(
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		_storages.erase(p_storage);
	}
	else
	{
		detail::mgr_handle_cmp_not_reg(get_name());
	}
}
//------------------------------------------------------------------------------
// manager::_does_know_cmp_type
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_does_know_cmp_type(component_uid_t cid) const
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------------------------
// manager::_apply_on_base_stg
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Result, typename Func>
inline
Result
manager<Entity>::
_apply_on_base_stg(
	Result fallback,
	const Func& func,
	component_uid_t cid,
	base::string(*get_name)(void)
) const
{
	auto p_storage = _storages.find(cid);

	if(p_storage != _storages.end())
	{
		auto& bs_storage = *p_storage;
		if(bs_storage)
		{
			return func(bs_storage);
		}
	}
	detail::mgr_handle_cmp_not_reg(get_name());
	return fallback;
}
//------------------------------------------------------------------------------
// manager::_apply_on_cmp_stg
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Result, typename Func>
inline
Result
manager<Entity>::
_apply_on_cmp_stg(
	Result fallback,
	const Func& func
) const
{
	return _apply_on_base_stg(
		fallback,
		[&func](auto& b_storage) -> Result
		{
			typedef component_storage<Entity, Component> cs_t;

			cs_t* ct_storage = dynamic_cast<cs_t*>(b_storage.get());
			assert(ct_storage);

			return func(ct_storage);
		},
		get_component_uid<Component>(),
		_cmp_name_getter<Component>()
	);
}
//------------------------------------------------------------------------------
// manager::_get_cmp_type_caps
//------------------------------------------------------------------------------
template <typename Entity>
inline
storage_capabilities
manager<Entity>::
_get_cmp_type_caps(
	component_uid_t cid,
	base::string(*get_name)(void)
) const
{
	return _apply_on_base_stg(
		storage_capabilities(),
		[](auto& b_storage) -> storage_capabilities
		{
			return b_storage->capabilities();
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_does_have
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_does_have(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> bool
		{
			return b_storage->has(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_is_hidn
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_is_hidn(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> bool
		{
			return b_storage->hidden(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_show
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_show(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> bool
		{
			return b_storage->show(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_hide
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_hide(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> bool
		{
			return b_storage->hide(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_add
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component>
inline bool
manager<Entity>::
_do_add(const Entity& ent, Component&& component)
{
	return _apply_on_cmp_stg<Component>(
		false,
		[&ent, &component](auto& c_storage) -> bool
		{
			c_storage->store(std::move(component), ent);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// manager::_do_cpy
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_cpy(
	const Entity& from,
	const Entity& to,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&from, &to](auto& b_storage) -> bool
		{
			return b_storage->copy(to, from);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_swp
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_swp(
	const Entity& e1,
	const Entity& e2,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&e1, &e2](auto& b_storage) -> bool
		{
			b_storage->swap(e1, e2);
			return true;
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_do_rem
//------------------------------------------------------------------------------
template <typename Entity>
inline bool
manager<Entity>::
_do_rem(
	const Entity& ent,
	component_uid_t cid,
	base::string(*get_name)(void)
)
{
	return _apply_on_base_stg(
		false,
		[&ent](auto& b_storage) -> bool
		{
			return b_storage->remove(ent);
		},
		cid, get_name
	);
}
//------------------------------------------------------------------------------
// manager::_call_rem_if
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Pred>
inline std::size_t
manager<Entity>::
_call_rem_if(const Pred& predicate)
{
	return _apply_on_cmp_stg<Component>(
		false,
		[&predicate](auto& c_storage) -> bool
		{
			c_storage->remove_if(predicate);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// manager::_call_for_single
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline bool
manager<Entity>::
_call_for_single(const Func& func, const Entity& ent)
{
	return _apply_on_cmp_stg<Component>(
		false,
		[&func, &ent](auto& c_storage) -> bool
		{
			return c_storage->for_single(func, ent);
		}
	);
}
//------------------------------------------------------------------------------
// manager::_call_for_each
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline void
manager<Entity>::
_call_for_each(const Func& func)
{
	_apply_on_cmp_stg<Component>(
		false,
		[&func](auto& c_storage) -> bool
		{
			c_storage->for_each(func);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// _manager_for_each_m_hlp_base
//------------------------------------------------------------------------------
template <typename Entity, std::size_t N>
class _manager_for_each_m_hlp_base
{
private:
	static_assert(N >= 1, "At least 2 components are required.");
protected:
	base::array<base_storage<Entity>*, N> _storages;

	base::array<storage_capabilities, N> _capabilities;

	base::array<storage_iterator<Entity>*, N> _iterators;


	template <typename ... Storage>
	_manager_for_each_m_hlp_base(
		Storage& ... storage
	): _storages{{static_cast<base_storage<Entity>*>(&storage)...}}
	 , _capabilities{{storage.capabilities()...}}
	 , _iterators{{storage.new_iterator()...}}
	{ }

	_manager_for_each_m_hlp_base(_manager_for_each_m_hlp_base&& that)
	 : _storages(that._storages)
	 , _capabilities(that._capabilities)
	{
		for(std::size_t i=0; i<N; ++i)
		{
			_iterators[i] = that._iterators[i];
			that._iterators[i] = nullptr;
		}
	}

	_manager_for_each_m_hlp_base(const _manager_for_each_m_hlp_base& that)
	 : _storages(that._storages)
	 , _capabilities(that._capabilities)
	{
		for(std::size_t i=0; i<N; ++i)
		{
			_iterators[i] = _storages[i]->clone_iterator(
				that._iterators[i]
			);
		}
	}

	std::size_t _find_min(void)
	{
		Entity min;
		std::size_t imin, i=0;
		while(i < N)
		{
			if(!_iterators[i]->done())
			{
				min = _iterators[i]->current();
				imin = i;
				break;
			}
			++i;
		}

		if(i == N)
		{
			return N;
		}

		while(i < N)
		{
			if(!_iterators[i]->done())
			{
				Entity tmp = _iterators[i]->current();
				if(min > tmp)
				{
					min = tmp;
					imin = i;
				}
			}
			++i;
		}
		return imin;
	}

	std::size_t _find_next(std::size_t imin)
	{
		assert(imin < N);

		Entity ent = _iterators[imin]->current();

		for(std::size_t i=0; i<N; ++i)
		{
			if(!_iterators[i]->done())
			{
				Entity tmp = _iterators[i]->current();
				if(tmp == ent)
				{
					_iterators[i]->next();
				}
			}
		}
		return _find_min();
	}

	void _sync(void)
	{
		while(!_iterators[0]->done())
		{
			Entity ent = _iterators[0]->current();
			Entity max = ent;

			bool some_done = false;
			for(std::size_t i=1; i<N; ++i)
			{
				if(_iterators[i]->done())
				{
					some_done = true;
					break;
				}

				Entity tmp = _iterators[i]->current();
				if(max < tmp)
				{
					max = tmp;
				}
			}

			if(some_done)
			{
				break;
			}

			if(ent < max)
			{
				while(!_iterators[0]->done())
				{
					ent = _iterators[0]->current();
					if(ent >= max)
					{
						break;
					}
					_iterators[0]->next();
				}
			}
			for(std::size_t i=1; i<N; ++i)
			{
				while(!_iterators[i]->done())
				{
					Entity tmp = _iterators[i]->current();
					if(tmp >= ent)
					{
						break;
					}
					_iterators[i]->next();
				}
			}

			bool all_equal = true;
			for(std::size_t i=1; i<N; ++i)
			{
				if(_iterators[i]->done())
				{
					all_equal = false;
					break;
				}

				Entity tmp = _iterators[i]->current();
				if(tmp != ent)
				{
					all_equal = false;
					break;
				}
			}

			if(all_equal)
			{
				break;
			}
		}
	}

	static
	void _handle_unsupported_storage_op(void)
	noexcept
	{
		assert(!"Storage does not support requested operation!");
	}
public:
	~_manager_for_each_m_hlp_base(void)
	{
		for(std::size_t i=0; i<N; ++i)
		{
			if(_iterators[i])
			{
				_storages[i]->delete_iterator(_iterators[i]);
			}
		}
	}
};
//------------------------------------------------------------------------------
// _manager_for_each_m_p_hlp_base
//------------------------------------------------------------------------------
template <typename Entity, std::size_t N>
class _manager_for_each_m_p_hlp_base
 : public _manager_for_each_m_hlp_base<Entity, N>
{
protected:
	typedef _manager_for_each_m_hlp_base<Entity, N> _base;
	std::size_t _imin;

	template <typename ... Storage>
	_manager_for_each_m_p_hlp_base(
		Storage& ... storage
	): _base(storage...)
	 , _imin(_base::_find_min())
	{ }

	Entity _current(void)
	{
		assert(_imin < N);
		assert(!this->_iterators[_imin]->done());
		return this->_iterators[_imin]->current();
	}
public:
	bool done(void) const
	{
		return _imin >= N;
	}

	void next(void)
	{
		assert(!done());
		_imin = this->_find_next(_imin);
	}
};
//------------------------------------------------------------------------------
// _manager_for_each_m_p_helper
//------------------------------------------------------------------------------
template <typename Entity, typename ... Component>
class _manager_for_each_m_p_helper
 : public _manager_for_each_m_p_hlp_base<Entity, sizeof ... (Component)>
{
private:
	typedef _manager_for_each_m_p_hlp_base<
		Entity,
		sizeof ... (Component)
	> _base;

	template <typename C>
	struct _bare_c : meta::remove_const<
		typename meta::remove_reference<C>::type
	>{ };

	template <typename ... C>
	struct _list { };

	template <typename Func, typename ... Cp>
	inline
	void _apply(
		const Func& func,
		std::size_t,
		const Entity& e,
		_list<>,
		Cp*...cp
	)
	{
		func(e, cp...);
	}

	template <
		typename Func,
		typename C,
		typename ... Ct,
		typename ... Cp
	>
	inline
	void _apply(
		const Func& func,
		std::size_t i,
		const Entity& e,
		_list<C, Ct...>,
		Cp* ... cp
	)
	{
		typedef component_storage<
			Entity,
			typename _bare_c<C>::type
		> cs_t;

		cs_t* ct_storage = dynamic_cast<cs_t*>(this->_storages[i]);
		assert(ct_storage);

		storage_iterator<Entity>* iter = this->_iterators[i];

		if(!iter->done() && (iter->current() == e))
		{
			storage_capabilities caps = this->_capabilities[i];

			bool is_const = meta::is_const<C>();
			if(!is_const)
			{
				assert(caps & storage_capability::modify);
			}

			if(caps & storage_capability::point_to)
			{
				C* pc = ct_storage->access(
					typename base::access<C&>::type(),
					e,
					iter
				);
				_apply(func, i+1, e, _list<Ct...>(), cp..., pc);
			}
			else if(caps & storage_capability::fetch)
			{
				typename _bare_c<C>::type c;
				C* pc = &c;
				ct_storage->fetch(c, e, iter);
				_apply(func, i+1, e, _list<Ct...>(), cp..., pc);

				if(!is_const)
				{
					assert(caps&storage_capability::store);
					ct_storage->store(std::move(c), e,iter);
				}
			}
			else
			{
				this->_handle_unsupported_storage_op();
			}
		}
		else
		{
			_apply(func, i+1, e, _list<Ct...>(), cp..., (C*)0);
		}
	}
public:
	_manager_for_each_m_p_helper(
		component_storage<
			Entity,
			typename _bare_c<Component>::type
		>& ... storage
	): _base(storage...)
	{ }

	_manager_for_each_m_p_helper(
		const _manager_for_each_m_p_helper&
	) = default;

	_manager_for_each_m_p_helper(
		_manager_for_each_m_p_helper&&
	) = default;

	template <typename Func>
	void apply(const Func& func)
	{
		_apply(
			func, 0,
			this->_current(),
			_list<Component...>()
		);
	}
};
//------------------------------------------------------------------------------
// manager::_call_for_each_m_p
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... Component, typename Func>
inline void
manager<Entity>::
_call_for_each_m_p(const Func& func)
{
	_manager_for_each_m_p_helper<Entity, Component...> hlp(
		_find_storage<typename _bare_c<Component>::type>()...
	);
	while(!hlp.done())
	{
		hlp.apply(func);
		hlp.next();
	}
}
//------------------------------------------------------------------------------
// _manager_for_each_m_r_hlp_base
//------------------------------------------------------------------------------
template <typename Entity, std::size_t N>
class _manager_for_each_m_r_hlp_base
 : public _manager_for_each_m_hlp_base<Entity, N>
{
protected:
	typedef _manager_for_each_m_hlp_base<Entity, N> _base;

	using _base::_sync;

	template <typename ... Storage>
	_manager_for_each_m_r_hlp_base(
		Storage& ... storage
	): _base(storage...)
	{
		_sync();
	}

	Entity _current(void)
	{
		return this->_iterators[0]->current();
	}
public:
	bool done(void) const
	{
		for(std::size_t i=0; i<N; ++i)
		{
			if(this->_iterators[i]->done())
			{
				return true;
			}
		}
		return false;
	}

	void next(void)
	{
		assert(!done());
		this->_iterators[0]->next();
		_sync();
	}
};
//------------------------------------------------------------------------------
// _manager_for_each_m_r_helper
//------------------------------------------------------------------------------
template <typename Entity, typename ... Component>
class _manager_for_each_m_r_helper
 : public _manager_for_each_m_r_hlp_base<Entity, sizeof ... (Component)>
{
private:
	typedef _manager_for_each_m_r_hlp_base<
		Entity,
		sizeof ... (Component)
	> _base;

	template <typename C>
	struct _bare_c : meta::remove_const<
		typename meta::remove_reference<C>::type
	>{ };

	template <typename ... C>
	struct _list { };

	template <typename Func, typename ... Cr>
	inline
	void _apply(
		const Func& func,
		std::size_t,
		const Entity& e,
		_list<>,
		Cr&...cr
	)
	{
		func(e, cr...);
	}

	template <
		typename Func,
		typename C,
		typename ... Ct,
		typename ... Cr
	>
	inline
	void _apply(
		const Func& func,
		std::size_t i,
		const Entity& e,
		_list<C, Ct...>,
		Cr& ... cr
	)
	{
		typedef component_storage<
			Entity,
			typename _bare_c<C>::type
		> cs_t;

		cs_t* ct_storage = dynamic_cast<cs_t*>(this->_storages[i]);
		assert(ct_storage);

		storage_iterator<Entity>* iter = this->_iterators[i];
		storage_capabilities caps = this->_capabilities[i];
		bool is_const = meta::is_const<C>();

		assert(iter->current() == e);

		if(!is_const)
		{
			assert(caps & storage_capability::modify);
		}

		if(caps & storage_capability::point_to)
		{
			C* pc = ct_storage->access(
				typename base::access<C&>::type(),
				e,
				iter
			);
			_apply(func, i+1, e, _list<Ct...>(), cr..., *pc);
		}
		else if(caps & storage_capability::fetch)
		{
			typename _bare_c<C>::type c;
			ct_storage->fetch(c, e, iter);
			_apply(func, i+1, e, _list<Ct...>(), cr..., c);

			if(!is_const)
			{
				assert(caps & storage_capability::store);
				ct_storage->store(std::move(c), e, iter);
			}
		}
		else
		{
			this->_handle_unsupported_storage_op();
		}
	}
public:
	_manager_for_each_m_r_helper(
		component_storage<
			Entity,
			typename _bare_c<Component>::type
		>& ... storage
	): _base(storage...)
	{ }

	_manager_for_each_m_r_helper(
		const _manager_for_each_m_r_helper&
	) = default;

	_manager_for_each_m_r_helper(
		_manager_for_each_m_r_helper&&
	) = default;

	template <typename Func>
	void apply(const Func& func)
	{
		_apply(
			func, 0,
			this->_current(),
			_list<Component...>()
		);
	}
};
//------------------------------------------------------------------------------
// manager::_call_for_each_m_r
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... Component, typename Func>
inline void
manager<Entity>::
_call_for_each_m_r(const Func& func)
{
	_manager_for_each_m_r_helper<Entity, Component...> hlp(
		_find_storage<typename _bare_c<Component>::type>()...
	);
	while(!hlp.done())
	{
		hlp.apply(func);
		hlp.next();
	}
}
//------------------------------------------------------------------------------
// manager::_call_pl_for_each
//------------------------------------------------------------------------------
template <typename Entity>
template <typename Component, typename Func>
inline void
manager<Entity>::
_call_pl_for_each(
	const Func& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	_apply_on_cmp_stg<Component>(
		false,
		[&func,&prlzr,&param](auto& c_storage) -> bool
		{
			c_storage->parallel_for_each(func, prlzr, param);
			return true;
		}
	);
}
//------------------------------------------------------------------------------
// _manager_pl_for_each_m_wrap
//------------------------------------------------------------------------------
template <
	typename Func,
	template <class, class...> class Helper,
	typename Entity,
	typename ... Component
>
class _manager_pl_for_each_m_wrap
{
private:
	Func _func;
	Helper<Entity, Component...> _hlpr;
	std::size_t _curr;
public:
	_manager_pl_for_each_m_wrap(const _manager_pl_for_each_m_wrap&)=default; 
	_manager_pl_for_each_m_wrap(_manager_pl_for_each_m_wrap&&) = default;

	template <typename ... Storage>
	_manager_pl_for_each_m_wrap(const Func& func, Storage& ... storage)
	 : _func(func)
	 , _hlpr(storage...)
	 , _curr(0)
	{ }

	bool operator()(std::size_t next)
	{
		while(!_hlpr.done() && (_curr < next))
		{
			_hlpr.next();
			++_curr;
		}
		if(!_hlpr.done())
		{
			_hlpr.apply(_func);
			return true;
		}
		return false;
	}
};
//------------------------------------------------------------------------------
// manager::_call_pl_for_each_m_p
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... Component, typename Func>
inline void
manager<Entity>::
_call_pl_for_each_m_p(
	const Func& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	prlzr.execute_stateful(
		_manager_pl_for_each_m_wrap<
			Func,
			_manager_for_each_m_p_helper,
			Entity,
			Component...
		>(
			func,
			_find_storage<typename _bare_c<Component>::type>()...
		), param
	).wait();
}
//------------------------------------------------------------------------------
// manager::_call_pl_for_each_m_r
//------------------------------------------------------------------------------
template <typename Entity>
template <typename ... Component, typename Func>
inline void
manager<Entity>::
_call_pl_for_each_m_r(
	const Func& func,
	base::parallelizer& prlzr,
	base::execution_params& param
)
{
	prlzr.execute_stateful(
		_manager_pl_for_each_m_wrap<
			Func,
			_manager_for_each_m_r_helper,
			Entity,
			Component...
		>(
			func,
			_find_storage<typename _bare_c<Component>::type>()...
		), param
	).wait();
}
//------------------------------------------------------------------------------
// manager::_do_get
//------------------------------------------------------------------------------
template <typename Entity>
template <typename T, typename C>
inline T
manager<Entity>::
_do_get(T C::* mvp, const Entity& ent, T res)
{
	assert(mvp);

	auto getter = [mvp, &res](const Entity&, const C& cmp) -> void
	{
		res = cmp.*mvp;
	};
	base::functor<void(const Entity&, const C&)> func(getter);

	_call_for_single<C>(func, ent);
	return res;
}
//------------------------------------------------------------------------------
} // namespace ecs
} // namespace eagine


