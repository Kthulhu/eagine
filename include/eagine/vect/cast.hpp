/**
 *  @file eagine/vect/cast.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_VECT_CAST_1308281038_HPP
#define EAGINE_VECT_CAST_1308281038_HPP

#include <eagine/vect/fill.hpp>
#include <eagine/meta/int_sequence.hpp>

namespace eagine {
namespace vect {

template <typename DF, typename DT>
struct data_caster;

template <typename T, unsigned N>
struct data_caster<data<T, N>, data<T, N>>
{
	static constexpr inline
	typename data<T, N>::type
	apply(typename param<data<T, N>>::type v, T)
	noexcept
	{
		return v;
	}
};

template <typename TF, unsigned NF, typename TT, unsigned NT>
struct data_caster<data<TF, NF>, data<TT, NT>>
{
	template <unsigned ... I, unsigned ... D>
	static constexpr inline
	typename data<TT, NT>::type
	_cast(
		typename param<data<TF, NF>>::type v,
		typename param<data<TT, sizeof...(D)>>::type d,
		meta::unsigned_sequence<I...>,
		meta::unsigned_sequence<D...>
	) noexcept
	{
		return typename data<TT, NT>::type
			{TT(v[I])..., TT(d[D])...};
	}

	template <unsigned ... I>
	static constexpr inline
	typename data<TT, NT>::type
	_cast(
		typename param<data<TF, NF>>::type v,
		typename param<data<TT, 0u>>::type,
		meta::unsigned_sequence<I...>,
		meta::integer_sequence<unsigned>
	) noexcept
	{
		return typename data<TT, NT>::type
			{TT(v[I])...};
	}

	static constexpr inline
	typename data<TT, NT>::type
	apply(
		typename param<data<TF, NF>>::type v,
		typename param<data<TT, (NT>NF)?NT-NF:0>>::type d
	)
	noexcept
	{
		typedef typename meta::make_unsigned_sequence<
			(NT>NF)?NF:NT
		>::type is;
		typedef typename meta::make_unsigned_sequence<
			(NT>NF)?NT-NF:0
		>::type ds;
		return _cast(v, d, is(), ds());
	}

	static constexpr inline
	typename data<TT, NT>::type
	apply(typename param<data<TF, NF>>::type v, TT d)
	noexcept
	{
		return apply(v, fill<TT, (NT>NF)?NT-NF:0>::apply(d));
	}
};

template <typename TF, unsigned NF, typename TT, unsigned NT>
struct cast
 : data_caster<data<TF, NF>, data<TT, NT>>
{ };

} // namespace vect
} // namespace eagine

#endif //include guard

