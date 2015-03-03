/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/matrix.hpp>
#endif

#include <cstdlib>
#include "fake_use.hpp"

int main(int argc, const char** argv)
{
	static const unsigned M = EAGINE_BM_M;
	static const unsigned N = EAGINE_BM_N;

	T data[M*N];

	for(unsigned k=0; k<M*N; ++k)
	{
		data[k] = T(std::rand())/T(RAND_MAX);
	}

	for(unsigned j=0; j!=100000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
		data[0] = T(j+i);
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;

		auto m1 = matrix<T,M,N, true>::from(data, M*N);
		auto m2 = identity<matrix<T,M,N, true>>()();

		if(!gauss_jordan(m1, m2))
		{
			return 1;
		}

		fake_use(&m2);
#else
		fake_use(data);

#endif
	}

	return 0;
}
