/**
 *  .file devel/test07.cpp
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
#include <eagine/dyli/loader.hpp>
//------------------

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::dyli;

		dyli::loader ldr;
		dyli::library lib = ldr.load("libm.so");

		dyli::weak_lib wlib = lib;
		dyli::function<double(double)> sin;

		if(dyli::library lib2 = wlib)
		{
			sin = lib2.function<double(double)>("sin");

			dyli::weak_func<double(double)> wsin = sin;

			std::cout << wsin.require()(1) << std::endl;
			std::cout << wsin(2) << std::endl;
		}

		lib.release();

		std::cout << sin(3) << std::endl;

		dyli::weak_func<double(double)> wsin = sin;
		
		std::cout << wsin(4) << std::endl;

		sin.release();

		std::cout << wsin(5) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
