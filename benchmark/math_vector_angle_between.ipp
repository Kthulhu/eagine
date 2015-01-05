#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif

int main(int argc, const char** argv)
{
#ifndef EAGINE_BENCHMARK_BASELINE
	static const unsigned N = EAGINE_BM_N;
#endif

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::fill(argc);
		vector<T, N> v = vector<T, N>::axis<0>(i);

		if(value(angle_between(u, v)) > T(2))
#else
		if(T(0.01) > T(argc+i))
#endif
		{
			return 1;
		}
	}

	return 0;
}
