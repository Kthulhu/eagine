/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>
#include "common.hpp"

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
		T a[N];

		for(unsigned k=0; k<N; ++k)
		{
			a[k] = T((k==i%N)?i-j:0);
		}

#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::from(a, N);

		vector<T, N> v = normalized(u);
		fake_use(&v);
#else
		fake_use(a);
#endif
	}

	return 0;
}
