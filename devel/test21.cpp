/**
 *  .file devel/test21.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/dbg/hexdump.hpp>
#include <eagine/base/functor.hpp>
#include <eagine/base/multi_alloc.hpp>
#include <eagine/base/stack_alloc.hpp>
#include <eagine/base/fallback_alloc.hpp>
#include <eagine/base/memory_buffer.hpp>
#include <eagine/base/vector.hpp>
//------------------
#include <iostream>
#include <cmath>

struct foo
{
	float plus(float a, float b)
	{
		return a+b;
	}

	float minus(float a, float b) const
	{
		return a-b;
	}
};

int main(int argc, const char**)
{
	using namespace EAGine::dbg;
	using namespace EAGine::base;

	memory_buffer buf1(1024);
	memory_block blk1 = buf1;
	std::memset(blk1.addr(), 0, blk1.size());

	typedef multi_allocator<
		allocator_with_fallback<
			byte,
			stack_allocator<byte>
		>
	> ma_t;

	ma_t ma(blk1);

	const long N = 16;

	{
		std::vector<char*, ma_t::rebind<char*>::other> cs(ma);
		std::vector<long*, ma_t::rebind<long*>::other> ls(ma);

		for(long i=0; i<N; ++i)
		{
			cs.push_back(ma.allocate<char>(1));
			*cs.back() = 'A'+i;

			ls.push_back(ma.allocate<long>(1));
			*ls.back() = i;
		}

		{
			std::basic_string<
				char,
				std::char_traits<char>,
				ma_t::rebind<char>::other
			> s("blahbleh", ma);

			s = "ho-ho-ho!";

			char* x = ma.allocate<char>(1);
			*x = 'X';

			std::cout << hexdump(blk1) << std::endl;

			ma.deallocate<char>(x, 1);
		}

		for(long i=0; i<N; ++i)
		{
			ma.deallocate<char>(cs.back(), 1);
			cs.pop_back();

			ma.deallocate<long>(ls.back(), 1);
			ls.pop_back();
		}
	}


	std::cout << ma.max_size<byte>() << std::endl;

	std::cout << hexdump(blk1) << std::endl;

	functor_ref<double(double)> fr(&std::sin);

	assert(fr);

	std::cout << fr(M_PI) << std::endl;

	foo f;

	functor_ref<float(float, float)> frp(
		&f,
		EAGine::meta::member_function_constant<
			float(foo::*)(float, float) const,
			&foo::minus
		>()
	);
	std::cout << frp(12, 34) << std::endl;

	typedef functor<double(double, double)> fn_t;

	vector<fn_t, ma_t::rebind<fn_t>::other> v(ma);

	for(int i=0; i<4; ++i)
	{
		v.emplace_back(fn_t(
			std::allocator_arg,
			ma,
			[](double a, double b) -> double
			{
				return a+b;
			}
		));
	}

	std::cout << hexdump(blk1) << std::endl;

	std::cout << v.back().ref()(12, 34) << std::endl;

	return 0;
}
