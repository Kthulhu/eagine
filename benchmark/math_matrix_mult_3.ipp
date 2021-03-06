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
	static const unsigned M = EAGINE_BM_M;
	static const unsigned N = EAGINE_BM_N;
	static const unsigned O = 5;

	T data[O][M*N];

	for(unsigned l=0; l<O; ++l)
	for(unsigned k=0; k<M*N; ++k)
	{
		data[l][k] = T(std::rand())/T(1111);
	}

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
		data[j%O][0] = T(j+1);
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;

		auto m0 = matrix<T,M,N, true>::from(data[(0+i)%O], M*N);
		auto m1 = matrix<T,M,N,false>::from(data[(1+i)%O], M*N);
		auto m2 = matrix<T,M,N,false>::from(data[(2+i)%O], M*N);
		auto m3 = matrix<T,M,N,false>::from(data[(3+i)%O], M*N);
		auto m4 = matrix<T,M,N,false>::from(data[(4+i)%O], M*N);

# if EAGINE_VECT_OPTS
		matrix<T,M,N, true> m = fast_multiply(m0,m1,m2,m3,m4);
# else
		matrix<T,M,N, true> m = m0|m1|m2|m3|m4;
# endif

		fake_use(&m);
#else
		fake_use(data);

#endif
	}

	return 0;
}
