#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>
#include "fake_use.hpp"

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = 3;
#endif

	for(unsigned j=0; j!=100000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::axis<0>(argc+i);
		vector<T, N> v = vector<T, N>::axis<1>(argc+i);
		vector<T, N> w = cross(u, v);

		fake_use(&w);
#else
		fake_use(&i, &j);
#endif
	}

	return 0;
}
