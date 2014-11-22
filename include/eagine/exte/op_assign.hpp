/**
 *  @file eagine/exte/op_assign.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_OP_ASSIGN_1308281038_HPP
#define EAGINE_EXTE_OP_ASSIGN_1308281038_HPP

#include <eagine/exte/wrap_or_fwd.hpp>

namespace eagine {
namespace exte {

// assign_tag
template <int A>
struct operator_tag<meta::string<'='>,A>
{
	template <typename L, typename R>
	auto operator()(L& l, R&& r) const
	{
		return l = std::forward<R>(r);
	}
};

// assignment to nullary_expression
template <typename Tag>
template <typename A>
constexpr inline
nary_expression<
	assign_tag<2>,
	nary_expression<Tag>,
	typename wrap_or_fwd_result<A>::type
> nary_expression<Tag>::operator = (A&& a)
{
	return {*this, wrap_or_fwd(std::forward<A>(a))};
}

// assignment to unary_expression
template <typename Tag, typename U>
template <typename A>
constexpr inline
nary_expression<
	assign_tag<2>,
	nary_expression<Tag, U>,
	typename wrap_or_fwd_result<A>::type
> nary_expression<Tag, U>::operator = (A&& a)
{
	return {*this, wrap_or_fwd(std::forward<A>(a))};
}

// assignment to binary_expression
template <typename Tag, typename L, typename R>
template <typename A>
constexpr inline
nary_expression<
	assign_tag<2>,
	nary_expression<Tag, L, R>,
	typename wrap_or_fwd_result<A>::type
> nary_expression<Tag, L, R>::operator = (A&& a)
{
	return {*this, wrap_or_fwd(std::forward<A>(a))};
}

// assignment to nary_expression
template <typename Tag, typename ... Arg>
template <typename A>
constexpr inline
nary_expression<
	assign_tag<2>,
	nary_expression<Tag, Arg...>,
	typename wrap_or_fwd_result<A>::type
> nary_expression<Tag, Arg...>::operator = (A&& a)
{
	return {*this, wrap_or_fwd(std::forward<A>(a))};
}

} // namespace exte
} // namespace eagine

#endif //include guard

