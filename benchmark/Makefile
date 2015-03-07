# Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++
OPT ?= O2

TIME ?= time
GNUPLOT ?= gnuplot

SOURCES = $(basename $(wildcard *.cpp))
DEPENDENCIES = $(addprefix _bld/,$(addsuffix .d ,$(SOURCES)))
BENCHMARKS = $(foreach src,$(SOURCES), $(foreach var,BASELINE NOSSE SSE, _out/$(src)-$(OPT)-$(var)))
TIMES = $(addsuffix .time,$(BENCHMARKS))
CHARTS = $(addprefix _pdf/,$(addsuffix -$(OPT).pdf,$(SOURCES))) _pdf/run-speedup.pdf

OUT_DIRS = _pdf _out _bld

local_OPTIONS = -std=c++1y -Wall -pedantic -march=native
local_INCLDIRS = -I../_build/include -I../include -I../implement -I../third_party/include
local_CXXFLAGS = $(CXXFLAGS) $(local_OPTIONS) $(local_INCLDIRS)
local_LDFLAGS = $(LDFLAGS) $(local_OPTIONS)

all: charts
.PHONY: all
.SECONDARY:

benchmarks: $(BENCHMARKS)

timing: benchmarks $(TIMES)

charts: timing $(CHARTS)

$(OUT_DIRS):
	mkdir -p $@

_pdf/run-speedup.pdf: _bld/run-speedup.gp _bld/run-speedup.gp.dat | _pdf
	$(GNUPLOT) $<

_pdf/%.pdf: _bld/%-case-times.gp _bld/%-case-times.gp.dat | _pdf
	$(GNUPLOT) $<

_bld/%-case-times.gp: ./make-case-times.gp.py | _bld
	./make-case-times.gp.py _bld/$* _pdf/$* > $@

_bld/%-case-times.gp.dat: _out/%-BASELINE.time _out/%-SSE.time _out/%-NOSSE.time | _bld
	./make-case-times.gp.dat.py $^ > $@

_bld/run-speedup.gp: ./make-run-speedup.gp.py | _bld
	./make-run-speedup.gp.py _bld/run-speedup _pdf/run-speedup "$(CXX) -$(OPT)" > $@

_bld/run-speedup.gp.dat: $(TIMES) | _bld
	./make-run-speedup.gp.dat.py $(addprefix _out/,$(addsuffix -$(OPT),$(SOURCES))) > $@

_out/%.time: _out/% | _out
	$(TIME) -f "%x:%S:%U:%e" -o $@ $<

_out/%-$(OPT)-BASELINE: _bld/%-$(OPT)-BASELINE.o _bld/fake_use.o | _out
	$(CXX) $(local_LDFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $^ -o $@

_out/%-$(OPT)-NOSSE: _bld/%-$(OPT)-NOSSE.o _bld/fake_use.o | _out
	$(CXX) $(local_LDFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $^ -o $@

_out/%-$(OPT)-SSE: _bld/%-$(OPT)-SSE.o _bld/fake_use.o | _out
	$(CXX) $(local_LDFLAGS) -msse -DEAGINE_USE_SSE=1 -$(OPT) $^ -o $@

_bld/%-$(OPT)-BASELINE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $< -c -o $@

_bld/%-$(OPT)-NOSSE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $< -c -o $@

_bld/%-$(OPT)-SSE.o: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) -msse -DEAGINE_USE_SSE=1 -$(OPT) $< -c -o $@

_bld/fake_use.o: fake_use.cxx | _bld
	$(CXX) $(local_CXXFLAGS) $< -c -o $@

_bld/%.d: %.cpp | _bld
	$(CXX) $(local_CXXFLAGS) $< -MM -MT _bld/$*-$(OPT)-BASELINE.o > $@
	$(CXX) $(local_CXXFLAGS) $< -MM -MT _bld/$*-$(OPT)-NOSSE.o >> $@
	$(CXX) $(local_CXXFLAGS) $< -MM -MT _bld/$*-$(OPT)-SSE.o >> $@

sinclude $(DEPENDENCIES)

.PHONY: clean
clean:
	rm -rf $(OUT_DIRS)

