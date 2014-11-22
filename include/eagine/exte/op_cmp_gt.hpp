/**
 *  @file eagine/exte/op_cmp_gt.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_OP_CMP_GT_1308281038_HPP
#define EAGINE_EXTE_OP_CMP_GT_1308281038_HPP

#include <eagine/exte/wrap_or_fwd.hpp>

namespace eagine {
namespace exte {

// cmp_gt_tag
template <>
struct operator_tag<meta::string<'>'>, 2>
{
	template <typename L, typename R>
	constexpr inline
	auto operator()(L&& l, R&& r) const
	{
		return l > r;
	}
};
template <int A>
using cmp_gt_tag = operator_tag<meta::string<'>'>, A>;

// binary cmp_gt
template <typename L, typename R>
static constexpr inline
binary_expression<
	cmp_gt_tag<2>,
	typename wrap_or_fwd_result<L>::type,
	typename wrap_or_fwd_result<R>::type
>
operator >  (L&& l, R&& r)
{
	return {
		wrap_or_fwd(std::forward<L>(l)),
		wrap_or_fwd(std::forward<R>(r))
	};
}

} // namespace exte
} // namespace eagine

#endif //include guard

