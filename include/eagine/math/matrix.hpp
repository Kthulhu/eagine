/**
 *  @file eagine/math/matrix.hpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_MATH_MATRIX_1308281038_HPP
#define EAGINE_MATH_MATRIX_1308281038_HPP

#include <eagine/math/vector.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/meta/int_sequence.hpp>
#include <cassert>

namespace EAGine {
namespace math {

// matrix
template <typename T, unsigned R, unsigned C, bool RowMajor>
struct matrix;

// matrix Row-Major
template <typename T, unsigned R, unsigned C>
struct matrix<T,R,C,true>
{
	typedef typename vect::data<T, C>::type _vT;

	_vT _v[R];
};

// matrix Column-Major
template <typename T, unsigned R, unsigned C>
struct matrix<T,R,C,false>
{
	typedef typename vect::data<T, R>::type _vT;

	_vT _v[C];
};

// (number of) rows
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
unsigned rows(const matrix<T,R,C,RM>&)
{
	return R;
}

// (number of) columns
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
unsigned columns(const matrix<T,R,C,RM>&)
{
	return C;
}

// (is) row major
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
bool row_major(const matrix<T,R,C,RM>&)
{
	return RM;
}

// equality
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
bool
operator == (const matrix<T,R,C,RM>& a, const matrix<T,R,C,RM>& b)
{
	for(unsigned i=0;i<(RM?R:C); ++i)
		if(!vect::equal<T, (RM?C:R)>::apply(a._v[i], b._v[i]))
			return false;
	return true;
}

// non-eqality
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
bool
operator != (const matrix<T,R,C,RM>& a, const matrix<T,R,C,RM>& b)
{
	for(unsigned i=0;i<(RM?R:C); ++i)
		if(!vect::equal<T, (RM?C:R)>::apply(a._v[i], b._v[i]))
			return true;
	return false;
}

// transpose_tpl helper 4x4 matrix
template <bool DstRM, typename T>
static constexpr inline
matrix<T,4,4,DstRM> transpose_tpl_hlp(
	const typename vect::data<T, 4>::type& q0,
	const typename vect::data<T, 4>::type& q1,
	const typename vect::data<T, 4>::type& q2,
	const typename vect::data<T, 4>::type& q3
)
{
	return {{
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
{
	return transpose_tpl_hlp<DstRM, T>(
		vect::shuffle2<T,4>::template apply<0,1,4,5>(m._v[0], m._v[1]),
		vect::shuffle2<T,4>::template apply<2,3,6,7>(m._v[0], m._v[1]),
		vect::shuffle2<T,4>::template apply<0,1,4,5>(m._v[2], m._v[3]),
		vect::shuffle2<T,4>::template apply<2,3,6,7>(m._v[2], m._v[3])
	);
}

// transpose
template <typename T, unsigned R, unsigned C, bool RM>
static inline
matrix<T,R,C,RM> transpose(const matrix<T,R,C,RM>& m)
{
	return transpose_tpl<RM, RM, T>(m);
}

// reorder
template <typename T, unsigned R, unsigned C, bool RM>
static inline
matrix<T,R,C,!RM> reorder(const matrix<T,R,C,RM>& m)
{
	return transpose_tpl<!RM, RM, T>(m);
}

// get (Row-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(I<R && J<C), T>::type
get(const matrix<T,R,C,true>& m)
{
	return m._v[I][J];
}

// get (Column-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(I<R && J<C), T>::type
get(const matrix<T,R,C,false>& m)
{
	return m._v[J][I];
}

// get_elem (Row-major)
template <unsigned E, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(E<R*C), T>::type
get_elem(const matrix<T,R,C, true>& m)
{
	return m._v[E/C][E%C];
}

// get_elem (Column-major)
template <unsigned E, typename T, unsigned R, unsigned C>
static constexpr inline
typename meta::enable_if<(E<R*C), T>::type
get_elem(const matrix<T,R,C,false>& m)
{
	return m._v[E/R][E%R];
}

// get (Row-major, run-time)
template <typename T, unsigned R, unsigned C>
static constexpr inline
T get(const matrix<T,R,C,true>& m, unsigned i, unsigned j)
{
	return m._v[i][j];
}

// get (Column-major, run-time)
template <typename T, unsigned R, unsigned C>
static constexpr inline
T get(const matrix<T,R,C,false>& m, unsigned i, unsigned j)
{
	return m._v[j][i];
}

// set (Row-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static inline
typename meta::enable_if<(I<R && J<C), void>::type
set(matrix<T,R,C,true>& m, const T& v)
{
	m._v[I][J] = v;
}

// set (Column-major)
template <unsigned I, unsigned J, typename T, unsigned R, unsigned C>
static inline
typename meta::enable_if<(I<R && J<C), void>::type
set(matrix<T,R,C,false>& m, const T& v)
{
	m._v[J][I] = v;
}

// set (Row-major, run-time)
template <typename T, unsigned R, unsigned C>
static inline
void set(matrix<T,R,C,true>& m, unsigned i, unsigned j, const T& v)
{
	m._v[i][j] = v;
}

// set (Column-major, run-time)
template <typename T, unsigned R, unsigned C>
static inline
void set(matrix<T,R,C,false>& m, unsigned i, unsigned j, const T& v)
{
	m._v[j][i] = v;
}

// major_vector
template <unsigned I, typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
typename meta::enable_if<(I<(RM?R:C)), vector<T, (RM?C:R)>>::type
major_vector(const matrix<T,R,C,RM>& m)
{
	return {m._v[I]};
}

// minor_vector mat4x4
template <unsigned I, typename T, bool RM>
static constexpr inline
typename meta::enable_if<(I<4), vector<T, 4>>::type
minor_vector(const matrix<T,4,4,RM>& m)
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
{
	return major_vector<I>(m);
}

// row (Column-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R>
row(const matrix<T,R,C,false>& m)
{
	return minor_vector<I>(m);
}

// row_hlp
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, RM?C:R> row_hlp(
	const matrix<T,R,C,RM>& m,
	meta::integral_constant<unsigned, 0u>,
	unsigned i
)
{
	assert(i == 0);
	return row<0>(m);
}

// row_hlp
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static inline
vector<T, RM?C:R> row_hlp(
	const matrix<T,R,C,RM>& m,
	meta::integral_constant<unsigned, I>,
	unsigned i
)
{
	if(I == i) return row<I>(m);
	return row_hlp(m, meta::integral_constant<unsigned, I-1>(), i);
}

// row - run-time
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, RM?C:R>
row(const matrix<T,R,C,RM>& m, unsigned i)
{
	typedef meta::integral_constant<unsigned, (RM?R:C)-1> I;
	return row_hlp(m, I(), i);
}

// column (Column-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R>
column(const matrix<T,R,C,false>& m)
{
	return major_vector<I>(m);
}

// column (Row-Major)
template <unsigned I, typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R>
column(const matrix<T,R,C,true>& m)
{
	return minor_vector<I>(m);
}

// col_hlp
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, RM?R:C> col_hlp(
	const matrix<T,R,C,RM>& m,
	meta::integral_constant<unsigned, 0u>,
	unsigned i
)
{
	assert(i == 0);
	return column<0>(m);
}

// col_hlp
template <typename T, unsigned R, unsigned C, bool RM, unsigned I>
static inline
vector<T, RM?R:C> col_hlp(
	const matrix<T,R,C,RM>& m,
	meta::integral_constant<unsigned, I>,
	unsigned i
)
{
	if(I == i) return column<I>(m);
	return col_hlp(m, meta::integral_constant<unsigned, I-1>(), i);
}

// column - run-time
template <typename T, unsigned R, unsigned C, bool RM>
static inline
vector<T, RM?R:C>
column(const matrix<T,R,C,RM>& m, unsigned i)
{
	typedef meta::integral_constant<unsigned, (RM?R:C)-1> I;
	return col_hlp(m, I(), i);
}

// matrix elements
template <typename T, unsigned N, bool Fast>
struct matrix_elements;

// matrix elements (fast)
template <typename T, unsigned N>
struct matrix_elements<T, N, true>
{
	const T* _e;
};

// matrix elements (safe)
template <typename T, unsigned N>
struct matrix_elements<T, N,false>
{
	const T _e[N];
};

// data(matrix_elements)
template <typename T, unsigned N, bool F>
static constexpr inline 
const T* data(const matrix_elements<T,N,F>& me)
{
	return me._e;
}

// size(matrix_elements)
template <typename T, unsigned N, bool F>
static constexpr inline
unsigned size(const matrix_elements<T,N,F>&)
{
	return N;
}

// matrix_elements_reinterpretable trait
template <typename M>
struct matrix_elements_reinterpretable;

// matrix_elements_reinterpretable
template <typename T, unsigned R, unsigned C, bool RM>
struct matrix_elements_reinterpretable<matrix<T,R,C,RM>>
 : meta::integral_constant<
	bool,
	meta::is_pod<decltype(matrix<T,R,C,RM>::_v)>::value &&
	meta::is_pod<const T[R*C]>::value &&
	(sizeof(decltype(matrix<T,R,C,RM>::_v)) == sizeof(const T[R*C])) &&
	(alignof(decltype(matrix<T,R,C,RM>::_v)) == alignof(const T[R*C]))
>
{ };

// elements(matrix) (fast)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
typename meta::enable_if<
	matrix_elements_reinterpretable<matrix<T,R,C,RM>>::value,
	matrix_elements<T, R*C, true>
>::type elements(const matrix<T,R,C,RM>& m)
{
	return {reinterpret_cast<const T*>(m._v)};
}

template <typename T, unsigned R, unsigned C, bool RM, unsigned ... I>
static constexpr inline
matrix_elements<T, R*C,false>
elements_copy(const matrix<T,R,C,RM>& m, meta::integer_sequence<unsigned, I...>)
{
	return {get_elem<I>(m)...};
}

// elements(matrix) (safe)
template <typename T, unsigned R, unsigned C, bool RM>
static constexpr inline
typename meta::enable_if<
	!matrix_elements_reinterpretable<matrix<T,R,C,RM>>::value,
	matrix_elements<T, R*C,false>
>::type elements(const matrix<T,R,C,RM>& m)
{
	typedef typename meta::make_integer_sequence<
		unsigned, R*C
	>::type is;
	return elements_copy(m, is());
}

// _multiply_hlp2
template <
	unsigned I,
	unsigned ... J,
	typename T,
	unsigned M,
	unsigned N,
	unsigned K
>
static constexpr inline
typename vect::data<T, N>::type
_multiply_hlp2(
	meta::integer_sequence<unsigned, J...>,
	const matrix<T, M, K, true>& m1,
	const matrix<T, K, N,false>& m2
)
{
	return {dot(row<I>(m1), column<J>(m2))...};
}

// multiply hlp
template <
	unsigned ... I,
	typename T,
	unsigned M,
	unsigned N,
	unsigned K,
	bool RM
>
static constexpr inline
matrix<T, M, N, RM>
_multiply_hlp(
	meta::integer_sequence<unsigned, I...>,
	const matrix<T, M, K, RM>& m1,
	const matrix<T, K, N,!RM>& m2
)
{
	typedef typename meta::make_integer_sequence<
		unsigned, N
	>::type is;
	return {{_multiply_hlp2<I>(is(), m1, m2)...}};
}

// multiply MxM
template <typename T, unsigned M, unsigned N, unsigned K, bool RM>
static constexpr inline
matrix<T, M, N, RM> multiply(
	const matrix<T, M, K, RM>& m1,
	const matrix<T, K, N,!RM>& m2
)
{
	typedef typename meta::make_integer_sequence<
		unsigned, M
	>::type is;
	return _multiply_hlp(is(), m1, m2);
}

// multiply MxM
template <typename T, unsigned M, unsigned N, unsigned K, bool RM>
static constexpr inline
matrix<T, M, N, RM> multiply(
	const matrix<T, M, K, RM>& m1,
	const matrix<T, K, N, RM>& m2
)
{
	return multiply(m1, reorder(m2));
}

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
	meta::integer_sequence<unsigned, I...>,
	const matrix<T, R, C, true>& m,
	const vector<T, C>& v
)
{
	return {dot(row<I>(m), v)...};
}

// multiply MxV
template <typename T, unsigned R, unsigned C>
static constexpr inline
vector<T, R> multiply(
	const matrix<T, R, C, true>& m,
	const vector<T, C>& v
)
{
	typedef typename meta::make_integer_sequence<
		unsigned, R
	>::type is;
	return _multiply_hlp(is(), m, v);
}

// identity
template <typename X>
struct identity;

// identity Matrix
template <typename T, unsigned R, unsigned C, bool RM>
struct identity<matrix<T,R,C,RM>>
{
	template <unsigned ... I>
	static constexpr inline matrix<T,R,C,RM>
	_identity(meta::integer_sequence<unsigned, I...>)
	{
		return {{vect::axis<T, C, I>::apply(1)...}};
	}

	constexpr inline operator matrix<T,R,C,RM> (void) const
	{
		typedef typename meta::make_integer_sequence<
			unsigned, R
		>::type _riS;
		return _identity(_riS());
	}
};

} // namespace math
} // namespace EAGine

#endif //include guard

