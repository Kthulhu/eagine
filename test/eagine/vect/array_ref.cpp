/**
 *  .file test/eagine/vect/array_ref.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_array_ref
#include <boost/test/unit_test.hpp>

#include <eagine/vect/array_ref.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(vect_array_ref)

template <typename T, unsigned N, bool V>
void test_vect_array_ref_apply_TNV(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		typename eagine::vect::data<T, N, V>::type v = {};

		for(unsigned i=0; i<N; ++i)
		{
			v[i] = std::rand() / T(3);
		}

		auto a = eagine::vect::array_ref<T, N, V>(v);

		for(unsigned i=0; i<N; ++i)
		{
			using eagine::math::equal_to;
			BOOST_ASSERT(v[i] <<equal_to>> a.data()[i]);
		}
	}
}

template <typename T, bool V>
void test_vect_array_ref_apply_TV(void)
{
	test_vect_array_ref_apply_TNV<T, 2, V>();
	test_vect_array_ref_apply_TNV<T, 3, V>();
	test_vect_array_ref_apply_TNV<T, 4, V>();
	test_vect_array_ref_apply_TNV<T, 5, V>();
	test_vect_array_ref_apply_TNV<T, 6, V>();
	test_vect_array_ref_apply_TNV<T, 7, V>();
	test_vect_array_ref_apply_TNV<T, 8, V>();
}

template <typename T>
void test_vect_array_ref_apply_T(void)
{
	test_vect_array_ref_apply_TV<T, true>();
	test_vect_array_ref_apply_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(vect_array_ref_apply)
{
	test_vect_array_ref_apply_T<int>();
	test_vect_array_ref_apply_T<float>();
	test_vect_array_ref_apply_T<double>();
}


BOOST_AUTO_TEST_SUITE_END()
