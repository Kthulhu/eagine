/**
 *  @file eagine/exte/expression.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_EXPRESSION_1308281038_HPP
#define EAGINE_EXTE_EXPRESSION_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/string.hpp>

namespace EAGine {
namespace exte {

template <typename Symbol, int Arity>
struct operator_tag;

template <typename Tag, typename ... Arg>
struct nary_expression;

// assign_tag
template <int A>
using assign_tag = operator_tag<meta::string<'='>,A>;

// wrap_or_fwd_result
template <typename X>
struct wrap_or_fwd_result;

// is_expression trait
template <typename X>
struct is_expression
 : meta::false_type
{ };

// nullary_expression
template <typename Tag>
struct nary_expression<Tag>
{
	template <typename A>
	constexpr
	nary_expression<
		assign_tag<2>,
		nary_expression<Tag>,
		typename wrap_or_fwd_result<A>::type
	> operator = (A&&);
};

// unary_expression
template <typename Tag, typename U>
struct nary_expression<Tag, U>
{
	U value;

	template <typename A>
	constexpr
	nary_expression<
		assign_tag<2>,
		nary_expression<Tag, U>,
		typename wrap_or_fwd_result<A>::type
	> operator = (A&&);
};

// binary_expression
template <typename Tag, typename L, typename R>
struct nary_expression<Tag, L, R>
{
	L left_value;
	R right_value;

	template <typename A>
	constexpr
	nary_expression<
		assign_tag<2>,
		nary_expression<Tag, L, R>,
		typename wrap_or_fwd_result<A>::type
	> operator = (A&&);
};

// nary_expression
template <typename Tag, typename ... Arg>
struct nary_expression
{
	template <typename A>
	constexpr
	nary_expression<
		assign_tag<2>,
		nary_expression<Tag, Arg...>,
		typename wrap_or_fwd_result<A>::type
	> operator = (A&&);
};

// is_expression<nary_expression>
template <typename Tag, typename ... Arg>
struct is_expression<nary_expression<Tag, Arg...>>
 : meta::true_type
{ };

template <typename Tag>
using nullary_expression = nary_expression<Tag>;

template <typename Tag, typename U>
using unary_expression = nary_expression<Tag, U>;

template <typename Tag, typename L, typename R>
using binary_expression = nary_expression<Tag, L, R>;

} // namespace exte
} // namespace EAGine

#endif //include guard

