/**
 *  .file devel/test09.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <cstdlib>
//------------------
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/string.hpp>

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		lim_string<6> s = cstrref("Blablebla");
		const_string_ref sr = s;

		std::cout.write(sr.data(), sr.size()) << std::endl;
		std::cout << sr.data() << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
