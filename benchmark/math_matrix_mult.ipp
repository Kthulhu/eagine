/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/matrix.hpp>
#endif
#include "common.hpp"

int main(int argc, const char** argv)
{
	static const unsigned M = EAGINE_BM_M;
	static const unsigned N = EAGINE_BM_N;

	T data[M*N];

	for(unsigned k=0; k<M*N; ++k)
	{
		data[k] = T(k);
	}

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
		data[0] = T(j+1);
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;

		auto m1 = matrix<T,M,N, true>::from(data, M*N);
		auto m2 = matrix<T,M,N,false>::from(data, M*N);

# if EAGINE_USE_SSE
		matrix<T,M,N, true> m3 = multiply(m1, m2);
# else
		matrix<T,M,N, true> m3 = trivial_multiply(m1, m2);
# endif

		fake_use(&m3);
#else
		fake_use(data);

#endif
	}

	return 0;
}
