#!/usr/bin/python
# Copyright 2014-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
import sys, os

print('reset')
print('set output "%s.pdf"' % sys.argv[2])
print('set term pdf truecolor')
print('set termopt enhanced')
print('set title "%s"' % sys.argv[3])
print('set key left on inside nobox')
print('set style data lines')
print('set ylabel "Speedup"')
print('set logscale y 10')
print('set xtics axis out nomirror offset 0 rotate by -50 font ",4"')
print('set bmargin 7')
print('set rmargin 7')
print('set grid')
print('set boxwidth 0.9 relative')
print('set style fill transparent solid 0.7 border lt -1')

print('plot "%s.gp.dat" \
	using 2:xtic(1) title col lw 5 lc rgb"#404080", \'\' \
	using 3:xtic(1) title col lw 3 lc rgb"#8080B0", \'\' \
	using 4:xtic(1) title col lw 1 lc rgb"#A0A0FF", \'\' \
	using 5:xtic(1) title col lw 2 lc rgb"black"' %
	sys.argv[1]
	
)
