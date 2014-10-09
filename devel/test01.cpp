/**
 *  .file devel/test01.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/function.hpp>
#include <eagine/base/thread.hpp>
#include <eagine/base/future.hpp>
#include <eagine/base/error.hpp>
#include <eagine/base/type.hpp>
#include <eagine/base/string.hpp>
#include <eagine/base/vector.hpp>
#include <eagine/base/io.hpp>

#include <iostream>
#include <fstream>

namespace EAGine {
} // namespace EAGine

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		future<vector<byte>> b = async(load_file_data, cstrref("test01.cpp"));

		std::cout << b.get().size() << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
		base::exception* pe = &error;
		while(true)
		{
			try
			{
				rethrow_if_nested(*pe);
				break;
			}
			catch(base::exception& ne)
			{
				std::cerr << ne.what() << std::endl;
				pe = &ne;
			}
			catch(...){ break; }
		}
	}
	return 1;
}
