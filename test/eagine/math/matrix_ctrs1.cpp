/**
 *  .file test/eagine/math/matrix_ctrs1.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix_ctrs1
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix_ctrs.hpp>
#include <utility>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix_ctrs1)

template <typename MC, typename T, unsigned R, unsigned C, bool RM, bool V>
void do_test_math_matrix_constructor_TRCRMV(void)
{
	typedef eagine::math::matrix<T,R,C,RM,V> M;

	BOOST_ASSERT(eagine::math::is_matrix_constructor<MC>());

	BOOST_ASSERT((
		std::is_same<
			typename eagine::math::constructed_matrix<MC>::type,
			M
		>()
	));

	BOOST_ASSERT((
		std::is_same<
			typename eagine::math::constructed_matrix<
				decltype(eagine::math::reorder_mat_ctr(
					std::declval<MC>()
				))
			>::type,
			decltype(reorder(std::declval<M>()))
		>()
	));
}

template <typename T, bool RM, bool V>
void test_math_matrix_constructor_TRMV(void)
{
	// translation
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// translation_I
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_I<
			eagine::math::matrix<T,4,4,RM,V>, 0
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_x<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_I<
			eagine::math::matrix<T,4,4,RM,V>, 1
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_y<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_I<
				eagine::math::matrix<T,4,4,RM,V>, 2
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::translation_z<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// rotation_I
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM,V>, 0
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_x<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::pitch<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM,V>, 1
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_y<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::yaw<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM,V>, 2
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_z<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::roll<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// rotation_a
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::rotation_a<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// scale
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// scale_I
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM,V>, 0
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_x<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM,V>, 1
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_y<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM,V>, 2
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::scale_z<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// uniform_scale
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::uniform_scale<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// reflection_I
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM,V>, 0
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_x<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM,V>, 1
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_y<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM,V>, 2
		>,T,4,4,RM,V
	>();
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::reflection_z<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// shear
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::shear<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// ortho
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::ortho<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// looking_at_y_up
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::looking_at_y_up<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// looking_at
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::looking_at<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// orbiting_y_up
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::orbiting_y_up<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// perspective
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::perspective<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
	// screen_stretch
	do_test_math_matrix_constructor_TRCRMV<
		eagine::math::screen_stretch<
			eagine::math::matrix<T,4,4,RM,V>
		>,T,4,4,RM,V
	>();
}

template <typename T>
void test_math_matrix_constructor_T(void)
{
	test_math_matrix_constructor_TRMV<T, true, true>();
	test_math_matrix_constructor_TRMV<T,false, true>();
	test_math_matrix_constructor_TRMV<T, true,false>();
	test_math_matrix_constructor_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_is_matrix_constructor)
{
	test_math_matrix_constructor_T<float>();
	test_math_matrix_constructor_T<double>();
}

BOOST_AUTO_TEST_SUITE_END()
