/**
 *  .file test/eagine/base/utf8.cpp
 *  .brief Test case for base utf8 functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_utf8
#include <boost/test/unit_test.hpp>

#include <eagine/base/utf8.hpp>
#include <cstdlib>

BOOST_AUTO_TEST_SUITE(base_utf8)

BOOST_AUTO_TEST_CASE(base_utf8_1)
{
	char str[128];
	for(unsigned i=0; i<128; ++i)
	{
		str[i] = char(i & 0xFF);
	}

	BOOST_ASSERT(eagine::base::valid_utf8(str+1, str+128));
}

template <std::size_t N>
void do_test_base_utf8_2(void)
{
	typedef eagine::base::unicode_cp cp_t;

	cp_t cps1[N];
	for(std::size_t i=0; i<N; ++i)
	{
		do { cps1[i] = cp_t(std::rand()) & 0x7FFFFFFFu; }
		while(cps1[i] == 0);
	}

	eagine::base::vector<char> str;

	eagine::base::convert_code_points_to_utf8(cps1, N, str);

	BOOST_ASSERT(eagine::base::valid_utf8(
		str.data(),
		str.data()+
		str.size()
	));

	eagine::base::vector<cp_t> cps2;

	eagine::base::convert_utf8_to_code_points(str.data(), str.size(), cps2);

	BOOST_ASSERT(cps2.size() == N);

	for(std::size_t i=0; i<N; ++i)
	{
		BOOST_ASSERT(cps1[i] == cps2[i]);
	}
}

BOOST_AUTO_TEST_CASE(base_utf8_2)
{
	for(unsigned i=0; i<10240; ++i)
	{
		do_test_base_utf8_2<1024>();
	}
}

BOOST_AUTO_TEST_SUITE_END()
