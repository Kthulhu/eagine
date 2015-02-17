/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>
#include "fake_use.hpp"

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;

	for(unsigned j=0; j!=100000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
		T a[N];

		for(unsigned k=0; k<N; ++k)
		{
			a[k] = T((k==i%N)?i-j:0);
		}

#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::from(a, N);

		T l = length(u); 
		fake_use(&l);
#else
		fake_use(a, &i);
#endif
	}

	return 0;
}
