/**
 *  @file eagine/base/callable.hpp
 *  @brief Polymorphic callable wrapper.
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_FUNCTOR_1308281038_HPP
#define EAGINE_BASE_FUNCTOR_1308281038_HPP

#include <eagine/meta/mem_fn_const.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/base/memory.hpp>
#include <cstdint>
#include <utility>
#include <cassert>

namespace eagine {
namespace base {

template <typename FuncSig>
class callable_ref;

template <typename RV, typename ... P>
class callable_ref<RV(P...)>
{
private:
	void* _data;
	void(*_func)(void);

	typedef void(*_func_t)(void);
	typedef RV(*_func_pt)(P...);
	typedef RV(*_func_vpt)(void*, P...);

	static constexpr inline
	void* _invptr(void)
	noexcept
	{
		return (void*)(~(std::uintptr_t)(void*)nullptr);
	}

	bool _no_data(void) const
	noexcept
	{
		return _data == _invptr();
	}

	template <typename C>
	static
	RV _cls_fn_call_op(void* that, P...p)
	{
		assert(that);
		C& obj = *((C*)that);
		return obj(std::forward<P>(p)...);
	}

	template <typename C>
	static
	RV _cls_fn_call_op_c(void* that, P...p)
	{
		assert(that);
		const C& obj = *((const C*)that);
		return obj(std::forward<P>(p)...);
	}
public:
	callable_ref(void)
	noexcept
	 : _data(nullptr)
	 , _func(nullptr)
	{ }

	callable_ref(RV(*func)(P...))
	noexcept
	 : _data(_invptr())
	 , _func((_func_t)func)
	{ }

	template <typename T>
	callable_ref(T* data, RV(*func)(T*, P...))
	noexcept
	 : _data((void*)data)
	 , _func((_func_t)func)
	{
		assert(_data != _invptr());
	}

	template <typename T>
	callable_ref(T& data, RV(*func)(T*, P...))
	noexcept
	 : _data((void*)&data)
	 , _func((_func_t)func)
	{
		assert(_data != _invptr());
	}

	template <
		typename C,
		typename MF,
		MF Ptr,
		typename = typename meta::enable_if<
			meta::is_same<
				typename meta::member_function_constant<
					MF,
					Ptr
				>::scope, C
			>::value
		>::type
	>
	callable_ref(
		C* obj,
		meta::member_function_constant<MF, Ptr> mfc
	) noexcept
	 : _data((void*)obj)
	 , _func((_func_t)mfc.make_free())
	{
		assert(_data != nullptr);
		assert(_data != _invptr());
	}

	template <typename C>
	explicit
	callable_ref(C& obj)
	noexcept
	 : _data((void*)&obj)
	 , _func((_func_t)(&_cls_fn_call_op<C>))
	{ }

	template <typename C>
	explicit
	callable_ref(const C& obj)
	noexcept
	 : _data((void*)&obj)
	 , _func((_func_t)(&_cls_fn_call_op_c<C>))
	{ }

	bool is_callable(void) const
	noexcept
	{
		return _func != nullptr;
	}

	explicit operator bool (void) const
	noexcept
	{
		return is_callable();
	}

	template <typename ... A>
	RV operator()(A&&...a) const
	{
		assert(is_callable());
		if(_no_data())
		{
			return ((_func_pt)(_func))(
				std::forward<A>(a)...
			);
		}
		else
		{
			return ((_func_vpt)(_func))(
				_data,
				std::forward<A>(a)...
			);
		}
	}
};

template <typename F>
class callable;

template <typename RV, typename ... P>
class callable<RV(P...)>
{
private:
	typedef RV (*_func_t)(void*, P ...);

	struct _intf
	{
		virtual ~_intf(void) { }

		virtual void* impl_ptr(void) noexcept = 0;
		virtual _func_t func_ptr(void) noexcept = 0;
	};

	template <typename Func>
	struct _wrap : _intf
	{
		Func _func;

		_wrap(Func&& func)
		 : _func(std::move(func))
		{ }

		static
		RV _free_func(Func* func, P ... p)
		{
			assert(func != nullptr);
			return (*func)(std::forward<P>(p)...);
		}

		void* impl_ptr(void)
		noexcept
		{
			return (void*)(&_func);
		}

		_func_t func_ptr(void)
		noexcept
		{
			return (_func_t)&_free_func;
		}
		
	};

	shared_ptr<_intf> _store;
	void* _impl;
	_func_t _func;

	template <typename T>
	struct _fix
	 : meta::remove_reference<T>
	{ };
public:
	callable(void) = default;
	callable(const callable&) = default;
	callable(callable&&) = default;

	callable& operator = (const callable&) = default;
	callable& operator = (callable&&) = default;

	template <typename Func>
	callable(Func&& func)
	 : _store(make_shared<_wrap<typename _fix<Func>::type>>(
		std::forward<Func>(func))
	), _impl(_store->impl_ptr())
	 , _func(_store->func_ptr())
	{ }

	template <typename Func, typename Alloc>
	callable(
		std::allocator_arg_t,
		Alloc& alloc,
		Func&& func
	): _store(allocate_shared<
		_wrap<typename _fix<Func>::type>>(
			typename Alloc::
				template rebind<
					_wrap<typename _fix<Func>::type>
				>::other(alloc),
			std::forward<Func>(func)
		)
	), _impl(_store->impl_ptr())
	 , _func(_store->func_ptr())
	{ }

	bool is_callable(void) const
	{
		return (_store && _impl && _func);
	}

	explicit operator bool (void) const
	{
		return is_callable();
	}

	template <typename ... A>
	RV operator ()(A&& ... a) const
	{
		assert(is_callable());
		return _func(_impl, std::forward<A>(a)...);
	}

	callable_ref<RV(P...)> ref(void) const
	{
		return callable_ref<RV(P...)>(_impl, _func);
	}

	operator callable_ref<RV(P...)> (void) const
	{
		return ref();
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

