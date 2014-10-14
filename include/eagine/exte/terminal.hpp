/**
 *  @file eagine/exte/terminal.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_TERMINAL_1308281038_HPP
#define EAGINE_EXTE_TERMINAL_1308281038_HPP

#include <eagine/exte/expression.hpp>
#include <utility>

namespace EAGine {
namespace exte {

// terminal tag
struct terminal_tag
{
	template <typename T>
	T&& operator()(T&& v) const
	{
		return std::forward<T>(v);
	}
};

// terminal
template <typename U>
using terminal = unary_expression<terminal_tag, U>;

// val
template <typename T>
static constexpr inline
terminal<
	typename meta::remove_reference<T>::type
> val(T&& t)
{
	return {std::forward<T>(t)};

}

// val
template <typename T>
static constexpr inline
terminal<T> val(T& r)
{
	return {r};
}

// ref
template <typename T>
static constexpr inline
terminal<T&> ref(T& r)
{
	return {r};
}

} // namespace exte
} // namespace EAGine

#endif //include guard

