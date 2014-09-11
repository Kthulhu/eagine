# Copyright 2012-2014 Matus Chochlik. Distributed under the Boost
# Software License, Version 1.0. (See accompanying file
# LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

TESTS = $(basename $(wildcard ./test*.cpp))
CXX ?= g++

all: $(TESTS)

test%: test%.o
	$(CXX) -std=c++0x $(LDFLAGS) $< -rdynamic -o $@ -lpthread -ldl -lboost_locale

test%.o: test%.cpp
	$(CXX) -std=c++0x -I../_build/include -I../include -I../implement $(CXXFLAGS) $< -c -o $@

clean:
	rm -rf $(TESTS)
