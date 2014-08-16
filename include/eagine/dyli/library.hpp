/**
 *  @file eagine/dyli/library.hpp
 *  @brief Dynamic library wrapper
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_DYLI_LIBRARY_1408161720_HPP
#define EAGINE_DYLI_LIBRARY_1408161720_HPP

#include <eagine/dyli/function.hpp>

namespace EAGine {
namespace dyli {

class loader;
class weak_lib;

class library
{
private:
	base::shared_ptr<base::dynamic_library> _lib;

	friend class weak_lib;
	friend class loader;

	library(const base::shared_ptr<base::dynamic_library>& lib)
	 : _lib(lib)
	{ }

	library(base::shared_ptr<base::dynamic_library>&& lib)
	 : _lib(base::move(lib))
	{ }
public:
	library(void) { }


	void release(void)
	{
		_lib.reset();	
	}

	explicit operator bool (void) const
	{
		return bool(_lib);
	}

	template <
		typename FuncType,
		typename = typename meta::enable_if<
			meta::is_function<FuncType>::value
		>::type*
	>
	function<FuncType> function(base::cstrref name) const
	{
		return dyli::function<FuncType>(
			_lib,
			_lib->template function<FuncType>(name)
		);
	}
/*
	func_ptr try_get_function(const char* name) const
	{
		try { return get_function(name); }
		catch(std::runtime_error&) { func_ptr(); }
	}
*/
};

class weak_lib
{
private:
	base::weak_ptr<base::dynamic_library> _wlib;
public:
	weak_lib(const library& lib)
	 : _wlib(lib._lib)
	{ }

	explicit operator bool (void) const
	{
		return !_wlib.expired();
	}

	operator library (void) const noexcept
	{
		return library(_wlib.lock());
	}

	library require(void) const;
};

} // namespace dyli
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/dyli/library.inl>
#endif

#endif //include guard

