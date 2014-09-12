/**
 *  @file eagine/base/type_name.inl
 *  @brief Implementation of type name-related utilities
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <eagine/eagine_config.hpp>
#include <eagine/base/memory.hpp>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

namespace EAGine {
namespace base {

EAGINE_LIB_FUNC
string demangle_type_name(const char* name)
{
#ifdef __GNUG__
	int status = -1;

	unique_ptr<char, void(*)(void*)> demangled {
		::abi::__cxa_demangle(name, nullptr, nullptr, &status),
		::std::free
	};

	return (status == 0) ? demangled.get() : name;
#else
	return name;
#endif
}

} // namespace base
} // namespace EAGine

