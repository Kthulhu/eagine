#!/usr/bin/python
# coding=utf-8
#  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

def generate(coord_str):
	import itertools

	coords = list("O"+coord_str)
	index = dict()

	for i in range(0, len(coords)):
		index[coords[i]] = i

	getters = {0: "c", 1: "v.x()", 2: "v.y()", 3: "v.z()", 4:"v.w()"}

	print("/*  .file eagine/math/vector_swizzles.ipp")
	print(" *  Automatically generated file do not modify manually.")
	print(" *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost")
	print(" *  Software License, Version 1.0. (See accompanying file")
	print(" *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)")
	print(" */")

	for n in range(2, 5):
		for comb in itertools.product(coords, repeat=n):
			name = str("").join(comb)
			if name != n * coords[0]:
				print("BOOST_ASSERT((v.%(name)s(c) == eagine::math::tvec<T,%(N)d>(%(gets)s)));" % {
					"name": name,
					"gets": str(", ").join([str(getters[index[x]]) for x in comb]),
					"N" : len(comb)
				})

def main():
	generate("xyzw")


if __name__ == "__main__": main()
