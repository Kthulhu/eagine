#ifndef EAGINE_BENCHMARK_BASELINE
#include <eagine/math/vector.hpp>
#endif

int main(int argc, const char** argv)
{
	static const unsigned N = EAGINE_BM_N;

	for(unsigned j=0; j!=100000; ++j)
	for(unsigned i=0; i!=100000; ++i)
	{
#ifndef EAGINE_BENCHMARK_BASELINE
		using namespace eagine::math;
		vector<T, N> u = vector<T, N>::fill(argc+i);

		for(unsigned i=1; i<N; ++i)
		{
			if(hsum(u)[i] != hsum(u)[0])
			{
				return 1;
			}
		}

		if(hsum(u)[0] != T((argc+i)*N))
#else
		if(-1.0f == T((argc+i)*N))
#endif
		{
			return 1;
		}
	}

	return 0;
}
