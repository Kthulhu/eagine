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
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/sim_clock.hpp>

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		sim_clock c;
		c.update(1.0);
		std::cout << c.time() << std::endl;
		c.update(2.0);
		std::cout << c.time() << std::endl;
		c.pace(0.5);
		std::cout << c.time() << std::endl;
		c.advance(0.5);
		std::cout << c.time() << std::endl;
		c.advance(0.5);
		std::cout << c.time() << std::endl;
		c.pace(2.0);
		c.advance(0.25);
		std::cout << c.time() << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
