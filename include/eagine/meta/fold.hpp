/**
 *  @file eagine/meta/fold.hpp
 *  @brief Fold function.
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_FOLD_1308281038_HPP
#define EAGINE_META_FOLD_1308281038_HPP

#include <utility>

namespace eagine {
namespace meta {

template <typename Op, typename T>
static constexpr inline
auto fold_with(const Op&, T&& t)
{
	return std::forward<T>(t);
}

template <typename Op, typename H, typename N, typename ... T>
static constexpr inline
auto fold_with(const Op& op, H&& h, N&& n, T&& ... t)
{
	return op(h, fold_with(op, std::forward<N>(n), std::forward<T>(t)...));
}

template <typename Op, typename ... P>
static constexpr inline
auto fold(P&& ... p)
{
	return fold_with(Op(), std::forward<P>(p)...);
}

} // namespace meta
} // namespace eagine

#endif //include guard

