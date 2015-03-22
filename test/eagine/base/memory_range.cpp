/**
 *  .file test/eagine/base/memory_range.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_memory_range
#include <boost/test/unit_test.hpp>

#include <eagine/base/memory_range.hpp>

BOOST_AUTO_TEST_SUITE(base_memory_range)

template <typename MemoryRange>
void test_base_memory_range_construction_1_T()
{
	MemoryRange mr;

	BOOST_ASSERT(mr.addr() == nullptr);
	BOOST_ASSERT(mr.size() == 0);
	BOOST_ASSERT(mr.empty());

	typename MemoryRange::iterator pb = mr.begin();
	typename MemoryRange::iterator pe = mr.end();
	typename MemoryRange::iterator po = mr.offs(0);
}

template <typename T>
void test_base_memory_range_construction_1()
{
	test_base_memory_range_construction_1_T<
		::eagine::base::typed_memory_range<T>
	>();
	test_base_memory_range_construction_1_T<
		::eagine::base::typed_memory_range<const T>
	>();
}

BOOST_AUTO_TEST_CASE(base_memory_range_construction_1)
{
	test_base_memory_range_construction_1<bool>();
	test_base_memory_range_construction_1<char>();
	test_base_memory_range_construction_1<int>();
	test_base_memory_range_construction_1<float>();
	test_base_memory_range_construction_1<double>();
}

template <typename MemoryRange, typename T>
void test_base_memory_range_construction_2_T(std::size_t n)
{
	T b[n];

	MemoryRange mr(b, b+n);

	BOOST_ASSERT(mr.addr() == (void*)b);
	BOOST_ASSERT(mr.size() == n);
	BOOST_ASSERT(mr.empty() == (n == 0));

	mr.begin();
	mr.end();

	for(std::size_t i = 0; i<n; ++i)
	{
		mr.offs(i);
	}
}

template <typename T>
void test_base_memory_range_construction_2(std::size_t n)
{
	test_base_memory_range_construction_2_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_construction_2_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_construction_2)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_range_construction_2<bool>(i);
		test_base_memory_range_construction_2<char>(i);
		test_base_memory_range_construction_2<int>(i);
		test_base_memory_range_construction_2<float>(i);
		test_base_memory_range_construction_2<double>(i);
	}
}

template <typename MemoryRange, typename T>
void test_base_memory_range_construction_3_T(std::size_t n)
{
	T b[n];

	MemoryRange mr(b, n);

	BOOST_ASSERT(mr.addr() == (void*)b);
	BOOST_ASSERT(mr.size() == n);
	BOOST_ASSERT(mr.empty() == (n == 0));

	mr.begin();
	mr.end();

	for(std::size_t i = 0; i<n; ++i)
	{
		mr.offs(i);
	}
}

template <typename T>
void test_base_memory_range_construction_3(std::size_t n)
{
	test_base_memory_range_construction_3_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_construction_3_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_construction_3)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_range_construction_3<bool>(i);
		test_base_memory_range_construction_3<char>(i);
		test_base_memory_range_construction_3<int>(i);
		test_base_memory_range_construction_3<float>(i);
		test_base_memory_range_construction_3<double>(i);
	}
}

template <typename MemoryRange>
void test_base_memory_range_begin_end_offs_1_T()
{
	MemoryRange mr;

	BOOST_ASSERT(mr.begin() == mr.end());
	BOOST_ASSERT(mr.offs(0) == mr.begin());
	BOOST_ASSERT(mr.offs(0) == mr.end());
}

template <typename T>
void test_base_memory_range_begin_end_offs_1(void)
{
	test_base_memory_range_begin_end_offs_1_T<
		::eagine::base::typed_memory_range<T>
	>();
	test_base_memory_range_begin_end_offs_1_T<
		::eagine::base::typed_memory_range<const T>
	>();
}

BOOST_AUTO_TEST_CASE(base_memory_range_begin_end_offs_1)
{
	test_base_memory_range_begin_end_offs_1<bool>();
	test_base_memory_range_begin_end_offs_1<char>();
	test_base_memory_range_begin_end_offs_1<long>();
	test_base_memory_range_begin_end_offs_1<float>();
	test_base_memory_range_begin_end_offs_1<double>();
}

template <typename MemoryRange, typename T>
void test_base_memory_range_begin_end_offs_2_T(std::size_t n)
{
	T b[n];

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = T(i);
	}

	MemoryRange mr(b, n);

	BOOST_ASSERT((mr.begin() == mr.end()) == (n == 0));
	BOOST_ASSERT((mr.begin() != mr.end()) == (n != 0));

	BOOST_ASSERT(*mr.begin() == b[0]);

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(*mr.offs(i) == b[i]);
	}
}

template <typename T>
void test_base_memory_range_begin_end_offs_2(std::size_t n)
{
	test_base_memory_range_begin_end_offs_2_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_begin_end_offs_2_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_begin_end_offs_2)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_range_begin_end_offs_2<bool>(i);
		test_base_memory_range_begin_end_offs_2<char>(i);
		test_base_memory_range_begin_end_offs_2<long>(i);
		test_base_memory_range_begin_end_offs_2<float>(i);
		test_base_memory_range_begin_end_offs_2<double>(i);
	}
}


template <typename MemoryRange, typename T>
void test_base_memory_range_element_T(std::size_t n)
{
	T b[n];

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = T(i);
	}

	MemoryRange mr(b, n);

	BOOST_ASSERT((mr.begin() == mr.end()) == (n == 0));
	BOOST_ASSERT((mr.begin() != mr.end()) == (n != 0));

	BOOST_ASSERT(*mr.begin() == b[0]);

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(mr[i] == b[i]);
	}
}

template <typename T>
void test_base_memory_range_element(std::size_t n)
{
	test_base_memory_range_element_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_element_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_element)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_range_element<bool>(i);
		test_base_memory_range_element<char>(i);
		test_base_memory_range_element<long>(i);
		test_base_memory_range_element<float>(i);
		test_base_memory_range_element<double>(i);
	}
}

template <typename MemoryRange, typename T>
void test_base_memory_range_slice_1_T(std::size_t n)
{
	T b[n];

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = T(i);
	}

	MemoryRange mr(b, n);

	for(std::size_t i = 0; i<n; ++i)
	{
		for(std::size_t j = 0; j<n-i; ++j)
		{
			MemoryRange mr2 = mr.slice(i, j);

			for(std::size_t k = 0; k<j; ++k)
			{
				BOOST_ASSERT(mr2[k] == mr[i+k]);
			}
		}
	}
}

template <typename T>
void test_base_memory_range_slice_1(std::size_t n)
{
	test_base_memory_range_slice_1_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_slice_1_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_slice_1)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_range_slice_1<bool>(i);
		test_base_memory_range_slice_1<char>(i);
		test_base_memory_range_slice_1<long>(i);
		test_base_memory_range_slice_1<float>(i);
		test_base_memory_range_slice_1<double>(i);
	}
}

template <typename MemoryRange, typename T>
void test_base_memory_range_slice_2_T(std::size_t n)
{
	T b[n];

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = T(i);
	}

	MemoryRange mr(b, n);

	for(std::size_t i = 0; i<n; ++i)
	{
		MemoryRange mr2 = mr.slice(i);

		for(std::size_t k = 0; k<mr2.size(); ++k)
		{
			BOOST_ASSERT(mr2[k] == mr[i+k]);
		}
	}
}

template <typename T>
void test_base_memory_range_slice_2(std::size_t n)
{
	test_base_memory_range_slice_2_T<
		::eagine::base::typed_memory_range<T>, T
	>(n);
	test_base_memory_range_slice_2_T<
		::eagine::base::typed_memory_range<const T>, T
	>(n);
}

BOOST_AUTO_TEST_CASE(base_memory_range_slice_2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_range_slice_2<bool>(i);
		test_base_memory_range_slice_2<char>(i);
		test_base_memory_range_slice_2<long>(i);
		test_base_memory_range_slice_2<float>(i);
		test_base_memory_range_slice_2<double>(i);
	}
}

template <typename T>
void test_base_memory_range_compare(void)
{
	static const std::size_t n = 512;
	T b[n];

	for(unsigned k=0; k<1000; ++k)
	{
		std::size_t i1 = std::rand() % n;
		std::size_t i2 = std::rand() % n;
		std::size_t l1 = std::rand() % (n-i1);
		std::size_t l2 = std::rand() % (n-i2);

		if(std::rand() % 10 == 0)
		{
			i2 = i1;
			l2 = l1;
		}

		::eagine::base::typed_memory_range<const T> mr1(b+i1, l1);
		::eagine::base::typed_memory_range<const T> mr2(b+i2, l2);

		BOOST_ASSERT((mr1 == mr2) == ((i1==i2) && (l1==l2)));
		BOOST_ASSERT((mr1 != mr2) == ((i1!=i2) || (l1!=l2)));
		BOOST_ASSERT((mr1 <  mr2) == ((i1<i2) || ((i1==i2)&&(l1<l2))));
	}
}

BOOST_AUTO_TEST_CASE(base_memory_range_compare)
{
	test_base_memory_range_compare<bool>();
	test_base_memory_range_compare<char>();
	test_base_memory_range_compare<long>();
	test_base_memory_range_compare<float>();
	test_base_memory_range_compare<double>();
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
