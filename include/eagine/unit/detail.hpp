/**
 *  @file eagine/unit/detail.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_UNIT_DETAIL_1308281038_HPP
#define EAGINE_UNIT_DETAIL_1308281038_HPP

#include <eagine/unit/fwd.hpp>
#include <eagine/unit/base_dim.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/nil_t.hpp>

namespace eagine {
namespace unit {
namespace bits {

// nil_t
using meta::nil_t;

// zero
typedef meta::integral_constant<int, 0> zero;

template <template <class...> class MetaFunc, typename X, typename ... P>
struct apply;

// dim_pow
template <typename Dim, typename Pow>
struct dim_pow
{
	typedef Dim dim;
	typedef Pow pow;
};

// dims
template <typename Head, typename Tail>
struct dims
{
	typedef dims type;
};

typedef dims<nil_t, nil_t> dimless;

// apply
template <template <class...> class MF, typename ... P>
struct apply<MF, nil_t, P...>
 : MF<P...>
{ };

template <template <class...> class MF, typename ... P>
struct apply<MF, dims<nil_t, nil_t>, P...>
 : MF<P...>
{ };

template <template <class...> class MF, typename H, typename T, typename ... P>
struct apply<MF, dims<H, T>, P...>
 : apply<MF, T, P..., H>
{ };

// dim_add
template <typename Dims1, typename Dims2>
struct dim_add;

template <>
struct dim_add<nil_t, nil_t>
 : nil_t
{ };

template <typename H, typename T>
struct dim_add<nil_t, dims<H, T>>
 : dims<H, T>
{ };

template <typename H, typename T>
struct dim_add<dims<H, T>, nil_t>
 : dims<H, T>
{ };

template <>
struct dim_add<dimless, dimless>
 : dimless
{ };

template <typename H, typename T>
struct dim_add<dims<H, T>, dimless>
 : dims<H, T>
{ };

template <typename H, typename T>
struct dim_add<dimless, dims<H, T>>
 : dims<H, T>
{ };

template <
	typename Dim,
	typename Pow1, typename Tail1,
	typename Pow2, typename Tail2
> struct dim_add<
	dims<dim_pow<Dim, Pow1>, Tail1>,
	dims<dim_pow<Dim, Pow2>, Tail2>
>: meta::conditional<
	(Pow1::value+Pow2::value == 0),
	typename dim_add<Tail1, Tail2>::type,
	dims<
		dim_pow<
			Dim,
			typename meta::plus<Pow1, Pow2>::type
		>,
		typename dim_add<Tail1, Tail2>::type
	>
>::type
{ };
	
template <
	typename Dim1, typename Pow1, typename Tail1,
	typename Dim2, typename Pow2, typename Tail2
>
struct dim_add<
	dims<dim_pow<Dim1, Pow1>, Tail1>, 
	dims<dim_pow<Dim2, Pow2>, Tail2> 
> : meta::conditional<
	(base::dim_num<Dim1>::value < base::dim_num<Dim2>::value),
	dims<
		dim_pow<Dim1, Pow1>,
		typename dim_add<
			Tail1,
			dims<dim_pow<Dim2, Pow2>, Tail2> 
		>::type
	>,
	dims<
		dim_pow<Dim2, Pow2>,
		typename dim_add<
			dims<dim_pow<Dim1, Pow1>, Tail1>,
			Tail2
		>::type
	>
>::type
{ };

// dim_sub
template <typename Dims1, typename Dims2>
struct dim_sub;

template <>
struct dim_sub<nil_t, nil_t>
 : dimless
{ };

template <>
struct dim_sub<nil_t, dims<nil_t, nil_t>>
 : dimless
{ };

template <typename H, typename T>
struct dim_sub<dims<H, T>, nil_t>
 : dims<H, T>
{ };

template <typename D, typename P, typename T>
struct dim_sub<nil_t, dims<dim_pow<D, P>, T>>
 : dims<
	dim_pow<D, typename meta::negate<P>::type>,
	typename dim_sub<nil_t, T>::type
>
{ };

template <>
struct dim_sub<dimless, dimless>
 : dimless
{ };

template <typename H, typename T>
struct dim_sub<dims<H, T>, dimless>
 : dims<H, T>
{ };

template <typename D, typename P, typename T>
struct dim_sub<dimless, dims<dim_pow<D, P>, T>>
 : dims<dim_pow<D, typename meta::negate<P>::type>, T>
{ };

template <
	typename Dim,
	typename Pow1, typename Tail1,
	typename Pow2, typename Tail2
> struct dim_sub<
	dims<dim_pow<Dim, Pow1>, Tail1>,
	dims<dim_pow<Dim, Pow2>, Tail2>
>: meta::conditional<
	(Pow1::value-Pow2::value == 0),
	typename dim_sub<Tail1, Tail2>::type,
	dims<
		dim_pow<
			Dim,
			typename meta::minus<Pow1, Pow2>::type
		>,
		typename dim_sub<Tail1, Tail2>::type
	>
>::type
{ };
	
template <
	typename Dim1, typename Pow1, typename Tail1,
	typename Dim2, typename Pow2, typename Tail2
>
struct dim_sub<
	dims<dim_pow<Dim1, Pow1>, Tail1>, 
	dims<dim_pow<Dim2, Pow2>, Tail2> 
> : meta::conditional<
	(base::dim_num<Dim1>::value < base::dim_num<Dim2>::value),
	dims<
		dim_pow<Dim1, Pow1>,
		typename dim_sub<
			Tail1,
			dims<dim_pow<Dim2, Pow2>, Tail2> 
		>::type
	>,
	dims<
		dim_pow<Dim2, typename meta::negate<Pow2>::type>,
		typename dim_sub<
			dims<dim_pow<Dim1, Pow1>, Tail1>,
			Tail2
		>::type
	>
>::type
{ };

// uni_sca
template <typename Unit, typename Scale>
struct uni_sca;

template <typename Head, typename Tail>
struct unit_scales
{
	typedef unit_scales type;
};

// insert
template <typename UnitScales, typename Unit, typename Scale>
struct insert;

template <typename U, typename S>
struct insert<nil_t, U, S>
 : unit_scales<uni_sca<U, S>, nil_t>
{ };

template <typename U, typename S>
struct insert<unit_scales<nil_t, nil_t>, U, S>
 : unit_scales<uni_sca<U, S>, nil_t>
{ };

template <typename U, typename SO, typename SN, typename T>
struct insert<unit_scales<uni_sca<U, SO>, T>, U, SN>
 : unit_scales<uni_sca<U, SN>, T>
{ };

template <typename H, typename T, typename U, typename S>
struct insert<unit_scales<H, T>, U, S>
 : unit_scales<H, typename insert<T, U, S>::type>
{ };

// get_scale
template <typename UnitScales, typename Unit, typename Fallback>
struct get_scale;

template <typename U, typename Fallback>
struct get_scale<nil_t, U, Fallback>
 : Fallback
{ };

template <typename U, typename Fallback>
struct get_scale<unit_scales<nil_t, nil_t>, U, Fallback>
 : Fallback
{ };

template <typename U, typename Scale, typename T, typename F>
struct get_scale<unit_scales<uni_sca<U, Scale>, T>, U, F>
 : Scale
{ };

template <typename H, typename T, typename U, typename F>
struct get_scale<unit_scales<H, T>, U, F>
 : get_scale<T, U, F>
{ };

// get_dim
template <typename UnitScales, typename BaseDim, typename Fallback>
struct get_dim_unit;

template <typename BD, typename Fallback>
struct get_dim_unit<nil_t, BD, Fallback>
 : Fallback
{ };

template <typename BD, typename Fallback>
struct get_dim_unit<unit_scales<nil_t, nil_t>, BD, Fallback>
 : Fallback
{ };

template <typename U, typename S, typename T, typename BD, typename F>
struct get_dim_unit<unit_scales<uni_sca<U, S>, T>, BD, F>
 : meta::conditional<
	meta::is_same<typename U::dimension, BD>::value,
	base::scaled_unit<S, U>,
	typename get_dim_unit<T, BD, F>::type
>::type
{ };

// merge
template <typename UnitScales1, typename UnitScales2>
struct merge;

template <>
struct merge<nil_t, nil_t>
 : unit_scales<nil_t, nil_t>
{ };

template <>
struct merge<unit_scales<nil_t, nil_t>, unit_scales<nil_t, nil_t>>
 : unit_scales<nil_t, nil_t>
{ };

template <typename H, typename T>
struct merge<unit_scales<H, T>, nil_t>
 : unit_scales<H, T>
{ };

template <typename H, typename T>
struct merge<nil_t, unit_scales<H, T>>
 : unit_scales<H, T>
{ };

template <typename H, typename T>
struct merge<unit_scales<H, T>, unit_scales<nil_t, nil_t>>
 : unit_scales<H, T>
{ };

template <typename H, typename T>
struct merge<unit_scales<nil_t, nil_t>, unit_scales<H, T>>
 : unit_scales<H, T>
{ };

template <typename U, typename S1, typename S2, typename T1, typename T2>
struct merge<
	unit_scales<uni_sca<U, S1>, T1>,
	unit_scales<uni_sca<U, S2>, T2>
> : unit_scales<uni_sca<U, S1>, typename merge<T1, T2>::type>
{ };

template <
	typename U1, typename U2,
	typename S1, typename S2,
	typename T1, typename T2
> struct merge<
	unit_scales<uni_sca<U1, S1>, T1>,
	unit_scales<uni_sca<U2, S2>, T2>
>: meta::conditional<
	(
		base::dim_num<typename U1::dimension>::value<
		base::dim_num<typename U2::dimension>::value
	),
	unit_scales<
		uni_sca<U1, S1>,
		typename merge<T1, unit_scales<uni_sca<U2, S2>, T2>>::type
	>,
	unit_scales<
		uni_sca<U2, S2>,
		typename merge<unit_scales<uni_sca<U1, S1>, T1>, T2>::type
	>
>{ };

// _sc_unit_sc_hlp
template <typename Scales, typename System>
struct _sc_unit_sc_hlp
{
	template <typename T>
	static constexpr inline T _pow(T v, int exp)
	{
		return	(exp == 0)?1:
			(exp >  0)?
				_pow(v, exp-1)*v:
				_pow(v, exp+1)/v;
	}

	template <typename DimPow>
	static constexpr inline auto _one_dim_pow(DimPow)
	{
		typedef typename System::template base_unit<
			typename DimPow::dim
		>::type base_unit;

		typedef typename base_unit::scale base_scale;

		return _pow(
			bits::get_scale<
				Scales,
				base_unit,
				base_scale
			>::value,
			DimPow::pow::value
		);
	}

	static constexpr double _prod(void)
	noexcept
	{
		return 1.0;
	}

	template <typename X, typename ... P>
	static constexpr auto _prod(X v, P ... p)
	{
		return v*_prod(p...);
	}
};

} // namespace bits
} // namespace unit
} // namespace eagine

#endif //include guard

