/**
 *  @file eagine/exte/op_pipe.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_OP_PIPE_1308281038_HPP
#define EAGINE_EXTE_OP_PIPE_1308281038_HPP

#include <eagine/exte/wrap_or_fwd.hpp>

namespace EAGine {
namespace exte {

// pipe_tag
struct pipe_tag { };

// dbl_pipe_tag
struct dbl_pipe_tag { };

// binary single pipe
template <typename L, typename R>
static constexpr inline
binary_expression<
	pipe_tag,
	typename wrap_or_fwd_result<L>::type,
	typename wrap_or_fwd_result<R>::type
>
operator | (L&& l, R&& r)
{
	return {
		wrap_or_fwd(std::forward<L>(l)),
		wrap_or_fwd(std::forward<R>(r))
	};
}

// binary double pipe
template <typename L, typename R>
static constexpr inline
binary_expression<
	dbl_pipe_tag,
	typename wrap_or_fwd_result<L>::type,
	typename wrap_or_fwd_result<R>::type
>
operator || (L&& l, R&& r)
{
	return {
		wrap_or_fwd(std::forward<L>(l)),
		wrap_or_fwd(std::forward<R>(r))
	};
}

} // namespace exte
} // namespace EAGine

#endif //include guard

