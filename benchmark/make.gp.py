#!/usr/bin/python
import sys, os

print('reset')
print('set output "%s.pdf"' % sys.argv[2])
print('set term pdf truecolor')
print('set title "%s"' % os.path.basename(sys.argv[2]))
print('set style data histograms')
print('set style histogram rowstacked')
print('set ylabel "Execution time [s]"')
print('set xlabel "Configuration"')
print('set grid')
print('set boxwidth 0.9 relative')
print('set style fill transparent solid 0.7 border lt -1')

#print('plot "%s.gp.dat" using 2:xticlabels(1) smooth freq with boxes lc rgb"white" notitle, '' using 3 smooth freq with boxes lc rgb"gray" notitle' % sys.argv[1])
print('plot "%s.gp.dat" using 2 notitle, \'\' using 3:xticlabels(1) notitle' % sys.argv[1])
