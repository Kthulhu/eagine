/**
 *  .file devel/test13.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
//------------------
#include <eagine/base/error.hpp>
#include <eagine/base/string.hpp>
#include <eagine/base/offset_ptr.hpp>
#include <cassert>

namespace EAGine {
namespace base {

} // namespace base
} // namespace EAGine

int main(int argc, const char* argv[])
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		struct test_data_t
		{
			const int32_t p_d;
			const int32_t p_i;
			const int32_t p_s;
			const int32_t p_c;

			double d;
			int i;
			uint32_t ssize;
			const char sdata[7];
			char c;
			
		} const test_data = {
			offsetof(test_data_t, d)-offsetof(test_data_t, p_d),
			offsetof(test_data_t, i)-offsetof(test_data_t, p_i),
			offsetof(test_data_t, ssize)-offsetof(test_data_t, p_s),
			offsetof(test_data_t, c)-offsetof(test_data_t, p_c),

			123.456,
			7890,
			6U,
			"EAGine",
			'X'
		};

		struct test_index_t
		{
			offset_ptr<double> p_d;
			offset_ptr<int> p_i;
			offset_ptr<cvarstr> p_s;
			offset_ptr<char> p_c;
		} const & test_index =
			*(const test_index_t*)(const void*)&test_data;

		assert(test_index.p_d);
		assert(test_index.p_d != nullptr);
		assert(test_index.p_d == &test_data.d);

		std::cout << *test_index.p_d << std::endl;
		std::cout << *test_index.p_i << std::endl;
		std::cout << *test_index.p_c << std::endl;
		std::cout.write(
			test_index.p_s->data(),
			test_index.p_s->size()
		) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
