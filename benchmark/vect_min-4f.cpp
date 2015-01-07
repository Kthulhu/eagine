/*
 *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/vect/minmax.hpp>
#endif

int main(int argc, const char** argv)
{
	typedef float T;
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = 4;
#endif

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::vect;
		data<T, N>::type u = {T(i), T(argc+i), T(i)+T(j), T(argc)};
		data<T, N>::type v = {T(j), T(argc+j), T(i)-T(j), T(0)};

		data<T, N>::type w = min<T, N>::apply(u, v);

		if(!(
			((i<j)?w[0]==T(i):w[0]==T(j)) &&
			((i<j)?w[1]==T(argc+i):w[1]==T(argc+j)) &&
			(w[2]==T(i)-T(j)) &&
			(w[3]==T(0))
			
		))
#else
		if(
			(-1.0f == T(argc+i)) ||
			(-1.0f == T(argc+j)) ||
			(-1.0f == T(i)+T(j)) ||
			(T(i)-T(j) > T(i)+T(j))
		)
#endif
		{
			return 1;
		}
	}

	return 0;
}
