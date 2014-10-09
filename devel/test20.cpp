/**
 *  .file devel/test20.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/varray.hpp>
#include <eagine/dbg/hexdump.hpp>
#include <eagine/meta/type_traits.hpp>
#include <eagine/base/type.hpp>
//------------------
#include <iostream>
#include <iterator>
#include <cassert>

#include <vector>

int main(int argc, const char**)
{
	using namespace EAGine::dbg;
	using namespace EAGine::base;

	std::array<double, 128> a;

	std::cout << std::endl;

	{
		typedef basic_pod_varray<int, std::size_t> cpv;

		cpv* v = make_basic_pod_varray<int, std::size_t>({1,2,3,4,5,6,7,8,9,10});

		for(int x : *v)
		{
			std::cout << x << std::endl;
		}

		std::cout << std::endl;

		free_basic_pod_varray(v);
	}
	{
		typedef basic_pod_varray<double, std::size_t> cpv;

		stack_allocator<double> ssa(a.data(), a.size());

		cpv* v = make_basic_pod_varray<double, std::size_t>({0.,1.,2.,3.,4.,5.,6.,7.,8.,9.}, ssa);

		for(double x : *v)
		{
			std::cout << x << std::endl;
		}

		std::cout << std::endl;
		free_basic_pod_varray(v, ssa);
	}
	std::cout << hexdump(a) << std::endl;
	{
		typedef basic_pod_varray<char, std::size_t> cpv;

		cpv* v = make_basic_pod_varray<char, std::size_t>({'a','b','c','d','e','f','g','h','i','j'});

		for(char x : *v)
		{
			std::cout << x << std::endl;
		}
		std::cout << hexdump(v, v->instance_size()) << std::endl;

		std::cout << std::endl;

		free_basic_pod_varray(v);
	}

	return 0;
}
