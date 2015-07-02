#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os, math

times = {}

for arg in sys.argv[1:]:
	t = open(arg).readline().strip().split(":")
	n = os.path.splitext(arg)[0].split("-")
	times[n[-1]] = t[3]

baseline = float(times['BASELINE'])

labels = {
	'BASELINE': 'Baseline',
	'OPT_SIMD': 'SIMD_{Opt}',
	'NOOPT_SIMD': 'SIMD_{NoOpt}',
	'OPT_NOSIMD': 'Plain_{Opt}',
	'NOOPT_NOSIMD': 'Plain_{NoOpt}',
}

for key in ['BASELINE', 'OPT_SIMD', 'NOOPT_SIMD', 'OPT_NOSIMD', 'NOOPT_NOSIMD']:

	label = labels[key]
	time = float(times[key])

	maxt = max([float(x) for x in times.values()])

	if (time > maxt*0.9):
		lblpos = time - maxt*0.05
	else: lblpos = time + maxt*0.05

	if time > baseline:
		print("%s\t%.2f\t%.2f\t%s\t%f" % (
			label,
			baseline,
			time-baseline,
			"%.*f/%.*f" % (
				max(2-int(math.log10(time)),0),
				time,
				max(2-int(math.log10(time-baseline)),0),
				time-baseline
			),
			lblpos
		))
	else:
		print("%s\t%.2f\t%.2f\t%.2f\t%f" % (
			label,
			time,
			0,
			time,
			lblpos
		))
