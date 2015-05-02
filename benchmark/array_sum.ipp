/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/vect/esum.hpp>
#include <eagine/vect/fill.hpp>
#include "common.hpp"

int main(int argc, const char** argv)
{
	static const unsigned M = EAGINE_BM_M;
	static const unsigned N = EAGINE_BM_N;
	typedef eagine::vect::data<T,N,true>::type V;

	static_assert(M % N == 0, "");

	alignas(V) T d[M] = {};

	for(unsigned k=0; k<M; ++k)
	{
		d[k] = T(k);
	}

	for(unsigned j=0; j!=EAGINE_BR_M; ++j)
	for(unsigned i=0; i!=EAGINE_BR_N; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
# if EAGINE_USE_SIMD || EAGINE_VECT_OPTS
		V* v = reinterpret_cast<V*>(d);
		V t = eagine::vect::fill<T,N,true>::apply(T(0));

		for(unsigned k=0; k<M/N; ++k)
		{
			t = t + v[k];
		}

		T s = eagine::vect::esum<T,N,true>::apply(t);
# else
		T* v = d;
		T s = T(0);
		for(unsigned k=0; k<M; ++k)
		{
			s += v[k];
		}
# endif
		fake_use(&s);
#else
		fake_use(d, &j);
#endif
	}

	return 0;
}
