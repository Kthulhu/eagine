/**
 *  .file devel/test18.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/math/quaternion.hpp>
#include <eagine/math/io.hpp>
//------------------
#include <iostream>

int main(void)
{
	using namespace EAGine::unit;
	using namespace EAGine::math;

	typedef angle<double> ang;
	typedef vector<double, 3> vec3;
	typedef quaternion<double> quat;

	quat q1 = quat::from_axis_angle(vec3{1,0,0}, quantity<degree>(90));
	quat q2 = conjugate(q1);
	quat q3 = inverse(q2);
	quat q4 = *q3;
	quat q5 = grassman_product(q3,q4);

	vec3 v = {0,1,0};

	std::cout << magnitude(q1) << std::endl;
	std::cout << magnitude(q2) << std::endl;
	std::cout << q1 << std::endl;
	std::cout << q2 << std::endl;
	std::cout << q3 << std::endl;
	std::cout << q4 << std::endl;
	std::cout << q5 << std::endl;

	std::cout << rotate(v, q3) << std::endl;
	std::cout << rotate(v, q3*q4) << std::endl;

	quantity<degree> x = angle_between(v, rotate(v, q3));
	std::cout << value(x) << std::endl;


	return 1;
}
