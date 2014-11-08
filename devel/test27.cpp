/**
 *  .file devel/test27.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//------------------
#include <eagine/base/logging_alloc.hpp>
#include <eagine/base/fallback_alloc.hpp>
#include <eagine/base/stack_alloc.hpp>
#include <eagine/base/alloc.hpp>
#include <eagine/base/memory_buffer.hpp>
#include <eagine/dbg/hexdump.hpp>
//------------------
#include <vector>
#include <iostream>
#include <exception>
#include <cstring>

namespace EAGine {
namespace base {

} // namespace base
} // namespace EAGine

int main(int argc, const char* argv [])
{
	using namespace EAGine::base;
	using namespace EAGine::dbg;

	memory_buffer buf1(8*1024);
	memory_block blk1 = buf1;
	std::memset(blk1.addr(), 0, blk1.size());

	{
	concrete_byte_allocator<byte_allocator_with_fallback> cba(
		stack_byte_allocator<>(blk1),
		default_byte_allocator()
	);

	allocator<void> a((cba.reference()));

	typedef std::basic_string<char, std::char_traits<char>, allocator<char>> s_t;

	std::vector<s_t, allocator<s_t>> v(a);

	for(int i=0; i<256; ++i)
	{
		v.push_back(s_t(argv[i%argc], a));
	}

	//std::cout << hexdump(blk1) << std::endl;

	std::cout << cba.get().required_fallback_size() << std::endl;
	std::cout << v.size() << std::endl;
	}

	{
	allocator<void> a((
		logging_byte_allocator<>(
			stack_aligned_byte_allocator<>(blk1, alignof(float))
		)
	));

	std::vector<float, allocator<float>> v(a);
	for(int i=0; i<128; ++i)
	{
		v.push_back(float(i));
	}

	std::cout << v.size() << std::endl;
	}


	return 0;
}
