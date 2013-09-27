/**
 *  @file eagine/base/dyn_lib.inl
 *  @brief Implementation dynamic library loader functionality
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/eagine_config.hpp>

#include <eagine/base/error.hpp>

#include <cassert>
#include <dlfcn.h>
// TODO winapi

namespace EAGine {
namespace base {

EAGINE_LIB_FUNC
void* dynamic_library::_check_and_open(const char* module_name)
{
	::dlerror();
	void* handle = ::dlopen(module_name, RTLD_NOW);

	const char* error_message = ::dlerror();
	if(error_message)
	{
		handle = nullptr;
		throw runtime_error(error_message);
	}
	return handle;
}

EAGINE_LIB_FUNC
dynamic_library::dynamic_library(void)
 : _handle(_check_and_open(nullptr))
{ }

EAGINE_LIB_FUNC
dynamic_library::dynamic_library(cstrref module_name)
 : _handle(_check_and_open(
	module_name.null_terminated()?
	module_name.data():
	module_name.str().c_str()
))
{ }

dynamic_library::~dynamic_library(void)
{
	if(_handle)
	{
		::dlclose(_handle);
	}
}

void* dynamic_library::symbol(cstrref symbol_name)
{
	void* result = ::dlsym(
		_handle,
		symbol_name.null_terminated()?
		symbol_name.data():
		symbol_name.str().c_str()
	);

	const char* error_message = ::dlerror();
	if(error_message)
	{
		throw runtime_error(error_message);
	}
	return result;
}

} // namespace base
} // namespace EAGine


