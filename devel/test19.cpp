/**
 *  .file devel/test19.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/math/elements.hpp>
#include <eagine/math/matrix_ctrs.hpp>
#include <eagine/math/io.hpp>
//------------------
#include <iostream>

int main(int argc, const char**)
{
	using namespace EAGine;

	using math::row;
	using math::column;

	typedef math::vector<float,4> vec4;
	typedef math::matrix<float,4,4, true> mat4;
	typedef math::matrix<float,4,4,false> mat4c;

	vec4 v = {0, 0, 0, 1};
	mat4 m0 = math::identity<mat4>();
	mat4 m1 = {{
		{ 1, 2, 3, 4},
		{ 5, 6, 7, 8},
		{ 9,10,11,12},
		{13,14,15,16}
	}};
	mat4 m2 = math::translation<mat4>(1,2,3);

	std::cout << m0 << std::endl;
	std::cout << row<1>(m0) << std::endl;
	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	std::cout << transpose(m1) << std::endl;
	std::cout << reorder(m1) << std::endl;
	std::cout << column<0>(m1) << std::endl;
	std::cout << column<1>(m1) << std::endl;
	std::cout << column<2>(m1) << std::endl;
	std::cout << column<3>(m1) << std::endl;

	std::cout << std::endl;
	for(unsigned i=0; i<rows(m1); ++i)
	{
		std::cout << multiply(m0, row(m1, i)) << std::endl;
	}

	std::cout << std::endl;
	for(unsigned i=0; i<columns(m1); ++i)
	{
		std::cout << multiply(m0, column(m1, i)) << std::endl;
	}

	std::cout << multiply(m0,m1) << std::endl;
	std::cout << multiply(m1,m0) << std::endl;
	std::cout << multiply(m1,m1) << std::endl;

	for(unsigned i=0; i<200000; ++i)
	{
		set(m1, 0, 0, float(argc+i));
		mat4 x = multiply(m1, m1);
		if(get(x, 0, 0) < 0) return 1;
	}

	auto m1e = elements(m1);

	for(unsigned i=0; i<size(m1e); ++i)
	{
		std::cout << data(m1e)[i] << " ";
	}
	std::cout << std::endl;

	auto m1c1e = elements(column<1>(m1));

	for(unsigned i=0; i<size(m1c1e); ++i)
	{
		std::cout << data(m1c1e)[i] << " ";
	}
	std::cout << std::endl;

	typedef vect::data<float, 2>::type vd2_t;
	typedef vect::data<float, 3>::type vd3_t;
	typedef vect::data<float, 4>::type vd4_t;

	std::cout <<
		math::translation<mat4>( 1, 0, 0)*
		math::translation<mat4>(-1, 0, 0)*
		v << std::endl;

	return 0;
}
