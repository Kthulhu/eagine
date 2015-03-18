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

	print("/*  .file eagine/math/swizzle_%s.ipp" % coord_str)
	print(" *  Automatically generated file do not modify manually.")
	print(" *  Copyright 2014-2015 Matus Chochlik. Distributed under the Boost")
	print(" *  Software License, Version 1.0. (See accompanying file")
	print(" *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)")
	print(" */")

	for n in range(2, 5):
		for comb in itertools.product(coords, repeat=n):
			name = str("").join(comb)
			if name != n * coords[0]:
				nums = str(",").join([str(index[x]) for x in comb])
				print("constexpr auto %(name)s(value_type c = 0) const noexcept { return this->swizzle<%(nums)s>(c); }" % {
					"nums": nums,
					"name": name
				})

def main():
	generate("xyzw")


if __name__ == "__main__": main()
