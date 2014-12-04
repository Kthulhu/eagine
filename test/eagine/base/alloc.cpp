/**
 *  .file test/eagine/base/alloc.cpp
 *  .brief Test case for base::alloc class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_alloc
#include <boost/test/unit_test.hpp>

#include <eagine/base/alloc.hpp>
#include <vector>
#include <utility>

BOOST_AUTO_TEST_SUITE(base_alloc)

BOOST_AUTO_TEST_CASE(base_alloc_default_construction)
{
	eagine::base::allocator<void> a_v;
	eagine::base::allocator<bool> a_b;
	eagine::base::allocator<char> a_c;
	eagine::base::allocator<short> a_s;
	eagine::base::allocator<int> a_i;
	eagine::base::allocator<long> a_l;
	eagine::base::allocator<float> a_f;
	eagine::base::allocator<double> a_d;
	eagine::base::allocator<std::pair<char, double>> a_p;

	(void)a_v;
	(void)a_b;
	(void)a_c;
	(void)a_s;
	(void)a_i;
	(void)a_l;
	(void)a_f;
	(void)a_d;
	(void)a_p;
}

BOOST_AUTO_TEST_CASE(base_alloc_copy_construction)
{
	eagine::base::allocator<void> a_v1;
	eagine::base::allocator<bool> a_b1;
	eagine::base::allocator<char> a_c1;
	eagine::base::allocator<short> a_s1;
	eagine::base::allocator<int> a_i1;
	eagine::base::allocator<long> a_l1;
	eagine::base::allocator<float> a_f1;
	eagine::base::allocator<double> a_d1;
	eagine::base::allocator<std::pair<char, double>> a_p1;

	eagine::base::allocator<void> a_v2(a_v1);
	eagine::base::allocator<bool> a_b2(a_b1);
	eagine::base::allocator<char> a_c2(a_c1);
	eagine::base::allocator<short> a_s2(a_s1);
	eagine::base::allocator<int> a_i2(a_i1);
	eagine::base::allocator<long> a_l2(a_l1);
	eagine::base::allocator<float> a_f2(a_f1);
	eagine::base::allocator<double> a_d2(a_d1);
	eagine::base::allocator<std::pair<char, double>> a_p2(a_p1);

	(void)a_v2;
	(void)a_b2;
	(void)a_c2;
	(void)a_s2;
	(void)a_i2;
	(void)a_l2;
	(void)a_f2;
	(void)a_d2;
	(void)a_p2;
}

BOOST_AUTO_TEST_CASE(base_alloc_move_construction)
{
	eagine::base::allocator<void> a_v1;
	eagine::base::allocator<bool> a_b1;
	eagine::base::allocator<char> a_c1;
	eagine::base::allocator<short> a_s1;
	eagine::base::allocator<int> a_i1;
	eagine::base::allocator<long> a_l1;
	eagine::base::allocator<float> a_f1;
	eagine::base::allocator<double> a_d1;
	eagine::base::allocator<std::pair<char, double>> a_p1;

	eagine::base::allocator<void> a_v2(std::move(a_v1));
	eagine::base::allocator<bool> a_b2(std::move(a_b1));
	eagine::base::allocator<char> a_c2(std::move(a_c1));
	eagine::base::allocator<short> a_s2(std::move(a_s1));
	eagine::base::allocator<int> a_i2(std::move(a_i1));
	eagine::base::allocator<long> a_l2(std::move(a_l1));
	eagine::base::allocator<float> a_f2(std::move(a_f1));
	eagine::base::allocator<double> a_d2(std::move(a_d1));
	eagine::base::allocator<std::pair<char, double>> a_p2(std::move(a_p1));

	(void)a_v2;
	(void)a_b2;
	(void)a_c2;
	(void)a_s2;
	(void)a_i2;
	(void)a_l2;
	(void)a_f2;
	(void)a_d2;
	(void)a_p2;
}

BOOST_AUTO_TEST_CASE(base_alloc_rebind)
{
	eagine::base::allocator<void> a_v1;
	eagine::base::allocator<int> a_i1;
	eagine::base::allocator<std::pair<char, double>> a_p1;

	eagine::base::allocator<bool> a_b2(a_v1);
	eagine::base::allocator<float> a_f2(a_v1);
	eagine::base::allocator<char> a_c2(a_i1);
	eagine::base::allocator<long> a_l2(a_p1);
	eagine::base::allocator<std::pair<bool, float>> a_p2(a_i1);
	
	(void) a_b2;
	(void) a_f2;
	(void) a_c2;
	(void) a_l2;
	(void) a_p2;
}

BOOST_AUTO_TEST_CASE(base_alloc_vector_1)
{
	eagine::base::allocator<int> a;

	const unsigned n = 1000;

	std::vector<int*> v;
	v.reserve(n);

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(new (a.allocate(1)) int(i));
	}

	for(unsigned i=n; i!=0; --i)
	{
		BOOST_ASSERT(*v.back() == int(i-1));
		a.deallocate(v.back(), 1);
		v.pop_back();
	}
}

BOOST_AUTO_TEST_CASE(base_alloc_vector_2)
{
	eagine::base::allocator<unsigned> a;

	std::vector<unsigned, eagine::base::allocator<unsigned>> v(a);

	const unsigned n = 16000;

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(i);
	}

	for(unsigned i=0; i!=n; ++i)
	{
		BOOST_ASSERT(v[i] == i);
	}

	BOOST_ASSERT(v.size() == n);
}

BOOST_AUTO_TEST_CASE(base_alloc_vector_3)
{
	eagine::base::allocator<std::vector<int>> a;

	std::vector<std::vector<int>> v;

	const unsigned n = 1000;
	const unsigned m = 50;

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(std::vector<int>());
		for(unsigned j=0; j!=m; ++j)
		{
			v.back().push_back(j);
		}
	}

	BOOST_ASSERT(v.size() == n);

	for(unsigned i=0; i!=n; ++i)
	{
		BOOST_ASSERT(v[i].size() == m);
		for(unsigned j=0; j!=m; ++j)
		{
			BOOST_ASSERT(v[i][j] == int(j));
		}
	}

	for(unsigned i=0; i!=n; ++i)
	{
		for(unsigned j=0; j!=m; ++j)
		{
			v[i].pop_back();
		}
	}

	for(unsigned i=0; i!=n; ++i)
	{
		v.pop_back();
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
