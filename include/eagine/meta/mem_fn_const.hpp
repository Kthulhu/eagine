/**
 *  @file eagine/meta/mem_fn_const.hpp
 *  @brief Compile-time member function pointer constant.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_MEM_FN_CONST_1308281038_HPP
#define EAGINE_META_MEM_FN_CONST_1308281038_HPP

#include <utility>

namespace eagine {
namespace meta {

template <typename T, T Ptr>
struct member_function_constant;

template <typename RV, typename C, typename ... P, RV(C::*Ptr)(P...)>
struct member_function_constant<RV(C::*)(P...), Ptr>
{
	typedef RV(C::*pointer)(P...);
	typedef RV(*free_pointer)(C*, P...);
	typedef RV result_type;
	typedef C scope;

	static RV free_func(C* c, P ... a)
	{
		return (c->*Ptr)(std::forward<P>(a)...);
	}

	static free_pointer make_free(void)
	noexcept
	{
		return &free_func;
	}
};

template <typename RV, typename C, typename ... P, RV(C::*Ptr)(P...) const>
struct member_function_constant<RV(C::*)(P...) const, Ptr>
{
	typedef RV(C::*pointer)(P...) const;
	typedef RV(*free_pointer)(const C*, P...);
	typedef RV result_type;
	typedef C scope;

	static RV free_func(const C* c, P ... a)
	{
		return (c->*Ptr)(std::forward<P>(a)...);
	}

	static free_pointer make_free(void)
	noexcept
	{
		return &free_func;
	}
};

} // namespace meta
} // namespace eagine

#endif //include guard

