/**
 *  .file test/eagine/base/string.cpp
 *  .brief Test case for base::string class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_string
#include <boost/test/unit_test.hpp>

#include <eagine/base/string.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/array.hpp>
#include <cstring>
#include <algorithm>

#include <iostream> // TODO 

BOOST_AUTO_TEST_SUITE(base_string)

BOOST_AUTO_TEST_CASE(base_string_default_construction)
{
	eagine::base::string s;
}

BOOST_AUTO_TEST_CASE(base_string_construction_from_literal)
{
	eagine::base::string s("a string");
}

BOOST_AUTO_TEST_CASE(base_string_construction_from_array)
{
	const char c_str[] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string s(c_str);
}

BOOST_AUTO_TEST_CASE(base_string_copy_construction)
{
	eagine::base::string s1("a string");
	eagine::base::string s2(s1);
}

BOOST_AUTO_TEST_CASE(base_string_move_construction)
{
	eagine::base::string s1(eagine::base::string("a string"));
}

BOOST_AUTO_TEST_CASE(base_string_assignment_from_literal)
{
	eagine::base::string s1;
	s1 = "a string";
}

BOOST_AUTO_TEST_CASE(base_string_assignment_from_array)
{
	eagine::base::string s1;
	const char c_str[] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	s1 = c_str;
}

BOOST_AUTO_TEST_CASE(base_string_assignment_copy)
{
	eagine::base::string s1("a string");
	eagine::base::string s2;
	s2 = s1;
}

BOOST_AUTO_TEST_CASE(base_string_equality_comparison)
{
	eagine::base::string s1("a string");
	eagine::base::string s2("another string");
	eagine::base::string s3;

	BOOST_ASSERT(s1 == s1);
	BOOST_ASSERT(s2 == s2);
	BOOST_ASSERT(s3 == s3);

	BOOST_ASSERT(s1 != s2);
	BOOST_ASSERT(s1 != s3);
	BOOST_ASSERT(s2 != s1);
	BOOST_ASSERT(s2 != s3);
	BOOST_ASSERT(s3 != s1);
	BOOST_ASSERT(s3 != s2);
}

BOOST_AUTO_TEST_CASE(base_string_empty)
{
	eagine::base::string s1("a string");
	eagine::base::string s2;
	BOOST_ASSERT(!s1.empty());
	BOOST_ASSERT( s2.empty());
}

BOOST_AUTO_TEST_CASE(base_string_size)
{
	eagine::base::string s1("a string");
	eagine::base::string s2;
	BOOST_ASSERT(s1.size() == 8);
	BOOST_ASSERT(s2.size() == 0);
}

BOOST_AUTO_TEST_CASE(base_string_clear)
{
	eagine::base::string s1("a string");
	BOOST_ASSERT(!s1.empty());
	BOOST_ASSERT(s1.size() == 8);
	s1.clear();
	BOOST_ASSERT( s1.empty());
	BOOST_ASSERT(s1.size() == 0);
}

// TODO

BOOST_AUTO_TEST_CASE(base_string_ref_default_construction)
{
	eagine::base::string_ref sr;
	eagine::base::const_string_ref csr;
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_c_str)
{
	const char* c_str = "a string";
	eagine::base::const_string_ref csr(c_str);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_c_array)
{
	char c_str[] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr(c_str);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_const_string)
{
	const eagine::base::string cs = "a string";
	eagine::base::const_string_ref csr(cs);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_string)
{
	eagine::base::string s = "a string";
	eagine::base::string_ref sr(s);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_literal)
{
	eagine::base::const_string_ref sr ="a string"; 
	(void)sr;
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_const_vector)
{
	const eagine::base::vector<char> cv(10, 'a');
	eagine::base::const_string_ref csr(cv);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_vector)
{
	eagine::base::vector<char> v(10, 'a');
	eagine::base::string_ref sr(v);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_const_array)
{
	eagine::base::array<char, 5> a;
	const eagine::base::array<char, 5>& ca = a;
	eagine::base::const_string_ref csr(ca);
}

BOOST_AUTO_TEST_CASE(base_string_ref_construction_array)
{
	eagine::base::array<char, 5> a;
	eagine::base::string_ref sr(a);
}

BOOST_AUTO_TEST_CASE(base_string_ref_copy_construction)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr1 = c_str;
	eagine::base::string_ref sr2 = sr1;
	eagine::base::const_string_ref csr1 = sr2;
	eagine::base::const_string_ref csr2 = csr1;
	(void)csr2;
}

BOOST_AUTO_TEST_CASE(base_string_ref_empty)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr1 = c_str;
	eagine::base::string_ref sr2;
	BOOST_ASSERT(!sr1.empty());
	BOOST_ASSERT( sr2.empty());
}

BOOST_AUTO_TEST_CASE(base_string_ref_size)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr1 = c_str;
	eagine::base::string_ref sr2;
	BOOST_ASSERT(sizeof(c_str)/sizeof(c_str[0]) == 8);
	BOOST_ASSERT(sr1.size() == 8);
	BOOST_ASSERT(sr2.size() == 0);
}

BOOST_AUTO_TEST_CASE(base_string_ref_data)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string str("a string");
	eagine::base::string_ref sr = c_str;
	eagine::base::const_string_ref csr = c_str;

	BOOST_ASSERT(sizeof(c_str)/sizeof(c_str[0]) == sr.size());
	BOOST_ASSERT(str.size() == csr.size());
	BOOST_ASSERT(sr.size() == csr.size());

	BOOST_ASSERT(std::strncmp(c_str, sr.data(), sr.size()) == 0);
	BOOST_ASSERT(std::strncmp(str.c_str(), sr.data(), sr.size()) == 0);
	BOOST_ASSERT(std::strncmp(sr.data(), csr.data(), sr.size()) == 0);
}

BOOST_AUTO_TEST_CASE(base_string_ref_iterator_1)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr1 = c_str;
	eagine::base::string_ref sr2;

	BOOST_ASSERT(sr1.begin() != sr1.end());
	BOOST_ASSERT(sr1.begin()+sr1.size() == sr1.end());
	BOOST_ASSERT(sr1.begin() == sr1.end()-sr1.size());
	BOOST_ASSERT(sr1.begin()+sr1.size()+1 != sr1.end());
	BOOST_ASSERT(sr1.begin()+sr1.size()-1 != sr1.end());

	BOOST_ASSERT(sr2.begin() == sr2.end());
	BOOST_ASSERT(sr2.begin()+sr2.size() == sr2.end());
	BOOST_ASSERT(sr2.begin() == sr2.end()-sr2.size());
}

BOOST_AUTO_TEST_CASE(base_string_ref_iterator_2)
{
	char c_str[8] = {'a', ' ', 's','t', 'r', 'i', 'n', 'g'};
	eagine::base::string_ref sr1 = c_str;

	BOOST_ASSERT(std::equal(sr1.begin(), sr1.end(), c_str));
	BOOST_ASSERT(std::equal(c_str, c_str+8, sr1.begin()));
}

BOOST_AUTO_TEST_SUITE_END()
