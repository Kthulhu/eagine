/**
 *  .file devel/test12.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
//------------------
#include <eagine/base/error.hpp>
#include <eagine/base/file_mapping.hpp>
#include <eagine/base/file_content.hpp>
#include <eagine/base/indexed_array.hpp>

namespace eagine {
namespace base {

} // namespace base
} // namespace eagine

int main(int argc, const char* argv[])
{
	using namespace eagine;

	try
	{
		using namespace eagine::base;

		cstrref fn = cstrref(argv[0]);

		file_mapping fm(fn, access_read_only);

		mapped_file_region mr(fm, 1, 3);

		std::cout << mr.size() << std::endl;

		std::cout.write((const char*)mr.address(), mr.size()) << std::endl;

		file_content fc(fn);

		const_byte_range cbr = fc.block();

		std::cout << cbr.size() << std::endl;

		file_content vsd("varstr.dat");
		file_content vsi("varstr.idx");

		indexed_array<cvarstr> va(vsd.block(), vsi.block());

		std::cout << va.size() << std::endl;

		for(auto& str : va)
		{
			std::cout.write(str.data(), str.size()) << std::endl;
		}

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
