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
#include <eagine/ecs/storage/posix_fs.hpp>
//------------------
#include <eagine/base/io.hpp>
#include <eagine/base/sstream.hpp>
#include <eagine/base/guid.hpp>
#include <eagine/base/error.hpp>
//------------------

namespace eagine {
namespace ecs {

template <>
struct entity_traits<unsigned>
{
	static constexpr inline
	unsigned nil(void)
	{
		return 0;
	}

	static inline
	bool is_valid_string(const base::cstrref& s)
	{ 
		for(char c : s)
		{
			if(!((c >= '0') && (c <= '9')))
			{
				return false;
			}
		}
		return true;
	}

	static inline
	base::string to_string(unsigned u)
	{
		base::stringstream ss;
		ss << u;
		return ss.str();
	}

	static inline
	unsigned from_string(const base::cstrref& s)
	{
		return unsigned(std::atoi(base::c_str(s)));
	}
	
};

} // namespace ecs
} // namespace eagine

struct cmp_1
 : eagine::ecs::component<cmp_1>
{
	int i;

	cmp_1(void) = default;

	cmp_1(int x)
	 : i(x)
	{ }
};

struct cmp_2
 : eagine::ecs::component<cmp_2>
{
	double d;

	cmp_2(void) = default;

	cmp_2(double x)
	 : d(x)
	{ }
};

struct cmp_3
 : eagine::ecs::component<cmp_3>
{
	std::string s;

	cmp_3(void) = default;

	cmp_3(std::string&& x)
	 : s(std::move(x))
	{ }
};

struct cmp_3_io
 : public eagine::ecs::posix_fs_component_io<cmp_3>
{
	bool read(const eagine::base::cstrref& path, cmp_3& c)
	override
	{
		auto fc = eagine::base::load_file_text(path);
		c.s.assign(fc.data(), fc.size());
		return true;
	}

	bool write(const eagine::base::cstrref& path, const cmp_3& c)
	override
	{
		assert(!"Not implemented");
		return false;
	}
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
		ep._thread_count = 4;

		manager<unsigned> m;

		m.register_component_storage<normal_component_storage, cmp_1>();
		assert(m.knows_component_type<cmp_1>());

		std::size_t dmy[6] = {0u, 0u, 0u};
		base::const_memory_block blk(dmy, sizeof(dmy));

		m.register_component_storage<immutable_component_storage, cmp_2>(blk);
		assert(m.knows_component_type<cmp_2>());

		m.register_component_storage<posix_fs_component_storage, cmp_3>(
			base::string("./tmp/"),
			base::string(".txt"),
			base::make_shared<cmp_3_io>()
		);
		assert(m.knows_component_type<cmp_3>());

		for(unsigned i=1; i<=1000; ++i)
		{
			m.add(i, cmp_1(i));
		}

		base::atomic<unsigned> n(0);

		m.parallel_for_each_with<const cmp_1>(
			[&n](unsigned, const cmp_1& c)
			{
				if(fib(20+c.i % 10) % 2 == 0)
				{
					++n;
				}
			}, p, ep
		);

		std::cout << unsigned(n) << std::endl;

		m.for_each_with<const cmp_3>(
			[](unsigned e, const cmp_3& c)
			{
				std::cout << e << "|" << c.s << std::endl;
			}
		);

		std::cout << std::endl;

		m.for_each_with<cmp_1, const cmp_3>(
			[](unsigned, cmp_1& c1, const cmp_3& c3)
			{
				std::cout << c1.i << "|" << c3.s << std::endl;
			}
		);

		std::cout << std::endl;

		m.remove_if(
			base::functor_ref<bool(const unsigned&, const cmp_1&)>(
			[](unsigned, const cmp_1& c) -> bool
			{
				return c.i % 2 == 0;
			})
		);

		m.for_each_with<cmp_1, const cmp_3>(
			[](unsigned, cmp_1& c1, const cmp_3& c3)
			{
				std::cout << c1.i << "|" << c3.s << std::endl;
			}
		);

		std::cout << std::endl;

		m.parallel_for_each_with<const cmp_1, const cmp_3>(
			[&n](unsigned, const cmp_1&, const cmp_3&)
			{
				++n;
			}, p, ep
		);

		std::cout << unsigned(n) << std::endl;

		return 0;
	}
	catch(base::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 1;
}
