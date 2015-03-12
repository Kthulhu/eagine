/**
 *  @file eagine/vect/shuffle.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_SHUFFLE_1308281038_HPP
#define EAGINE_VECT_SHUFFLE_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/vect/data.hpp>
#include <cstdint>

namespace eagine {
namespace vect {

template <int ... I>
struct shuffle_mask
{ };

#if EAGINE_USE_SIMD && defined(__GNUC__) && !defined(__clang__)
template <typename T, unsigned N>
struct mask : _vec_data<T, N>
{ };

template <unsigned N>
struct mask<float, N> : _vec_data<std::int32_t, N>
{ };

template <unsigned N>
struct mask<double, N> : _vec_data<std::int64_t, N>
{ };
#endif

template <typename T, unsigned N>
struct shuffle
{
	typedef typename data<T, N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	template <int ... I>
	static constexpr inline
	_dT _do_apply(
		_dpT v,
		shuffle_mask<I...>,
		meta::true_type
	) noexcept
	{
		return typename data<T, N>::type{v[I]...};
	}

	template <int ... I>
	static constexpr inline
	_dT _do_apply(
		_dpT v,
		shuffle_mask<I...>,
		meta::false_type
	) noexcept
	{
#if EAGINE_USE_SIMD && defined(__clang__)
		return _dT(__builtin_shufflevector(v, v, I...));
#elif EAGINE_USE_SIMD && defined(__GNUC__)
		typedef typename mask<T, N>::type _mT;
		return __builtin_shuffle(v, _mT{I...});
#else
		return _do_apply(
			v,
			shuffle_mask<I...>(),
			meta::true_type()
		);
#endif
	}

	template <int ... I>
	static constexpr inline
	_dT apply(
		_dpT v,
		shuffle_mask<I...> m = {}
	) noexcept
	{
		return _do_apply(
			v, m,
			typename meta::is_same<_dT, _ary_data<T, N>>::type()
		);
	}
};

template <typename T, unsigned N>
struct shuffle2
{
	typedef typename data<T, N>::type _dT;
	typedef typename data_param<T, N>::type _dpT;

	template <unsigned M, int ... I>
	static inline
	_dT _do_apply(
		_dpT v1,
		_dpT v2,
		shuffle_mask<I...>,
		meta::unsigned_constant<M>,
		meta::true_type
	) noexcept
	{
		return typename data<T, N>::type{
			I<0?T(0):(unsigned(I)<N? v1[I]: v2[I%N])...
		};
	}

	template <unsigned M, int ... I>
	static inline
	_dT _do_apply(
		_dpT v1,
		_dpT v2,
		shuffle_mask<I...>,
		meta::unsigned_constant<M>,
		meta::false_type
	) noexcept
	{
#if EAGINE_USE_SIMD && defined(__clang__)
		return _dT(__builtin_shufflevector(v1,v2, I...));
#elif EAGINE_USE_SIMD && defined(__GNUC__)
		typedef typename mask<T, N>::type _mT;
		return __builtin_shuffle(v1, v2, _mT{I...});
#else
		return _do_apply(
			v1, v2,
			shuffle_mask<I...>(),
			meta::unsigned_constant<M>(),
			meta::true_type()
		);
#endif
	}

	template <int ... I>
	static inline
	_dT _do_apply(
		_dpT v1,
		_dpT v2,
		shuffle_mask<I...>,
		meta::unsigned_constant<3>,
		meta::false_type
	) noexcept
	{
#if EAGINE_USE_SIMD && defined(__clang__)
		return _dT(__builtin_shufflevector(v1,v2, I>=3?I+1:I...));
#elif EAGINE_USE_SIMD && defined(__GNUC__)
		typedef typename mask<T, N>::type _mT;
		return __builtin_shuffle(v1, v2, _mT{(I>=3?I+1:I)...});
#else
		return _do_apply(
			v1, v2,
			shuffle_mask<I...>(),
			meta::unsigned_constant<3>(),
			meta::true_type()
		);
#endif
	}

	template <int ... I>
	static inline
	_dT apply(
		_dpT v1,
		_dpT v2,
		shuffle_mask<I...> m = {}
	) noexcept
	{
		return _do_apply(
			v1, v2, m,
			meta::unsigned_constant<N>(),
			typename meta::is_same<_dT, _ary_data<T, N>>::type()
		);
	}
};

} // namespace vect
} // namespace eagine

#endif //include guard

