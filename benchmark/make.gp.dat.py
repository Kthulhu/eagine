#!/usr/bin/python
import sys, os

times = {}

for arg in sys.argv[1:]:
	t = open(arg).readline().strip().split(":")
	n = os.path.splitext(arg)[0].split("-")
	times[n[-1]] = t[2]

baseline = float(times['BASELINE'])
sse = float(times['SSE'])
nosse = float(times['NOSSE'])

print("Baseline\t%f\t0.0" % baseline)
print("With_SSE\t%f\t%f" % (baseline, sse-baseline))
print("No_SSE\t%f\t%f" % (baseline, nosse-baseline))
