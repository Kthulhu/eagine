/**
 *  .file test/eagine/math/vector.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_math_vector
#include <boost/test/unit_test.hpp>

#include <eagine/math/vector.hpp>
#include <cstdlib>
#include <cmath>
#include "common.hpp"

BOOST_AUTO_TEST_SUITE(math_vector)

BOOST_AUTO_TEST_CASE(math_vector_default_ctr)
{
	eagine::math::vector<int, 1> vi1;
	eagine::math::vector<int, 2> vi2;
	eagine::math::vector<int, 3> vi3;
	eagine::math::vector<int, 4> vi4;
	eagine::math::vector<int, 5> vi5;
	eagine::math::vector<int, 6> vi6;
	eagine::math::vector<int, 7> vi7;
	eagine::math::vector<int, 8> vi8;

	eagine::math::vector<float, 1> vf1;
	eagine::math::vector<float, 2> vf2;
	eagine::math::vector<float, 3> vf3;
	eagine::math::vector<float, 4> vf4;
	eagine::math::vector<float, 5> vf5;
	eagine::math::vector<float, 6> vf6;
	eagine::math::vector<float, 7> vf7;
	eagine::math::vector<float, 8> vf8;

	eagine::math::vector<double, 1> vd1;
	eagine::math::vector<double, 2> vd2;
	eagine::math::vector<double, 3> vd3;
	eagine::math::vector<double, 4> vd4;
	eagine::math::vector<double, 5> vd5;
	eagine::math::vector<double, 6> vd6;
	eagine::math::vector<double, 7> vd7;
	eagine::math::vector<double, 8> vd8;

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_init_ctr1)
{
	eagine::math::vector<int, 1> vi1 = {{1}};
	eagine::math::vector<int, 2> vi2 = {{1, 2}};
	eagine::math::vector<int, 3> vi3 = {{1, 2, 3}};
	eagine::math::vector<int, 4> vi4 = {{1, 2, 3, 4}};
	eagine::math::vector<int, 5> vi5 = {{1, 2, 3, 4, 5}};
	eagine::math::vector<int, 6> vi6 = {{1, 2, 3, 4, 5, 6}};
	eagine::math::vector<int, 7> vi7 = {{1, 2, 3, 4, 5, 6, 7}};
	eagine::math::vector<int, 8> vi8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	eagine::math::vector<float, 1> vf1 = {{1.f}};
	eagine::math::vector<float, 2> vf2 = {{1.f, 2.f}};
	eagine::math::vector<float, 3> vf3 = {{1.f, 2.f, 3.f}};
	eagine::math::vector<float, 4> vf4 = {{1.f, 2.f, 3.f, 4.f}};
	eagine::math::vector<float, 5> vf5 = {{1.f, 2.f, 3.f, 4.f, 5.f}};
	eagine::math::vector<float, 6> vf6 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
	eagine::math::vector<float, 7> vf7 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}};
	eagine::math::vector<float, 8> vf8 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f}};

	eagine::math::vector<double, 1> vd1 = {{1.0}};
	eagine::math::vector<double, 2> vd2 = {{1.0, 2.0}};
	eagine::math::vector<double, 3> vd3 = {{1.0, 2.0, 3.0}};
	eagine::math::vector<double, 4> vd4 = {{1.0, 2.0, 3.0, 4.0}};
	eagine::math::vector<double, 5> vd5 = {{1.0, 2.0, 3.0, 4.0, 5.0}};
	eagine::math::vector<double, 6> vd6 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
	eagine::math::vector<double, 7> vd7 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
	eagine::math::vector<double, 8> vd8 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_copy_ctr)
{
	eagine::math::vector<int, 1> via1 = {{1}};
	eagine::math::vector<int, 2> via2 = {{1, 2}};
	eagine::math::vector<int, 3> via3 = {{1, 2, 3}};
	eagine::math::vector<int, 4> via4 = {{1, 2, 3, 4}};
	eagine::math::vector<int, 5> via5 = {{1, 2, 3, 4, 5}};
	eagine::math::vector<int, 6> via6 = {{1, 2, 3, 4, 5, 6}};
	eagine::math::vector<int, 7> via7 = {{1, 2, 3, 4, 5, 6, 7}};
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	eagine::math::vector<float, 1> vfa1 = {{1.f}};
	eagine::math::vector<float, 2> vfa2 = {{1.f, 2.f}};
	eagine::math::vector<float, 3> vfa3 = {{1.f, 2.f, 3.f}};
	eagine::math::vector<float, 4> vfa4 = {{1.f, 2.f, 3.f, 4.f}};
	eagine::math::vector<float, 5> vfa5 = {{1.f, 2.f, 3.f, 4.f, 5.f}};
	eagine::math::vector<float, 6> vfa6 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
	eagine::math::vector<float, 7> vfa7 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}};
	eagine::math::vector<float, 8> vfa8 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f}};

	eagine::math::vector<double, 1> vda1 = {{1.0}};
	eagine::math::vector<double, 2> vda2 = {{1.0, 2.0}};
	eagine::math::vector<double, 3> vda3 = {{1.0, 2.0, 3.0}};
	eagine::math::vector<double, 4> vda4 = {{1.0, 2.0, 3.0, 4.0}};
	eagine::math::vector<double, 5> vda5 = {{1.0, 2.0, 3.0, 4.0, 5.0}};
	eagine::math::vector<double, 6> vda6 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
	eagine::math::vector<double, 7> vda7 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
	eagine::math::vector<double, 8> vda8 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

	eagine::math::vector<int, 1> vi1 = via1;
	eagine::math::vector<int, 2> vi2 = via2;
	eagine::math::vector<int, 3> vi3 = via3;
	eagine::math::vector<int, 4> vi4 = via4;
	eagine::math::vector<int, 5> vi5 = via5;
	eagine::math::vector<int, 6> vi6 = via6;
	eagine::math::vector<int, 7> vi7 = via7;
	eagine::math::vector<int, 8> vi8 = via8;

	eagine::math::vector<float, 1> vf1 = vfa1;
	eagine::math::vector<float, 2> vf2 = vfa2;
	eagine::math::vector<float, 3> vf3 = vfa3;
	eagine::math::vector<float, 4> vf4 = vfa4;
	eagine::math::vector<float, 5> vf5 = vfa5;
	eagine::math::vector<float, 6> vf6 = vfa6;
	eagine::math::vector<float, 7> vf7 = vfa7;
	eagine::math::vector<float, 8> vf8 = vfa8;

	eagine::math::vector<double, 1> vd1 = vda1;
	eagine::math::vector<double, 2> vd2 = vda2;
	eagine::math::vector<double, 3> vd3 = vda3;
	eagine::math::vector<double, 4> vd4 = vda4;
	eagine::math::vector<double, 5> vd5 = vda5;
	eagine::math::vector<double, 6> vd6 = vda6;
	eagine::math::vector<double, 7> vd7 = vda7;
	eagine::math::vector<double, 8> vd8 = vda8;


	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_make)
{
	auto vi1 = eagine::math::vector<int, 1>::make(1);
	auto vi2 = eagine::math::vector<int, 2>::make(1, 2);
	auto vi3 = eagine::math::vector<int, 3>::make(1, 2, 3);
	auto vi4 = eagine::math::vector<int, 4>::make(1, 2, 3, 4);
	auto vi5 = eagine::math::vector<int, 5>::make(1, 2, 3, 4, 5);
	auto vi6 = eagine::math::vector<int, 6>::make(1, 2, 3, 4, 5, 6);
	auto vi7 = eagine::math::vector<int, 7>::make(1, 2, 3, 4, 5, 6, 7);
	auto vi8 = eagine::math::vector<int, 8>::make(1, 2, 3, 4, 5, 6, 7, 8);

	auto vf1 = eagine::math::vector<float, 1>::make(1.f);
	auto vf2 = eagine::math::vector<float, 2>::make(1.f, 2.f);
	auto vf3 = eagine::math::vector<float, 3>::make(1.f, 2.f, 3.f);
	auto vf4 = eagine::math::vector<float, 4>::make(1.f, 2.f, 3.f, 4.f);
	auto vf5 = eagine::math::vector<float, 5>::make(1.f, 2.f, 3.f, 4.f, 5.f);
	auto vf6 = eagine::math::vector<float, 6>::make(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
	auto vf7 = eagine::math::vector<float, 7>::make(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
	auto vf8 = eagine::math::vector<float, 8>::make(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f);

	auto vd1 = eagine::math::vector<double, 1>::make(1);
	auto vd2 = eagine::math::vector<double, 2>::make(1, 2);
	auto vd3 = eagine::math::vector<double, 3>::make(1, 2, 3);
	auto vd4 = eagine::math::vector<double, 4>::make(1, 2, 3, 4);
	auto vd5 = eagine::math::vector<double, 5>::make(1, 2, 3, 4, 5);
	auto vd6 = eagine::math::vector<double, 6>::make(1, 2, 3, 4, 5, 6);
	auto vd7 = eagine::math::vector<double, 7>::make(1, 2, 3, 4, 5, 6, 7);
	auto vd8 = eagine::math::vector<double, 8>::make(1, 2, 3, 4, 5, 6, 7, 8);

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_from1)
{
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	auto vi8 = eagine::math::vector<int, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vi7 = eagine::math::vector<int, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vi6 = eagine::math::vector<int, 6>::from<0,1,2,3,4,5>(via8);
	auto vi5 = eagine::math::vector<int, 5>::from<0,1,2,3,4>(via8);
	auto vi4 = eagine::math::vector<int, 4>::from<0,1,2,3>(via8);
	auto vi3 = eagine::math::vector<int, 3>::from<0,1,2>(via8);
	auto vi2 = eagine::math::vector<int, 2>::from<0,1>(via8);
	auto vi1 = eagine::math::vector<int, 1>::from<0>(via8);

	auto vf8 = eagine::math::vector<float, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vf7 = eagine::math::vector<float, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vf6 = eagine::math::vector<float, 6>::from<0,1,2,3,4,5>(via8);
	auto vf5 = eagine::math::vector<float, 5>::from<0,1,2,3,4>(via8);
	auto vf4 = eagine::math::vector<float, 4>::from<0,1,2,3>(via8);
	auto vf3 = eagine::math::vector<float, 3>::from<0,1,2>(via8);
	auto vf2 = eagine::math::vector<float, 2>::from<0,1>(via8);
	auto vf1 = eagine::math::vector<float, 1>::from<0>(via8);

	auto vd8 = eagine::math::vector<double, 8>::from<0,1,2,3,4,5,6,7>(via8);
	auto vd7 = eagine::math::vector<double, 7>::from<0,1,2,3,4,5,6>(via8);
	auto vd6 = eagine::math::vector<double, 6>::from<0,1,2,3,4,5>(via8);
	auto vd5 = eagine::math::vector<double, 5>::from<0,1,2,3,4>(via8);
	auto vd4 = eagine::math::vector<double, 4>::from<0,1,2,3>(via8);
	auto vd3 = eagine::math::vector<double, 3>::from<0,1,2>(via8);
	auto vd2 = eagine::math::vector<double, 2>::from<0,1>(via8);
	auto vd1 = eagine::math::vector<double, 1>::from<0>(via8);

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

BOOST_AUTO_TEST_CASE(math_vector_from2)
{
	eagine::math::vector<int, 1> via1 = {{1}};
	eagine::math::vector<int, 2> via2 = {{1, 2}};
	eagine::math::vector<int, 3> via3 = {{1, 2, 3}};
	eagine::math::vector<int, 4> via4 = {{1, 2, 3, 4}};
	eagine::math::vector<int, 5> via5 = {{1, 2, 3, 4, 5}};
	eagine::math::vector<int, 6> via6 = {{1, 2, 3, 4, 5, 6}};
	eagine::math::vector<int, 7> via7 = {{1, 2, 3, 4, 5, 6, 7}};
	eagine::math::vector<int, 8> via8 = {{1, 2, 3, 4, 5, 6, 7, 8}};

	eagine::math::vector<float, 1> vfa1 = {{1.f}};
	eagine::math::vector<float, 2> vfa2 = {{1.f, 2.f}};
	eagine::math::vector<float, 3> vfa3 = {{1.f, 2.f, 3.f}};
	eagine::math::vector<float, 4> vfa4 = {{1.f, 2.f, 3.f, 4.f}};
	eagine::math::vector<float, 5> vfa5 = {{1.f, 2.f, 3.f, 4.f, 5.f}};
	eagine::math::vector<float, 6> vfa6 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f}};
	eagine::math::vector<float, 7> vfa7 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}};
	eagine::math::vector<float, 8> vfa8 = {{1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f}};

	eagine::math::vector<double, 1> vda1 = {{1.0}};
	eagine::math::vector<double, 2> vda2 = {{1.0, 2.0}};
	eagine::math::vector<double, 3> vda3 = {{1.0, 2.0, 3.0}};
	eagine::math::vector<double, 4> vda4 = {{1.0, 2.0, 3.0, 4.0}};
	eagine::math::vector<double, 5> vda5 = {{1.0, 2.0, 3.0, 4.0, 5.0}};
	eagine::math::vector<double, 6> vda6 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};
	eagine::math::vector<double, 7> vda7 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
	eagine::math::vector<double, 8> vda8 = {{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

	auto vi1 = eagine::math::vector<int, 1>::from<0>(via1);
	auto vi2 = eagine::math::vector<int, 2>::from<1, 0>(via2);
	auto vi3 = eagine::math::vector<int, 3>::from<2, 1, 0>(via3);
	auto vi4 = eagine::math::vector<int, 4>::from<3, 2, 1, 0>(via4);
	auto vi5 = eagine::math::vector<int, 5>::from<4, 3, 2, 1, 0>(via5);
	auto vi6 = eagine::math::vector<int, 6>::from<5, 4, 3, 2, 1, 0>(via6);
	auto vi7 = eagine::math::vector<int, 7>::from<6, 5, 4, 3, 2, 1, 0>(via7);
	auto vi8 = eagine::math::vector<int, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(via8);

	auto vf1 = eagine::math::vector<float, 1>::from<0>(vfa1);
	auto vf2 = eagine::math::vector<float, 2>::from<1, 0>(vfa2);
	auto vf3 = eagine::math::vector<float, 3>::from<2, 1, 0>(vfa3);
	auto vf4 = eagine::math::vector<float, 4>::from<3, 2, 1, 0>(vfa4);
	auto vf5 = eagine::math::vector<float, 5>::from<4, 3, 2, 1, 0>(vfa5);
	auto vf6 = eagine::math::vector<float, 6>::from<5, 4, 3, 2, 1, 0>(vfa6);
	auto vf7 = eagine::math::vector<float, 7>::from<6, 5, 4, 3, 2, 1, 0>(vfa7);
	auto vf8 = eagine::math::vector<float, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(vfa8);

	auto vd1 = eagine::math::vector<double, 1>::from<0>(vda1);
	auto vd2 = eagine::math::vector<double, 2>::from<1, 0>(vda2);
	auto vd3 = eagine::math::vector<double, 3>::from<2, 1, 0>(vda3);
	auto vd4 = eagine::math::vector<double, 4>::from<3, 2, 1, 0>(vda4);
	auto vd5 = eagine::math::vector<double, 5>::from<4, 3, 2, 1, 0>(vda5);
	auto vd6 = eagine::math::vector<double, 6>::from<5, 4, 3, 2, 1, 0>(vda6);
	auto vd7 = eagine::math::vector<double, 7>::from<6, 5, 4, 3, 2, 1, 0>(vda7);
	auto vd8 = eagine::math::vector<double, 8>::from<7, 6, 5, 4, 3, 2, 1, 0>(vda8);

	(void)vi1; (void)vi2; (void)vi3; (void)vi4; (void)vi5; (void)vi6; (void)vi7; (void)vi8;
	(void)vf1; (void)vf2; (void)vf3; (void)vf4; (void)vf5; (void)vf6; (void)vf7; (void)vf8;
	(void)vd1; (void)vd2; (void)vd3; (void)vd4; (void)vd5; (void)vd6; (void)vd7; (void)vd8;
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
