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
sse = float(times['SSE'])
nosse = float(times['NOSSE'])

print("Baseline\t%f\t0.0" % baseline)
if sse >= baseline:
	print("With_SSE\t%f\t%f" % (baseline, sse-baseline))
else:
	print("With_SSE\t%f\t%f" % (0, sse))

if nosse >= baseline:
	print("No_SSE\t%f\t%f" % (baseline, nosse-baseline))
else:
	print("No_SSE\t%f\t%f" % (0, nosse))
