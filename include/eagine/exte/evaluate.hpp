/**
 *  @file eagine/exte/evaluate.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_EVALUATE_1308281038_HPP
#define EAGINE_EXTE_EVALUATE_1308281038_HPP

#include <eagine/exte/terminal.hpp>

namespace EAGine {
namespace exte {

// evaluate terminal
template <typename Evaluator, typename U>
static constexpr inline
decltype(auto) evaluate(
	const Evaluator& ev,
	const unary_expression<terminal_tag, U>& ex
)
{
	return ev.eval(terminal_tag(), ex.value);
}

// evaluate nullary expression
template <typename Evaluator, typename Tag>
static constexpr inline
decltype(auto) evaluate(
	const Evaluator& ev,
	const nullary_expression<Tag>& ex
)
{
	return ev.eval(Tag());
}

// evaluate unary expression
template <typename Evaluator, typename Tag, typename U>
static constexpr inline
decltype(auto) evaluate(
	const Evaluator& ev,
	const unary_expression<Tag, U>& ex
)
{
	return ev.eval(Tag(), evaluate(ev, ex.value));
}

// evaluate binary_expression
template <typename Evaluator, typename Tag, typename L, typename R>
static constexpr inline
decltype(auto) evaluate(
	const Evaluator& ev,
	const binary_expression<Tag, L, R>& ex
)
{
	return ev.eval(
		Tag(),
		evaluate(ev, ex.left_value),
		evaluate(ev, ex.right_value)
	);
}

} // namespace exte
} // namespace EAGine

#endif //include guard

