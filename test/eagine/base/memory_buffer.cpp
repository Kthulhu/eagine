/**
 *  .file test/eagine/base/memory_buffer.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE eagine_base_memory_buffer
#include <boost/test/unit_test.hpp>

#include <eagine/base/memory_buffer.hpp>

BOOST_AUTO_TEST_SUITE(base_memory_buffer)

template <typename MemoryBuffer>
void test_base_memory_buffer_construction_1()
{
	MemoryBuffer mb;

	BOOST_ASSERT(mb.addr() == nullptr);
	BOOST_ASSERT(mb.size() == 0);
	BOOST_ASSERT(mb.empty());

	typename MemoryBuffer::iterator pb = mb.begin();
	typename MemoryBuffer::iterator pe = mb.end();
	typename MemoryBuffer::iterator po = mb.offs(0);

	(void)pb; (void)pe; (void)po;
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_construction_1)
{
	test_base_memory_buffer_construction_1<
		::eagine::base::memory_buffer
	>();
}

template <typename MemoryBuffer>
void test_base_memory_buffer_construction_2(std::size_t n)
{
	MemoryBuffer mb(n);

	BOOST_ASSERT((mb.addr() != nullptr) || (n == 0));
	BOOST_ASSERT(mb.size() == n);
	BOOST_ASSERT(mb.empty() == (n == 0));

	mb.begin();
	mb.end();

	for(std::size_t i = 0; i<n; ++i)
	{
		mb.offs(i);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_construction_2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_construction_2<
			::eagine::base::memory_buffer
		>(i);
	}
}

template <typename MemoryBuffer>
void test_base_memory_buffer_resize(std::size_t n)
{
	MemoryBuffer mb;

	for(unsigned i=0; i<n; ++i)
	{
		mb.resize(n);

		BOOST_ASSERT((mb.addr() != nullptr) || (n == 0));
		BOOST_ASSERT(mb.size() == n);
		BOOST_ASSERT(mb.empty() == (n == 0));
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_resize)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_resize<
			::eagine::base::memory_buffer
		>(i);
	}
}

template <typename MemoryBuffer>
void test_base_memory_buffer_begin_end_offs_1()
{
	MemoryBuffer mb;

	BOOST_ASSERT(mb.begin() == mb.end());
	BOOST_ASSERT(mb.offs(0) == mb.begin());
	BOOST_ASSERT(mb.offs(0) == mb.end());
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_begin_end_offs_1)
{
	test_base_memory_buffer_begin_end_offs_1<
		::eagine::base::memory_buffer
	>();
}

template <typename MemoryBuffer>
void test_base_memory_buffer_begin_end_offs_2(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();

	MemoryBuffer mb(n);

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = eagine::base::byte(i);
		mb[i] = b[i];
	}

	BOOST_ASSERT((mb.begin() == mb.end()) == (n == 0));
	BOOST_ASSERT((mb.begin() != mb.end()) == (n != 0));

	BOOST_ASSERT((n == 0) || (*mb.begin() == b[0]));

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(*mb.offs(i) == b[i]);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_begin_end_offs_2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_begin_end_offs_2<
			::eagine::base::memory_buffer
		>(i);
	}
}

template <typename MemoryBuffer>
void test_base_memory_buffer_element(std::size_t n)
{
	std::vector<eagine::base::byte> v(n);
	eagine::base::byte* b=v.data();
	MemoryBuffer mb(n);

	for(unsigned i=0; i<n; ++i)
	{
		b[i] = eagine::base::byte(i);
		mb[i] = b[i];
	}

	for(std::size_t i = 0; i<n; ++i)
	{
		BOOST_ASSERT(mb[i] == b[i]);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_element)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_element<
			::eagine::base::memory_buffer
		>(i);
	}
}

template <typename MemoryBuffer>
void test_base_memory_buffer_slice_1(std::size_t n)
{
	MemoryBuffer mb(n);

	for(std::size_t i = 0; i<n; ++i)
	{
		for(std::size_t j = 0; j<n-i; ++j)
		{
			auto mb2 = mb.slice(i, j);

			BOOST_ASSERT(mb2.begin() == mb.offs(i));
			BOOST_ASSERT(mb2.size() == j);

		}
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_slice_1)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_slice_1<
			::eagine::base::memory_buffer
		>(i);
	}
}

template <typename MemoryBuffer>
void test_base_memory_buffer_slice_2(std::size_t n)
{
	MemoryBuffer mb(n);

	for(std::size_t i = 0; i<n; ++i)
	{
		auto mb2 = mb.slice(i);

		BOOST_ASSERT(mb2.begin() == mb.offs(i));
		BOOST_ASSERT(mb2.size() == n-i);
	}
}

BOOST_AUTO_TEST_CASE(base_memory_buffer_slice_2)
{
	for(unsigned i=0; i<100; ++i)
	{
		test_base_memory_buffer_slice_2<
			::eagine::base::memory_buffer
		>(i);
	}
}

// TODO

BOOST_AUTO_TEST_SUITE_END()
