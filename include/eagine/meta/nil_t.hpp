/**
 *  @file eagine/meta/nil_t.hpp
 *  @brief NIL type.
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_META_NIL_T_1308281038_HPP
#define EAGINE_META_NIL_T_1308281038_HPP

#include <eagine/meta/int_const.hpp>

namespace EAGine {
namespace meta {

struct nil_t
{
	typedef nil_t type;
	static constexpr int value = 0;
};

template <typename X>
struct is_nil
 : false_type
{ };

template <>
struct is_nil<nil_t>
 : true_type
{ };

} // namespace meta
} // namespace EAGine

#endif //include guard

