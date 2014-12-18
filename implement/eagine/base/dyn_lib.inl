/**
 *  @file eagine/base/dyn_lib.inl
 *  @brief Implementation dynamic library loader functionality
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#include <cassert>
#include <dlfcn.h>
// TODO winapi

namespace eagine {
namespace base {
//------------------------------------------------------------------------------
// dynamic_library::_check_and_open
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
void* dynamic_library::_check_and_open(const char* module_name)
{
	::dlerror();
	void* handle = ::dlopen(module_name, RTLD_NOW);

	const char* error_message = ::dlerror();
	if(error_message)
	{
		handle = nullptr;
		throw open_error(error_message);
	}
	return handle;
}
//------------------------------------------------------------------------------
// dynamic_library::dynamic_library
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
dynamic_library::dynamic_library(void)
 : _handle(_check_and_open(nullptr))
{ }

//------------------------------------------------------------------------------
// dynamic_library::dynamic_library
//------------------------------------------------------------------------------
EAGINE_LIB_FUNC
dynamic_library::dynamic_library(cstrref module_name)
 : _handle(_check_and_open(c_str(module_name)))
{ }
//------------------------------------------------------------------------------
// dynamic_library::~dynamic_library
//------------------------------------------------------------------------------
dynamic_library::~dynamic_library(void)
noexcept
{
	if(_handle)
	{
		::dlclose(_handle);
	}
}
//------------------------------------------------------------------------------
// dynamic_library::symbol
//------------------------------------------------------------------------------
void* dynamic_library::symbol(cstrref symbol_name)
{
	void* result = ::dlsym(_handle, c_str(symbol_name));

	const char* error_message = ::dlerror();
	if(error_message)
	{
		throw symbol_error(error_message);
	}
	return result;
}
//------------------------------------------------------------------------------
} // namespace base
} // namespace eagine


