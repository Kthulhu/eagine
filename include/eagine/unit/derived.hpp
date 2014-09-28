/**
 *  @file eagine/unit/derived.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_DERIVED_1308281038_HPP
#define EAGINE_UNIT_DERIVED_1308281038_HPP

#include <eagine/unit/traits.hpp>
#include <eagine/meta/type_traits.hpp>

namespace EAGine {
namespace unit {

template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename add_result<U1, U2>::type
>::type operator + (U1, U2);

template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename sub_result<U1, U2>::type
>::type operator - (U1, U2);

template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename mul_result<U1, U2>::type
>::type operator * (U1, U2);

template <typename U1, typename U2>
typename meta::enable_if<
	is_unit<U1>::value &&
	is_unit<U2>::value,
	typename div_result<U1, U2>::type
>::type operator / (U1, U2);

} // namespace unit
} // namespace EAGine

#endif //include guard

