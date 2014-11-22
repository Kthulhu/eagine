/**
 *  .file devel/test19.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/math/elements.hpp>
#include <eagine/math/matrix_ctrs.hpp>
#include <eagine/math/interpolation.hpp>
#include <eagine/math/io.hpp>
//------------------
#include <iostream>

int main(int argc, const char**)
{
	using namespace eagine;

	using math::row;
	using math::column;
	using unit::quantity;

	typedef math::vector<float,4> vec4;
	typedef math::matrix<float,4,4, true> mat4;

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

	std::cout <<
		math::reflection_x<mat4>()*
		math::scale<mat4>(2,2,2)*
		math::translation_y<mat4>(1)*
		math::uniform_scale<mat4>(4)*
		math::interpolation<math::translation_x<mat4>>(1,2)(0.5f)*
		v
		<< std::endl;

	std::cout <<
		math::identity<mat4>()*
		math::perspective<mat4>::x(quantity<unit::degree>(75), 4.0/3.0, 1, 100)*
		math::shear<mat4>(0,-1, 0)*
		vec4{ 1, 0, 0, 1}
		<< std::endl;

	return 0;
}
