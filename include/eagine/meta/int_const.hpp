/**
 *  @file eagine/meta/int_const.hpp
 *  @brief Compile-time integral_constants.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_META_INT_CONST_1308281038_HPP
#define EAGINE_META_INT_CONST_1308281038_HPP

#include <type_traits>

namespace EAGine {
namespace meta {

using ::std::integral_constant;
using ::std::true_type;
using ::std::false_type;

template <typename IC1, typename IC2>
struct plus;

template <typename Int, Int I0, Int I1>
struct plus<integral_constant<Int, I0>, integral_constant<Int, I1>>
 : integral_constant<Int, I0+I1>
{ };

template <typename IC1, typename IC2>
struct minus;

template <typename Int, Int I0, Int I1>
struct minus<integral_constant<Int, I0>, integral_constant<Int, I1>>
 : integral_constant<Int, I0-I1>
{ };

template <typename IC>
struct negate;

template <typename Int, Int I>
struct negate<integral_constant<Int, I>>
 : integral_constant<Int, -I>
{ };


} // namespace meta
} // namespace EAGine

#endif //include guard

