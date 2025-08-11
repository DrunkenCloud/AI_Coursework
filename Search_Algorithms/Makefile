CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = $(wildcard *.cpp)
BINS = $(patsubst %.cpp,%,$(SRCS))

all: $(BINS)
	@echo "Compilation complete. Executables created: $(BINS)"

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@.out

.PHONY: run
run: $(firstword $(BINS))
	@echo "Running the first executable: $<"
	./$<

run-%:
	@filename=$(shell ls *.cpp | sed -n '$*p' | sed 's/\.cpp//') ; \
	echo "Running file $*: $$filename" ; \
	./$$filename

.PHONY: clean
clean:
	@echo "Cleaning up generated binaries..."
	rm -f $(BINS) a.out

