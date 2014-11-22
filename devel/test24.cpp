/**
 *  .file devel/test24.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/vectre.hpp>
#include <eagine/base/string.hpp>
//------------------
#include <iostream>
#include <exception>
#include <ctime>
#include <chrono>
#include <thread>

class test
{
private:
	int _i;
public:
	test(int i)
	 : _i(i)
	{ }

	test(const test& t)
	 : _i(t._i)
	{
		std::chrono::milliseconds ms(1);
		std::this_thread::sleep_for(ms);
	}

	int size(void) const { return _i; }
};

int main(int argc, const char**)
{
	using namespace eagine::base;

	//std::srand(std::time(0));

	vectre<test> v(2*1024);
	//vector<test> v;

	const int m = 100000;
	int n, s = 0;

	for(int r=0; r<10; ++r)
	{
		std::cout << r << ":" << std::endl;

		n = std::rand() % (m - s);
		s += n;

		for(int i=0; i<n; ++i)
		{
			v.emplace_back(i);
		}

		assert(unsigned(s) == v.size());

		n = std::rand() % s;
		s -= n;

		for(int i=0; i<n; ++i)
		{
			v.pop_back();
		}

		assert(unsigned(s) == v.size());
	}

	n = 0;
	for(auto& x : v)
	{
		n += x.size();
	}

	std::cout << n << std::endl;

	std::cout << v.capacity() << std::endl;

	return 0;
}
