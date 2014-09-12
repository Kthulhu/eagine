/**
 *  .file devel/test11.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/ecs/eck_map_basic.hpp>
#include <eagine/ecs/manager.hpp>
//------------------
#include <eagine/base/guid.hpp>
#include <eagine/base/error.hpp>
//------------------
#include <eagine/base/flat_map.hpp>

namespace EAGine {
namespace ecs {

} // namespace ecs
} // namespace EAGine

struct cmp_1
{
	int i;
};

int main(void)
{
	using namespace EAGine;

	try
	{
		using namespace EAGine::ecs;

		manager<base::guid> m;

/*
		m.register_component_type<cmp_1>(
			base::make_shared<basic_entity_component_map<base::guid>>(),
			base::make_shared<>()
		);
*/

		auto e1 = m.make_entity();

		base::make_shared<basic_entity_component_map<base::guid>>()->get(e1, 0);

		if(m.has<cmp_1>(e1)) std::cout << "has" << std::endl;
		else std::cout << "has not" << std::endl;

		m.unregister_component_type<cmp_1>();

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
