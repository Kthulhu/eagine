/**
 *  @file eagine/base/dyn_lib.hpp
 *  @brief Dynamic library loading functionality wrapper.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_DYN_LIB_1308281038_HPP
#define EAGINE_BASE_DYN_LIB_1308281038_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/error.hpp>
#include <eagine/meta/type_traits.hpp>

namespace EAGine {
namespace base {

/// A wrapper for dynamic libraries/shader objects
class dynamic_library
{
private:
	void* _handle;
	static void* _check_and_open(const char* module_name);
	// TODO: winapi

protected:
	dynamic_library(void);
public:
	class open_error : public runtime_error
	{
	public:
		open_error(const string& msg)
		 : runtime_error(msg)
		{ }
	};

	class symbol_error : public runtime_error
	{
	public:
		symbol_error(const string& msg)
		 : runtime_error(msg)
		{ }
	};

	/// Construction from module name or path
	dynamic_library(cstrref module_name);

	/// dynamic libraries are not copy-constructible
	dynamic_library(const dynamic_library&) = delete;

	/// dynamic libraries are movable
	dynamic_library(dynamic_library&& tmp)
	 : _handle(tmp._handle)
	{
		tmp._handle = nullptr;
	}

	~dynamic_library(void);

	/// Returns a pointer to an exported symbol with the specified name
	void* symbol(cstrref symbol_name);


	/// returns a pointer to a function with the specified name and type
	template <
		typename FuncType,
		typename = typename meta::enable_if<
			meta::is_function<FuncType>::value
		>::type*
	>
	FuncType* function(cstrref function_name)
	{
		// EVIL hack to keep the compiler from complaining
		static_assert(sizeof(void*) == sizeof(FuncType*), "");
		void* sptr = symbol(function_name);
		return *(FuncType**)(&sptr);
	}
};

/// A wrapper for the current executable module
class executable_module
 : public dynamic_library
{
public:
	executable_module(void)
	 : dynamic_library()
	{ }
};

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/dyn_lib.inl>
#endif

#endif //include guard

