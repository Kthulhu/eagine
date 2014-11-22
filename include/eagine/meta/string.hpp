/**
 *  @file eagine/meta/string.hpp
 *  @brief The compile-time strings.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_STRING_1308281038_HPP
#define EAGINE_META_STRING_1308281038_HPP

#include <eagine/meta/int_const.hpp>
#include <cstddef>

namespace eagine {
namespace meta {

template <typename Char, Char ... C>
struct basic_string
{
	typedef basic_string<Char, C...> type;
};

template <char ... C>
using string = basic_string<char, C...>;

typedef string<> empty_string;

template <typename String>
struct size
 : size<typename String::type>
{ };

template <typename Char, Char ... C>
struct size<basic_string<Char, C...>>
 : integral_constant<std::size_t, sizeof...(C)>
{ };

template <typename String>
struct c_str
 : c_str<typename String::type>
{ };

template <typename Char, Char ... C>
struct c_str<basic_string<Char, C...>>
{
	static constexpr Char value[] = { C..., '\0' };

	constexpr operator const char* (void) const
	noexcept
	{
		return value;
	}
};

template <typename Char, Char ... C>
constexpr Char c_str<basic_string<Char, C...>>::value[];

template <typename ... X>
struct concat;

template <typename S>
struct concat<S>
 : concat<typename S::type>
{ };

template <typename S1, typename S2, typename ... Sp>
struct concat<S1, S2, Sp...>
 : concat<typename S1::type, typename concat<S2, Sp...>::type>
{ };

template <typename Char, Char ... C>
struct concat<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Char, Char ... C1, Char ... C2>
struct concat<basic_string<Char, C1...>, basic_string<Char, C2...> >
 : basic_string<Char, C1..., C2...>
{ };

template <typename Sep, typename ... X>
struct join;

template <typename Sep, typename S1, typename S2, typename ... Sp>
struct join<Sep, S1, S2, Sp...>
 : concat<S1, Sep, typename join<Sep, S2, Sp...>::type>
{ };

template <typename Sep, typename Str>
struct join<Sep, Str>
 : Str
{ };

template <typename Char, Char ... C>
struct join<basic_string<Char, C...>>
 : basic_string<Char>
{ };

template <unsigned I>
struct uint_to_str;

template <> struct uint_to_str<0u> : string<'0'> { };
template <> struct uint_to_str<1u> : string<'1'> { };
template <> struct uint_to_str<2u> : string<'2'> { };
template <> struct uint_to_str<3u> : string<'3'> { };
template <> struct uint_to_str<4u> : string<'4'> { };
template <> struct uint_to_str<5u> : string<'5'> { };
template <> struct uint_to_str<6u> : string<'6'> { };
template <> struct uint_to_str<7u> : string<'7'> { };
template <> struct uint_to_str<8u> : string<'8'> { };
template <> struct uint_to_str<9u> : string<'9'> { };

template <unsigned I>
struct uint_to_str
 : concat<typename uint_to_str<I/10>::type, typename uint_to_str<I%10>::type>
{ };

template <int I>
struct int_to_str
 : std::conditional<
	(I < 0),
	concat<string<'-'>, typename uint_to_str<unsigned(-I)>::type>,
	uint_to_str<unsigned( I)>
>::type{ };

} // namespace meta
} // namespace eagine

#endif //include guard

