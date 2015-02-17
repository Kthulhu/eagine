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

		T r = std::fabs(dot(u,w))+std::fabs(dot(v,w));
#else
		T r = std::fabs(argc+i)+std::fabs(argc+j);
#endif
		fake_use(&r);
	}

	return 0;
}
