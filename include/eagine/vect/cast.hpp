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

namespace EAGine {
namespace vect {

template <typename DF, typename DT>
struct data_caster;

template <typename DF, typename DT>
static constexpr inline
typename DT::type data_cast(const typename DF::type& v)
{
	return data_caster<DF, DT>::apply(v, 0);
}

template <typename T, unsigned N>
struct data_caster<data<T, N>, data<T, N>>
{
	static constexpr inline
	typename data<T, N>::type
	apply(const typename data<T, N>::type& v, T)
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
		const typename data<TF, NF>::type& v,
		const typename data<TT, sizeof...(D)>::type& d,
		meta::integer_sequence<unsigned, I...>,
		meta::integer_sequence<unsigned, D...>
	)
	{
		return {TT(v[I])..., d[D]...};
	}

	template <unsigned ... I>
	static constexpr inline
	typename data<TT, NT>::type
	_cast(
		const typename data<TF, NF>::type& v,
		const typename data<TT, 0u>::type&,
		meta::integer_sequence<unsigned, I...>,
		meta::integer_sequence<unsigned>
	)
	{
		return {TT(v[I])...};
	}

	static constexpr inline
	typename data<TT, NT>::type
	apply(const typename data<TF, NF>::type& v, TT d)
	{
		typedef typename meta::make_integer_sequence<
			unsigned,
			(NT>NF)?NF:NT
		>::type is;
		typedef typename meta::make_integer_sequence<
			unsigned,
			(NT>NF)?NT-NF:0
		>::type ds;
		return _cast(v, fill<TT,(NT>NF)?NT-NF:0>::apply(d), is(), ds());
	}
};

} // namespace vect
} // namespace EAGine

#endif //include guard

