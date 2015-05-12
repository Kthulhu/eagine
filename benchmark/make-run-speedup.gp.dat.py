#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os, operator

times = {}

for p in sys.argv[1:]:
	n = os.path.basename(p[1:-3])
	times[n] = {}
	for s in ["BASELINE", "NOOPT_SIMD", "OPT_SIMD", "NOOPT_NOSIMD", "OPT_NOSIMD"]:
		i = p+("-%s.time" % s)
		t = open(i).readline().strip().split(":")
		times[n][s] = float(t[3])

speedups1 = {}
speedups2 = {}
speedups3 = {}

for n,t in iter(sorted(times.iteritems())):
	speedups1[n] = max(t['NOOPT_NOSIMD']/t['OPT_SIMD'], 0);
	speedups2[n] = max(t['OPT_NOSIMD']/t['OPT_SIMD'], 0);
	speedups3[n] = max(t['NOOPT_NOSIMD']/t['NOOPT_SIMD'], 0);
	#speedups2[n] = min(max((t['NOSSE']-t['BASELINE'])/max(t['SSE']-t['BASELINE'], 0.01), 0.01), 100);

print("Name\tt_{Plain_{NoOpt}}/t_{SIMD_{Opt}}\tt_{Plain_{Opt}}/t_{SIMD_{Opt}}\tt_{Plain_{NoOpt}}/t_{SIMD_{NoOpt}})\tS=1")

for n,s1 in iter(sorted(speedups1.iteritems(), key=operator.itemgetter(1))):
	s2 = speedups2[n]
	s3 = speedups3[n]
	print("%s\t%f\t%f\t%f\t1" % (n.replace('_','-'), s1, s2, s3))
	

