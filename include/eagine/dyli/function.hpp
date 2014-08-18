/**
 *  @file eagine/dyli/function.hpp
 *  @brief Dynamically linked function wrapper
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_DYLI_FUNCTION_1408161720_HPP
#define EAGINE_DYLI_FUNCTION_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/utility.hpp>
#include <eagine/base/dyn_lib.hpp>
#include <eagine/dyli/detail.hpp>

namespace EAGine {
namespace dyli {

template <typename FuncType>
class function;
template <typename FuncType>
class weak_func;

template <typename RV, typename ... P>
class function<RV(P...)>
{
private:
	typedef typename detail::func_util<RV(P...)>::adjusted_t _func_t;
	base::shared_ptr<base::dynamic_library> _lib;
	_func_t* _ptr;

	friend class weak_func<RV(P...)>;
	friend class library;

	function(
		const base::shared_ptr<base::dynamic_library>& lib,
		_func_t* ptr
	): _lib(lib)
	 , _ptr(ptr)
	{ }
public:
	function(void) noexcept = default;

	void release(void)
	{
		_lib.reset();	
		_ptr = nullptr;
	}

	explicit operator bool (void) const noexcept
	{
		return bool(_lib) && bool(_ptr);
	}

	template <typename ... PP>
	RV operator ()(PP&& ... p) const
	{
		assert(bool(*this));
		return detail::func_util<RV(P...)>::adapt_rv(
			_lib,
			_ptr(std::forward<PP>(p)...)
		);
	}
};

template <typename RV, typename ... P>
class weak_func<RV(P...)>
{
private:
	base::weak_ptr<base::dynamic_library> _wlib;
	RV(*_ptr)(P...);
public:
	weak_func(const function<RV(P...)>& func)
	 : _wlib(func._lib)
	 , _ptr(func._ptr)
	{ }

	explicit operator bool (void) const noexcept
	{
		return (!_wlib.expired()) && bool(_ptr);
	}

	operator function<RV(P...)> (void) const noexcept
	{
		return function<RV(P...)>(
			_wlib.lock(),
			_ptr
		);
	}

	function<RV(P...)> require(void) const
	{
		return function<RV(P...)>(
			detail::require_lib(_wlib),
			_ptr
		);
	}

	template <typename ... PP>
	RV operator ()(PP&& ... p) const
	{
		return require()(std::forward<PP>(p)...);
	}
};

} // namespace dyli
} // namespace EAGine

#endif //include guard

