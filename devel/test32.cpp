/**
 *  .file devel/test32.cpp
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <cstdlib>
//------------------
#include <eagine/base/error.hpp>
//------------------
#include <eagine/math/tvec.hpp>
#include <eagine/math/vector_swizzles.hpp>
#include <eagine/math/io.hpp>

namespace eagine {
namespace math {

} // namespace math
} // namespace eagine

int main(void)
{
	using namespace eagine;

	try
	{
		using namespace eagine::math;

		vector_swizzles<tvec<float,4>> v(1,2,3,4);

		std::cout << v << std::endl;
		std::cout << v.xyz() << std::endl;
		std::cout << v.wOwO(5) << std::endl;
		std::cout << v.z() << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
