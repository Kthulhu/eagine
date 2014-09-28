/**
 *  @file eagine/unit/traits.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_TRAITS_1308281038_HPP
#define EAGINE_UNIT_TRAITS_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/meta/int_const.hpp>

namespace EAGine {
namespace unit {

template <typename X>
struct is_unit
 : meta::false_type
{ };

template <typename D, typename S>
struct is_unit<unit<D, S>>
 : meta::true_type
{ };

template <typename D, typename US, typename S>
struct is_unit<scaled_unit<D, US, S>>
 : meta::true_type
{ };

template <typename X, typename Y>
struct same_dimension
 : meta::false_type
{ };

template <typename D, typename S>
struct same_dimension<unit<D, S>, unit<D, S>>
 : meta::true_type
{ };

template <typename D, typename US, typename S>
struct same_dimension<unit<D, S>, scaled_unit<D, US, S>>
 : meta::true_type
{ };

template <typename D, typename US, typename S>
struct same_dimension<scaled_unit<D, US, S>, unit<D, S>>
 : meta::true_type
{ };

template <typename D, typename US1, typename US2, typename S>
struct same_dimension<scaled_unit<D, US1, S>, scaled_unit<D, US2, S>>
 : meta::true_type
{ };

} // namespace unit
} // namespace EAGine

#endif //include guard

