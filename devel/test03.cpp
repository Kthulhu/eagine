/**
 *  .file devel/test03.cpp
 *
 *  Copyright 2012-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <fstream>
//------------------
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/format.hpp>
#include <eagine/base/locale.hpp>

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
		std::cout.imbue(std::locale("en_US.UTF-8"));
		std::cout << format(translate("Blable {1}")) % 12345 << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
