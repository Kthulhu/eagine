/**
 *  @file eagine/base/program_args.hpp
 *  @brief argc/argv wrapper
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#pragma once

#ifndef EAGINE_BASE_PROGRAM_ARGS_1308281038_HPP
#define EAGINE_BASE_PROGRAM_ARGS_1308281038_HPP

#include <eagine/base/string.hpp>
#include <eagine/base/iterator.hpp>

namespace EAGine {
namespace base {

class program_args
{
private:
	const std::size_t _argc;
	const char** _argv;
public:
	program_args(int argc, const char* argv[])
	 : _argc(argc<0?0:argc)
	 , _argv(argv)
	{ }

	typedef cstrref value_type;
	typedef cstrref reference;

	bool empty(void) const
	{
		return _argc <= 1;
	}

	std::size_t size(void) const
	{
		return _argc;
	}

	cstrref at(std::size_t pos) const
	{
		assert(pos < _argc);
		return cstrref(_argv[pos]);
	}

	cstrref operator [] (std::size_t pos) const
	{
		return at(pos);
	}

	cstrref command(void) const
	{
		return at(0);
	}

	typedef ras_iterator<const program_args> iterator;
	typedef iterator const_iterator;

	iterator begin(void) const
	{
		return iterator(*this, 1);
	}

	iterator end(void) const
	{
		return iterator(*this, _argc);
	}
};

} // namespace base
} // namespace EAGine

#endif //include guard

