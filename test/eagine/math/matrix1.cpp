/**
 *  .file test/eagine/math/matrix1.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_matrix1
#include <boost/test/unit_test.hpp>

#include <eagine/math/matrix.hpp>
#include <eagine/math/difference.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_matrix1)

template <typename T, unsigned R, unsigned C, bool RM, bool V>
bool test_math_matrix_close(
	const eagine::math::matrix<T, R, C, RM, V>& a,
	const eagine::math::matrix<T, R, C, RM, V>& b
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

template <typename T, bool RM, bool V>
void test_math_matrix_default_ctr_TRMV(void)
{
	eagine::math::matrix<T, 1, 1, RM, V> m11;
	eagine::math::matrix<T, 1, 2, RM, V> m12;
	eagine::math::matrix<T, 1, 3, RM, V> m13;
	eagine::math::matrix<T, 1, 4, RM, V> m14;
	eagine::math::matrix<T, 1, 5, RM, V> m15;

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1, RM, V> m21;
	eagine::math::matrix<T, 2, 2, RM, V> m22;
	eagine::math::matrix<T, 2, 3, RM, V> m23;
	eagine::math::matrix<T, 2, 4, RM, V> m24;
	eagine::math::matrix<T, 2, 5, RM, V> m25;

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1, RM, V> m31;
	eagine::math::matrix<T, 3, 2, RM, V> m32;
	eagine::math::matrix<T, 3, 3, RM, V> m33;
	eagine::math::matrix<T, 3, 4, RM, V> m34;
	eagine::math::matrix<T, 3, 5, RM, V> m35;

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1, RM, V> m41;
	eagine::math::matrix<T, 4, 2, RM, V> m42;
	eagine::math::matrix<T, 4, 3, RM, V> m43;
	eagine::math::matrix<T, 4, 4, RM, V> m44;
	eagine::math::matrix<T, 4, 5, RM, V> m45;

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1, RM, V> m51;
	eagine::math::matrix<T, 5, 2, RM, V> m52;
	eagine::math::matrix<T, 5, 3, RM, V> m53;
	eagine::math::matrix<T, 5, 4, RM, V> m54;
	eagine::math::matrix<T, 5, 5, RM, V> m55;

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

template <typename T>
void test_math_matrix_default_ctr_T(void)
{
	test_math_matrix_default_ctr_TRMV<T, true, true>();
	test_math_matrix_default_ctr_TRMV<T,false, true>();
	test_math_matrix_default_ctr_TRMV<T, true,false>();
	test_math_matrix_default_ctr_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_default_ctr)
{
	test_math_matrix_default_ctr_T<float>();
	test_math_matrix_default_ctr_T<double>();
}

template <typename T, bool V>
void test_math_matrix_init_ctr_rm_TV(void)
{
	eagine::math::matrix<T, 1, 1, true, V> m11{{
		{T(1)}
	}};
	eagine::math::matrix<T, 1, 2, true, V> m12{{
		{T(1),T(2)}
	}};
	eagine::math::matrix<T, 1, 3, true, V> m13{{
		{T(1),T(2),T(3)}
	}};
	eagine::math::matrix<T, 1, 4, true, V> m14{{
		{T(1),T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 1, 5, true, V> m15{{
		{T(1),T(2),T(3),T(4),T(5)}
	}};

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1, true, V> m21{{
		{T(1)},
		{T(2)}
	}};
	eagine::math::matrix<T, 2, 2, true, V> m22{{
		{T(1),T(2)},
		{T(2),T(3)}
	}};
	eagine::math::matrix<T, 2, 3, true, V> m23{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 2, 4, true, V> m24{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 2, 5, true, V> m25{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)}
	}};

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1, true, V> m31{{
		{T(1)},
		{T(2)},
		{T(3)}
	}};
	eagine::math::matrix<T, 3, 2, true, V> m32{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)}
	}};
	eagine::math::matrix<T, 3, 3, true, V> m33{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 3, 4, true, V> m34{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 3, 5, true, V> m35{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)}
	}};

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1, true, V> m41{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)}
	}};
	eagine::math::matrix<T, 4, 2, true, V> m42{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};
	eagine::math::matrix<T, 4, 3, true, V> m43{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 4, 4, true, V> m44{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 4, 5, true, V> m45{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)}
	}};

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1, true, V> m51{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)},
		{T(5)}
	}};
	eagine::math::matrix<T, 5, 2, true, V> m52{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)},
		{T(5),T(6)}
	}};
	eagine::math::matrix<T, 5, 3, true, V> m53{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)},
		{T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 5, 4, true, V> m54{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)},
		{T(5),T(6),T(7),T(8)}
	}};
	eagine::math::matrix<T, 5, 5, true, V> m55{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)},
		{T(5),T(6),T(7),T(8),T(9)}
	}};

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;

}

template <typename T>
void test_math_matrix_init_ctr_rm_T(void)
{
	test_math_matrix_init_ctr_rm_TV<T, true>();
	test_math_matrix_init_ctr_rm_TV<T,false>();
}

template <typename T, bool V>
void test_math_matrix_init_ctr_cm_TV(void)
{
	eagine::math::matrix<T, 1, 1,false, V> m11{{
		{T(1)}
	}};
	eagine::math::matrix<T, 1, 2,false, V> m12{{
		{T(1)},
		{T(2)}
	}};
	eagine::math::matrix<T, 1, 3,false, V> m13{{
		{T(1)},
		{T(2)},
		{T(3)}
	}};
	eagine::math::matrix<T, 1, 4,false, V> m14{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)}
	}};
	eagine::math::matrix<T, 1, 5,false, V> m15{{
		{T(1)},
		{T(2)},
		{T(3)},
		{T(4)},
		{T(5)}
	}};

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	eagine::math::matrix<T, 2, 1,false, V> m21{{
		{T(1),T(2)}
	}};
	eagine::math::matrix<T, 2, 2,false, V> m22{{
		{T(1),T(2)},
		{T(2),T(3)}
	}};
	eagine::math::matrix<T, 2, 3,false, V> m23{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)}
	}};
	eagine::math::matrix<T, 2, 4,false, V> m24{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};
	eagine::math::matrix<T, 2, 5,false, V> m25{{
		{T(1),T(2)},
		{T(2),T(3)},
		{T(3),T(4)},
		{T(4),T(5)}
	}};

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	eagine::math::matrix<T, 3, 1,false, V> m31{{
		{T(1),T(2),T(3)}
	}};
	eagine::math::matrix<T, 3, 2,false, V> m32{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 3, 3,false, V> m33{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 3, 4,false, V> m34{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 3, 5,false, V> m35{{
		{T(1),T(2),T(3)},
		{T(2),T(3),T(4)},
		{T(3),T(4),T(5)},
		{T(4),T(5),T(6)},
		{T(5),T(6),T(7)}
	}};

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	eagine::math::matrix<T, 4, 1,false, V> m41{{
		{T(1),T(2),T(3),T(4)}
	}};
	eagine::math::matrix<T, 4, 2,false, V> m42{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 4, 3,false, V> m43{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 4, 4,false, V> m44{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 4, 5,false, V> m45{{
		{T(1),T(2),T(3),T(4)},
		{T(2),T(3),T(4),T(5)},
		{T(3),T(4),T(5),T(6)},
		{T(4),T(5),T(6),T(7)},
		{T(5),T(6),T(7),T(8)}
	}};

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	eagine::math::matrix<T, 5, 1,false, V> m51{{
		{T(1),T(2),T(3),T(4),T(5)}
	}};
	eagine::math::matrix<T, 5, 2,false, V> m52{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)}
	}};
	eagine::math::matrix<T, 5, 3,false, V> m53{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)}
	}};
	eagine::math::matrix<T, 5, 4,false, V> m54{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)}
	}};
	eagine::math::matrix<T, 5, 5,false, V> m55{{
		{T(1),T(2),T(3),T(4),T(5)},
		{T(2),T(3),T(4),T(5),T(6)},
		{T(3),T(4),T(5),T(6),T(7)},
		{T(4),T(5),T(6),T(7),T(8)},
		{T(5),T(6),T(7),T(8),T(9)},
	}};

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

template <typename T>
void test_math_matrix_init_ctr_cm_T(void)
{
	test_math_matrix_init_ctr_cm_TV<T, true>();
	test_math_matrix_init_ctr_cm_TV<T,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_init_ctr1)
{
	test_math_matrix_init_ctr_rm_T<float>();
	test_math_matrix_init_ctr_cm_T<float>();
	test_math_matrix_init_ctr_rm_T<double>();
	test_math_matrix_init_ctr_cm_T<double>();
}

template <typename T, bool RM, bool V>
void test_math_matrix_copy_ctr_TRMV(void)
{
	eagine::math::matrix<T, 1, 1, RM, V> m11a;
	eagine::math::matrix<T, 1, 2, RM, V> m12a;
	eagine::math::matrix<T, 1, 3, RM, V> m13a;
	eagine::math::matrix<T, 1, 4, RM, V> m14a;
	eagine::math::matrix<T, 1, 5, RM, V> m15a;

	eagine::math::matrix<T, 1, 1, RM, V> m11b(m11a);
	eagine::math::matrix<T, 1, 2, RM, V> m12b(m12a);
	eagine::math::matrix<T, 1, 3, RM, V> m13b(m13a);
	eagine::math::matrix<T, 1, 4, RM, V> m14b(m14a);
	eagine::math::matrix<T, 1, 5, RM, V> m15b(m15a);

	(void)m11b; (void)m12b; (void)m13b; (void)m14b; (void)m15b;

	eagine::math::matrix<T, 2, 1, RM, V> m21a;
	eagine::math::matrix<T, 2, 2, RM, V> m22a;
	eagine::math::matrix<T, 2, 3, RM, V> m23a;
	eagine::math::matrix<T, 2, 4, RM, V> m24a;
	eagine::math::matrix<T, 2, 5, RM, V> m25a;

	eagine::math::matrix<T, 2, 1, RM, V> m21b(m21a);
	eagine::math::matrix<T, 2, 2, RM, V> m22b(m22a);
	eagine::math::matrix<T, 2, 3, RM, V> m23b(m23a);
	eagine::math::matrix<T, 2, 4, RM, V> m24b(m24a);
	eagine::math::matrix<T, 2, 5, RM, V> m25b(m25a);

	(void)m21b; (void)m22b; (void)m23b; (void)m24b; (void)m25b;

	eagine::math::matrix<T, 3, 1, RM, V> m31a;
	eagine::math::matrix<T, 3, 2, RM, V> m32a;
	eagine::math::matrix<T, 3, 3, RM, V> m33a;
	eagine::math::matrix<T, 3, 4, RM, V> m34a;
	eagine::math::matrix<T, 3, 5, RM, V> m35a;

	eagine::math::matrix<T, 3, 1, RM, V> m31b(m31a);
	eagine::math::matrix<T, 3, 2, RM, V> m32b(m32a);
	eagine::math::matrix<T, 3, 3, RM, V> m33b(m33a);
	eagine::math::matrix<T, 3, 4, RM, V> m34b(m34a);
	eagine::math::matrix<T, 3, 5, RM, V> m35b(m35a);

	(void)m31b; (void)m32b; (void)m33b; (void)m34b; (void)m35b;

	eagine::math::matrix<T, 4, 1, RM, V> m41a;
	eagine::math::matrix<T, 4, 2, RM, V> m42a;
	eagine::math::matrix<T, 4, 3, RM, V> m43a;
	eagine::math::matrix<T, 4, 4, RM, V> m44a;
	eagine::math::matrix<T, 4, 5, RM, V> m45a;

	eagine::math::matrix<T, 4, 1, RM, V> m41b(m41a);
	eagine::math::matrix<T, 4, 2, RM, V> m42b(m42a);
	eagine::math::matrix<T, 4, 3, RM, V> m43b(m43a);
	eagine::math::matrix<T, 4, 4, RM, V> m44b(m44a);
	eagine::math::matrix<T, 4, 5, RM, V> m45b(m45a);

	(void)m41b; (void)m42b; (void)m43b; (void)m44b; (void)m45b;

	eagine::math::matrix<T, 5, 1, RM, V> m51a;
	eagine::math::matrix<T, 5, 2, RM, V> m52a;
	eagine::math::matrix<T, 5, 3, RM, V> m53a;
	eagine::math::matrix<T, 5, 4, RM, V> m54a;
	eagine::math::matrix<T, 5, 5, RM, V> m55a;

	eagine::math::matrix<T, 5, 1, RM, V> m51b(m51a);
	eagine::math::matrix<T, 5, 2, RM, V> m52b(m52a);
	eagine::math::matrix<T, 5, 3, RM, V> m53b(m53a);
	eagine::math::matrix<T, 5, 4, RM, V> m54b(m54a);
	eagine::math::matrix<T, 5, 5, RM, V> m55b(m55a);

	(void)m51b; (void)m52b; (void)m53b; (void)m54b; (void)m55b;

}

template <typename T>
void test_math_matrix_copy_ctr_T(void)
{
	test_math_matrix_copy_ctr_TRMV<T, true, true>();
	test_math_matrix_copy_ctr_TRMV<T,false, true>();
	test_math_matrix_copy_ctr_TRMV<T, true,false>();
	test_math_matrix_copy_ctr_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_copy_ctr)
{
	test_math_matrix_copy_ctr_T<float>();
	test_math_matrix_copy_ctr_T<double>();
}

template <typename T, bool RM, bool V>
void test_math_matrix_from_data_TRMV(void)
{
	T d11[1*1] = {1};
	auto m11 = eagine::math::matrix<T, 1, 1, RM, V>::from(d11, 1*1);
	T d12[1*2] = {1,2};
	auto m12 = eagine::math::matrix<T, 1, 2, RM, V>::from(d12, 1*2);
	T d13[1*3] = {1,2,3};
	auto m13 = eagine::math::matrix<T, 1, 3, RM, V>::from(d13, 1*3);
	T d14[1*4] = {1,2,3,4};
	auto m14 = eagine::math::matrix<T, 1, 4, RM, V>::from(d14, 1*4);
	T d15[1*5] = {1,2,3,4,5};
	auto m15 = eagine::math::matrix<T, 1, 5, RM, V>::from(d15, 1*5);

	(void)m11; (void)m12; (void)m13; (void)m14; (void)m15;

	T d21[2*1] = {1,2};
	auto m21 = eagine::math::matrix<T, 2, 1, RM, V>::from(d21, 2*1);
	T d22[2*2] = {1,2,2,3};
	auto m22 = eagine::math::matrix<T, 2, 2, RM, V>::from(d22, 2*2);
	T d23[2*3] = {1,2,3,2,3,4};
	auto m23 = eagine::math::matrix<T, 2, 3, RM, V>::from(d23, 2*3);
	T d24[2*4] = {1,2,3,4,2,3,4,5};
	auto m24 = eagine::math::matrix<T, 2, 4, RM, V>::from(d24, 2*4);
	T d25[2*5] = {1,2,3,4,5,2,3,4,5,6};
	auto m25 = eagine::math::matrix<T, 2, 5, RM, V>::from(d25, 2*5);

	(void)m21; (void)m22; (void)m23; (void)m24; (void)m25;

	T d31[3*1] = {1,2,3};
	auto m31 = eagine::math::matrix<T, 3, 1, RM, V>::from(d31, 3*1);
	T d32[3*2] = {1,2,2,3,3,4};
	auto m32 = eagine::math::matrix<T, 3, 2, RM, V>::from(d32, 3*2);
	T d33[3*3] = {1,2,3,2,3,4,3,4,5};
	auto m33 = eagine::math::matrix<T, 3, 3, RM, V>::from(d33, 3*3);
	T d34[3*4] = {1,2,3,4,2,3,4,5,3,4,5,6};
	auto m34 = eagine::math::matrix<T, 3, 4, RM, V>::from(d34, 3*4);
	T d35[3*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7};
	auto m35 = eagine::math::matrix<T, 3, 5, RM, V>::from(d35, 3*5);

	(void)m31; (void)m32; (void)m33; (void)m34; (void)m35;

	T d41[4*1] = {1,2,3,4};
	auto m41 = eagine::math::matrix<T, 4, 1, RM, V>::from(d41, 4*1);
	T d42[4*2] = {1,2,2,3,3,4,4,5};
	auto m42 = eagine::math::matrix<T, 4, 2, RM, V>::from(d42, 4*2);
	T d43[4*3] = {1,2,3,2,3,4,3,4,5,4,5,6};
	auto m43 = eagine::math::matrix<T, 4, 3, RM, V>::from(d43, 4*3);
	T d44[4*4] = {1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7};
	auto m44 = eagine::math::matrix<T, 4, 4, RM, V>::from(d44, 4*4);
	T d45[4*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7,4,5,6,7,8};
	auto m45 = eagine::math::matrix<T, 4, 5, RM, V>::from(d45, 4*5);

	(void)m41; (void)m42; (void)m43; (void)m44; (void)m45;

	T d51[4*1] = {1,2,3,4};
	auto m51 = eagine::math::matrix<T, 5, 1, RM, V>::from(d51, 5*1);
	T d52[5*2] = {1,2,2,3,3,4,4,5};
	auto m52 = eagine::math::matrix<T, 5, 2, RM, V>::from(d52, 5*2);
	T d53[5*3] = {1,2,3,2,3,4,3,4,5,4,5,6};
	auto m53 = eagine::math::matrix<T, 5, 3, RM, V>::from(d53, 5*3);
	T d54[5*4] = {1,2,3,4,2,3,4,5,3,4,5,6,4,5,6,7};
	auto m54 = eagine::math::matrix<T, 5, 4, RM, V>::from(d54, 5*4);
	T d55[5*5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7,4,5,6,7,8};
	auto m55 = eagine::math::matrix<T, 5, 5, RM, V>::from(d55, 5*5);

	(void)m51; (void)m52; (void)m53; (void)m54; (void)m55;
}

template <typename T>
void test_math_matrix_from_data_T(void)
{
	test_math_matrix_from_data_TRMV<T, true, true>();
	test_math_matrix_from_data_TRMV<T,false, true>();
	test_math_matrix_from_data_TRMV<T, true,false>();
	test_math_matrix_from_data_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_from_data)
{
	test_math_matrix_from_data_T<float>();
	test_math_matrix_from_data_T<double>();
}

template <typename T, bool RM, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, RM>,
	eagine::meta::integral_constant<bool, V>
)
{
	return eagine::math::matrix<T,1,1,RM,V>{{
		{d[0]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>
)
{
	return eagine::math::matrix<T,1,2,true,V>{{
		{d[0],d[1]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,2,false,V>{{
		{d[0]},
		{d[1]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,3,true,V>{{
		{d[0],d[1],d[2]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,3,false,V>{{
		{d[0]},
		{d[1]},
		{d[2]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,4,true,V>{{
		{d[0],d[1],d[2],d[3]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,4,false,V>{{
		{d[0]},
		{d[1]},
		{d[2]},
		{d[3]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,5,true,V>{{
		{d[0],d[1],d[2],d[3],d[4]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,1,5,false,V>{{
		{d[0]},
		{d[1]},
		{d[2]},
		{d[3]},
		{d[4]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,1,true,V>{{
		{d[0]},
		{d[1]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,1,false,V>{{
		{d[0],d[1]}
	}};
}

template <typename T, bool RM, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, RM>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,2,RM,V>{{
		{d[0],d[1]},
		{d[2],d[3]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,3,true,V>{{
		{d[0],d[1],d[2]},
		{d[3],d[4],d[5]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,3,false,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,4,true,V>{{
		{d[0],d[1],d[2],d[3]},
		{d[4],d[5],d[6],d[7]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,4,false,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]},
		{d[6],d[7]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,5,true,V>{{
		{d[0],d[1],d[2],d[3],d[4]},
		{d[5],d[6],d[7],d[8],d[9]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,2,5,false,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]},
		{d[6],d[7]},
		{d[8],d[9]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,1,true,V>{{
		{d[0]},
		{d[1]},
		{d[2]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,1,false,V>{{
		{d[0],d[1],d[2]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,2,true,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,2,false,V>{{
		{d[0],d[1],d[2]},
		{d[3],d[4],d[5]}
	}};
}

template <typename T, bool RM, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, RM>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,3,RM,V>{{
		{d[0],d[1],d[2]},
		{d[3],d[4],d[5]},
		{d[6],d[7],d[8]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,4,true,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3]},
		{d[ 4],d[ 5],d[ 6],d[ 7]},
		{d[ 8],d[ 9],d[10],d[11]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,4,false,V>{{
		{d[ 0],d[ 1],d[ 2]},
		{d[ 3],d[ 4],d[ 5]},
		{d[ 6],d[ 7],d[ 8]},
		{d[ 9],d[10],d[11]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,5,true,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3],d[ 4]},
		{d[ 5],d[ 6],d[ 7],d[ 8],d[ 9]},
		{d[10],d[11],d[12],d[13],d[14]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,3,5,false,V>{{
		{d[ 0],d[ 1],d[ 2]},
		{d[ 3],d[ 4],d[ 5]},
		{d[ 6],d[ 7],d[ 8]},
		{d[ 9],d[10],d[11]},
		{d[12],d[13],d[14]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,1,true,V>{{
		{d[0]},
		{d[1]},
		{d[2]},
		{d[3]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,1,false,V>{{
		{d[0],d[1],d[2],d[3]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,2,true,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]},
		{d[6],d[7]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,2,false,V>{{
		{d[0],d[1],d[2],d[3]},
		{d[4],d[5],d[6],d[7]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,3,true,V>{{
		{d[ 0],d[ 1],d[ 2]},
		{d[ 3],d[ 4],d[ 5]},
		{d[ 6],d[ 7],d[ 8]},
		{d[ 9],d[10],d[11]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,3,false,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3]},
		{d[ 4],d[ 5],d[ 6],d[ 7]},
		{d[ 8],d[ 9],d[10],d[11]}
	}};
}

template <typename T, bool RM, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, RM>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,4,RM,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3]},
		{d[ 4],d[ 5],d[ 6],d[ 7]},
		{d[ 8],d[ 9],d[10],d[11]},
		{d[12],d[13],d[14],d[15]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,5,true,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3],d[ 4]},
		{d[ 5],d[ 6],d[ 7],d[ 8],d[ 9]},
		{d[10],d[11],d[12],d[13],d[14]},
		{d[15],d[16],d[17],d[18],d[19]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,4,5,false,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3]},
		{d[ 4],d[ 5],d[ 6],d[ 7]},
		{d[ 8],d[ 9],d[10],d[11]},
		{d[12],d[13],d[14],d[15]},
		{d[16],d[17],d[18],d[19]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,1,true,V>{{
		{d[0]},
		{d[1]},
		{d[2]},
		{d[3]},
		{d[4]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 1>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,1,false,V>{{
		{d[0],d[1],d[2],d[3],d[4]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,2,true,V>{{
		{d[0],d[1]},
		{d[2],d[3]},
		{d[4],d[5]},
		{d[6],d[7]},
		{d[8],d[9]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 2>,
	eagine::meta::integral_constant<bool,false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,2,false,V>{{
		{d[0],d[1],d[2],d[3],d[4]},
		{d[5],d[6],d[7],d[8],d[9]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,3,true,V>{{
		{d[ 0],d[ 1],d[ 2]},
		{d[ 3],d[ 4],d[ 5]},
		{d[ 6],d[ 7],d[ 8]},
		{d[ 9],d[10],d[11]},
		{d[12],d[13],d[14]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 3>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,3,false,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3],d[ 4]},
		{d[ 5],d[ 6],d[ 7],d[ 8],d[ 9]},
		{d[10],d[11],d[12],d[13],d[14]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, true>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,4,true,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3]},
		{d[ 4],d[ 5],d[ 6],d[ 7]},
		{d[ 8],d[ 9],d[10],d[11]},
		{d[12],d[13],d[14],d[15]},
		{d[16],d[17],d[18],d[19]}
	}};
}

template <typename T, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 4>,
	eagine::meta::integral_constant<bool, false>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,4,false,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3],d[ 4]},
		{d[ 5],d[ 6],d[ 7],d[ 8],d[ 9]},
		{d[10],d[11],d[12],d[13],d[14]},
		{d[15],d[16],d[17],d[18],d[19]}
	}};
}

template <typename T, bool RM, bool V>
auto test_make_math_matrix(
	const T* d,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<unsigned, 5>,
	eagine::meta::integral_constant<bool, RM>,
	eagine::meta::integral_constant<bool, V>

)
{
	return eagine::math::matrix<T,5,5,RM,V>{{
		{d[ 0],d[ 1],d[ 2],d[ 3],d[ 4]},
		{d[ 5],d[ 6],d[ 7],d[ 8],d[ 9]},
		{d[10],d[11],d[12],d[13],d[14]},
		{d[15],d[16],d[17],d[18],d[19]},
		{d[20],d[21],d[22],d[23],d[24]}
	}};
}

template <typename T, unsigned R, unsigned C, bool RM, bool V>
void test_math_matrix_elements_1_TRCRMV(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	eagine::math::matrix<T,R,C,RM,V> m = test_make_math_matrix(
		d,
		eagine::meta::integral_constant<unsigned, R>(),
		eagine::meta::integral_constant<unsigned, C>(),
		eagine::meta::integral_constant<bool, RM>(),
		eagine::meta::integral_constant<bool, V>()
	);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		BOOST_ASSERT(test_math_close(m[RM?i:j][RM?j:i], d[(RM?i:j)*(RM?C:R)+(RM?j:i)]));
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_elements_1_TRMV(void)
{
	test_math_matrix_elements_1_TRCRMV<T, 1, 1, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 1, 2, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 1, 3, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 1, 4, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 1, 5, RM, V>();

	test_math_matrix_elements_1_TRCRMV<T, 2, 1, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 2, 2, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 2, 3, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 2, 4, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 2, 5, RM, V>();

	test_math_matrix_elements_1_TRCRMV<T, 3, 1, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 3, 2, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 3, 3, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 3, 4, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 3, 5, RM, V>();

	test_math_matrix_elements_1_TRCRMV<T, 4, 1, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 4, 2, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 4, 3, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 4, 4, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 4, 5, RM, V>();

	test_math_matrix_elements_1_TRCRMV<T, 5, 1, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 5, 2, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 5, 3, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 5, 4, RM, V>();
	test_math_matrix_elements_1_TRCRMV<T, 5, 5, RM, V>();
}

template <typename T>
void test_math_matrix_elements_1_T(void)
{
	test_math_matrix_elements_1_TRMV<T, true, true>();
	test_math_matrix_elements_1_TRMV<T,false, true>();
	test_math_matrix_elements_1_TRMV<T, true,false>();
	test_math_matrix_elements_1_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_elements_1)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_elements_1_T<float>();
		test_math_matrix_elements_1_T<double>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM, bool V>
void test_math_matrix_elements_2_TRCRMV(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	eagine::math::matrix<T,R,C,RM,V> m =
		eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);

	for(unsigned i=0; i<R; ++i)
	for(unsigned j=0; j<C; ++j)
	{
		BOOST_ASSERT(test_math_close(m[RM?i:j][RM?j:i], d[(RM?i:j)*(RM?C:R)+(RM?j:i)]));
	}
}

template <typename T, bool RM, bool V>
void test_math_matrix_elements_2_TRMV(void)
{
	test_math_matrix_elements_2_TRCRMV<T, 1, 1, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 1, 2, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 1, 3, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 1, 4, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 1, 5, RM, V>();

	test_math_matrix_elements_2_TRCRMV<T, 2, 1, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 2, 2, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 2, 3, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 2, 4, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 2, 5, RM, V>();

	test_math_matrix_elements_2_TRCRMV<T, 3, 1, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 3, 2, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 3, 3, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 3, 4, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 3, 5, RM, V>();

	test_math_matrix_elements_2_TRCRMV<T, 4, 1, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 4, 2, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 4, 3, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 4, 4, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 4, 5, RM, V>();

	test_math_matrix_elements_2_TRCRMV<T, 5, 1, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 5, 2, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 5, 3, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 5, 4, RM, V>();
	test_math_matrix_elements_2_TRCRMV<T, 5, 5, RM, V>();
}

template <typename T>
void test_math_matrix_elements_2_T(void)
{
	test_math_matrix_elements_2_TRMV<T, true, true>();
	test_math_matrix_elements_2_TRMV<T,false, true>();
	test_math_matrix_elements_2_TRMV<T, true,false>();
	test_math_matrix_elements_2_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_elements_2)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_elements_2_T<float>();
		test_math_matrix_elements_2_T<double>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM, bool V>
void test_math_matrix_equal_TRCRMV(void)
{
	T d[R*C];

	for(unsigned k=0; k<R*C; ++k)
	{
		d[k] = std::rand() / T(3);
	}

	eagine::math::matrix<T,R,C,RM,V> m1 =
		eagine::math::matrix<T,R,C,RM,V>::from(d, R*C);
	eagine::math::matrix<T,R,C,RM,V> m2 = test_make_math_matrix(
		d,
		eagine::meta::integral_constant<unsigned, R>(),
		eagine::meta::integral_constant<unsigned, C>(),
		eagine::meta::integral_constant<bool, RM>(),
		eagine::meta::integral_constant<bool, V>()
	);
	eagine::math::matrix<T,R,C,RM,V> m3(m1);

	BOOST_ASSERT(m1 == m2);
	BOOST_ASSERT(m2 == m1);
	BOOST_ASSERT(m1 == m3);
	BOOST_ASSERT(m3 == m1);
	BOOST_ASSERT(m2 == m3);
	BOOST_ASSERT(m3 == m2);
}

template <typename T, bool RM, bool V>
void test_math_matrix_equal_TRMV(void)
{
	test_math_matrix_equal_TRCRMV<T, 1, 1, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 1, 2, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 1, 3, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 1, 4, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 1, 5, RM, V>();

	test_math_matrix_equal_TRCRMV<T, 2, 1, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 2, 2, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 2, 3, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 2, 4, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 2, 5, RM, V>();

	test_math_matrix_equal_TRCRMV<T, 3, 1, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 3, 2, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 3, 3, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 3, 4, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 3, 5, RM, V>();

	test_math_matrix_equal_TRCRMV<T, 4, 1, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 4, 2, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 4, 3, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 4, 4, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 4, 5, RM, V>();

	test_math_matrix_equal_TRCRMV<T, 5, 1, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 5, 2, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 5, 3, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 5, 4, RM, V>();
	test_math_matrix_equal_TRCRMV<T, 5, 5, RM, V>();
}

template <typename T>
void test_math_matrix_equal_T(void)
{
	test_math_matrix_equal_TRMV<T, true, true>();
	test_math_matrix_equal_TRMV<T,false, true>();
	test_math_matrix_equal_TRMV<T, true,false>();
	test_math_matrix_equal_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_equal)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_equal_T<float>();
		test_math_matrix_equal_T<double>();
	}
}

template <typename T, unsigned R, unsigned C, bool RM, bool V>
void test_math_matrix_compare_TRCRMV(void)
{
	T d1[R*C];
	T d2[R*C];

	bool gen_eq = std::rand() % 23 == 0;
	bool all_eq = true;

	for(unsigned k=0; k<R*C; ++k)
	{
		d1[k] = std::rand() / T(3);
		d2[k] = gen_eq?d1[k]:std::rand() / T(3);

		using eagine::math::equal_to;
		all_eq &= (d1[k] <<equal_to>> d2[k]);
	}

	eagine::math::matrix<T,R,C,RM,V> m1 =
		eagine::math::matrix<T,R,C,RM,V>::from(d1, R*C);
	eagine::math::matrix<T,R,C,RM,V> m2 =
		eagine::math::matrix<T,R,C,RM,V>::from(d2, R*C);

	BOOST_ASSERT((m1 == m2) ==  all_eq);
	BOOST_ASSERT((m1 != m2) == !all_eq);
}

template <typename T, bool RM, bool V>
void test_math_matrix_compare_TRMV(void)
{
	test_math_matrix_compare_TRCRMV<T, 1, 1, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 1, 2, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 1, 3, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 1, 4, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 1, 5, RM, V>();

	test_math_matrix_compare_TRCRMV<T, 2, 1, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 2, 2, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 2, 3, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 2, 4, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 2, 5, RM, V>();

	test_math_matrix_compare_TRCRMV<T, 3, 1, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 3, 2, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 3, 3, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 3, 4, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 3, 5, RM, V>();

	test_math_matrix_compare_TRCRMV<T, 4, 1, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 4, 2, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 4, 3, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 4, 4, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 4, 5, RM, V>();

	test_math_matrix_compare_TRCRMV<T, 5, 1, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 5, 2, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 5, 3, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 5, 4, RM, V>();
	test_math_matrix_compare_TRCRMV<T, 5, 5, RM, V>();
}

template <typename T>
void test_math_matrix_compare_T(void)
{
	test_math_matrix_compare_TRMV<T, true, true>();
	test_math_matrix_compare_TRMV<T,false, true>();
	test_math_matrix_compare_TRMV<T, true,false>();
	test_math_matrix_compare_TRMV<T,false,false>();
}

BOOST_AUTO_TEST_CASE(math_matrix_compare)
{
	for(int i=0; i<100; ++i)
	{
		test_math_matrix_compare_T<float>();
		test_math_matrix_compare_T<double>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
