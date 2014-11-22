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

namespace eagine {
namespace base {

class program_args
{
private:
	const std::size_t _argc;
	const char** _argv;
public:
	program_args(int argc, const char* argv[])
	noexcept
	 : _argc(argc<0?0:argc)
	 , _argv(argv)
	{ }

	typedef cstrref value_type;
	typedef cstrref reference;

	bool empty(void) const
	noexcept
	{
		return _argc <= 1;
	}

	std::size_t size(void) const
	noexcept
	{
		return _argc;
	}

	cstrref at(std::size_t pos) const
	noexcept
	{
		assert(pos < _argc);
		return cstrref(_argv[pos]);
	}

	cstrref operator [] (std::size_t pos) const
	noexcept
	{
		return at(pos);
	}

	cstrref command(void) const
	noexcept
	{
		return at(0);
	}

	typedef ras_iterator<const program_args> iterator;
	typedef iterator const_iterator;

	iterator begin(void) const
	noexcept
	{
		return iterator(*this, 1);
	}

	iterator end(void) const
	noexcept
	{
		return iterator(*this, _argc);
	}
};

} // namespace base
} // namespace eagine

#endif //include guard

