/**
 *  @file eagine/exte/op_excl_mark.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_OP_EXCL_MARK_1308281038_HPP
#define EAGINE_EXTE_OP_EXCL_MARK_1308281038_HPP

#include <eagine/exte/wrap_or_fwd.hpp>

namespace EAGine {
namespace exte {

// excl_mark_tag
template <>
struct operator_tag<meta::string<'!'>,-1>
{
	template <typename U>
	constexpr inline
	auto operator()(U&& v) const
	{
		return !v;
	}
};
template <int A>
using excl_mark_tag = operator_tag<meta::string<'!'>,-1>;

// unary exclamation mark
template <typename U>
static constexpr inline
unary_expression<
	excl_mark_tag<-1>,
	typename wrap_or_fwd_result<U>::type
>
operator ! (U&& v)
{
	return {wrap_or_fwd(std::forward<U>(v))};
}

} // namespace exte
} // namespace EAGine

#endif //include guard

