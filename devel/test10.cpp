/**
 *  .file devel/test10.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <iostream>
#include <cstdlib>
#include <eagine/base/flat_map.hpp>
//------------------
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/guid.hpp>
#include <eagine/base/string.hpp>
//------------------
#include <eagine/base/vector.hpp>
#include <eagine/base/alloc.hpp>
#include <cstddef>
#include <memory>
#include <cassert>
#include <algorithm>

namespace EAGine {
namespace base {


} // namespace base
} // namespace EAGine

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::base;

		typedef flat_map<guid, std::size_t> vm_t;
		vm_t vm;

		guid g1, g2, g3, g4;

		vm.insert(g1, 1);
		vm.insert(g2, 2);
		vm.insert(g3, 3);
		vm.insert(g4, 4);

		assert(vm.get(g1, 0) == 1);
		assert(vm.get(g2, 0) == 2);
		assert(vm.get(g3, 0) == 3);
		assert(vm.get(g4, 0) == 4);
		assert(vm.size() == 4);

		vm.erase(g1);

		assert(vm.get(g1, 0) == 0);
		assert(vm.get(g2, 0) == 2);
		assert(vm.get(g3, 0) == 3);
		assert(vm.get(g4, 0) == 4);
		assert(vm.size() == 3);

		vm.erase(g2);

		assert(vm.get(g1, 0) == 0);
		assert(vm.get(g2, 0) == 0);
		assert(vm.get(g3, 0) == 3);
		assert(vm.get(g4, 0) == 4);
		assert(vm.size() == 2);

		vm.erase(g3);

		assert(vm.get(g1, 0) == 0);
		assert(vm.get(g2, 0) == 0);
		assert(vm.get(g3, 0) == 0);
		assert(vm.get(g4, 0) == 4);
		assert(vm.size() == 1);

		vm.erase(g4);

		assert(vm.get(g1, 0) == 0);
		assert(vm.get(g2, 0) == 0);
		assert(vm.get(g3, 0) == 0);
		assert(vm.get(g4, 0) == 0);
		assert(vm.size() == 0);

		std::cout << "Done" << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
