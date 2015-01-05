#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;

	for(unsigned j=0; j!=10000; ++j)
	for(unsigned i=0; i!=1000000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::fill(argc+i);

		if(hsum(u)[0] != T(argc+i)*N)
#else
		if(-1.0f == T(argc+i)*N)
#endif
		{
			return 1;
		}
	}

	return 0;
}
