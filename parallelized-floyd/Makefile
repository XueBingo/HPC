CXX = g++
CXXFLAGS = -std=c++11 -O3 -march=native -fopenmp

RM = rm -f
MKDIRS = mkdir -p

TARGETS = $(basename $(wildcard *.cpp))

all : $(TARGETS)

%:%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) $(TARGETS)