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
		BOOST_ASSERT((get(m, i, j) == T(i==j?1:0)));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] == T(i==j?1:0)));
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
		BOOST_ASSERT((get(m1, i, j) == T(i==j?1:0)));
		BOOST_ASSERT((get(m2, i, j) == T(i==j?1:0)));
		BOOST_ASSERT((m2[RM?i:j][RM?j:i] == T(i==j?1:0)));
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
		BOOST_ASSERT((get(m, i, j) == d[k]));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] == d[k]));
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
auto make_math_tmat(
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
void test_math_tmat_init_ctr_TRC(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand()/T(11);
	}

	eagine::math::tmat<T,R,C,RM> m = make_math_tmat(
		d,
		eagine::meta::integral_constant<unsigned, R>(),
		eagine::meta::integral_constant<unsigned, C>(),
		eagine::meta::integral_constant<bool, RM>()
	);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		unsigned k = RM?i*C+j:j*R+i;
		BOOST_ASSERT((get(m, i, j) == d[k]));
		BOOST_ASSERT((m[RM?i:j][RM?j:i] == d[k]));
	}
}

template <typename T, bool RM>
void test_math_tmat_init_ctr(void)
{
	test_math_tmat_init_ctr_TRC<T,2,2,RM>();
	test_math_tmat_init_ctr_TRC<T,2,3,RM>();
	test_math_tmat_init_ctr_TRC<T,2,4,RM>();
	test_math_tmat_init_ctr_TRC<T,2,5,RM>();

	test_math_tmat_init_ctr_TRC<T,3,2,RM>();
	test_math_tmat_init_ctr_TRC<T,3,3,RM>();
	test_math_tmat_init_ctr_TRC<T,3,4,RM>();
	test_math_tmat_init_ctr_TRC<T,3,5,RM>();

	test_math_tmat_init_ctr_TRC<T,4,2,RM>();
	test_math_tmat_init_ctr_TRC<T,4,3,RM>();
	test_math_tmat_init_ctr_TRC<T,4,4,RM>();
	test_math_tmat_init_ctr_TRC<T,4,5,RM>();

	test_math_tmat_init_ctr_TRC<T,5,2,RM>();
	test_math_tmat_init_ctr_TRC<T,5,3,RM>();
	test_math_tmat_init_ctr_TRC<T,5,4,RM>();
	test_math_tmat_init_ctr_TRC<T,5,5,RM>();
}

BOOST_AUTO_TEST_CASE(math_tmat_init_ctr)
{
	test_math_tmat_init_ctr<float, true>();
	test_math_tmat_init_ctr<float,false>();

	test_math_tmat_init_ctr<double, true>();
	test_math_tmat_init_ctr<double,false>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
