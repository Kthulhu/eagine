/**
 *  @file eagine/unit/detail.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef EAGINE_UNIT_DETAIL_1308281038_HPP
#define EAGINE_UNIT_DETAIL_1308281038_HPP

#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/nil_t.hpp>
#include <eagine/unit/base_dim.hpp>

namespace EAGine {
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

// plus
template <typename Dims1, typename Dims2>
struct plus;

template <>
struct plus<nil_t, nil_t>
 : nil_t
{ };

template <typename H, typename T>
struct plus<nil_t, dims<H, T>>
 : dims<H, T>
{ };

template <typename H, typename T>
struct plus<dims<H, T>, nil_t>
 : dims<H, T>
{ };

template <>
struct plus<dimless, dimless>
 : dimless
{ };

template <typename H, typename T>
struct plus<dims<H, T>, dimless>
 : dims<H, T>
{ };

template <typename H, typename T>
struct plus<dimless, dims<H, T>>
 : dims<H, T>
{ };

template <
	typename Dim,
	typename Pow1, typename Tail1,
	typename Pow2, typename Tail2
> struct plus<
	dims<dim_pow<Dim, Pow1>, Tail1>,
	dims<dim_pow<Dim, Pow2>, Tail2>
>: meta::conditional<
	(Pow1::value+Pow2::value == 0),
	typename plus<Tail1, Tail2>::type,
	dims<
		dim_pow<
			Dim,
			typename meta::plus<Pow1, Pow2>::type
		>,
		typename plus<Tail1, Tail2>::type
	>
>::type
{ };
	
template <
	typename Dim1, typename Pow1, typename Tail1,
	typename Dim2, typename Pow2, typename Tail2
>
struct plus<
	dims<dim_pow<Dim1, Pow1>, Tail1>, 
	dims<dim_pow<Dim2, Pow2>, Tail2> 
> : meta::conditional<
	(base::dim_num<Dim1>::value < base::dim_num<Dim2>::value),
	dims<
		dim_pow<Dim1, Pow1>,
		typename plus<
			Tail1,
			dims<dim_pow<Dim2, Pow2>, Tail2> 
		>::type
	>,
	dims<
		dim_pow<Dim2, Pow2>,
		typename plus<
			dims<dim_pow<Dim1, Pow1>, Tail1>,
			Tail2
		>::type
	>
>::type
{ };

// minus
template <typename Dims1, typename Dims2>
struct minus;

template <>
struct minus<nil_t, nil_t>
 : nil_t
{ };

template <typename H, typename T>
struct minus<dims<H, T>, nil_t>
 : dims<H, T>
{ };

template <typename D, typename P, typename T>
struct minus<nil_t, dims<dim_pow<D, P>, T>>
 : dims<dim_pow<D, typename meta::negate<P>::type>, T>
{ };

template <>
struct minus<dimless, dimless>
 : dimless
{ };

template <typename H, typename T>
struct minus<dims<H, T>, dimless>
 : dims<H, T>
{ };

template <typename D, typename P, typename T>
struct minus<dimless, dims<dim_pow<D, P>, T>>
 : dims<dim_pow<D, typename meta::negate<P>::type>, T>
{ };

template <
	typename Dim,
	typename Pow1, typename Tail1,
	typename Pow2, typename Tail2
> struct minus<
	dims<dim_pow<Dim, Pow1>, Tail1>,
	dims<dim_pow<Dim, Pow2>, Tail2>
>: meta::conditional<
	(Pow1::value-Pow2::value == 0),
	typename minus<Tail1, Tail2>::type,
	dims<
		dim_pow<
			Dim,
			typename meta::minus<Pow1, Pow2>::type
		>,
		typename minus<Tail1, Tail2>::type
	>
>::type
{ };
	
template <
	typename Dim1, typename Pow1, typename Tail1,
	typename Dim2, typename Pow2, typename Tail2
>
struct minus<
	dims<dim_pow<Dim1, Pow1>, Tail1>, 
	dims<dim_pow<Dim2, Pow2>, Tail2> 
> : meta::conditional<
	(base::dim_num<Dim1>::value < base::dim_num<Dim2>::value),
	dims<
		dim_pow<Dim1, Pow1>,
		typename minus<
			Tail1,
			dims<dim_pow<Dim2, Pow2>, Tail2> 
		>::type
	>,
	dims<
		dim_pow<Dim2, typename meta::negate<Pow2>::type>,
		typename minus<
			dims<dim_pow<Dim1, Pow1>, Tail1>,
			Tail2
		>::type
	>
>::type
{ };

template <typename Unit, typename Scale>
struct uni_sca;

template <typename Head, typename Tail>
struct unit_scales
{
	typedef unit_scales type;
};

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


} // namespace bits
} // namespace unit
} // namespace EAGine

#endif //include guard

