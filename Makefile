#Makefile for osprj1
#MasonBrainard 2/13/20

CXX = g++

OBJS = 

g++ -c shell.cc 
g++ -c history.cc
g++ -c alias.cc
g++ -c parser.cc
g++ -c builtin.cc

g++ -o run-shell shell.o history.o alias.o parser.o builtin.o