# Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++
OPT = O2

SOURCES = $(basename $(wildcard ./*.cpp))
BENCHMARKS = $(foreach src,$(SOURCES), $(foreach var,BASELINE NOSSE SSE, $(src)-$(OPT)-$(var)))

local_OPTIONS = -std=c++1y -Wall -Werror -pedantic
local_INCLDIRS = -I../_build/include -I../include -I../implement -I../third_party/include
local_CXXFLAGS = $(CXXFLAGS) $(local_OPTIONS) $(local_INCLDIRS)
local_LDFLAGS = $(LDFLAGS) $(local_OPTIONS)

.PHONY: all
all: $(BENCHMARKS)

%-$(OPT)-BASELINE: %-$(OPT)-BASELINE.o
	$(CXX) $(local_LDFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $< -o $@

%-$(OPT)-NOSSE: %-$(OPT)-NOSSE.o
	$(CXX) $(local_LDFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $< -o $@

%-$(OPT)-SSE: %-$(OPT)-SSE.o
	$(CXX) $(local_LDFLAGS) -DEAGINE_USE_SSE=1 -$(OPT) $< -o $@

%-$(OPT)-BASELINE.o: %.cpp
	$(CXX) $(local_CXXFLAGS) -DEAGINE_BENCHMARK_BASELINE -$(OPT) $< -c -o $@

%-$(OPT)-NOSSE.o: %.cpp
	$(CXX) $(local_CXXFLAGS) -DEAGINE_USE_SSE=0 -$(OPT) $< -c -o $@

%-$(OPT)-SSE.o: %.cpp
	$(CXX) $(local_CXXFLAGS) -DEAGINE_USE_SSE=1 -$(OPT) $< -c -o $@


.PHONY: clean
clean:
	rm -f $(BENCHMARKS) $(addsuffix .o, $(BENCHMARKS))
