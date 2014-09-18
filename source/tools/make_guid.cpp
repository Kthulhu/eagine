/**
 *  .file tools/make_guid.cpp
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/base/guid.hpp>
#include <eagine/base/program_args.hpp>

#include <iostream>

std::ostream& print_usage(std::ostream& out)
{
	return out
		<< "Usage: make_guid [--help] | [-n|--nil]"
		<< std::endl
		<< std::endl
		<< "Options:"
		<< std::endl
		<< "--help | -h: Print this help screen and exit."
		<< std::endl
		<< "--nil  | -n: Generate a nil GUID."
		<< std::endl;
}

int main(int argc, const char* argv[])
{
	using namespace EAGine::base;

	bool inv_opt = false;
	bool gen_nil = false;

	for(auto arg : program_args(argc, argv))
	{
		if(arg.in("-h", "--help"))
		{
			std::cout
				<< "make_guid: globally unique identifier generator"
				<< std::endl
				<< print_usage;
			return 0;
		}
		else if(arg.in("-n", "--nil"))
		{
			gen_nil = true;
		}
		else
		{
			std::cout
				<< "Invalid command line option '"
				<< arg
				<< "'!"
				<< std::endl;
			inv_opt = true;
		}
	}

	if(inv_opt)
	{
		print_usage(std::cerr << std::endl);
		return 1;
	}

	std::cout
		<< (gen_nil ? guid::nil() : guid())
		<< std::endl;
	
	return 0;
}
