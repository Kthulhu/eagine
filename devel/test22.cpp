/**
 *  .file devel/test22.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/exte/ops.hpp>
#include <eagine/exte/evaluate.hpp>
//------------------
#include <eagine/base/type_name.hpp>
#include <eagine/base/sstream.hpp>
#include <iostream>
#include <sstream>

namespace eagine {
namespace exte {

template <typename T>
struct type_tag { };

template <typename T, T C>
struct constant_tag { };

} // namespace exte

struct myeval
{
	template <typename T>
	base::string eval(exte::terminal_tag, T&& v) const
	{
		base::stringstream ss;
		ss << v;
		return ss.str();
	}

	template <typename Symbol>
	base::string eval(
		exte::operator_tag<Symbol,-1>,
		base::string&& v
	) const
	{
		return base::string(
			meta::c_str<Symbol>::value,
			meta::size <Symbol>::value
		)+v;
	}

	template <typename Symbol>
	base::string eval(
		exte::operator_tag<Symbol, 1>,
		base::string&& v
	) const
	{
		return v+base::string(
			meta::c_str<Symbol>::value,
			meta::size <Symbol>::value
		);
	}

	template <typename Symbol>
	base::string eval(
		exte::operator_tag<Symbol, 2>,
		base::string&& l,
		base::string&& r
	) const
	{
		return "("+l+base::string(
			meta::c_str<Symbol>::value,
			meta:: size<Symbol>::value
		)+r+")";
	}

	template <typename Tag, typename ... Arg>
	decltype(auto) eval(Tag t, const Arg& ... arg) const
	{
		return t(arg...);
	}
};

} // namespace eagine

int main(int argc, const char**)
{
	using namespace eagine;

	using exte::val;
	using exte::ref;

	int i = 2;

	auto p = -((val(0) + 1 - ref(i)++) * 10);

	std::cout << evaluate(myeval(), p) << std::endl;

	i = 4;

	std::cout << evaluate(myeval(), p) << std::endl;

	return 0;
}
