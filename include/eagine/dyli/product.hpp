/**
 *  @file eagine/dyli/product.hpp
 *  @brief Dynamically linked product wrapper
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_DYLI_PRODUCT_1408161720_HPP
#define EAGINE_DYLI_PRODUCT_1408161720_HPP

#include <eagine/base/memory.hpp>
#include <eagine/base/utility.hpp>
#include <eagine/base/dyn_lib.hpp>
#include <eagine/dyli/detail.hpp>

namespace eagine {
namespace dyli {

template <typename T>
class weak_prod;

template <typename T>
class product
{
private:
	base::shared_ptr<base::dynamic_library> _lib;
	base::shared_ptr<T> _ptr;
	friend class weak_prod<T>;
public:
	product(
		const base::shared_ptr<base::dynamic_library>& lib,
		base::shared_ptr<T>&& ptr
	): _lib(lib)
	 , _ptr(ptr)
	{ }
public:
	product(void) noexcept = default;

	void release(void)
	{
		_lib.reset();
		_ptr.reset();
	}

	explicit operator bool (void) const noexcept
	{
		return bool(_lib) && bool(_ptr);
	}

	T* operator -> (void) noexcept
	{
		assert(bool(*this));
		return _ptr.operator -> ();
	}

	T& operator * (void) noexcept
	{
		assert(bool(*this));
		return _ptr.operator * ();
	}

	T const * operator -> (void) const noexcept
	{
		assert(bool(*this));
		return _ptr.operator -> ();
	}

	T const & operator * (void) const noexcept
	{
		assert(bool(*this));
		return _ptr.operator * ();
	}
};

template <typename T>
class weak_prod
{
private:
	base::weak_ptr<base::dynamic_library> _wlib;
	base::weak_ptr<T> _ptr;
public:
	weak_prod(const product<T>& data)
	 : _wlib(data._lib)
	 , _ptr(data._ptr)
	{ }

	explicit operator bool (void) const noexcept
	{
		return (!_wlib.expired()) && bool(_ptr);
	}

	operator product<T> (void) const noexcept
	{
		return product<T>(_wlib.lock(), _ptr.lock());
	}

	product<T> require(void) const
	{
		return product<T>(
			detail::require_lib(_wlib),
			detail::require_ptr(_ptr)
		);
	}
};

} // namespace dyli
} // namespace eagine

#endif //include guard

