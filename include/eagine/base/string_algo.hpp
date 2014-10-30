/**
 *  @file eagine/base/string.hpp
 *  @brief String algorithms
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_STRING_ALGO_1308281038_HPP
#define EAGINE_BASE_STRING_ALGO_1308281038_HPP

#include <eagine/base/string.hpp>

namespace EAGine {
namespace base {

// string_view
template <typename Str>
struct string_view
{
	typedef basic_string_ref<
		typename meta::add_const<
			typename char_string_traits<Str>::value_type
		>::type
	> type;
};

// are_compatible_string_views
template <typename X1, typename X2>
struct are_compatible_string_views
 : detail::are_char_strings_any_const<
	typename char_string_traits<X1>::value_type,
	X1, X2
>
{ };

// slice
template <typename Str>
inline 
typename meta::enable_if<
	is_string<Str>::value,
	typename string_view<Str>::type
>::type
slice(const Str& str, std::size_t pos, std::size_t len)
noexcept
{
	if(pos > str.size())
	{
		pos = str.size();
	}
	if(len > str.size()-pos)
	{
		len = str.size()-pos;
	}
	return {str.data()+pos, len};
}

// slice
template <typename Str>
inline 
typename meta::enable_if<
	is_string<Str>::value,
	typename string_view<Str>::type
>::type
slice(const Str& str, std::size_t pos)
noexcept
{
	if(pos > str.size())
	{
		pos = str.size();
	}
	return {str.data()+pos, str.size()-pos};
}

// head
template <typename Str>
inline 
typename meta::enable_if<
	is_string<Str>::value,
	typename string_view<Str>::type
>::type
head(const Str& str, std::size_t len)
noexcept
{
	return slice(str, 0, len);
}

// tail
template <typename Str>
inline 
typename meta::enable_if<
	is_string<Str>::value,
	typename string_view<Str>::type
>::type
tail(const Str& str, std::size_t len)
noexcept
{
	if(len > str.size())
	{
		len = str.size();
	}
	return slice(str, str.size()-len, len);
}

// starts_with
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	bool
>::type
starts_with(const Str1& str, const Str2& with)
noexcept
{
	return head(str, with.size()) == with;
}

// ends_with
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	bool
>::type
ends_with(const Str1& str, const Str2& with)
noexcept
{
	return tail(str, with.size()) == with;
}

// find_pos
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	std::size_t
>::type
find_pos(const Str1& str, const Str2& target)
noexcept
{
	if(!str.empty() && !target.empty())
	{
		const std::size_t ls = str.size();
		const std::size_t lt = target.size();

		if(ls >= lt)
		{
			std::size_t p = 0;
			const std::size_t n = ls-lt;

			while(p != n)
			{
				if(slice(str, p, lt) == target)
				{
					return p;
				}
				++p;
			}
		}
		return ls;
	}
	return 0;
}

// contains
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	bool
>::type
contains(const Str1& str, const Str2& target)
noexcept
{
	return find_pos(str, target) < str.size();
}

// find
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	typename string_view<Str1>::type
>::type
find(const Str1& str, const Str2& target)
noexcept
{
	return slice(str, find_pos(str, target));
}

// strip_prefix
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	typename string_view<Str1>::type
>::type
strip_prefix(const Str1& str, const Str2& target)
noexcept
{
	std::size_t ofs = 0;
	if(starts_with(str, target))
	{
		ofs = target.size();
	}
	return slice(str, ofs);
}

// strip_suffix
template <typename Str1, typename Str2>
inline
typename meta::enable_if<
	are_compatible_string_views<Str1, Str2>::value,
	typename string_view<Str1>::type
>::type
strip_suffix(const Str1& str, const Str2& target)
noexcept
{
	std::size_t ofs = str.size();
	if(ends_with(str, target))
	{
		ofs = ofs-target.size();
	}
	return slice(str, 0, ofs);
}

} // namespace base
} // namespace EAGine

#endif //include guard

