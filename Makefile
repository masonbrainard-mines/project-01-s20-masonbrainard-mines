#Makefile for osprj1
#MasonBrainard 2/13/20

CXX = g++
CXXFLAGS = -Wall -g

shell: shell.o history.o alias.o parser.o builtin.o
	$(CXX) $(CXXFLAGS) -o shell shell.o history.o alias.o parser.o builtin.o

shell.o: shell.cc history.hh alias.hh parser.hh builtin.hh
	$(CXX) $(CXXFLAGS) -c shell.cc

builtin.o: builtin.hh history.hh alias.hh parser.hh

history.o: history.hh

alias.o: alias.hh

parser.o: parser.hh
