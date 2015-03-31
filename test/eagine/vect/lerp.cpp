/**
 *  .file test/eagine/vect/lerp.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_vect_lerp
#include <boost/test/unit_test.hpp>

#include <eagine/vect/lerp.hpp>
#include <cstdlib>

#include "common.hpp"

BOOST_AUTO_TEST_SUITE(vect_lerp)

template <typename T, unsigned N>
void test_vect_lerp_apply(void)
{
	for(unsigned k=0; k<1000; ++k)
	{
		T a[N], b[N];

		typename eagine::vect::data<T, N>::type u = {}, v = {};

		for(unsigned i=0; i<N; ++i)
		{
			a[i] = std::rand() / T(2);
			u[i] = a[i];
			b[i] = std::rand() / T(2);
			v[i] = b[i];
		}

		T t = T(0);

		eagine::vect::lerp<T, N> _lerp;

		while(t <= T(1))
		{
			typename eagine::vect::data<T, N>::type w =
				_lerp(u, v, t);

			for(unsigned i=0; i<N; ++i)
			{
				BOOST_ASSERT(test_vect_data_close(
					w[i],
					a[i]*(1-t)+b[i]*t)
				);
			}

			t += T(1)/T(1+std::rand() % 1000);
		}
	}
}

BOOST_AUTO_TEST_CASE(vect_lerp_apply)
{
	test_vect_lerp_apply<float, 2>();
	test_vect_lerp_apply<float, 3>();
	test_vect_lerp_apply<float, 4>();
	test_vect_lerp_apply<float, 5>();
	test_vect_lerp_apply<float, 8>();

	test_vect_lerp_apply<double, 2>();
	test_vect_lerp_apply<double, 3>();
	test_vect_lerp_apply<double, 4>();
	test_vect_lerp_apply<double, 5>();
	test_vect_lerp_apply<double, 8>();
}


BOOST_AUTO_TEST_SUITE_END()
