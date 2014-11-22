/**
 *  .file devel/test04.cpp
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
#include <eagine/base/optional.hpp>

namespace eagine {
namespace base {

optional<float> my_sqrt(float f)
{
	optional<float> result;
	if(f >= 0.0) result = std::sqrt(f);
	return result;
}

} // namespace base
} // namespace eagine

int main(void)
{
	using namespace eagine;

	try
	{
		using namespace eagine::base;

		std::srand(std::time(nullptr));

		float x = std::rand() % 10 - 5;
		std::cout << "sqrt(" << x << ") = ";


		optional<float> y = my_sqrt(x);
		if(y) std::cout << *y;
		else std::cout << "N/A";

		std::cout << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
