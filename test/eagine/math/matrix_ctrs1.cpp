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

template <typename MC, typename T, unsigned R, unsigned C, bool RM>
void do_test_math_matrix_constructor(void)
{
	typedef eagine::math::matrix<T,R,C,RM> M;

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

template <typename T, bool RM>
void test_math_matrix_constructor(void)
{
	// translation
	do_test_math_matrix_constructor<
		eagine::math::translation<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// translation_I
	do_test_math_matrix_constructor<
		eagine::math::translation_I<
			eagine::math::matrix<T,4,4,RM>, 0
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::translation_x<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::translation_I<
			eagine::math::matrix<T,4,4,RM>, 1
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::translation_y<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::translation_I<
				eagine::math::matrix<T,4,4,RM>, 2
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::translation_z<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// rotation_I
	do_test_math_matrix_constructor<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM>, 0
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::rotation_x<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::pitch<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM>, 1
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::rotation_y<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::yaw<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::rotation_I<
			eagine::math::matrix<T,4,4,RM>, 2
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::rotation_z<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::roll<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// rotation_a
	do_test_math_matrix_constructor<
		eagine::math::rotation_a<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// scale
	do_test_math_matrix_constructor<
		eagine::math::scale<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// scale_I
	do_test_math_matrix_constructor<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM>, 0
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::scale_x<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM>, 1
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::scale_y<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::scale_I<
			eagine::math::matrix<T,4,4,RM>, 2
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::scale_z<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// uniform_scale
	do_test_math_matrix_constructor<
		eagine::math::uniform_scale<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// reflection_I
	do_test_math_matrix_constructor<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM>, 0
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::reflection_x<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM>, 1
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::reflection_y<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::reflection_I<
			eagine::math::matrix<T,4,4,RM>, 2
		>,T,4,4,RM
	>();
	do_test_math_matrix_constructor<
		eagine::math::reflection_z<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// shear
	do_test_math_matrix_constructor<
		eagine::math::shear<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// ortho
	do_test_math_matrix_constructor<
		eagine::math::ortho<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// looking_at_y_up
	do_test_math_matrix_constructor<
		eagine::math::looking_at_y_up<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// orbiting_y_up
	do_test_math_matrix_constructor<
		eagine::math::orbiting_y_up<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// perspective
	do_test_math_matrix_constructor<
		eagine::math::perspective<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
	// screen_stretch
	do_test_math_matrix_constructor<
		eagine::math::screen_stretch<
			eagine::math::matrix<T,4,4,RM>
		>,T,4,4,RM
	>();
}

BOOST_AUTO_TEST_CASE(math_is_matrix_constructor)
{
	test_math_matrix_constructor<float, true>();
	test_math_matrix_constructor<float,false>();
	test_math_matrix_constructor<double, true>();
	test_math_matrix_constructor<double,false>();
}

BOOST_AUTO_TEST_SUITE_END()
