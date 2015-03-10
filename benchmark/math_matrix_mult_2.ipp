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
		static const unsigned M = EAGINE_BM_M;
		static const unsigned N = EAGINE_BM_N;

		using namespace eagine::math;

		typedef matrix<T,M,N, true> mat;

		rotation_x<mat> r1((angle<T>(j)));
		translation_x<mat> t((T(i-j)));
		rotation_y<mat> r2((angle<T>(i)));
		scale_z<mat> s(T(1)/T(1+j));

#if EAGINE_USE_SSE
		matrix<T,M,N, true> m = fast_multiply(r1,t,r2,s);
#else
		matrix<T,M,N, true> m = r1()|t()|r2()|s();
#endif

		fake_use(&m);
#else
		fake_use(&i,&j);
#endif
	}

	return 0;
}
