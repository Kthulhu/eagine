/**
 *  .file devel/test11.cpp
 *
 *  Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/ecs/manager.hpp>
#include <eagine/ecs/storage/normal.hpp>
#include <eagine/ecs/storage/immutable.hpp>
//------------------
#include <eagine/base/guid.hpp>
#include <eagine/base/error.hpp>
//------------------

namespace eagine {
namespace ecs {


} // namespace ecs
} // namespace eagine

struct cmp_1
 : eagine::ecs::component<cmp_1>
{
	int i;

	cmp_1(int x)
	 : i(x)
	{ }
};

struct cmp_2
 : eagine::ecs::component<cmp_2>
{
	double d;

	cmp_2(double x)
	 : d(x)
	{ }
};

unsigned fib(unsigned i)
{
	return i>1?fib(i-1)+fib(i-2):1;
}

int main(void)
{
	using namespace eagine;

	try
	{
		using namespace eagine::ecs;

		base::parallelizer p;
		base::execution_params ep;
		ep.thread_count = 4;

		manager<unsigned> m;

		m.register_component_storage<normal_component_storage, cmp_1>();

		assert(m.knows_component_type<cmp_1>());

		for(unsigned i=0; i<100000; ++i)
		{
			m.add(i, cmp_1(i));
		}

		base::atomic<unsigned> n(0);

		m.parallel_for_each(
			base::functor_ref<void(const unsigned&, const cmp_1&)>(
			[&n](const unsigned&, const cmp_1& c)
			{
				if(fib(20+c.i % 10) % 2 == 0)
				{
					++n;
				}
			}), p, ep
		);

		std::cout << unsigned(n) << std::endl;

		std::cout << sizeof(unsigned) << std::endl;
		std::cout << sizeof(std::size_t) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
