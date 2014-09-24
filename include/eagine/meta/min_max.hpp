/**
 *  @file eagine/meta/min_max.hpp
 *  @brief Minimum/maximum from a pack of integral constants
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_META_MIN_MAX_1308281038_HPP
#define EAGINE_META_MIN_MAX_1308281038_HPP

#include <eagine/meta/type_traits.hpp>

namespace EAGine {
namespace meta {

template <typename T, T ...>
struct min_constant;

template <typename T, T M>
struct min_constant<T, M>
 : integral_constant<T, M>
{ };

template <typename T, T M, T N, T ... I>
struct min_constant<T, M, N, I...>
 : min_constant<T, (M<N?M:N), I...>
{ };

template <typename T, T ...>
struct max_constant;

template <typename T, T M>
struct max_constant<T, M>
 : integral_constant<T, M>
{ };

template <typename T, T M, T N, T ... I>
struct max_constant<T, M, N, I...>
 : max_constant<T, (M>N?M:N), I...>
{ };

} // namespace meta
} // namespace EAGine

#endif //include guard

