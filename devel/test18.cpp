/**
 *  .file devel/test18.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/math/interpolation.hpp>
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

	quat q0 = {0, 0, 0, 1};
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

	interpolation<quat> qs(q0, q1);

	for(int i=0; i<=90; ++i)
	{
		quat qt = qs(i/90.0);

		vec3 vt = rotate(v, qt);

		std::cout
			<< i
			<< ": "
			<< vt
			<< " "
			<< magnitude(vt)
			<< " "
			<< value(quantity<degree>(angle_between(v, vt)))
			<< std::endl;
	}

	return 1;
}
