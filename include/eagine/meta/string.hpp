/**
 *  @file eagine/meta/string.hpp
 *  @brief The compile-time strings.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_META_STRING_1308281038_HPP
#define EAGINE_META_STRING_1308281038_HPP

#include <eagine/meta/int_const.hpp>
#include <cstddef>

namespace EAGine {
namespace meta {

template <typename Char, Char ... C>
struct basic_string
{
	typedef basic_string<Char, C...> type;

	static constexpr Char value[] = { C..., '\0' };

	static constexpr std::size_t size = sizeof...(C);

	operator const char* (void) const
	{
		return value;
	}
};

template <typename Char, Char ... C>
constexpr Char basic_string<Char, C...>::value[];

template <char ... C>
struct string
 : basic_string<char, C...>
{ };

typedef string<> empty_string;

template <typename ... X>
struct concat;

template <typename S, typename ... Sp>
struct concat<S, Sp...>
 : concat<typename S::type, typename concat<Sp...>::type>
{ };

template <typename Char, Char ... C>
struct concat<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Char, Char ... C1, Char ... C2>
struct concat<basic_string<Char, C1...>, basic_string<Char, C2...> >
 : basic_string<Char, C1..., C2...>
{ };

} // namespace meta
} // namespace EAGine

#endif //include guard

