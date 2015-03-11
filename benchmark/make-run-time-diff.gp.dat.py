#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os, operator

bak_times = {}
new_times = {}

tmax = 0

for p in sys.argv[1:]:
	n = os.path.basename(p[1:-3]).replace("math_", "")
	bak_times[n] = {}
	new_times[n] = {}
	for s in ["BASELINE", "NOSSE", "SSE"]:
		i = p+("-%s.time" % s)

		t = open(i).readline().strip().split(":")
		new_times[n][s] = float(t[3])
		if tmax < new_times[n][s]: tmax = new_times[n][s]

		t = open(i.replace("_out/", "_bak/")).readline().strip().split(":")
		bak_times[n][s] = float(t[3])

diffs1 = {}
diffs2 = {}
diffs3 = {}

for n,tb in iter(sorted(bak_times.iteritems())):
	tn = new_times[n];

	diffs1[n] = pow(max(tb['SSE']/tn['SSE'], 0), tn['SSE']/tmax);
	diffs2[n] = pow(max(tb['NOSSE']/(tn['NOSSE']), 0), tn['SSE']/tmax);
	diffs3[n] = pow(max(tb['SSE']/tn['SSE'], 0), 1);

print("Name\tt_{SSE-bak}/t_{SSE-new}\tt_{NoSSE-bak}/t_{NoSSE-new}\tnorm(t_{SSE-bak}/t_{SSE-new})\tS=1")

for n,d1 in iter(sorted(diffs1.iteritems(), key=operator.itemgetter(1))):
	d2 = diffs2[n]
	d3 = diffs2[n]
	print("%s\t%f\t%f\t%f\t1" % (n.replace('_','-'), d1, d2, d3))
	

