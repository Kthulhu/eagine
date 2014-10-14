/**
 *  .file devel/test22.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/exte/op_ampersand.hpp>
#include <eagine/exte/op_pipe.hpp>
#include <eagine/exte/op_slash.hpp>
#include <eagine/exte/op_asterisk.hpp>
#include <eagine/exte/op_minus.hpp>
#include <eagine/exte/op_plus.hpp>
#include <eagine/exte/evaluate.hpp>
//------------------
#include <iostream>

namespace EAGine {

struct myeval
{
	template <typename U>
	auto eval(exte::terminal_tag, const U& v) const
	{
		return v;
	}

	template <typename U>
	auto eval(exte::plus_tag, const U& v) const
	{
		return v;
	}

	template <typename L, typename R>
	auto eval(exte::plus_tag, const L& l, const R& r) const
	{
		return l+r;
	}

	template <typename U>
	auto eval(exte::minus_tag, const U& v) const
	{
		return -v;
	}

	template <typename L, typename R>
	auto eval(exte::minus_tag, const L& l, const R& r) const
	{
		return l-r;
	}

	template <typename U>
	auto eval(exte::ampersand_tag, const U& v) const
	{
		return 100*v;
	}
};

} // namespace EAGine

int main(int argc, const char**)
{
	using namespace EAGine;

	using exte::val;
	using exte::ref;

	int blah = 2;

	std::cout << exte::evaluate(
		myeval(),
		&(val(argc)+blah-(+val(3))+(-val(1)))
	) << std::endl;

	return 0;
}
