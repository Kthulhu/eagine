# Copyright 2012-2015 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

CXX ?= g++
OPT ?= O2

TIME ?= time
GNUPLOT ?= gnuplot

VARIANTS = BASELINE OPT_SIMD OPT_NOSIMD NOOPT_SIMD NOOPT_NOSIMD

CXXFLAGS_BASELINE = -DEAGINE_BENCHMARK_BASELINE 
CXXFLAGS_OPT_SIMD = -msse -DEAGINE_USE_SIMD=1 -DEAGINE_VECT_OPTS=1
CXXFLAGS_OPT_NOSIMD = -DEAGINE_USE_SIMD=0 -DEAGINE_VECT_OPTS=1
CXXFLAGS_NOOPT_SIMD = -msse -DEAGINE_USE_SIMD=1 -DEAGINE_VECT_OPTS=0
CXXFLAGS_NOOPT_NOSIMD = -DEAGINE_USE_SIMD=0 -DEAGINE_VECT_OPTS=0

LDFLAGS_OPT_SIMD = -msse
LDFLAGS_NOOPT_SIMD = -msse

local_OPTIONS = -std=c++1y -Wall -pedantic -march=native
local_INCLDIRS = -I../_build/include -I../include -I../implement -I../third_party/include
local_CXXFLAGS = $(CXXFLAGS) $(local_OPTIONS) $(local_INCLDIRS)
local_LDFLAGS = $(LDFLAGS) $(local_OPTIONS)


SOURCES = \
	math_matrix_mult_1-4f \
	math_matrix_mult_1-4d \
	math_matrix_mult_2-4f \
	math_matrix_mult_2-4d \
	math_matrix_mult_3-4f \
	math_matrix_mult_3-4d \
	math_mat_vec_transf_1-4f \
	math_mat_vec_transf_1-4d \
	math_mat_vec_transf_2-4f \
	math_mat_vec_transf_2-4d \
	math_mat_vec_transf_3-4f \
	math_mat_vec_transf_3-4d \
	math_vector_cross-3f \
	math_vector_cross-3d \
	math_vector_normalize-3f \
	math_vector_normalize-3d \
	array_sum-1024-4d \
	array_sum-1024-4f \
	array_sum-1024-4i
#SOURCES = $(basename $(wildcard *.cpp))

DEPENDENCIES = $(addprefix _bld/,$(addsuffix .d ,$(SOURCES)))

BENCHMARKS = $(foreach src,$(SOURCES), $(foreach var,$(VARIANTS), _out/$(src)-$(OPT)-$(var)))
ASM_FILES= $(foreach src,$(SOURCES), $(foreach var,$(VARIANTS), _out/$(src)-$(OPT)-$(var).asm))
TIMES = $(addsuffix .time,$(BENCHMARKS))
BAK_TIMES = $(foreach src,$(SOURCES), $(foreach var,$(VARIANTS), _bak/$(src)-$(OPT)-$(var).time))
CHARTS = $(addprefix _pdf/,$(addsuffix -$(OPT).pdf,$(SOURCES))) _pdf/run-speedup.pdf

OUT_DIRS = _pdf _out _bld _bak

all: charts
.PHONY: all
.SECONDARY:

benchmarks: $(BENCHMARKS)

asm_files: $(ASM_FILES)

timing: benchmarks $(TIMES)

bak_times: $(BAK_TIMES)

charts: timing $(CHARTS)

diff_charts: timing _pdf/run-time-diff.pdf

$(OUT_DIRS):
	mkdir -p $@

_pdf/run-speedup.pdf: _bld/run-speedup.gp _bld/run-speedup.gp.dat | _pdf
	$(GNUPLOT) $<

_pdf/run-time-diff.pdf: _bld/run-time-diff.gp _bld/run-time-diff.gp.dat | _pdf
	$(GNUPLOT) $<

_pdf/%.pdf: _bld/%-case-times.gp _bld/%-case-times.gp.dat | _pdf
	$(GNUPLOT) $<

_bld/%-case-times.gp: ./make-case-times.gp.py | _bld
	./make-case-times.gp.py _bld/$* _pdf/$* > $@

_bld/%-case-times.gp.dat: $(foreach VAR,$(VARIANTS), _out/%-$(VAR).time) | _bld
	./make-case-times.gp.dat.py $^ > $@

_bld/run-speedup.gp: ./make-run-speedup.gp.py | _bld
	./make-run-speedup.gp.py _bld/run-speedup _pdf/run-speedup "$(CXX) -$(OPT)" > $@

_bld/run-speedup.gp.dat: $(TIMES) | _bld
	./make-run-speedup.gp.dat.py $(addprefix _out/,$(addsuffix -$(OPT),$(SOURCES))) > $@

_bld/run-time-diff.gp: ./make-run-time-diff.gp.py | _bld
	./make-run-time-diff.gp.py _bld/run-time-diff _pdf/run-time-diff "$(CXX) -$(OPT)" > $@

_bld/run-time-diff.gp.dat: $(TIMES) | _bld
	./make-run-time-diff.gp.dat.py $(addprefix _out/,$(addsuffix -$(OPT),$(SOURCES))) > $@

_bak/%.time: _out/%.time | _bak
	cp $< $@

_out/%.time: _out/% | _out
	$(TIME) -f "%x:%S:%U:%e" -o $@ $<

define make_var_rules
_out/%-$(OPT)-$1 : _bld/%-$(OPT)-$1.o _bld/fake_use.o | _out
	$$(CXX) $$(local_LDFLAGS) $$(LDFLAGS_$1) -$$(OPT) $$^ -o $$@

_bld/%-$(OPT)-$1.o: %.cpp | _bld
	$$(CXX) $$(local_CXXFLAGS) $$(CXXFLAGS_$1) -$$(OPT) $$< -c -o $$@

_out/%-$(OPT)-$1.asm: %.cpp | _out
	$$(CXX) $$(local_CXXFLAGS) $$(CXXFLAGS_$1) -$$(OPT) $$< -S -o $$@

endef

$(foreach VAR,$(VARIANTS), $(eval $(call make_var_rules,$(VAR))))

_bld/fake_use.o: fake_use.cxx | _bld
	$(CXX) $(local_CXXFLAGS) $< -c -o $@

_bld/%.d: %.cpp | _bld
	rm -f $@
	$(foreach VAR,$(VARIANTS), $(CXX) $(local_CXXFLAGS) $< -MM -MT _bld/$*-$(OPT)-$(VAR).o >> $@;)

ifneq ($(MAKECMDGOALS),clean)
	sinclude $(DEPENDENCIES)
endif

.PHONY: clean
clean:
	rm -rf $(OUT_DIRS)

