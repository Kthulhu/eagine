#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os

times = {}

for arg in sys.argv[1:]:
	t = open(arg).readline().strip().split(":")
	n = os.path.splitext(arg)[0].split("-")
	times[n[-1]] = t[3]

baseline = float(times['BASELINE'])

labels = {
	'BASELINE': 'Baseline',
	'OPT_SIMD': 'SIMD_opt',
	'NOOPT_SIMD': 'SIMD_noopt',
	'OPT_NOSIMD': 'PLAIN_opt',
	'NOOPT_NOSIMD': 'PLAIN_noopt',
}

for key in ['BASELINE', 'OPT_SIMD', 'NOOPT_SIMD', 'OPT_NOSIMD', 'NOOPT_NOSIMD']:

	label = labels[key]
	time = float(times[key])

	if time > baseline:
		print("%s\t%f\t%f" % (label, baseline, time-baseline))
	else:
		print("%s\t%f\t%f" % (label, 0, time))
