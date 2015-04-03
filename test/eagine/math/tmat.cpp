/**
 *  .file test/eagine/math/tmat.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_tmat
#include <boost/test/unit_test.hpp>

#include <eagine/math/tmat.hpp>
#include <eagine/math/tvec.hpp>
#include <eagine/math/close_to.hpp>
#include <type_traits>
#include <cstdlib>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_tmat)

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_default_ctr_TRC(void)
{
	eagine::math::tmat<T, R, C, RM> m;

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT((get(m, i, j) <<equal_to>> T(i==j?1:0)));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] <<equal_to>> T(i==j?1:0)));
	}
}

template <typename T, bool RM>
void test_math_tmat_default_ctr(void)
{
	test_math_tmat_default_ctr_TRC<T, 2, 2, RM>();
	test_math_tmat_default_ctr_TRC<T, 2, 3, RM>();
	test_math_tmat_default_ctr_TRC<T, 2, 4, RM>();
	test_math_tmat_default_ctr_TRC<T, 2, 5, RM>();

	test_math_tmat_default_ctr_TRC<T, 3, 2, RM>();
	test_math_tmat_default_ctr_TRC<T, 3, 3, RM>();
	test_math_tmat_default_ctr_TRC<T, 3, 4, RM>();
	test_math_tmat_default_ctr_TRC<T, 3, 5, RM>();

	test_math_tmat_default_ctr_TRC<T, 4, 2, RM>();
	test_math_tmat_default_ctr_TRC<T, 4, 3, RM>();
	test_math_tmat_default_ctr_TRC<T, 4, 4, RM>();
	test_math_tmat_default_ctr_TRC<T, 4, 5, RM>();

	test_math_tmat_default_ctr_TRC<T, 5, 2, RM>();
	test_math_tmat_default_ctr_TRC<T, 5, 3, RM>();
	test_math_tmat_default_ctr_TRC<T, 5, 4, RM>();
	test_math_tmat_default_ctr_TRC<T, 5, 5, RM>();

}

BOOST_AUTO_TEST_CASE(math_tmat_default_ctr)
{
	test_math_tmat_default_ctr<float, true>();
	test_math_tmat_default_ctr<float,false>();

	test_math_tmat_default_ctr<double, true>();
	test_math_tmat_default_ctr<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_copy_ctr_TRC(void)
{
	eagine::math::tmat<T, R, C, RM> m1;
	eagine::math::tmat<T, R, C, RM> m2 = m1;

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT((get(m1, i, j) <<equal_to>> T(i==j?1:0)));
		BOOST_ASSERT((get(m2, i, j) <<equal_to>> T(i==j?1:0)));
		BOOST_ASSERT((m2[RM?i:j][RM?j:i] <<equal_to>> T(i==j?1:0)));
	}
}

template <typename T, bool RM>
void test_math_tmat_copy_ctr(void)
{
	test_math_tmat_copy_ctr_TRC<T, 2, 2, RM>();
	test_math_tmat_copy_ctr_TRC<T, 2, 3, RM>();
	test_math_tmat_copy_ctr_TRC<T, 2, 4, RM>();
	test_math_tmat_copy_ctr_TRC<T, 2, 5, RM>();

	test_math_tmat_copy_ctr_TRC<T, 3, 2, RM>();
	test_math_tmat_copy_ctr_TRC<T, 3, 3, RM>();
	test_math_tmat_copy_ctr_TRC<T, 3, 4, RM>();
	test_math_tmat_copy_ctr_TRC<T, 3, 5, RM>();

	test_math_tmat_copy_ctr_TRC<T, 4, 2, RM>();
	test_math_tmat_copy_ctr_TRC<T, 4, 3, RM>();
	test_math_tmat_copy_ctr_TRC<T, 4, 4, RM>();
	test_math_tmat_copy_ctr_TRC<T, 4, 5, RM>();

	test_math_tmat_copy_ctr_TRC<T, 5, 2, RM>();
	test_math_tmat_copy_ctr_TRC<T, 5, 3, RM>();
	test_math_tmat_copy_ctr_TRC<T, 5, 4, RM>();
	test_math_tmat_copy_ctr_TRC<T, 5, 5, RM>();

}

BOOST_AUTO_TEST_CASE(math_tmat_copy_ctr)
{
	test_math_tmat_copy_ctr<float, true>();
	test_math_tmat_copy_ctr<float,false>();

	test_math_tmat_copy_ctr<double, true>();
	test_math_tmat_copy_ctr<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_data_ctr_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand()/T(11);
	}

	eagine::math::tmat<T, R, C, RM> m(d, R*C);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		unsigned k = RM?i*C+j:j*R+i;

		using eagine::math::equal_to;
		BOOST_ASSERT((get(m, i, j) <<equal_to>> d[k]));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] <<equal_to>> d[k]));
	}
}

template <typename T, bool RM>
void test_math_tmat_data_ctr(void)
{
	test_math_tmat_data_ctr_TRC<T, 2, 2, RM>();
	test_math_tmat_data_ctr_TRC<T, 2, 3, RM>();
	test_math_tmat_data_ctr_TRC<T, 2, 4, RM>();
	test_math_tmat_data_ctr_TRC<T, 2, 5, RM>();

	test_math_tmat_data_ctr_TRC<T, 3, 2, RM>();
	test_math_tmat_data_ctr_TRC<T, 3, 3, RM>();
	test_math_tmat_data_ctr_TRC<T, 3, 4, RM>();
	test_math_tmat_data_ctr_TRC<T, 3, 5, RM>();

	test_math_tmat_data_ctr_TRC<T, 4, 2, RM>();
	test_math_tmat_data_ctr_TRC<T, 4, 3, RM>();
	test_math_tmat_data_ctr_TRC<T, 4, 4, RM>();
	test_math_tmat_data_ctr_TRC<T, 4, 5, RM>();

	test_math_tmat_data_ctr_TRC<T, 5, 2, RM>();
	test_math_tmat_data_ctr_TRC<T, 5, 3, RM>();
	test_math_tmat_data_ctr_TRC<T, 5, 4, RM>();
	test_math_tmat_data_ctr_TRC<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_tmat_data_ctr)
{
	test_math_tmat_data_ctr<float, true>();
	test_math_tmat_data_ctr<float,false>();

	test_math_tmat_data_ctr<double, true>();
	test_math_tmat_data_ctr<double,false>();
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,2, true>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,3, true>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,4, true>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,5, true>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,2, true>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,3, true>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,4, true>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,5, true>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,2, true>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5]),
		eagine::math::tvec<T,2>(d[ 6], d[ 7])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,3, true>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8]),
		eagine::math::tvec<T,3>(d[ 9], d[10], d[11])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,4, true>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11]),
		eagine::math::tvec<T,4>(d[12], d[13], d[14], d[15])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,5, true>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14]),
		eagine::math::tvec<T,5>(d[15], d[16], d[17], d[18], d[19])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,2, true>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5]),
		eagine::math::tvec<T,2>(d[ 6], d[ 7]),
		eagine::math::tvec<T,2>(d[ 8], d[ 9])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,3, true>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8]),
		eagine::math::tvec<T,3>(d[ 9], d[10], d[11]),
		eagine::math::tvec<T,3>(d[12], d[13], d[14])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,4, true>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11]),
		eagine::math::tvec<T,4>(d[12], d[13], d[14], d[15]),
		eagine::math::tvec<T,4>(d[16], d[17], d[18], d[19])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,5, true>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14]),
		eagine::math::tvec<T,5>(d[15], d[16], d[17], d[18], d[19]),
		eagine::math::tvec<T,5>(d[20], d[21], d[22], d[23], d[24])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,2,false>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,3,false>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,4,false>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5]),
		eagine::math::tvec<T,2>(d[ 6], d[ 7])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,5,false>(
		eagine::math::tvec<T,2>(d[ 0], d[ 1]),
		eagine::math::tvec<T,2>(d[ 2], d[ 3]),
		eagine::math::tvec<T,2>(d[ 4], d[ 5]),
		eagine::math::tvec<T,2>(d[ 6], d[ 7]),
		eagine::math::tvec<T,2>(d[ 8], d[ 9])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,2,false>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,3,false>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,4,false>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8]),
		eagine::math::tvec<T,3>(d[ 9], d[10], d[11])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,5,false>(
		eagine::math::tvec<T,3>(d[ 0], d[ 1], d[ 2]),
		eagine::math::tvec<T,3>(d[ 3], d[ 4], d[ 5]),
		eagine::math::tvec<T,3>(d[ 6], d[ 7], d[ 8]),
		eagine::math::tvec<T,3>(d[ 9], d[10], d[11]),
		eagine::math::tvec<T,3>(d[12], d[13], d[14])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,2,false>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,3,false>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,4,false>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11]),
		eagine::math::tvec<T,4>(d[12], d[13], d[14], d[15])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,5,false>(
		eagine::math::tvec<T,4>(d[ 0], d[ 1], d[ 2], d[ 3]),
		eagine::math::tvec<T,4>(d[ 4], d[ 5], d[ 6], d[ 7]),
		eagine::math::tvec<T,4>(d[ 8], d[ 9], d[10], d[11]),
		eagine::math::tvec<T,4>(d[12], d[13], d[14], d[15]),
		eagine::math::tvec<T,4>(d[16], d[17], d[18], d[19])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,2,false>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,3,false>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,4,false>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14]),
		eagine::math::tvec<T,5>(d[15], d[16], d[17], d[18], d[19])
	);
}

template <typename T>
auto make_math_tmat_v(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,5,false>(
		eagine::math::tvec<T,5>(d[ 0], d[ 1], d[ 2], d[ 3], d[ 4]),
		eagine::math::tvec<T,5>(d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]),
		eagine::math::tvec<T,5>(d[10], d[11], d[12], d[13], d[14]),
		eagine::math::tvec<T,5>(d[15], d[16], d[17], d[18], d[19]),
		eagine::math::tvec<T,5>(d[20], d[21], d[22], d[23], d[24])
	);
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_vector_ctr_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand()/T(11);
	}

	eagine::math::tmat<T,R,C,RM> m = make_math_tmat_v(
		d,
		eagine::meta::integral_constant<unsigned, R>(),
		eagine::meta::integral_constant<unsigned, C>(),
		eagine::meta::integral_constant<bool, RM>()
	);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		unsigned k = RM?i*C+j:j*R+i;

		using eagine::math::equal_to;
		BOOST_ASSERT((get(m, i, j) <<equal_to>> d[k]));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] <<equal_to>> d[k]));
	}
}

template <typename T, bool RM>
void test_math_tmat_vector_ctr(void)
{
	test_math_tmat_vector_ctr_TRC<T,2,2,RM>();
	test_math_tmat_vector_ctr_TRC<T,2,3,RM>();
	test_math_tmat_vector_ctr_TRC<T,2,4,RM>();
	test_math_tmat_vector_ctr_TRC<T,2,5,RM>();

	test_math_tmat_vector_ctr_TRC<T,3,2,RM>();
	test_math_tmat_vector_ctr_TRC<T,3,3,RM>();
	test_math_tmat_vector_ctr_TRC<T,3,4,RM>();
	test_math_tmat_vector_ctr_TRC<T,3,5,RM>();

	test_math_tmat_vector_ctr_TRC<T,4,2,RM>();
	test_math_tmat_vector_ctr_TRC<T,4,3,RM>();
	test_math_tmat_vector_ctr_TRC<T,4,4,RM>();
	test_math_tmat_vector_ctr_TRC<T,4,5,RM>();

	test_math_tmat_vector_ctr_TRC<T,5,2,RM>();
	test_math_tmat_vector_ctr_TRC<T,5,3,RM>();
	test_math_tmat_vector_ctr_TRC<T,5,4,RM>();
	test_math_tmat_vector_ctr_TRC<T,5,5,RM>();
}

BOOST_AUTO_TEST_CASE(math_tmat_vector_ctr)
{
	test_math_tmat_vector_ctr<float, true>();
	test_math_tmat_vector_ctr<float,false>();

	test_math_tmat_vector_ctr<double, true>();
	test_math_tmat_vector_ctr<double,false>();
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,2, true>(
		d[ 0], d[ 1],
		d[ 2], d[ 3]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,3, true>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,4, true>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,2,5, true>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,2, true>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,3, true>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,4, true>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,3,5, true>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,2, true>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5],
		d[ 6], d[ 7]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,3, true>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8],
		d[ 9], d[10], d[11]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,4, true>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11],
		d[12], d[13], d[14], d[15]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,4,5, true>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14],
		d[15], d[16], d[17], d[18], d[19]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,2, true>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5],
		d[ 6], d[ 7],
		d[ 8], d[ 9]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,3, true>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8],
		d[ 9], d[10], d[11],
		d[12], d[13], d[14]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,4, true>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11],
		d[12], d[13], d[14], d[15],
		d[16], d[17], d[18], d[19]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>
)
{
	return eagine::math::tmat<T,5,5, true>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14],
		d[15], d[16], d[17], d[18], d[19],
		d[20], d[21], d[22], d[23], d[24]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,2,false>(
		d[ 0], d[ 1],
		d[ 2], d[ 3]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,3,false>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,4,false>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5],
		d[ 6], d[ 7]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,2,5,false>(
		d[ 0], d[ 1],
		d[ 2], d[ 3],
		d[ 4], d[ 5],
		d[ 6], d[ 7],
		d[ 8], d[ 9]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,2,false>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,3,false>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,4,false>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8],
		d[ 9], d[10], d[11]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,3,5,false>(
		d[ 0], d[ 1], d[ 2],
		d[ 3], d[ 4], d[ 5],
		d[ 6], d[ 7], d[ 8],
		d[ 9], d[10], d[11],
		d[12], d[13], d[14]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,2,false>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,3,false>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,4,false>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11],
		d[12], d[13], d[14], d[15]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,4,5,false>(
		d[ 0], d[ 1], d[ 2], d[ 3],
		d[ 4], d[ 5], d[ 6], d[ 7],
		d[ 8], d[ 9], d[10], d[11],
		d[12], d[13], d[14], d[15],
		d[16], d[17], d[18], d[19]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,2,false>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,3,false>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,4,false>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14],
		d[15], d[16], d[17], d[18], d[19]
	);
}

template <typename T>
auto make_math_tmat_p(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool,false>
)
{
	return eagine::math::tmat<T,5,5,false>(
		d[ 0], d[ 1], d[ 2], d[ 3], d[ 4],
		d[ 5], d[ 6], d[ 7], d[ 8], d[ 9],
		d[10], d[11], d[12], d[13], d[14],
		d[15], d[16], d[17], d[18], d[19],
		d[20], d[21], d[22], d[23], d[24]
	);
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_pack_ctr_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand()/T(11);
	}

	eagine::math::tmat<T,R,C,RM> m = make_math_tmat_p(
		d,
		eagine::meta::integral_constant<unsigned, R>(),
		eagine::meta::integral_constant<unsigned, C>(),
		eagine::meta::integral_constant<bool, RM>()
	);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		unsigned k = RM?i*C+j:j*R+i;

		using eagine::math::equal_to;
		BOOST_ASSERT((get(m, i, j) <<equal_to>> d[k]));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] <<equal_to>> d[k]));
	}
}

template <typename T, bool RM>
void test_math_tmat_pack_ctr(void)
{
	test_math_tmat_pack_ctr_TRC<T,2,2,RM>();
	test_math_tmat_pack_ctr_TRC<T,2,3,RM>();
	test_math_tmat_pack_ctr_TRC<T,2,4,RM>();
	test_math_tmat_pack_ctr_TRC<T,2,5,RM>();

	test_math_tmat_pack_ctr_TRC<T,3,2,RM>();
	test_math_tmat_pack_ctr_TRC<T,3,3,RM>();
	test_math_tmat_pack_ctr_TRC<T,3,4,RM>();
	test_math_tmat_pack_ctr_TRC<T,3,5,RM>();

	test_math_tmat_pack_ctr_TRC<T,4,2,RM>();
	test_math_tmat_pack_ctr_TRC<T,4,3,RM>();
	test_math_tmat_pack_ctr_TRC<T,4,4,RM>();
	test_math_tmat_pack_ctr_TRC<T,4,5,RM>();

	test_math_tmat_pack_ctr_TRC<T,5,2,RM>();
	test_math_tmat_pack_ctr_TRC<T,5,3,RM>();
	test_math_tmat_pack_ctr_TRC<T,5,4,RM>();
	test_math_tmat_pack_ctr_TRC<T,5,5,RM>();
}

BOOST_AUTO_TEST_CASE(math_tmat_pack_ctr)
{
	test_math_tmat_pack_ctr<float, true>();
	test_math_tmat_pack_ctr<float,false>();

	test_math_tmat_pack_ctr<double, true>();
	test_math_tmat_pack_ctr<double,false>();
}


template <typename T, unsigned P, unsigned Q, unsigned R>
void test_math_tmat_multiply_TPQR(void)
{
	T d1[P*Q];
	T d2[Q*R];

	for(unsigned k=0; k<P*Q; ++k)
	{
		d1[k] = std::rand() / T(3);
	}

	for(unsigned k=0; k<Q*R; ++k)
	{
		d2[k] = std::rand() / T(3);
	}

	auto m1 = eagine::math::tmat<T,P,Q, true>(d1, P*Q);
	auto m2 = eagine::math::tmat<T,Q,R,false>(d2, Q*R);

	eagine::math::tmat<T,P,R,true> m3 = m1*m2;
	eagine::math::tmat<T,P,R,true> m4 = trivial_multiply(m1, m2);

	for(unsigned i=0; i<P; ++i)
	for(unsigned j=0; j<R; ++j)
	{
		T s = T(0);

		for(unsigned k=0; k<Q; ++k)
		{
			s += m1[i][k]*m2[j][k];
		}
		BOOST_ASSERT(test_math_close(m3[i][j], s));
		BOOST_ASSERT(test_math_close(m4[i][j], s));
	}
}

template <typename T>
void test_math_tmat_multiply_T(void)
{
	test_math_tmat_multiply_TPQR<T, 1, 1, 1>();
	test_math_tmat_multiply_TPQR<T, 1, 1, 5>();
	test_math_tmat_multiply_TPQR<T, 1, 1, 5>();
	test_math_tmat_multiply_TPQR<T, 1, 1, 5>();
	test_math_tmat_multiply_TPQR<T, 1, 1, 5>();

	test_math_tmat_multiply_TPQR<T, 1, 2, 1>();
	test_math_tmat_multiply_TPQR<T, 1, 2, 2>();
	test_math_tmat_multiply_TPQR<T, 1, 2, 3>();
	test_math_tmat_multiply_TPQR<T, 1, 2, 4>();
	test_math_tmat_multiply_TPQR<T, 1, 2, 5>();

	test_math_tmat_multiply_TPQR<T, 1, 3, 1>();
	test_math_tmat_multiply_TPQR<T, 1, 3, 2>();
	test_math_tmat_multiply_TPQR<T, 1, 3, 3>();
	test_math_tmat_multiply_TPQR<T, 1, 3, 4>();
	test_math_tmat_multiply_TPQR<T, 1, 3, 5>();

	test_math_tmat_multiply_TPQR<T, 1, 4, 1>();
	test_math_tmat_multiply_TPQR<T, 1, 4, 2>();
	test_math_tmat_multiply_TPQR<T, 1, 4, 3>();
	test_math_tmat_multiply_TPQR<T, 1, 4, 4>();
	test_math_tmat_multiply_TPQR<T, 1, 4, 5>();

	test_math_tmat_multiply_TPQR<T, 1, 5, 1>();
	test_math_tmat_multiply_TPQR<T, 1, 5, 2>();
	test_math_tmat_multiply_TPQR<T, 1, 5, 3>();
	test_math_tmat_multiply_TPQR<T, 1, 5, 4>();
	test_math_tmat_multiply_TPQR<T, 1, 5, 5>();

	test_math_tmat_multiply_TPQR<T, 2, 1, 1>();
	test_math_tmat_multiply_TPQR<T, 2, 1, 2>();
	test_math_tmat_multiply_TPQR<T, 2, 1, 3>();
	test_math_tmat_multiply_TPQR<T, 2, 1, 4>();
	test_math_tmat_multiply_TPQR<T, 2, 1, 5>();

	test_math_tmat_multiply_TPQR<T, 2, 2, 1>();
	test_math_tmat_multiply_TPQR<T, 2, 2, 2>();
	test_math_tmat_multiply_TPQR<T, 2, 2, 3>();
	test_math_tmat_multiply_TPQR<T, 2, 2, 4>();
	test_math_tmat_multiply_TPQR<T, 2, 2, 5>();

	test_math_tmat_multiply_TPQR<T, 2, 3, 1>();
	test_math_tmat_multiply_TPQR<T, 2, 3, 2>();
	test_math_tmat_multiply_TPQR<T, 2, 3, 3>();
	test_math_tmat_multiply_TPQR<T, 2, 3, 4>();
	test_math_tmat_multiply_TPQR<T, 2, 3, 5>();

	test_math_tmat_multiply_TPQR<T, 2, 4, 1>();
	test_math_tmat_multiply_TPQR<T, 2, 4, 2>();
	test_math_tmat_multiply_TPQR<T, 2, 4, 3>();
	test_math_tmat_multiply_TPQR<T, 2, 4, 4>();
	test_math_tmat_multiply_TPQR<T, 2, 4, 5>();

	test_math_tmat_multiply_TPQR<T, 2, 5, 1>();
	test_math_tmat_multiply_TPQR<T, 2, 5, 2>();
	test_math_tmat_multiply_TPQR<T, 2, 5, 3>();
	test_math_tmat_multiply_TPQR<T, 2, 5, 4>();
	test_math_tmat_multiply_TPQR<T, 2, 5, 5>();

	test_math_tmat_multiply_TPQR<T, 3, 1, 1>();
	test_math_tmat_multiply_TPQR<T, 3, 1, 2>();
	test_math_tmat_multiply_TPQR<T, 3, 1, 3>();
	test_math_tmat_multiply_TPQR<T, 3, 1, 4>();
	test_math_tmat_multiply_TPQR<T, 3, 1, 5>();

	test_math_tmat_multiply_TPQR<T, 3, 2, 1>();
	test_math_tmat_multiply_TPQR<T, 3, 2, 2>();
	test_math_tmat_multiply_TPQR<T, 3, 2, 3>();
	test_math_tmat_multiply_TPQR<T, 3, 2, 4>();
	test_math_tmat_multiply_TPQR<T, 3, 2, 5>();

	test_math_tmat_multiply_TPQR<T, 3, 3, 1>();
	test_math_tmat_multiply_TPQR<T, 3, 3, 2>();
	test_math_tmat_multiply_TPQR<T, 3, 3, 3>();
	test_math_tmat_multiply_TPQR<T, 3, 3, 4>();
	test_math_tmat_multiply_TPQR<T, 3, 3, 5>();

	test_math_tmat_multiply_TPQR<T, 3, 4, 1>();
	test_math_tmat_multiply_TPQR<T, 3, 4, 2>();
	test_math_tmat_multiply_TPQR<T, 3, 4, 3>();
	test_math_tmat_multiply_TPQR<T, 3, 4, 4>();
	test_math_tmat_multiply_TPQR<T, 3, 4, 5>();

	test_math_tmat_multiply_TPQR<T, 3, 5, 1>();
	test_math_tmat_multiply_TPQR<T, 3, 5, 2>();
	test_math_tmat_multiply_TPQR<T, 3, 5, 3>();
	test_math_tmat_multiply_TPQR<T, 3, 5, 4>();
	test_math_tmat_multiply_TPQR<T, 3, 5, 5>();

	test_math_tmat_multiply_TPQR<T, 4, 1, 1>();
	test_math_tmat_multiply_TPQR<T, 4, 1, 2>();
	test_math_tmat_multiply_TPQR<T, 4, 1, 3>();
	test_math_tmat_multiply_TPQR<T, 4, 1, 4>();
	test_math_tmat_multiply_TPQR<T, 4, 1, 5>();

	test_math_tmat_multiply_TPQR<T, 4, 2, 1>();
	test_math_tmat_multiply_TPQR<T, 4, 2, 2>();
	test_math_tmat_multiply_TPQR<T, 4, 2, 3>();
	test_math_tmat_multiply_TPQR<T, 4, 2, 4>();
	test_math_tmat_multiply_TPQR<T, 4, 2, 5>();

	test_math_tmat_multiply_TPQR<T, 4, 3, 1>();
	test_math_tmat_multiply_TPQR<T, 4, 3, 2>();
	test_math_tmat_multiply_TPQR<T, 4, 3, 3>();
	test_math_tmat_multiply_TPQR<T, 4, 3, 4>();
	test_math_tmat_multiply_TPQR<T, 4, 3, 5>();

	test_math_tmat_multiply_TPQR<T, 4, 4, 1>();
	test_math_tmat_multiply_TPQR<T, 4, 4, 2>();
	test_math_tmat_multiply_TPQR<T, 4, 4, 3>();
	test_math_tmat_multiply_TPQR<T, 4, 4, 4>();
	test_math_tmat_multiply_TPQR<T, 4, 4, 5>();

	test_math_tmat_multiply_TPQR<T, 4, 5, 1>();
	test_math_tmat_multiply_TPQR<T, 4, 5, 2>();
	test_math_tmat_multiply_TPQR<T, 4, 5, 3>();
	test_math_tmat_multiply_TPQR<T, 4, 5, 4>();
	test_math_tmat_multiply_TPQR<T, 4, 5, 5>();

	test_math_tmat_multiply_TPQR<T, 5, 1, 1>();
	test_math_tmat_multiply_TPQR<T, 5, 1, 2>();
	test_math_tmat_multiply_TPQR<T, 5, 1, 3>();
	test_math_tmat_multiply_TPQR<T, 5, 1, 4>();
	test_math_tmat_multiply_TPQR<T, 5, 1, 5>();

	test_math_tmat_multiply_TPQR<T, 5, 2, 1>();
	test_math_tmat_multiply_TPQR<T, 5, 2, 2>();
	test_math_tmat_multiply_TPQR<T, 5, 2, 3>();
	test_math_tmat_multiply_TPQR<T, 5, 2, 4>();
	test_math_tmat_multiply_TPQR<T, 5, 2, 5>();

	test_math_tmat_multiply_TPQR<T, 5, 3, 1>();
	test_math_tmat_multiply_TPQR<T, 5, 3, 2>();
	test_math_tmat_multiply_TPQR<T, 5, 3, 3>();
	test_math_tmat_multiply_TPQR<T, 5, 3, 4>();
	test_math_tmat_multiply_TPQR<T, 5, 3, 5>();

	test_math_tmat_multiply_TPQR<T, 5, 4, 1>();
	test_math_tmat_multiply_TPQR<T, 5, 4, 2>();
	test_math_tmat_multiply_TPQR<T, 5, 4, 3>();
	test_math_tmat_multiply_TPQR<T, 5, 4, 4>();
	test_math_tmat_multiply_TPQR<T, 5, 4, 5>();

	test_math_tmat_multiply_TPQR<T, 5, 5, 1>();
	test_math_tmat_multiply_TPQR<T, 5, 5, 2>();
	test_math_tmat_multiply_TPQR<T, 5, 5, 3>();
	test_math_tmat_multiply_TPQR<T, 5, 5, 4>();
	test_math_tmat_multiply_TPQR<T, 5, 5, 5>();
}

BOOST_AUTO_TEST_CASE(math_tmat_multiply)
{
	for(int i=0; i<100; ++i)
	{
		test_math_tmat_multiply_T<float>();
		test_math_tmat_multiply_T<double>();
	}
}

template <typename ... X>
void test_eat(X...){ }

template <typename T, unsigned R, unsigned C, bool RM, unsigned I, unsigned J>
bool test_math_tmat_from_TRCIJ(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(1111);
	}

	eagine::math::tmat<T,R,C,RM> src(d);

	eagine::math::tmat<T,I+1,J+1,RM> dst = src;

	for(unsigned i=0; i<=I; ++i)
	for(unsigned j=0; j<=J; ++j)
	{
		using eagine::math::equal_to;
		BOOST_ASSERT(get(src,i,j) <<equal_to>> get(dst,i,j));
	}

	return true;
}

template <typename T, unsigned R, unsigned C, bool RM, unsigned I, unsigned ... J>
bool test_math_tmat_from_TRCIJ(eagine::meta::unsigned_sequence<J...>)
{
	test_eat(test_math_tmat_from_TRCIJ<T,R,C,RM,I,J>()...);
	return true;
}

template <typename T, unsigned R, unsigned C, bool RM, unsigned ... I>
void test_math_tmat_from_TRCI(eagine::meta::unsigned_sequence<I...>)
{
	test_eat(test_math_tmat_from_TRCIJ<T,R,C,RM,I>(
		eagine::meta::make_unsigned_sequence<C>()
	)...);
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_tmat_from_TRC(void)
{
	test_math_tmat_from_TRCI<T,R,C,RM>(
		eagine::meta::make_unsigned_sequence<R>()
	);
}

template <typename T, bool RM>
void test_math_tmat_from(void)
{
	test_math_tmat_from_TRC<T, 2, 2, RM>();
	test_math_tmat_from_TRC<T, 2, 3, RM>();
	test_math_tmat_from_TRC<T, 2, 4, RM>();

	test_math_tmat_from_TRC<T, 3, 2, RM>();
	test_math_tmat_from_TRC<T, 3, 3, RM>();
	test_math_tmat_from_TRC<T, 3, 4, RM>();

	test_math_tmat_from_TRC<T, 4, 2, RM>();
	test_math_tmat_from_TRC<T, 4, 3, RM>();
	test_math_tmat_from_TRC<T, 4, 4, RM>();
}

BOOST_AUTO_TEST_CASE(math_tmat_from)
{
	for(unsigned k=0; k<100; ++k)
	{
		test_math_tmat_from<float, true>();
		test_math_tmat_from<float,false>();
		test_math_tmat_from<double, true>();
		test_math_tmat_from<double,false>();
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
