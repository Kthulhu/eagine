/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=1000000; ++i)
	{
		T a[N], b[N];

		for(unsigned k=0; k<N; ++k)
		{
			a[k] = T((k==i%N)?i-j:0);
			b[k] = T((k==j%N)?j-k-i:0);
		}

#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::from(a, N);
		vector<T, N> v = vector<T, N>::from(b, N);

		if(distance(u, v) < T(0))
#else
		if(a[(i+1)%N] < T(0) && b[(j+1)%N] < T(0))
#endif
		{
			return 1;
		}
	}

	return 0;
}
