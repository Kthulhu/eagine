/**
 *  .file test/eagine/math/matrix.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix)

template <typename T, unsigned R, unsigned C, bool RM>
bool test_math_matrix_close(
	const eagine::math::matrix<T, R, C, RM>& a,
	const eagine::math::matrix<T, R, C, RM>& b
)
{
	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		if(!test_math_close(a[RM?i:j][RM?j:i], b[RM?i:j][RM?j:i]))
		{
			return false;
		}
	}
	return true;
}

template <typename T, bool RM>
void test_math_matrix_default_ctr(void)
{
	eagine::math::matrix<T, 1, 1, RM> m11;
	eagine::math::matrix<T, 1, 2, RM> m12;
	eagine::math::matrix<T, 1, 3, RM> m13;
	eagine::math::matrix<T, 1, 4, RM> m14;
	eagine::math::matrix<T, 1, 5, RM> m15;

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1, RM> m21;
	eagine::math::matrix<T, 2, 2, RM> m22;
	eagine::math::matrix<T, 2, 3, RM> m23;
	eagine::math::matrix<T, 2, 4, RM> m24;
	eagine::math::matrix<T, 2, 5, RM> m25;

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1, RM> m31;
	eagine::math::matrix<T, 3, 2, RM> m32;
	eagine::math::matrix<T, 3, 3, RM> m33;
	eagine::math::matrix<T, 3, 4, RM> m34;
	eagine::math::matrix<T, 3, 5, RM> m35;

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1, RM> m41;
	eagine::math::matrix<T, 4, 2, RM> m42;
	eagine::math::matrix<T, 4, 3, RM> m43;
	eagine::math::matrix<T, 4, 4, RM> m44;
	eagine::math::matrix<T, 4, 5, RM> m45;

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1, RM> m51;
	eagine::math::matrix<T, 5, 2, RM> m52;
	eagine::math::matrix<T, 5, 3, RM> m53;
	eagine::math::matrix<T, 5, 4, RM> m54;
	eagine::math::matrix<T, 5, 5, RM> m55;

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

BOOST_AUTO_TEST_CASE(math_matrix_default_ctr)
{
	test_math_matrix_default_ctr<float, true>();
	test_math_matrix_default_ctr<float,false>();
	test_math_matrix_default_ctr<double, true>();
	test_math_matrix_default_ctr<double,false>();
}

template <typename T>
void test_math_matrix_init_ctr_rm(void)
{
	eagine::math::matrix<T, 1, 1, true> m11{{
		{T(1)}
	}};
	eagine::math::matrix<T, 1, 2, true> m12{{
		{T(1),T(2)}
	}};
	eagine::math::matrix<T, 1, 3, true> m13{{
		{T(1),T(2),T(3)}
	}};
	eagine::math::matrix<T, 1, 4, true> m14{{
		{T(1),T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 1, 5, true> m15{{
		{T(1),T(2),T(3),T(4),T(5)}
	}};

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1, true> m21{{
		{T(1)},
		{T(2)}
	}};
	eagine::math::matrix<T, 2, 2, true> m22{{
		{T(1),T(2)},
		{T(2),T(3)}
	}};
	eagine::math::matrix<T, 2, 3, true> m23{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 2, 4, true> m24{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 2, 5, true> m25{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)}
	}};

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1, true> m31{{
		{T(1)},
		{T(2)},
		{T(3)}
	}};
	eagine::math::matrix<T, 3, 2, true> m32{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)}
	}};
	eagine::math::matrix<T, 3, 3, true> m33{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 3, 4, true> m34{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 3, 5, true> m35{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)}
	}};

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1, true> m41{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)}
	}};
	eagine::math::matrix<T, 4, 2, true> m42{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};
	eagine::math::matrix<T, 4, 3, true> m43{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 4, 4, true> m44{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 4, 5, true> m45{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)}
	}};

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1, true> m51{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)},
		{T(5)}
	}};
	eagine::math::matrix<T, 5, 2, true> m52{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)},
		{T(5),T(6)}
	}};
	eagine::math::matrix<T, 5, 3, true> m53{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)},
		{T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 5, 4, true> m54{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)},
		{T(5),T(6),T(7),T(8)}
	}};
	eagine::math::matrix<T, 5, 5, true> m55{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)},
		{T(5),T(6),T(7),T(8),T(9)}
	}};

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;

}

template <typename T>
void test_math_matrix_init_ctr_cm(void)
{
	eagine::math::matrix<T, 1, 1,false> m11{{
		{T(1)}
	}};
	eagine::math::matrix<T, 1, 2,false> m12{{
		{T(1)},
		{T(2)}
	}};
	eagine::math::matrix<T, 1, 3,false> m13{{
		{T(1)},
		{T(2)},
		{T(3)}
	}};
	eagine::math::matrix<T, 1, 4,false> m14{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)}
	}};
	eagine::math::matrix<T, 1, 5,false> m15{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)},
		{T(5)}
	}};

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1,false> m21{{
		{T(1),T(2)}
	}};
	eagine::math::matrix<T, 2, 2,false> m22{{
		{T(1),T(2)},
		{T(2),T(3)}
	}};
	eagine::math::matrix<T, 2, 3,false> m23{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)}
	}};
	eagine::math::matrix<T, 2, 4,false> m24{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};
	eagine::math::matrix<T, 2, 5,false> m25{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1,false> m31{{
		{T(1),T(2),T(3)}
	}};
	eagine::math::matrix<T, 3, 2,false> m32{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 3, 3,false> m33{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 3, 4,false> m34{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 3, 5,false> m35{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)},
		{T(5),T(6),T(7)}
	}};

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1,false> m41{{
		{T(1),T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 4, 2,false> m42{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 4, 3,false> m43{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 4, 4,false> m44{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 4, 5,false> m45{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)},
		{T(5),T(6),T(7),T(8)}
	}};

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1,false> m51{{
		{T(1),T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 5, 2,false> m52{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 5, 3,false> m53{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 5, 4,false> m54{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)}
	}};
	eagine::math::matrix<T, 5, 5,false> m55{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)},
		{T(5),T(6),T(7),T(8),T(9)},
	}};

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

BOOST_AUTO_TEST_CASE(math_matrix_init_ctr1)
{
	test_math_matrix_init_ctr_rm<float>();
	test_math_matrix_init_ctr_cm<float>();
	test_math_matrix_init_ctr_rm<double>();
	test_math_matrix_init_ctr_cm<double>();
}

template <typename T, bool RM>
void test_math_matrix_copy_ctr(void)
{
	eagine::math::matrix<T, 1, 1, RM> m11a;
	eagine::math::matrix<T, 1, 2, RM> m12a;
	eagine::math::matrix<T, 1, 3, RM> m13a;
	eagine::math::matrix<T, 1, 4, RM> m14a;
	eagine::math::matrix<T, 1, 5, RM> m15a;

	eagine::math::matrix<T, 1, 1, RM> m11b(m11a);
	eagine::math::matrix<T, 1, 2, RM> m12b(m12a);
	eagine::math::matrix<T, 1, 3, RM> m13b(m13a);
	eagine::math::matrix<T, 1, 4, RM> m14b(m14a);
	eagine::math::matrix<T, 1, 5, RM> m15b(m15a);

	(void)m11b; (void)m12b; (void)m13b; (void)m14b; (void)m15b;

	eagine::math::matrix<T, 2, 1, RM> m21a;
	eagine::math::matrix<T, 2, 2, RM> m22a;
	eagine::math::matrix<T, 2, 3, RM> m23a;
	eagine::math::matrix<T, 2, 4, RM> m24a;
	eagine::math::matrix<T, 2, 5, RM> m25a;

	eagine::math::matrix<T, 2, 1, RM> m21b(m21a);
	eagine::math::matrix<T, 2, 2, RM> m22b(m22a);
	eagine::math::matrix<T, 2, 3, RM> m23b(m23a);
	eagine::math::matrix<T, 2, 4, RM> m24b(m24a);
	eagine::math::matrix<T, 2, 5, RM> m25b(m25a);

	(void)m21b; (void)m22b; (void)m23b; (void)m24b; (void)m25b;

	eagine::math::matrix<T, 3, 1, RM> m31a;
	eagine::math::matrix<T, 3, 2, RM> m32a;
	eagine::math::matrix<T, 3, 3, RM> m33a;
	eagine::math::matrix<T, 3, 4, RM> m34a;
	eagine::math::matrix<T, 3, 5, RM> m35a;

	eagine::math::matrix<T, 3, 1, RM> m31b(m31a);
	eagine::math::matrix<T, 3, 2, RM> m32b(m32a);
	eagine::math::matrix<T, 3, 3, RM> m33b(m33a);
	eagine::math::matrix<T, 3, 4, RM> m34b(m34a);
	eagine::math::matrix<T, 3, 5, RM> m35b(m35a);

	(void)m31b; (void)m32b; (void)m33b; (void)m34b; (void)m35b;

	eagine::math::matrix<T, 4, 1, RM> m41a;
	eagine::math::matrix<T, 4, 2, RM> m42a;
	eagine::math::matrix<T, 4, 3, RM> m43a;
	eagine::math::matrix<T, 4, 4, RM> m44a;
	eagine::math::matrix<T, 4, 5, RM> m45a;

	eagine::math::matrix<T, 4, 1, RM> m41b(m41a);
	eagine::math::matrix<T, 4, 2, RM> m42b(m42a);
	eagine::math::matrix<T, 4, 3, RM> m43b(m43a);
	eagine::math::matrix<T, 4, 4, RM> m44b(m44a);
	eagine::math::matrix<T, 4, 5, RM> m45b(m45a);

	(void)m41b; (void)m42b; (void)m43b; (void)m44b; (void)m45b;

	eagine::math::matrix<T, 5, 1, RM> m51a;
	eagine::math::matrix<T, 5, 2, RM> m52a;
	eagine::math::matrix<T, 5, 3, RM> m53a;
	eagine::math::matrix<T, 5, 4, RM> m54a;
	eagine::math::matrix<T, 5, 5, RM> m55a;

	eagine::math::matrix<T, 5, 1, RM> m51b(m51a);
	eagine::math::matrix<T, 5, 2, RM> m52b(m52a);
	eagine::math::matrix<T, 5, 3, RM> m53b(m53a);
	eagine::math::matrix<T, 5, 4, RM> m54b(m54a);
	eagine::math::matrix<T, 5, 5, RM> m55b(m55a);

	(void)m51b; (void)m52b; (void)m53b; (void)m54b; (void)m55b;

}

BOOST_AUTO_TEST_CASE(math_matrix_copy_ctr)
{
	test_math_matrix_copy_ctr<float, true>();
	test_math_matrix_copy_ctr<float,false>();
	test_math_matrix_copy_ctr<double, true>();
	test_math_matrix_copy_ctr<double,false>();
}

template <typename T, bool RM>
void test_math_matrix_from_data(void)
{
	T d11[1*1] = {1};
	auto m11 = eagine::math::matrix<T, 1, 1, true>::from(d11, 1*1);
	T d12[1*2] = {1,2};
	auto m12 = eagine::math::matrix<T, 1, 2, true>::from(d12, 1*2);
	T d13[1*3] = {1,2,3};
	auto m13 = eagine::math::matrix<T, 1, 3, true>::from(d13, 1*3);
	T d14[1*4] = {1,2,3,4};
	auto m14 = eagine::math::matrix<T, 1, 4, true>::from(d14, 1*4);
	T d15[1*5] = {1,2,3,4,5};
	auto m15 = eagine::math::matrix<T, 1, 5, true>::from(d15, 1*5);

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	T d21[2*1] = {1,2};
	auto m21 = eagine::math::matrix<T, 2, 1, true>::from(d21, 2*1);
	T d22[2*2] = {1,2,2,3};
	auto m22 = eagine::math::matrix<T, 2, 2, true>::from(d22, 2*2);
	T d23[2*3] = {1,2,3,2,3,4};
	auto m23 = eagine::math::matrix<T, 2, 3, true>::from(d23, 2*3);
	T d24[2*4] = {1,2,3,4,2,3,4,5};
	auto m24 = eagine::math::matrix<T, 2, 4, true>::from(d24, 2*4);
	T d25[2*5] = {1,2,3,4,5,2,3,4,5,6};
	auto m25 = eagine::math::matrix<T, 2, 5, true>::from(d25, 2*5);

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	T d31[3*1] = {1,2,3};
	auto m31 = eagine::math::matrix<T, 3, 1, true>::from(d31, 3*1);
	T d32[3*2] = {1,2,2,3,3,4};
	auto m32 = eagine::math::matrix<T, 3, 2, true>::from(d32, 3*2);
	T d33[3*3] = {1,2,3,2,3,4,3,4,5};
	auto m33 = eagine::math::matrix<T, 3, 3, true>::from(d33, 3*3);
	T d34[3*4] = {1,2,3,4,2,3,4,5,3,4,5,6};
	auto m34 = eagine::math::matrix<T, 3, 4, true>::from(d34, 3*4);
	T d35[3*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7};
	auto m35 = eagine::math::matrix<T, 3, 5, true>::from(d35, 3*5);

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	T d41[4*1] = {1,2,3,4};
	auto m41 = eagine::math::matrix<T, 4, 1, true>::from(d41, 4*1);
	T d42[4*2] = {1,2,2,3,3,4,4,5};
	auto m42 = eagine::math::matrix<T, 4, 2, true>::from(d42, 4*2);
	T d43[4*3] = {1,2,3,2,3,4,3,4,5,4,5,6};
	auto m43 = eagine::math::matrix<T, 4, 3, true>::from(d43, 4*3);
	T d44[4*4] = {1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7};
	auto m44 = eagine::math::matrix<T, 4, 4, true>::from(d44, 4*4);
	T d45[4*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7,4,5,6,7,8};
	auto m45 = eagine::math::matrix<T, 4, 5, true>::from(d45, 4*5);

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	T d51[4*1] = {1,2,3,4};
	auto m51 = eagine::math::matrix<T, 5, 1, true>::from(d51, 5*1);
	T d52[5*2] = {1,2,2,3,3,4,4,5};
	auto m52 = eagine::math::matrix<T, 5, 2, true>::from(d52, 5*2);
	T d53[5*3] = {1,2,3,2,3,4,3,4,5,4,5,6};
	auto m53 = eagine::math::matrix<T, 5, 3, true>::from(d53, 5*3);
	T d54[5*4] = {1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7};
	auto m54 = eagine::math::matrix<T, 5, 4, true>::from(d54, 5*4);
	T d55[5*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7,4,5,6,7,8};
	auto m55 = eagine::math::matrix<T, 5, 5, true>::from(d55, 5*5);

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

BOOST_AUTO_TEST_CASE(math_matrix_from_data)
{
	test_math_matrix_from_data<float, true>();
	test_math_matrix_from_data<float,false>();
	test_math_matrix_from_data<double, true>();
	test_math_matrix_from_data<double,false>();
}

template <typename T, unsigned R, unsigned C, bool RM>
void test_math_matrix_elements(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	eagine::math::matrix<T,R,C,RM> m =
		eagine::math::matrix<T,R,C,RM>::from(d, R*C);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		BOOST_ASSERT(test_math_close(m[RM?i:j][RM?j:i], d[(RM?i:j)*(RM?C:R)+(RM?j:i)]));
	}
}

template <typename T, bool RM>
void test_math_matrix_elements_TRM(void)
{
	test_math_matrix_elements<T, 1, 1, RM>();
	test_math_matrix_elements<T, 1, 2, RM>();
	test_math_matrix_elements<T, 1, 3, RM>();
	test_math_matrix_elements<T, 1, 4, RM>();
	test_math_matrix_elements<T, 1, 5, RM>();

	test_math_matrix_elements<T, 2, 1, RM>();
	test_math_matrix_elements<T, 2, 2, RM>();
	test_math_matrix_elements<T, 2, 3, RM>();
	test_math_matrix_elements<T, 2, 4, RM>();
	test_math_matrix_elements<T, 2, 5, RM>();

	test_math_matrix_elements<T, 3, 1, RM>();
	test_math_matrix_elements<T, 3, 2, RM>();
	test_math_matrix_elements<T, 3, 3, RM>();
	test_math_matrix_elements<T, 3, 4, RM>();
	test_math_matrix_elements<T, 3, 5, RM>();

	test_math_matrix_elements<T, 4, 1, RM>();
	test_math_matrix_elements<T, 4, 2, RM>();
	test_math_matrix_elements<T, 4, 3, RM>();
	test_math_matrix_elements<T, 4, 4, RM>();
	test_math_matrix_elements<T, 4, 5, RM>();

	test_math_matrix_elements<T, 5, 1, RM>();
	test_math_matrix_elements<T, 5, 2, RM>();
	test_math_matrix_elements<T, 5, 3, RM>();
	test_math_matrix_elements<T, 5, 4, RM>();
	test_math_matrix_elements<T, 5, 5, RM>();
}

BOOST_AUTO_TEST_CASE(math_matrix_elements)
{
	test_math_matrix_elements_TRM<float, true>();
	test_math_matrix_elements_TRM<float,false>();
	test_math_matrix_elements_TRM<double, true>();
	test_math_matrix_elements_TRM<double,false>();

}

BOOST_AUTO_TEST_SUITE_END()
