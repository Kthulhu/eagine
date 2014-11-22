/**
 *  .file devel/test27.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
//------------------
#include <eagine/base/chunk_alloc.hpp>
#include <eagine/base/align_alloc.hpp>
#include <eagine/base/expand_alloc.hpp>
#include <eagine/base/buffer_alloc.hpp>
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

namespace eagine {
namespace base {

} // namespace base
} // namespace eagine

int main(int argc, const char* argv [])
{
	using namespace eagine::base;
	using namespace eagine::meta;
	using namespace eagine::dbg;

	memory_buffer buf1(8*1024);
	memory_block blk1 = buf1;
	std::memset(blk1.addr(), 0, blk1.size());

	{
	concrete_byte_allocator<byte_allocator_with_fallback> cba((
		stack_byte_allocator<>(blk1)
	));

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
			multi_align_byte_allocator<integer_sequence<std::size_t, alignof(float)>>(
				expanding_byte_allocator<>([](void){
					//return buffer_backed_byte_allocator<stack_aligned_byte_allocator>(6*1024, alignof(float));
					return buffer_backed_byte_allocator<chunk_byte_allocator>(6*1024);
				})
			)
		)
	));

	std::cout << "bla" << std::endl;

	std::vector<float, allocator<float>> v(a);
	for(int i=0; i<1024; ++i)
	{
		v.push_back(float(i));
	}

	std::cout << v.size() << std::endl;
	}


	return 0;
}
