/**
 *  @file eagine/math/matrix.hpp
 *
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_MATRIX_1308281038_HPP
#define EAGINE_MATH_MATRIX_1308281038_HPP

#include <eagine/math/config.hpp>
#include <eagine/math/vector.hpp>
#include <eagine/math/difference.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/int_sequence.hpp>
#include <cassert>

namespace eagine {
namespace math {

// matrix Row-Major/Column-Major
template <typename T, unsigned R, unsigned C, bool RM>
struct matrix
{
	typedef matrix type;

	typedef typename vect::data<T, RM?C:R>::type _vT;

	_vT _v[RM?R:C];

	template <typename P, unsigned ... I>
	static inline
	matrix _from_hlp(
		const P* dt,
		std::size_t sz,
		meta::unsigned_sequence<I...>
	) noexcept
	{
		return matrix{{
			vect::from_array<T, RM?C:R>::apply(
				dt+I*(RM?C:R),
				sz-I*(RM?C:R)
			)...
		}};
	}

	template <typename P>
	static inline
	matrix from(const P* dt, std::size_t sz)
	noexcept
	{
		return _from_hlp(
			dt, sz,
			meta::make_unsigned_sequence<RM?R:C>()
		);
	}

	template <typename P, unsigned M, unsigned N, unsigned ... I>
	static inline
	matrix _from_hlp(
		const matrix<P,M,N,RM>& m,
		meta::unsigned_sequence<I...>
	) noexcept
	{
		return matrix{{
			vect::cast<
				P,(RM?N:M),
				T,(RM?C:R)
			>::apply(m._v[I],T(0))...
		}};
	}

	template <typename P, unsigned M, unsigned N>
	static inline
	typename meta::enable_if<
		(R<=M)&&(C<=N),
		matrix
	>::type
	from(const matrix<P,M,N,RM>& m)
	noexcept
	{
		return _from_hlp(
			m,
			meta::make_unsigned_sequence<RM?R:C>()
		);
	}

	inline
	const vector<T, RM?C:R> operator [] (unsigned i) const
	noexcept
	{
		return vector<T, RM?C:R>{_v[i]};
	}
};

template <typename X>
struct is_row_major;

template <typename T, unsigned R, unsigned C, bool RM>
struct is_row_major<matrix<T,R,C,RM>>
 : meta::boolean_constant<RM>
{ };

// reordered matrix trait
template <typename X>
struct reordered_matrix;

// reordered matrix
template <typename T, unsigned R, unsigned C, bool RM>
struct reordered_matrix<matrix<T,R,C,RM>>
 : matrix<T,R,C,!RM>
{ };

// (number of) rows
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
unsigned rows(const matrix<T,R,C,RM>&)
noexcept
{
	return R;
}

// (number of) columns
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
unsigned columns(const matrix<T,R,C,RM>&)
noexcept
{
	return C;
}

// (is) row major
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
bool row_major(const matrix<T,R,C,RM>&)
noexcept
{
	return RM;
}

// equality
template <typename T, unsigned R, unsigned C, bool RM>
static inline
bool
operator == (const matrix<T,R,C,RM>& a, const matrix<T,R,C,RM>& b)
noexcept
{
	for(unsigned i=0;i<(RM?R:C); ++i)
	{
		if(!vect::equal<T, (RM?C:R)>::apply(a._v[i], b._v[i]))
		{
			return false;
		}
	}
	return true;
}

// non-eqality
template <typename T, unsigned R, unsigned C, bool RM>
static inline
bool
operator != (const matrix<T,R,C,RM>& a, const matrix<T,R,C,RM>& b)
noexcept
{
	for(unsigned i=0;i<(RM?R:C); ++i)
	{
		if(!vect::equal<T, (RM?C:R)>::apply(a._v[i], b._v[i]))
		{
			return true;
		}
	}
	return false;
}

// get (Row-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(I<R && J<C), T>::type
get(const matrix<T,R,C,true>& m)
noexcept
{
	return m._v[I][J];
}

// get (Column-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(I<R && J<C), T>::type
get(const matrix<T,R,C,false>& m)
noexcept
{
	return m._v[J][I];
}

// get (Row-major, run-time)
template <typename T, unsigned R, unsigned C>
static constexpr inline
T get(const matrix<T,R,C,true>& m, unsigned i, unsigned j)
noexcept
{
	return m._v[i][j];
}

// get (Column-major, run-time)
template <typename T, unsigned R, unsigned C>
static constexpr inline
T get(const matrix<T,R,C,false>& m, unsigned i, unsigned j)
noexcept
{
	return m._v[j][i];
}

// set (Row-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static inline
typename meta::enable_if<(I<R && J<C), void>::type
set(matrix<T,R,C,true>& m, const T& v)
noexcept
{
	m._v[I][J] = v;
}

// set (Column-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static inline
typename meta::enable_if<(I<R && J<C), void>::type
set(matrix<T,R,C,false>& m, const T& v)
noexcept
{
	m._v[J][I] = v;
}

// set (Row-major, run-time)
template <typename T, unsigned R, unsigned C>
static inline
void set(matrix<T,R,C,true>& m, unsigned i, unsigned j, const T& v)
noexcept
{
	m._v[i][j] = v;
}

// set (Column-major, run-time)
template <typename T, unsigned R, unsigned C>
static inline
void set(matrix<T,R,C,false>& m, unsigned i, unsigned j, const T& v)
noexcept
{
	m._v[j][i] = v;
}

// transpose_tpl helper 4x4 matrix
template <bool DstRM, typename T>
static constexpr inline
matrix<T,4,4,DstRM> transpose_tpl_hlp(
	const typename vect::data<T, 4>::type& q0,
	const typename vect::data<T, 4>::type& q1,
	const typename vect::data<T, 4>::type& q2,
	const typename vect::data<T, 4>::type& q3
) noexcept
{
	return matrix<T,4,4,DstRM>{{
		vect::shuffle2<T,4>::template apply<0,2,4,6>(q0, q2),
		vect::shuffle2<T,4>::template apply<1,3,5,7>(q0, q2),
		vect::shuffle2<T,4>::template apply<0,2,4,6>(q1, q3),
		vect::shuffle2<T,4>::template apply<1,3,5,7>(q1, q3)
	}};
}

// transpose_tpl 4x4 matrix
template <bool DstRM, bool SrcRM, typename T>
static inline
matrix<T,4,4,DstRM> transpose_tpl(const matrix<T,4,4,SrcRM>& m)
noexcept
{
	return transpose_tpl_hlp<DstRM, T>(
		vect::shuffle2<T,4>::template apply<0,1,4,5>(m._v[0], m._v[1]),
		vect::shuffle2<T,4>::template apply<2,3,6,7>(m._v[0], m._v[1]),
		vect::shuffle2<T,4>::template apply<0,1,4,5>(m._v[2], m._v[3]),
		vect::shuffle2<T,4>::template apply<2,3,6,7>(m._v[2], m._v[3])
	);
}

// transpose_tpl matrix
template <bool DstRM, bool SrcRM, typename T, unsigned R, unsigned C>
static inline
matrix<T,(DstRM!=SrcRM?R:C),(DstRM!=SrcRM?C:R),DstRM>
transpose_tpl(const matrix<T,R,C,SrcRM>& m)
noexcept
{
	static const bool S = (DstRM != SrcRM);
	matrix<T,(S?R:C),(S?C:R),DstRM> r;

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		set(r, S?i:j, S?j:i, get(m,i,j));
	}

	return r;
}

// transpose
template <typename T, unsigned R, unsigned C, bool RM>
static inline
matrix<T,C,R,RM> transpose(const matrix<T,R,C,RM>& m)
noexcept
{
	return transpose_tpl<RM, RM, T>(m);
}

// reorder
template <typename T, unsigned R, unsigned C, bool RM>
static inline
matrix<T,R,C,!RM> reorder(const matrix<T,R,C,RM>& m)
noexcept
{
	return transpose_tpl<!RM, RM, T>(m);
}

// make_row_major
template <typename T, unsigned R, unsigned C>
static constexpr inline
matrix<T,R,C, true> make_row_major(matrix<T,R,C, true> m)
noexcept
{
	return m;
}

// make_row_major
template <typename T, unsigned R, unsigned C>
static inline
matrix<T,R,C, true> make_row_major(const matrix<T,R,C,false>& m)
noexcept
{
	return reorder(m);
}

// make_column_major
template <typename T, unsigned R, unsigned C>
static inline
matrix<T,R,C,false> make_column_major(const matrix<T,R,C, true>& m)
noexcept
{
	return reorder(m);
}

// make_column_major
template <typename T, unsigned R, unsigned C>
static constexpr inline
matrix<T,R,C,false> make_column_major(matrix<T,R,C,false> m)
noexcept
{
	return m;
}

// major_vector
template <unsigned I, typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
typename meta::enable_if<(I<(RM?R:C)), vector<T, (RM?C:R)>>::type
major_vector(const matrix<T,R,C,RM>& m)
noexcept
{
	return {m._v[I]};
}

// minor_vector
template <unsigned I, typename T, unsigned R, unsigned C, bool RM>
static inline
typename meta::enable_if<(I<(RM?C:R)), vector<T, (RM?R:C)>>::type
minor_vector(const matrix<T,R,C,RM>& m)
noexcept
{
	return major_vector<I>(reorder(m));
}

// minor_vector mat4x4
template <unsigned I, typename T, bool RM>
static inline
typename meta::enable_if<(I<4), vector<T, 4>>::type
minor_vector(const matrix<T,4,4,RM>& m)
noexcept
{
	return {vect::shuffle2<T,4>::template apply<0,1,4,5>(
		vect::shuffle2<T,4>::template apply<0+I,4+I,-1,-1>(m._v[0], m._v[1]),
		vect::shuffle2<T,4>::template apply<0+I,4+I,-1,-1>(m._v[2], m._v[3])
	)};
}

// row (Row-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, C>
row(const matrix<T,R,C,true>& m)
noexcept
{
	return major_vector<I>(m);
}

// row (Column-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static inline
vector<T, C>
row(const matrix<T,R,C,false>& m)
noexcept
{
	return minor_vector<I>(m);
}

// row_hlp
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, C> row_hlp(
	const matrix<T,R,C,RM>& m,
	meta::unsigned_constant<0u>,
	unsigned i
) noexcept
{
	assert(i == 0);
	return row<0>(m);
}

// row_hlp
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static inline
vector<T, C> row_hlp(
	const matrix<T,R,C,RM>& m,
	meta::unsigned_constant<I>,
	unsigned i
) noexcept
{
	if(I == i) return row<I>(m);
	return row_hlp(m, meta::unsigned_constant<I-1>(), i);
}

// row - run-time
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, C>
row(const matrix<T,R,C,RM>& m, unsigned i)
noexcept
{
	typedef meta::unsigned_constant<R-1> I;
	return row_hlp(m, I(), i);
}

// column (Column-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R>
column(const matrix<T,R,C,false>& m)
noexcept
{
	return major_vector<I>(m);
}

// column (Row-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static inline
vector<T, R>
column(const matrix<T,R,C,true>& m)
noexcept
{
	return minor_vector<I>(m);
}

// col_hlp
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, R> col_hlp(
	const matrix<T,R,C,RM>& m,
	meta::unsigned_constant<0u>,
	unsigned i
) noexcept
{
	assert(i == 0);
	return column<0>(m);
}

// col_hlp
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static inline
vector<T, R> col_hlp(
	const matrix<T,R,C,RM>& m,
	meta::unsigned_constant<I>,
	unsigned i
) noexcept
{
	if(I == i) return column<I>(m);
	return col_hlp(m, meta::unsigned_constant<I-1>(), i);
}

// column - run-time
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, R>
column(const matrix<T,R,C,RM>& m, unsigned i)
noexcept
{
	typedef meta::unsigned_constant<C-1> I;
	return col_hlp(m, I(), i);
}

// multipliable_matrices trait
template <typename M1, typename M2>
struct multipliable_matrices
 : meta::false_type
{ };

// multiplication result trait
template <typename M1, typename M2>
struct multiplication_result;

// multipliable_matrices MxV
template <typename T, unsigned R, unsigned C>
struct multipliable_matrices<matrix<T,R,C,true>, vector<T,C>>
 : meta::true_type
{ };

// multiplication result MxV
template <typename T, unsigned R, unsigned C>
struct multiplication_result<matrix<T,R,C,true>, vector<T,C>>
 : vector<T,R>
{ };

// multiply hlp
template <
	unsigned ... I,
	typename T,
	unsigned R,
	unsigned C
>
static constexpr inline
vector<T, R>
_multiply_hlp(
	meta::unsigned_sequence<I...>,
	const matrix<T, R, C, true>& m,
	const vector<T, C>& v
) noexcept
{
	return vector<T, R>
		{{dot(row<I>(m), v)...}};
}

// multipliable_matrices VxB
template <typename T, unsigned R, unsigned C>
struct multipliable_matrices<vector<T,R>, matrix<T,R,C,false>>
 : meta::true_type
{ };

// multiplication result VxM
template <typename T, unsigned R, unsigned C>
struct multiplication_result<vector<T,R>, matrix<T,R,C,false>>
 : vector<T,C>
{ };

// multiply hlp
template <
	unsigned ... J,
	typename T,
	unsigned R,
	unsigned C
>
static constexpr inline
vector<T, C>
_multiply_hlp(
	meta::unsigned_sequence<J...>,
	const vector<T, R>& v,
	const matrix<T, R, C,false>& m
) noexcept
{
	return vector<T, C>
		{{dot(v, column<J>(m))...}};
}

// multiply MxV
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R> multiply(
	const matrix<T, R, C, true>& m,
	const vector<T, C>& v
) noexcept
{
	typedef typename meta::make_unsigned_sequence<R>::type is;
	return _multiply_hlp(is(), m, v);
}

// multiply VxM
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, C> multiply(
	const vector<T, R>& v,
	const matrix<T, R, C,false>& m
) noexcept
{
	typedef typename meta::make_unsigned_sequence<C>::type is;
	return _multiply_hlp(is(), v, m);
}

// M * V
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R> operator * (
	const matrix<T, R, C, true>& m,
	const vector<T, C>& v
) noexcept
{
	return multiply(m, v);
}

// M * V
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R> operator * (
	const matrix<T, R, C,false>& m,
	const vector<T, C>& v
) noexcept
{
	return multiply(reorder(m), v);
}

// V * M
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, C> operator * (
	const vector<T, R>& v,
	const matrix<T, R, C,false>& m
) noexcept
{
	return multiply(v, m);
}

// _multiply_hlp2
template <
	unsigned ... J,
	typename T,
	unsigned K,
	unsigned N
>
static constexpr inline
typename vect::data<T, N>::type
_multiply_hlp2f(
	meta::unsigned_sequence<J...>,
	typename vect::data_param<T, K>::type v,
	const matrix<T, K, N,false>& m
) noexcept
{
	return typename vect::data<T, N>::type
		{vect::hsum<T, K>::apply(v * m._v[J])[0]...};
}

// _multiply_hlp2
template <
	unsigned ... J,
	typename T,
	typename ... P,
	unsigned N
>
static constexpr inline
typename vect::data<T, N>::type
_multiply_hlp2f(
	meta::unsigned_sequence<J...> is,
	typename vect::data_param<T, N>::type v,
	const matrix<T, N, N,false>& m1,
	const matrix<T, N, N,false>& m2,
	const matrix<P, N, N,false>& ... mn
) noexcept
{
	return _multiply_hlp2f(is, _multiply_hlp2f(is, v, m1), m2, mn...);
}

// _multiply_hlp2
template <
	unsigned ... J,
	typename T,
	unsigned K,
	unsigned N
>
static constexpr inline
typename vect::data<T, N>::type
_multiply_hlp2t(
	meta::unsigned_sequence<J...>,
	const vector<T, K>& v,
	const matrix<T, K, N,true>& m
) noexcept
{
	return typename vect::data<T, N>::type
		{dot(v, column<J>(m))...};
}

// multipliable_matrices
template <typename T, unsigned M, unsigned N, unsigned K, bool RM1, bool RM2>
struct multipliable_matrices<matrix<T,M,K,RM1>, matrix<T,K,N,RM2>>
 : meta::true_type
{ };

template <typename T, unsigned M, unsigned N, unsigned K, bool RM1, bool RM2>
struct multiplication_result<matrix<T,M,K,RM1>, matrix<T,K,N,RM2>>
 : matrix<T,M,N,RM1>
{ };

// multiply hlp
template <
	unsigned ... I,
	typename T,
	unsigned M,
	unsigned N,
	unsigned K
>
static constexpr inline
matrix<T, M, N, true>
_multiply_hlp(
	meta::unsigned_sequence<I...>,
	const matrix<T, M, K, true>& m1,
	const matrix<T, K, N,false>& m2
) noexcept
{
	typedef typename meta::make_unsigned_sequence<N>::type is;
	return matrix<T, M, N, true>
		{{_multiply_hlp2f(is(), m1._v[I], m2)...}};
}

// multiply hlp
template <
	unsigned ... I,
	typename T,
	typename ... P,
	unsigned N
>
static constexpr inline
matrix<T, N, N, true>
_multiply_hlp(
	meta::unsigned_sequence<I...> is,
	const matrix<T, N, N, true>& m1,
	const matrix<T, N, N,false>& m2,
	const matrix<T, N, N,false>& m3,
	const matrix<P, N, N,false>& ... mn
) noexcept
{
	return matrix<T, N, N, true>
		{{_multiply_hlp2f(is, m1._v[I], m2, m3, mn...)...}};
}

// multiply hlp
template <
	unsigned ... I,
	typename T,
	unsigned M,
	unsigned N,
	unsigned K
>
static constexpr inline
matrix<T, M, N,false>
_multiply_hlp(
	meta::unsigned_sequence<I...>,
	const matrix<T, M, K,false>& m1,
	const matrix<T, K, N, true>& m2
) noexcept
{
	typedef typename meta::make_unsigned_sequence<N>::type is;
	return matrix<T, M, N,false>
		{{_multiply_hlp2t(is(), row<I>(m1), m2)...}};
}

// multiply MxM
template <typename T, unsigned M, unsigned N, unsigned K, bool RM>
static constexpr inline
matrix<T, M, N, RM> multiply(
	const matrix<T, M, K, RM>& m1,
	const matrix<T, K, N,!RM>& m2
) noexcept
{
	typedef typename meta::make_unsigned_sequence<M>::type is;
	return _multiply_hlp(is(), m1, m2);
}

// multiply MxM
template <typename T, unsigned M, unsigned N, unsigned K, bool RM>
static constexpr inline
matrix<T, M, N, RM> multiply(
	const matrix<T, M, K, RM>& m1,
	const matrix<T, K, N, RM>& m2
) noexcept
{
	return multiply(m1, reorder(m2));
}

template <typename T, typename ... P, unsigned N>
static inline
matrix<T, N, N, true> multiply(
	const matrix<T, N, N, true>& m1,
	const matrix<T, N, N,false>& m2,
	const matrix<T, N, N,false>& m3,
	const matrix<P, N, N,false>& ... mn
)
{
	typedef typename meta::make_unsigned_sequence<N>::type is;
	return _multiply_hlp(is(), m1, m2, m3, mn...);
}

// trivial_multiply MxM
template <typename T, unsigned M, unsigned N, unsigned K, bool RM1, bool RM2>
static inline
matrix<T, M, N, RM1> trivial_multiply(
	const matrix<T, M, K, RM1>& m1,
	const matrix<T, K, N, RM2>& m2
) noexcept
{
	matrix<T, M, N, RM1> m3;

	for(unsigned i=0; i<M; ++i)
	for(unsigned j=0; j<N; ++j)
	{
		T s = T(0);

		for(unsigned k=0; k<K; ++k)
		{
			s += get(m1,i,k)*get(m2,k,j);
		}

		set(m3, i, j, s);
	}
	return m3;
}

// M * M
template <typename T, unsigned M, unsigned N, unsigned K, bool RM1, bool RM2>
static constexpr inline
matrix<T, M, N, RM1> operator * (
	const matrix<T, M, K, RM1>& m1,
	const matrix<T, K, N, RM2>& m2
) noexcept
{
	return multiply(m1, m2);
}

// M | M
template <typename T, unsigned M, unsigned N, unsigned K, bool RM1, bool RM2>
static constexpr inline
matrix<T, M, N, RM1> operator | (
	const matrix<T, M, K, RM1>& m1,
	const matrix<T, K, N, RM2>& m2
) noexcept
{
	return trivial_multiply(m1, m2);
}

// _fast_multiply M * M
template <typename T, unsigned N, bool RM1, bool RM2>
static constexpr inline
matrix<T, N, N, true> _fast_multiply(
	const matrix<T, N, N, RM1>& m1,
	const matrix<T, N, N, RM2>& m2,
	meta::true_type /*trivial */
) noexcept
{
	return trivial_multiply(make_row_major(m1), make_column_major(m2));
}

// _fast_multiply M * M
template <typename T, unsigned N, bool RM1, bool RM2>
static constexpr inline
matrix<T, N, N, true> _fast_multiply(
	const matrix<T, N, N, RM1>& m1,
	const matrix<T, N, N, RM2>& m2,
	meta::false_type /*trivial */
) noexcept
{
	return multiply(make_row_major(m1), make_column_major(m2));
}

// fast_multiply M * M
template <typename T, unsigned N, bool RM1, bool RM2>
static constexpr inline
matrix<T, N, N, true> fast_multiply(
	const matrix<T, N, N, RM1>& m1,
	const matrix<T, N, N, RM2>& m2
) noexcept
{
	return _fast_multiply(
		m1, m2,
		meta::boolean_constant<
			(EAGINE_MATH_FAST_MAT_MULT_TRIVIAL > 1) ||
			not(vect::_has_vec_data<T, N>())
		>()
	);
}

// fast_multiply M * ... M
template <typename T, unsigned N, bool RM1, bool RM2, bool RM3>
static constexpr inline
matrix<T, N, N, true> fast_multiply(
	const matrix<T, N, N, RM1>& m1,
	const matrix<T, N, N, RM2>& m2,
	const matrix<T, N, N, RM2>& m3
) noexcept
{
	typedef meta::boolean_constant<
		(EAGINE_MATH_FAST_MAT_MULT_TRIVIAL > 0) ||
		not(vect::_has_vec_data<T, N>())
	> _triv;
	return _fast_multiply(_fast_multiply(m1, m2, _triv()), m3, _triv());
}

// fast_multiply M * ... M
template <
	typename T,
	unsigned N,
	bool RM1,
	bool RM2,
	bool RM3,
	bool RM4,
	bool ... RMn
>
static constexpr inline
matrix<T, N, N, true> fast_multiply(
	const matrix<T, N, N, RM1>& m1,
	const matrix<T, N, N, RM2>& m2,
	const matrix<T, N, N, RM3>& m3,
	const matrix<T, N, N, RM4>& m4,
	const matrix<T, N, N, RMn>& ... m
) noexcept
{
	typedef meta::boolean_constant<
		(EAGINE_MATH_FAST_MAT_MULT_TRIVIAL > 0) ||
		not(vect::_has_vec_data<T, N>())
	> _triv;
	return fast_multiply(_fast_multiply(m1, m2, _triv()), m3, m4, m...);
}

// row_swap
template <typename T, unsigned R, unsigned C>
inline
void row_swap(matrix<T,R,C,true>& a, unsigned m, unsigned n)
noexcept
{
	using std::swap;
	swap(a._v[m], a._v[n]);
}

// row_multiply
template <typename T, unsigned R, unsigned C>
inline
void row_multiply(matrix<T,R,C,true>& a, unsigned n, T c)
noexcept
{
	a._v[n] = a._v[n]*vect::fill<T,C>::apply(c);
}

// row_add
template <typename T, unsigned R, unsigned C>
inline
void row_add(matrix<T,R,C,true>& a, unsigned m, unsigned n, T c)
noexcept
{
	a._v[m] = a._v[m] + a._v[n]*vect::fill<T,C>::apply(c);
}

// gauss matrix elimination
template <typename T, unsigned R, unsigned C1, unsigned C2>
inline
bool gauss(matrix<T,R,C1,true>& a, matrix<T,R,C2,true>& b)
noexcept
{
	for(unsigned i=0; i<R; ++i)
	{
		T d = a._v[i][i];

		if(d <<equal_to>> T(0))
		{
			for(unsigned k=i+1; k<R; ++k)
			{
				if(not(a._v[k][i] <<equal_to>> T(0)))
				{
					row_swap(a, i, k);
					row_swap(b, i, k);
					break;
				}
			}
			d = a._v[i][i];
		}

		if(d <<equal_to>> T(0))
		{
			return false;
		}

		row_multiply(a, i, T(1)/d);
		row_multiply(b, i, T(1)/d);

		for(unsigned k=i+1; k<R; ++k)
		{
			T c = a._v[k][i];
			if(not(c <<equal_to>> T(0)))
			{
				row_add(a, k, i,-c);
				row_add(b, k, i,-c);
			}
		}
	}
	return true;
}

/// gauss_jordan matrix elimination
template <typename T, unsigned R, unsigned C1, unsigned C2>
inline
bool gauss_jordan(matrix<T,R,C1,true>& a, matrix<T,R,C2,true>& b)
noexcept
{
	if(!gauss(a, b))
	{
		return false;
	}

	for(unsigned i=R-1; i>0; --i)
	{
		for(unsigned k=0; k<i; ++k)
		{
			T c = a._v[k][i];
			if(not(c <<equal_to>> T(0)))
			{
				row_add(a, k, i, -c);
				row_add(b, k, i, -c);
			}
		}
	}

	return true;
}


// is_matrix_constructor trait
template <typename X>
struct is_matrix_constructor
 : meta::false_type
{ };

// constructed_matrix trait
template <typename X>
struct constructed_matrix;

// constructed_matrix trait
template <
	template <class> class MC,
	typename T,
	unsigned R,
	unsigned C,
	bool RM
> struct constructed_matrix<MC<matrix<T,R,C,RM>>>
 : matrix<T,R,C,RM>
{ };

// constructed_matrix trait
template <
	template <class, unsigned> class MC,
	typename T,
	unsigned R,
	unsigned C,
	bool RM,
	unsigned I
> struct constructed_matrix<MC<matrix<T,R,C,RM>,I>>
 : matrix<T,R,C,RM>
{ };

// construct_matrix (noop)
template <bool RM, typename MC>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC>::value &&
	is_row_major<typename constructed_matrix<MC>::type>::value == RM,
	typename constructed_matrix<MC>::type
>::type construct_matrix(const MC& c)
noexcept
{
	return c;
}

// construct_matrix (reorder)
template <bool RM, typename MC>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC>::value &&
	is_row_major<typename constructed_matrix<MC>::type>::value != RM,
	typename reordered_matrix<
		typename constructed_matrix<MC>::type
	>::type
>::type construct_matrix(const MC& c)
noexcept
{
	return reorder_mat_ctr(c);
}

// construct_matrix (noop)
template <bool RM, typename T, unsigned R, unsigned C>
static constexpr inline
matrix<T,R,C,RM> construct_matrix(matrix<T,R,C,RM> m)
noexcept
{
	return m;
}

// construct_matrix (reorder)
template <bool RM, typename T, unsigned R, unsigned C>
static constexpr inline
matrix<T,R,C,RM> construct_matrix(const matrix<T,R,C,!RM>& m)
noexcept
{
	return reorder(m);
}

// matrix_constructor * matrix_constructor
template <typename MC1, typename MC2>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC1>::value &&
	is_matrix_constructor<MC2>::value &&
	multipliable_matrices<
		typename constructed_matrix<MC1>::type,
		typename constructed_matrix<MC2>::type
	>::value,
	typename constructed_matrix<MC1>::type
>::type operator * (const MC1& c1, const MC2& c2)
noexcept
{
	return multiply(
		construct_matrix<
			is_row_major<
				typename constructed_matrix<MC1>::type
			>::value
		>(c1),
		construct_matrix<
			!is_row_major<
				typename constructed_matrix<MC1>::type
			>::value
		>(c2)
	);
}

// matrix * matrix_constructor
template <typename T, unsigned R, unsigned C, bool RM, typename MC2>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC2>::value &&
	multipliable_matrices<
		matrix<T,R,C,RM>,
		typename constructed_matrix<MC2>::type
	>::value,
	matrix<T,R,C,RM>
>::type operator * (const matrix<T,R,C,RM>& m, const MC2& c2)
noexcept
{
	return multiply(m, construct_matrix<!RM>(c2));
}

// matrix_constructor * matrix
template <typename MC1, typename M2>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC1>::value &&
	multipliable_matrices<
		typename constructed_matrix<MC1>::type,
		M2
	>::value,
	typename multiplication_result<
		typename constructed_matrix<MC1>::type,
		M2
	>::type
>::type operator * (const MC1& c1, const M2& m2)
noexcept
{
	return multiply(typename constructed_matrix<MC1>::type(c1), m2);
}

// matrix_constructor * matrix
template <typename MC1, typename M2>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC1>::value &&
	multipliable_matrices<
		typename reordered_matrix<
			typename constructed_matrix<MC1>::type
		>::type,
		M2
	>::value,
	typename multiplication_result<
		typename reordered_matrix<
			typename constructed_matrix<MC1>::type
		>::type,
		M2
	>::type
>::type operator * (const MC1& c1, const M2& m2)
noexcept
{
	return multiply(
		typename reordered_matrix<
			typename constructed_matrix<MC1>::type
		>::type(reorder_mat_ctr(c1)),
		m2
	);
}

template <typename MC1, typename ... MCn>
static constexpr inline
typename meta::enable_if<
	is_matrix_constructor<MC1>::value,
	typename constructed_matrix<MC1>::type
>::type
fast_multiply(const MC1& c1, const MCn& ... cn)
noexcept
{
	return fast_multiply(
		construct_matrix<true>(c1),
		construct_matrix<false>(cn)...
	);
}

// identity
template <typename X>
struct identity;

// is_matrix_constructor<identity>
template <typename T, unsigned R, unsigned C, bool RM>
struct is_matrix_constructor<identity<matrix<T,R,C,RM>>>
 : meta::true_type
{ };

// identity Matrix
template <typename T, unsigned R, unsigned C, bool RM>
struct identity<matrix<T,R,C,RM>>
{
	template <unsigned ... I>
	static constexpr inline
	matrix<T,R,C,RM>
	_identity(meta::unsigned_sequence<I...>)
	noexcept
	{
		return {{vect::axis<T, RM?C:R, I>::apply(1)...}};
	}

	constexpr inline
	matrix<T,R,C,RM> operator()(void) const
	noexcept
	{
		typedef typename 
			meta::make_unsigned_sequence<RM?R:C>::type _riS;
		return _identity(_riS());
	}

	constexpr inline
	operator matrix<T,R,C,RM> (void) const
	noexcept
	{
		return (*this)();
	}
};

// identity * T
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
identity<matrix<T,R,C,RM>> operator * (identity<matrix<T,R,C,RM>> i, T)
noexcept
{
	return i;
}

// identity + identity
template <typename M>
static constexpr inline
identity<M> operator * (identity<M> i, identity<M>)
noexcept
{
	return i;
}

// reorder_mat_ctr(identity)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
identity<matrix<T,R,C,!RM>>
reorder_mat_ctr(const identity<matrix<T,R,C,RM>>&)
noexcept
{ return {}; }

// composite_data_ref<matrix>
template <typename T, unsigned R, unsigned C, bool RM>
class composite_data_ref<matrix<T, R, C, RM>>
 : public base::crtp_derived_memory_range<
	composite_data_ref<matrix<T, R, C, RM>>,
	base::typed_memory_range<const T>,
	const T
>
{
private:
	typedef meta::boolean_constant<
		sizeof(T[R*C]) == sizeof(typename matrix<T,R,C,RM>::_vT)
	> _alias;

	typedef typename meta::conditional<
		_alias::value,
		const T*,
		T [R*C]
	>::type _vT;

	_vT _v;

	template <typename Matrix>
	void _init(const Matrix& m, meta::true_type)
	noexcept
	{
		_v = reinterpret_cast<_vT>(&m._v);
	}

	template <typename Matrix>
	void _init(const Matrix& m, meta::false_type)
	noexcept
	{
		for(unsigned a=0; a<(RM?R:C); ++a)
		for(unsigned b=0; b<(RM?C:R); ++b)
		{
			_v[a*(RM?C:R)+b] = m._v[a][b];
		}
	}
public:
	composite_data_ref(const matrix<T,R,C,RM>& m)
	noexcept
	{
		_init(m, _alias());
	}

	const T* addr(void) const
	noexcept
	{
		return _v;
	}

	static constexpr inline
	std::size_t size(void)
	noexcept
	{
		return R*C;
	}

	static constexpr inline
	bool row_major(void)
	noexcept
	{
		return RM;
	}
};

// data
template <typename T, unsigned R, unsigned C, bool RM>
static inline 
composite_data_ref<matrix<T, R, C, RM>> data(const matrix<T, R, C, RM>& m)
noexcept
{
	return m;
}

} // namespace math
} // namespace eagine

#endif //include guard

