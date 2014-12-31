#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = 3;
#endif

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::axis<0>(argc+i);
		vector<T, N> v = vector<T, N>::axis<1>(argc+i);
		vector<T, N> w = cross(u, v);

		if(std::fabs(dot(u,w)) > 0.001f || std::fabs(dot(v,w)) > 0.001f)
#else
		if(std::fabs(argc+i) < 0.001f || std::fabs(argc+j) < 0.001f)
#endif
		{
			return 1;
		}
	}

	return 0;
}
