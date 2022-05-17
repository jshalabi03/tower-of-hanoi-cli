CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug $(INCLUDES)

run: bin/exec
	./$<

bin/exec: ./src/*.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

.DEFAULT_GOAL:=bin/exec