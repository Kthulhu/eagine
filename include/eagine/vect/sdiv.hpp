/**
 *  @file eagine/vect/sdiv.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_SDIV_1308281038_HPP
#define EAGINE_VECT_SDIV_1308281038_HPP

#include <eagine/vect/data.hpp>

namespace eagine {
namespace vect {

template <typename T, unsigned N>
struct sdiv
{
	typedef typename data<T, N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	static constexpr inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return a/b;
	}
};

#if EAGINE_USE_SIMD
#if defined(__GNUC__) || defined(__clang__)

template <typename T>
struct sdiv<T, 3>
{
	typedef typename data<T, 3>::type _dT;
	typedef typename data_param<T, 3>::type _dpT;

	static constexpr inline
	_dT _hlp(_dpT a, _dpT b, meta::true_type)
	{
		return a/_dT{b[0], b[1], b[2], T(1)};
	}

	static constexpr inline
	_dT _hlp(_dpT a, _dpT b, meta::false_type)
	{
		return a/b;
	}

	static constexpr inline
	_dT apply(_dpT a, _dpT b)
	noexcept
	{
		return _hlp(a, b, typename _has_vec_data<T, 3>::type());
	}
};

#endif
#endif

} // namespace vect
} // namespace eagine

#endif //include guard

