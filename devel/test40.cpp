#include <eagine/base/parallel.hpp>

#include <iostream>
#include <cstdlib>

namespace eagine {
namespace base {

} // namespace base
} // namespace eagine

unsigned fib(unsigned n)
{
	return n>1?fib(n-1)+fib(n-2):1;
}

int main(void)
{
	using namespace eagine::base;

	parallelizer pzr;


	{
		std::cout << "start" << std::endl;
		auto func =
			[](std::size_t i) -> bool
			{
				assert(fib(25+i%17)>0);
				return i<1000;
			};

		execution_params para;
		para._thread_count = 4;
		auto exec = pzr.execute_stateful(func, para);
		std::cout << "running" << std::endl;
		exec.wait();
		std::cout << "done" << std::endl;
	}
	{
		std::cout << "start" << std::endl;
		functor<bool(std::size_t)> func(
			[](std::size_t i) -> bool
			{
				assert(fib(25+i%17)>0);
				return i<1000;
			}
		);

		execution_params para;
		para._thread_count = 4;
		auto exec = pzr.execute(func, para);
		std::cout << "running" << std::endl;
		exec.wait();
		std::cout << "done" << std::endl;
	}

	return 0;
}
