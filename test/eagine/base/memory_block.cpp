/**
 *  .file test/eagine/base/memory_block.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_memory_block
#include <boost/test/unit_test.hpp>

#include <eagine/base/memory_block.hpp>
#include <vector>

BOOST_AUTO_TEST_SUITE(base_memory_block)

template <typename MemoryBlock>
void test_base_memory_block_construction_1()
{
	MemoryBlock mb;

	BOOST_ASSERT(mb.addr() == nullptr);
	BOOST_ASSERT(mb.size() == 0);
	BOOST_ASSERT(mb.empty());

	typename MemoryBlock::iterator pb = mb.begin();
	typename MemoryBlock::iterator pe = mb.end();
	typename MemoryBlock::iterator po = mb.offs(0);

	(void)pb; (void)pe; (void)po;
}

BOOST_AUTO_TEST_CASE(base_memory_block_construction_1)
{
	test_base_memory_block_construction_1<
		::eagine::base::memory_block
	>();
	test_base_memory_block_construction_1<
		::eagine::base::const_memory_block
	>();
}

template <typename MemoryBlock>
void test_base_memory_block_construction_2(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	MemoryBlock mb(b, b+n);

	BOOST_ASSERT(mb.addr() == b);
	BOOST_ASSERT(mb.size() == n);
	BOOST_ASSERT(mb.empty() == (n == 0));

	mb.begin();
	mb.end();

	for(std::size_t i = 0; i<n; ++i)
	{
		mb.offs(i);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_construction_2)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_block_construction_2<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_construction_2<
			::eagine::base::const_memory_block
		>(i);
	}
}

template <typename MemoryBlock>
void test_base_memory_block_construction_3(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	MemoryBlock mb(b, n);

	BOOST_ASSERT(mb.addr() == b);
	BOOST_ASSERT(mb.size() == n);
	BOOST_ASSERT(mb.empty() == (n == 0));

	mb.begin();
	mb.end();

	for(std::size_t i = 0; i<n; ++i)
	{
		mb.offs(i);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_construction_3)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_block_construction_3<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_construction_3<
			::eagine::base::const_memory_block
		>(i);
	}
}

template <typename MemoryBlock>
void test_base_memory_block_begin_end_offs_1()
{
	MemoryBlock mb;

	BOOST_ASSERT(mb.begin() == mb.end());
	BOOST_ASSERT(mb.offs(0) == mb.begin());
	BOOST_ASSERT(mb.offs(0) == mb.end());
}

BOOST_AUTO_TEST_CASE(base_memory_block_begin_end_offs_1)
{
	test_base_memory_block_begin_end_offs_1<
		::eagine::base::memory_block
	>();
	test_base_memory_block_begin_end_offs_1<
		::eagine::base::const_memory_block
	>();
}

template <typename MemoryBlock>
void test_base_memory_block_begin_end_offs_2(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	for(unsigned i=0; i<n; ++i)
	{
		v[i] = eagine::base::byte(i);
	}

	MemoryBlock mb(b, b+n);

	BOOST_ASSERT((mb.begin() == mb.end()) == (n == 0));
	BOOST_ASSERT((mb.begin() != mb.end()) == (n != 0));

	if(n > 0)
	{
		BOOST_ASSERT(*mb.begin() == b[0]);
	}

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(*mb.offs(i) == b[i]);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_begin_end_offs_2)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_block_begin_end_offs_2<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_begin_end_offs_2<
			::eagine::base::const_memory_block
		>(i);
	}
}

template <typename MemoryBlock>
void test_base_memory_block_element(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = eagine::base::byte(i);
	}

	MemoryBlock mb(b, b+n);

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(mb[i] == b[i]);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_element)
{
	for(unsigned i=0; i<500; ++i)
	{
		test_base_memory_block_element<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_element<
			::eagine::base::const_memory_block
		>(i);
	}
}

template <typename MemoryBlock>
void test_base_memory_block_slice_1(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = eagine::base::byte(i);
	}

	MemoryBlock mb(b, n);

	for(std::size_t i = 0; i<n; ++i)
	{
		for(std::size_t j = 0; j<n-i; ++j)
		{
			MemoryBlock mb2 = mb.slice(i, j);

			for(std::size_t k = 0; k<j; ++k)
			{
				BOOST_ASSERT(mb2[k] == mb[i+k]);
			}
		}
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_slice_1)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_block_slice_1<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_slice_1<
			::eagine::base::const_memory_block
		>(i);
	}
}

template <typename MemoryBlock>
void test_base_memory_block_slice_2(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = eagine::base::byte(i);
	}

	MemoryBlock mb(b, n);

	for(std::size_t i = 0; i<n; ++i)
	{
		MemoryBlock mb2 = mb.slice(i);

		for(std::size_t k = 0; k<mb2.size(); ++k)
		{
			BOOST_ASSERT(mb2[k] == mb[i+k]);
		}
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_slice_2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_block_slice_2<
			::eagine::base::memory_block
		>(i);
		test_base_memory_block_slice_2<
			::eagine::base::const_memory_block
		>(i);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_block_compare)
{
	static const std::size_t n = 512;
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	for(unsigned k=0; k<1000; ++k)
	{
		std::size_t i1 = std::size_t(std::rand()) % n;
		std::size_t i2 = std::size_t(std::rand()) % n;
		std::size_t l1 = std::size_t(std::rand()) % (n-i1);
		std::size_t l2 = std::size_t(std::rand()) % (n-i2);

		if(std::rand() % 10 == 0)
		{
			i2 = i1;
			l2 = l1;
		}

		::eagine::base::const_memory_block mb1(b+i1, l1);
		::eagine::base::const_memory_block mb2(b+i2, l2);

		BOOST_ASSERT((mb1 == mb2) == ((i1==i2) && (l1==l2)));
		BOOST_ASSERT((mb1 != mb2) == ((i1!=i2) || (l1!=l2)));
		BOOST_ASSERT((mb1 <  mb2) == ((i1<i2) || ((i1==i2)&&(l1<l2))));
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
