/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = EAGINE_BM_N;
#endif

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=1000000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::fill(argc);
		vector<T, N> v = vector<T, N>::axis<0>(i);

		if(dot(u,v) != T(argc*i))
#else
		if(-1.0f == T(argc*i))
#endif
		{
			return 1;
		}
	}

	return 0;
}
