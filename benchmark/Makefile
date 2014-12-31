# Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++
OPT = O2

TIME ?= time
GNUPLOT = gnuplot

SOURCES = $(basename $(wildcard ./*.cpp))
BENCHMARKS = $(foreach src,$(SOURCES), $(foreach var,BASELINE NOSSE SSE, _out/$(src)-$(OPT)-$(var)))
TIMES = $(addsuffix .time,$(BENCHMARKS))
CHARTS = $(addprefix _out/,$(addsuffix -$(OPT).pdf,$(SOURCES)))

local_OPTIONS = -std=c++1y -Wall -pedantic
local_INCLDIRS = -I../_build/include -I../include -I../implement -I../third_party/include
local_CXXFLAGS = $(CXXFLAGS) $(local_OPTIONS) $(local_INCLDIRS)
local_LDFLAGS = $(LDFLAGS) $(local_OPTIONS)

all: charts
.PHONY: all
.SECONDARY:

benchmarks: $(BENCHMARKS)

timing: benchmarks $(TIMES)

charts: timing $(CHARTS)

_out _bld:
	mkdir -p $@

_out/%.pdf: _bld/%.gp _bld/%.gp.dat
	$(GNUPLOT) $<

_bld/%.gp: ./make.gp.py
	./make.gp.py _bld/$* _out/$* > $@

_bld/%.gp.dat: _out/%-BASELINE.time _out/%-SSE.time _out/%-NOSSE.time 
	./make.gp.dat.py $^ > $@

_out/%.time: _out/%
	$(TIME) -f "%S:%U:%e" -o $@ $<

_out/%-$(OPT)-BASELINE: _bld/%-$(OPT)-BASELINE.o | _out
	$(CXX) $(local_LDFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $< -o $@

_out/%-$(OPT)-NOSSE: _bld/%-$(OPT)-NOSSE.o | _out
	$(CXX) $(local_LDFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $< -o $@

_out/%-$(OPT)-SSE: _bld/%-$(OPT)-SSE.o | _out
	$(CXX) $(local_LDFLAGS) -DEAGINE_USE_SSE=1 -$(OPT) $< -o $@

_bld/%-$(OPT)-BASELINE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $< -c -o $@

_bld/%-$(OPT)-NOSSE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $< -c -o $@

_bld/%-$(OPT)-SSE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -DEAGINE_USE_SSE=1 -$(OPT) $< -c -o $@

.PHONY: clean
clean:
	rm -rf _bld _out

