/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/vect/minmax.hpp>
#endif
#include "common.hpp"

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	typedef float T;
	static const unsigned N = 4;
#endif

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::vect;
		data<T, N>::type u = {T(i), T(argc+i), T(i)+T(j), T(argc)};
		data<T, N>::type v = {T(j), T(argc+j), T(i)-T(j), T(0)};

		data<T, N>::type w = min<T, N>::apply(u, v);

		fake_use(&w);
#else
		fake_use(&i, &j);
#endif
	}

	return 0;
}
