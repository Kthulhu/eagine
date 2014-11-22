/**
 *  @file eagine/dyli/content.hpp
 *  @brief Dynamically linked content wrapper
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DYLI_CONTENT_1408161720_HPP
#define EAGINE_DYLI_CONTENT_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/utility.hpp>
#include <eagine/base/dyn_lib.hpp>
#include <eagine/dyli/detail.hpp>

namespace eagine {
namespace dyli {

template <typename T>
class weak_cont;

template <typename T>
class content
{
private:
	base::shared_ptr<base::dynamic_library> _lib;
	T* _ptr;
	friend class weak_cont<T>;
public:
	content(
		const base::shared_ptr<base::dynamic_library>& lib,
		T* ptr
	): _lib(lib)
	 , _ptr(ptr)
	{ }
public:
	content(void) noexcept = default;

	void release(void)
	{
		_lib.reset();	
		_ptr = nullptr;
	}

	explicit operator bool (void) const noexcept
	{
		return bool(_lib) && bool(_ptr);
	}

	T* operator -> (void) noexcept
	{
		assert(bool(*this));
		return _ptr;
	}

	T& operator * (void) noexcept
	{
		assert(bool(*this));
		return *_ptr;
	}

	T const * operator -> (void) const noexcept
	{
		assert(bool(*this));
		return _ptr;
	}

	T const & operator * (void) const noexcept
	{
		assert(bool(*this));
		return *_ptr;
	}
};

template <typename T>
class weak_cont
{
private:
	base::weak_ptr<base::dynamic_library> _wlib;
	T* _ptr;
public:
	weak_cont(const content<T>& data)
	 : _wlib(data._lib)
	 , _ptr(data._ptr)
	{ }

	explicit operator bool (void) const noexcept
	{
		return (!_wlib.expired()) && bool(_ptr);
	}

	operator content<T> (void) const noexcept
	{
		return content<T>(_wlib.lock(), _ptr);
	}

	content<T> require(void) const
	{
		return content<T>(
			detail::require_lib(_wlib),
			_ptr
		);
	}
};

} // namespace dyli
} // namespace eagine

#endif //include guard

