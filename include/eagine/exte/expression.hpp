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

namespace EAGine {
namespace exte {

// is_expression trait
template <typename X>
struct is_expression
 : meta::false_type
{ };

// unary_expression
template <typename Tag, typename U>
struct unary_expression
{
	typedef U value_type;
	value_type value;
};

// is_expression<unary_expression>
template <typename Tag, typename U>
struct is_expression<unary_expression<Tag, U>>
 : meta::true_type
{ };


// binary expression
template <typename Tag, typename L, typename R>
struct binary_expression
{
	typedef L left_value_type;
	typedef R right_value_type;

	L left_value;
	R right_value;
};

// is_expression<binary_expression>
template <typename Tag, typename L, typename R>
struct is_expression<binary_expression<Tag, L, R>>
 : meta::true_type
{ };

} // namespace exte
} // namespace EAGine

#endif //include guard

