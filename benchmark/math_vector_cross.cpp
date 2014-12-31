#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif
#include <cmath>

int main(int argc, const char** argv)
{
	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<float, 3> u = vector<float, 3>::axis<0>(argc+i);
		vector<float, 3> v = vector<float, 3>::axis<1>(argc+i);
		vector<float, 3> w = cross(u, v);

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
