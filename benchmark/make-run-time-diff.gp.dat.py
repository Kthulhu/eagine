#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os, operator

bak_times = {}
new_times = {}

for p in sys.argv[1:]:
	n = os.path.basename(p[1:-3]).replace("math_", "")
	bak_times[n] = {}
	new_times[n] = {}
	for s in ["BASELINE", "NOSSE", "SSE"]:
		i = p+("-%s.time" % s)
		t = open(i).readline().strip().split(":")
		new_times[n][s] = float(t[3])
		t = open(i.replace("_out/", "_bak/")).readline().strip().split(":")
		bak_times[n][s] = float(t[3])

diffs1 = {}
diffs2 = {}

for n,tb in iter(sorted(bak_times.iteritems())):
	tn = new_times[n];

	diffs1[n] = max(tn['SSE']/tb['SSE'], 0);
	diffs2[n] = max(tn['NOSSE']/tb['NOSSE'], 0);

print("Name\tt_{SSE-new}/t_{SSE-bak}\tt_{NoSSE-new}/t_{NoSSE-bak}\tS=1")

for n,d1 in diffs1.iteritems():
	d2 = diffs2[n]
	print("%s\t%f\t%f\t1" % (n.replace('_','-'), d1, d2))
	

