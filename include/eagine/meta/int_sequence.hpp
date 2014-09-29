/**
 *  @file eagine/meta/int_sequence.hpp
 *  @brief Compile-time integer sequences.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_INT_SEQUENCE_1308281038_HPP
#define EAGINE_META_INT_SEQUENCE_1308281038_HPP

#include <eagine/meta/int_const.hpp>

namespace EAGine {
namespace meta {

template <typename Int, Int ... I>
struct integer_sequence
{
	typedef integer_sequence type;
};

template <typename IS, typename I>
struct push_back_t
 : push_back_t<typename IS::type, typename I::type>
{ };

template <typename Int, Int ... I, Int N>
struct push_back_t<integer_sequence<Int, I...>, integral_constant<Int, N>>
 : integer_sequence<Int, I..., N>
{ };

template <typename Int, typename N>
struct make_integer_sequence_t;

template <typename Int>
struct make_integer_sequence_t<Int, integral_constant<Int, 0>>
 : integer_sequence<Int>
{ };

template <typename Int, Int N>
struct make_integer_sequence_t<Int, integral_constant<Int, N>>
 : push_back_t<
	make_integer_sequence_t<Int, integral_constant<Int, N-1>>,
	integral_constant<Int, N>
>
{ };

template <typename Int, Int N>
struct make_integer_sequence
 : make_integer_sequence_t<Int, integral_constant<Int, N>>
{ };

} // namespace meta
} // namespace EAGine

#endif //include guard

