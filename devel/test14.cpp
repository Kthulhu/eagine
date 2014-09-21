/**
 *  .file devel/test14.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/ecs/package_immutable.hpp>
#include <eagine/ecs/manager.hpp>
//------------------
#include <eagine/base/guid.hpp>
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/file_content.hpp>
//------------------
#include <iostream>

struct some_str
 : EAGine::base::cvarstr
 , EAGine::ecs::component<some_str>
{ };

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::ecs;

		manager<base::guid> m;

		base::file_content fc("ecs_str.bin");

		immutable_component_package<base::guid, some_str>
			strings(fc.block());

		strings.register_with(m);

		auto f = [](const base::guid& e, const some_str& s) -> void
		{
			base::cstrref sr = s;
			std::cout << "|" << e << "|" << sr << "|" << std::endl;
		};

		auto fa = m.wrap_func_e_c<const some_str&>(f);

		m.for_each(fa);
		std::cout << std::endl;

		strings.unregister_from(m);
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
