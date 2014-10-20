/**
 *  .file devel/test21.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/scope_exit.hpp>
//------------------
#include <iostream>
#include <exception>

void success(void)
{
	std::cout << "success" << std::endl;
}

void failure(void)
{
	std::cout << "failure" << std::endl;
}

void finished(void)
{
	std::cout << "finished" << std::endl;
}

int main(int argc, const char**)
{
	using namespace EAGine::base;

	{
		on_scope_exit se(&success, &failure);
	}
	try
	{
		on_scope_exit se(&success, &failure);
		throw 1;
	}
	catch(...) { }

	{
		on_scope_exit se(&finished);
	}
	try
	{
		on_scope_exit se(&finished);
		throw 1;
	}
	catch(...) { }

	{
		on_scope_exit se(&success, &failure);
		se.dismiss_on_success();
	}
	try
	{
		on_scope_exit se(&success, &failure);
		se.dismiss_on_failure();
		throw 1;
	}
	catch(...) { }

	{
		on_scope_exit se(&finished);
		se.dismiss();
	}
	try
	{
		on_scope_exit se(&finished);
		se.dismiss();
		throw 1;
	}
	catch(...) { }

	return 0;
}
