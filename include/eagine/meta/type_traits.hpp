/**
 *  @file eagine/meta/type_traits.hpp
 *  @brief Compile-time type-traits
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_TYPE_TRAITS_1308281038_HPP
#define EAGINE_META_TYPE_TRAITS_1308281038_HPP

#include <eagine/meta/int_const.hpp>

namespace EAGine {
namespace meta {

using ::std::conditional;
using ::std::enable_if;
using ::std::is_const;
using ::std::add_const;
using ::std::remove_const;
using ::std::remove_reference;
using ::std::add_pointer;
using ::std::is_same;
using ::std::is_base_of;
using ::std::is_convertible;
using ::std::is_function;
using ::std::is_pod;
using ::std::is_copy_assignable;
using ::std::is_trivially_destructible;

template <typename Src, typename Dst>
struct add_same_constness
 : ::std::conditional<
	::std::is_const<Src>::value,
	typename ::std::add_const<Dst>::type,
	typename ::std::remove_const<Dst>::type
> { };

} // namespace meta
} // namespace EAGine

#endif //include guard

