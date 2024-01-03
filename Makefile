#
# Makefile
# ------------------------------------------------------------------------------
# Checkup for a Block of Memory, Containing a Repeated Single Byte
# ------------------------------------------------------------------------------
# Ver   1.00  Initial version                                       January 24
# ------------------------------------------------------------------------------
# Copyright (c) 2024 A.Yakovlev
#

CXX := g++

CXXFLAGS += -O3 -Wall -std=c++20
LDFLAGS  +=
LDLIBS   += 

.cpp:;	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@ ${LDLIBS}

all: $(basename $(wildcard tc????.cpp))

tc%: tc%.cpp compare.hpp

clean:;	rm -fr core *.o tc???? tc????.exe
