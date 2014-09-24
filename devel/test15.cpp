/**
 *  .file devel/test14.cpp
 *
 *  Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#include <eagine/math/swizzle.hpp>
//------------------
#include <iostream>

int main(void)
{
	using namespace EAGine::math;

	typedef vector<float, 3> vec3;
	typedef vector<float, 4> vec4;

	vec4 r0 = {{ 1, 2, 3, 4}};
	vec4 r1 = {{ 5, 6, 7, 8}};
	vec4 r2 = {{ 9,10,11,12}};
	vec4 r3 = {{13,14,15,16}};

	shuffle_mask<0,1,4,5> m1;
	shuffle_mask<2,3,6,7> m2;

	swizzle_mask<int,1,2,3> xyz = {0};
	swizzle_mask<int,3,2,1,0> zyx_ = {0};

	vec3 cx = r0/xyz;
	vec4 c = cx/zyx_(9);

	std::cout << c[0] << std::endl;
	std::cout << c[1] << std::endl;
	std::cout << c[2] << std::endl;
	std::cout << c[3] << std::endl;


	
	vec4 c0 = shuffle<0,2,4,6>(
		shuffle(r0, r1, m1),
		shuffle(r2, r3, m1)
	);

	std::cout << c0[0] << std::endl;
	std::cout << c0[1] << std::endl;
	std::cout << c0[2] << std::endl;
	std::cout << c0[3] << std::endl;

	vec4 c1 = shuffle<1,3,5,7>(
		shuffle(r0, r1, m1),
		shuffle(r2, r3, m1)
	);

	std::cout << c1[0] << std::endl;
	std::cout << c1[1] << std::endl;
	std::cout << c1[2] << std::endl;
	std::cout << c1[3] << std::endl;

	vec4 c2 = shuffle<0,2,4,6>(
		shuffle(r0, r1, m2),
		shuffle(r2, r3, m2)
	);

	std::cout << c2[0] << std::endl;
	std::cout << c2[1] << std::endl;
	std::cout << c2[2] << std::endl;
	std::cout << c2[3] << std::endl;

	vec4 c3 = shuffle<1,3,5,7>(
		shuffle(r0, r1, m2),
		shuffle(r2, r3, m2)
	);

	std::cout << c3[0] << std::endl;
	std::cout << c3[1] << std::endl;
	std::cout << c3[2] << std::endl;
	std::cout << c3[3] << std::endl;

	vec3 v30 = vec3::axis<0>();
	vec3 v31 = vec3::fill(2);
	vec3 v32 = cross(v30, v31);

	std::cout << v30[0] << "|" << v30[1] << "|" << v30[2] << std::endl;
	std::cout << v31[0] << "|" << v31[1] << "|" << v31[2] << std::endl;
	std::cout << v32[0] << "|" << v32[1] << "|" << v32[2] << std::endl;

	std::cout << distance(v31, v30) << std::endl;

	vec4 v40 = vec4::axis<0>();
	vec4 v41 = vec4::fill(2);
	vec4 v42 = {1,2,3,4};
	vec4 v43 = v41+v42;

	std::cout << v40[0] << "|" << v40[1] << "|" << v40[2] << "|" << v40[3] << std::endl;
	std::cout << v41[0] << "|" << v41[1] << "|" << v41[2] << "|" << v41[3] << std::endl;

	std::cout << distance(v41, v40) << std::endl;
	std::cout << distance(v42, v41) << std::endl;
	std::cout << distance(v43, v42) << std::endl;

	return 1;
}
