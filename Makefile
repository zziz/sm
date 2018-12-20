CXXFLAGS = -g -Wall -Wfatal-errors -std=c++14

ALL = examples

all: $(ALL)

examples: examples.cpp Makefile
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp

clean:
	$(RM) $(ALL) *.o

test: all
	bash examples