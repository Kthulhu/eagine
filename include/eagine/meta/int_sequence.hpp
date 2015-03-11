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

namespace eagine {
namespace meta {

template <typename Int, Int ... I>
struct integer_sequence
{
	typedef integer_sequence type;
};

template <unsigned ... I>
using unsigned_sequence = integer_sequence<unsigned, I ...>;

template <typename IS, typename I>
struct push_back_t;

template <typename Int, Int ... I, Int N>
struct push_back_t<integer_sequence<Int, I...>, integral_constant<Int, N>>
 : integer_sequence<Int, I..., N>
{ };

template <typename N>
struct make_integer_sequence_t;

template <typename Int>
struct make_integer_sequence_t<integral_constant<Int, Int(0)>>
 : integer_sequence<Int>
{ };

template <typename Int, Int N>
struct make_integer_sequence_t<integral_constant<Int, N>>
 : push_back_t<
	typename make_integer_sequence_t<integral_constant<Int, N-1>>::type,
	integral_constant<Int, N-1>
>
{ };

template <typename Int, Int N>
struct make_integer_sequence
 : make_integer_sequence_t<integral_constant<Int, N>>
{ };

template <unsigned N>
using make_unsigned_sequence = make_integer_sequence<unsigned, N>;

} // namespace meta
} // namespace eagine

#endif //include guard

