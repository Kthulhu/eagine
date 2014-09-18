# Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

TESTS = $(basename $(wildcard ./test*.cpp))
CXX ?= g++

all: $(TESTS)

test%: test%.o
	$(CXX) $(LDFLAGS) \
		-std=c++11 \
		-Wall \
		-pedantic \
		-rdynamic \
		$< -o $@ \
		-ldl \
		-lpthread \
		-lboost_locale

test%.o: test%.cpp
	$(CXX) $(CXXFLAGS) \
		-std=c++11 \
		-Wall \
		-Wshadow \
		-pedantic \
		-I../_build/include \
		-I../include \
		-I../implement \
		-I ../third_party/include \
		$< -c -o $@

clean:
	rm -f $(TESTS)
