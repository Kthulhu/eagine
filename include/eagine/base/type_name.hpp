/**
 *  @file eagine/base/type_name.hpp
 *  @brief Type name-related utilities.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_TYPE_NAME_1308281038_HPP
#define EAGINE_BASE_TYPE_NAME_1308281038_HPP

#include <eagine/base/string.hpp>
#include <typeinfo>

namespace EAGine {
namespace base {

string demangle_type_name(const char*)
noexcept;

template <typename T>
inline string type_name(const T& x)
noexcept
{
	return demangle_type_name(typeid(x).name());
}

template <typename T>
inline string type_name(void)
noexcept
{
	return demangle_type_name(typeid(T).name());
}

} // namespace base
} // namespace EAGine

#if !EAGINE_LINK_LIBRARY || defined(EAGINE_IMPLEMENTING_LIBRARY)
#include <eagine/base/type_name.inl>
#endif

#endif //include guard

