/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include "common.hpp"

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = EAGINE_BM_N;
#endif

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::fill(argc+i);
		vector<T, N> s = hsum(u);

		fake_use(&s);
#else
		fake_use(&i, &j);
#endif
	}

	return 0;
}
