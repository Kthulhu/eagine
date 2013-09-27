/**
 *  @file eagine/meta/type_traits.hpp
 *  @brief Compile-time type-traits
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_META_TYPE_TRAITS_1308281038_HPP
#define EAGINE_META_TYPE_TRAITS_1308281038_HPP

#include <type_traits>

namespace EAGine {
namespace meta {

using ::std::integral_constant;
using ::std::true_type;
using ::std::false_type;
using ::std::enable_if;
using ::std::add_const;
using ::std::remove_const;
using ::std::add_pointer;
using ::std::is_same;
using ::std::is_convertible;
using ::std::is_function;

} // namespace meta
} // namespace EAGine

#endif //include guard

