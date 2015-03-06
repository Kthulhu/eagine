/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/matrix.hpp>
#endif
#include "common.hpp"
#include <cstdlib>

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;
	static const unsigned O = 4;

	T data[O][N*N];

	for(unsigned l=0; l<O; ++l)
	for(unsigned k=0; k<N*N; ++k)
	{
		data[l][k] = T(std::rand())/T(1111);
	}

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;

		vector<T,N> v1 = vector<T,N>::fill(T(0));

		auto m0 = matrix<T,N,N, true>::from(data[(0+i)%O], N*N);
		auto m1 = matrix<T,N,N,false>::from(data[(1+i)%O], N*N);
		auto m2 = matrix<T,N,N,false>::from(data[(2+i)%O], N*N);
		auto m3 = matrix<T,N,N,false>::from(data[(3+i)%O], N*N);

# if EAGINE_USE_SSE
		vector<T,N> v2 = multiply(multiply(multiply(m0, m1), m2), m3)*v1;
# else
		vector<T,N> v2 = trivial_multiply(trivial_multiply(trivial_multiply(m0, m1), m2), m3)*v1; 
# endif

		fake_use(&v2);
#else
		fake_use(data);

#endif
	}

	return 0;
}
