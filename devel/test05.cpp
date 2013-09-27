/**
 *  .file devel/test05.cpp
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
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

		string s = "Blable";
		const_string_ref sr = s;

		std::cout.write(sr.data(), sr.size()) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
