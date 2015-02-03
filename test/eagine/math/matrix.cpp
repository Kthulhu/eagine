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

BOOST_AUTO_TEST_SUITE_END()
