/**
 *  .file devel/test06.cpp
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
#include <eagine/base/dyn_lib.hpp>
#include <eagine/base/dl_export.hpp>
#include <eagine/base/function.hpp>

EAGINE_DL_PUBLIC(int) add(int a, int b)
{
	return a+b;
}

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		std::cout << "begin" << std::endl;

		executable_module self;
		function<int(int, int)> padd = self.function<int(int, int)>("add");
		std::cout << padd(12,34) << std::endl;

		dynamic_library libm("libm.so");
		function<float(float,float)> ppowf = libm.function<float(float,float)>("powf");
		std::cout << ppowf(3.0, 4.0) << std::endl;

		std::cout << "done" << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
