/**
 *  .file test/eagine/base/alloc.cpp
 *  .brief Test case for base::alloc class and related functionality.
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_alloc
#include <boost/test/unit_test.hpp>

#include <eagine/base/alloc.hpp>
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>

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

BOOST_AUTO_TEST_CASE(base_alloc_max_size)
{
	eagine::base::allocator<bool> a_b;
	eagine::base::allocator<char> a_c;
	eagine::base::allocator<short> a_s;
	eagine::base::allocator<int> a_i;
	eagine::base::allocator<long> a_l;
	eagine::base::allocator<float> a_f;
	eagine::base::allocator<double> a_d;
	eagine::base::allocator<std::pair<char, double>> a_p;

	BOOST_ASSERT(a_b.max_size() >= sizeof(decltype(a_b)::value_type));
	BOOST_ASSERT(a_c.max_size() >= sizeof(decltype(a_c)::value_type));
	BOOST_ASSERT(a_s.max_size() >= sizeof(decltype(a_s)::value_type));
	BOOST_ASSERT(a_i.max_size() >= sizeof(decltype(a_i)::value_type));
	BOOST_ASSERT(a_l.max_size() >= sizeof(decltype(a_l)::value_type));
	BOOST_ASSERT(a_f.max_size() >= sizeof(decltype(a_f)::value_type));
	BOOST_ASSERT(a_d.max_size() >= sizeof(decltype(a_d)::value_type));
	BOOST_ASSERT(a_p.max_size() >= sizeof(decltype(a_p)::value_type));
}

BOOST_AUTO_TEST_CASE(base_alloc_allocate_deallocate)
{
	eagine::base::allocator<bool> a_b;
	eagine::base::allocator<char> a_c;
	eagine::base::allocator<short> a_s;
	eagine::base::allocator<int> a_i;
	eagine::base::allocator<long> a_l;
	eagine::base::allocator<float> a_f;
	eagine::base::allocator<double> a_d;
	eagine::base::allocator<std::pair<char, double>> a_p;

	unsigned m;

	for(unsigned i=0; i<1000; ++i)
	{
		m = 1 + std::rand() % 10;
		a_b.deallocate(a_b.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_c.deallocate(a_c.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_s.deallocate(a_s.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_i.deallocate(a_i.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_l.deallocate(a_l.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_d.deallocate(a_d.allocate(m*m), m*m);

		m = 1 + std::rand() % 10;
		a_p.deallocate(a_p.allocate(m*m), m*m);
	}
}

BOOST_AUTO_TEST_CASE(base_alloc_vector_1)
{
	eagine::base::allocator<int> a;

	const unsigned n = 1000;

	std::vector<int*> v;
	v.reserve(n);

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(new (a.allocate(1)) int(int(i)));
	}

	for(unsigned i=n; i!=0; --i)
	{
		BOOST_ASSERT(*v.back() == int(i-1));
		a.deallocate(v.back(), 1);
		v.pop_back();
	}

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(new (a.allocate(1)) int(int(i)));
	}

	for(unsigned i=n; i!=0; --i)
	{
		a.deallocate(v[i], 1);
	}
	v.clear();
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

	const unsigned n = 1000+std::rand() % 1000;
	const unsigned m = 50+std::rand() % 30;

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(std::vector<int>());
		for(unsigned j=0; j!=m; ++j)
		{
			v.back().push_back(int(j));
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

BOOST_AUTO_TEST_CASE(base_alloc_vector_4)
{
	eagine::base::allocator<void> a;

	std::vector<
		std::vector<int, eagine::base::allocator<int>>,
		eagine::base::allocator<std::vector<int, eagine::base::allocator<int>>>
	> v(a);

	const unsigned n = 1000+std::rand() % 1000;
	const unsigned m = 50+std::rand() % 30;

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(std::vector<int, eagine::base::allocator<int>>(a));
		for(unsigned j=0; j!=m; ++j)
		{
			v.back().push_back(int(j));
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

BOOST_AUTO_TEST_CASE(base_alloc_vector_5)
{
	eagine::base::allocator<void> a;

	const unsigned n = 1000+std::rand()%1000;

	std::vector<std::shared_ptr<std::pair<unsigned, unsigned>>> v;

	for(unsigned i=0; i!=n; ++i)
	{
		v.push_back(std::allocate_shared<std::pair<unsigned, unsigned>>(a, i, i+1));
	}

	for(unsigned i=n; i!=0; --i)
	{
		BOOST_ASSERT(v.back()->second == i);
		v.pop_back();
	}
}

BOOST_AUTO_TEST_CASE(base_alloc_map_1)
{
	eagine::base::allocator<void> a;
	eagine::base::allocator<
		std::pair<
			std::shared_ptr<std::pair<char, long>>,
			std::vector<int, eagine::base::allocator<int>>
		>
	> ma(a);
	std::less<std::shared_ptr<std::pair<char, long>>> l;

	std::map<
		std::shared_ptr<std::pair<char, long>>,
		std::vector<int, eagine::base::allocator<int>>,
		std::less<std::shared_ptr<std::pair<char, long>>>,
		eagine::base::allocator<
			std::pair<
				std::shared_ptr<std::pair<char, long>>,
				std::vector<int, eagine::base::allocator<int>>
			>
		>
	> m(l, ma);

	const unsigned n = 1000+std::rand()%1000;

	for(unsigned i=0; i<n; ++i)
	{
		std::vector<int, eagine::base::allocator<int>> v(a);

		const unsigned k = 50+std::rand()%30;

		if(k % 3 == 0)
		{
			v.reserve(k);
		}
		else if(k % 4 == 0)
		{
			v.reserve(k / 2);
		}

		for(unsigned j=0; j<k; ++j)
		{
			v.push_back(std::rand());
		}

		m[std::allocate_shared<std::pair<char, long>>(
			a,
			'A'+std::rand()%10,
			std::rand())
		] = std::move(v);
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
