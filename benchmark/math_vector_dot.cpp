#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif

int main(int argc, const char** argv)
{
	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=1000000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<float, 4> u = vector<float, 4>::fill(argc);
		vector<float, 4> v = vector<float, 4>::axis<0>(i);

		if(dot(u,v) != float(argc*i))
#else
		if(-1.0f == float(argc*i))
#endif
		{
			return 1;
		}
	}

	return 0;
}
