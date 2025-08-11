CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = $(wildcard *.cpp)
BINS = $(patsubst %.cpp,%,$(SRCS))

all: $(BINS)
	@echo "Compilation complete. Executables created: $(patsubst %,%.out,$(BINS))"

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@.out

.PHONY: run
run: 
	@echo "Running the first executable: $(firstword $(BINS)).out"
	./$(firstword $(BINS)).out

run-%:
	@filename=$(shell ls *.cpp | sed -n '$*p' | sed 's/\.cpp//') ; \
	echo "Running file $*: $$filename.out" ; \
	./$$filename.out

.PHONY: clean
clean:
	@echo "Cleaning up generated binaries..."
	rm -f $(patsubst %,%.out,$(BINS)) a.out