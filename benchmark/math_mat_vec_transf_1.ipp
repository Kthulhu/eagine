/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/matrix_ctrs.hpp>
#endif
#include "common.hpp"

int main(int argc, const char** argv)
{
	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		static const unsigned N = EAGINE_BM_N;

		using namespace eagine::math;

		typedef matrix<T,N,N, true> mat;

		vector<T,N> v1 = vector<T,N>::fill(T(0));

		rotation_x<mat> r1((angle<T>(j)));
		rotation_y<mat> r2((angle<T>(i)));
		rotation_z<mat> r3((angle<T>(i)));

#if EAGINE_VECT_OPTS
		vector<T,N> v2 = fast_multiply(r1,r2,r3)*v1;
#else
		vector<T,N> v2 = (r1()|r2()|r3())*v1;
#endif

		fake_use(&v2);
#else
		fake_use(&i,&j);
#endif
	}

	return 0;
}
