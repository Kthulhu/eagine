/**
 *  @file eagine/exte/wrap_or_fwd.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_EXTE_WRAP_OR_FWD_1308281038_HPP
#define EAGINE_EXTE_WRAP_OR_FWD_1308281038_HPP

#include <eagine/exte/terminal.hpp>
#include <utility>

namespace EAGine {
namespace exte {

template <typename X>
struct wrap_or_fwd_result
{
	typedef terminal<X> type;
};

template <typename X>
struct wrap_or_fwd_result<X&>
{
	typedef terminal<X&> type;
};

template <typename Tag, typename ... Arg>
struct wrap_or_fwd_result<nary_expression<Tag, Arg...>>
{
	typedef nary_expression<Tag, Arg...> type;
};

template <typename T>
static constexpr inline
typename meta::enable_if<
	!is_expression<T>::value,
	terminal<T>
>::type wrap_or_fwd(T&& v)
{
	return {std::forward<T>(v)};
}

template <typename T>
static constexpr inline
typename meta::enable_if<
	!is_expression<T>::value,
	terminal<T&>
>::type wrap_or_fwd(T& v)
{
	return {v};
}

template <typename E>
static constexpr inline
typename meta::enable_if<
	is_expression<E>::value,
	E&&
>::type wrap_or_fwd(E&& e)
{
	return static_cast<E&&>(e);
}

} // namespace exte
} // namespace EAGine

#endif //include guard

