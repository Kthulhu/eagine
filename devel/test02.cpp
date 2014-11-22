/**
 *  .file devel/test02.cpp
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <fstream>
//------------------
#include <eagine/base/error.hpp>
#include <eagine/base/path.hpp>

namespace eagine {
namespace base {

} // namespace base
} // namespace eagine

int main(void)
{
	using namespace eagine;

	try
	{
		using namespace eagine::base;

		path p = pa::th/"eagine"/"base"/"path";
		std::cout << p << std::endl;

		p.front() = "eagine";
		p.push_back(par::ent);
		std::cout << p << std::endl;

		p.back() = "string";
		std::cout << p << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
