CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wpedantic -Iinclude

SOURCES := $(wildcard src/*.cc)
OBJECTS := $(SOURCES:.cc=.o)
TARGET := avalanche_simulation

all: $(TARGET)

$(TARGET): $(OBJECTS) app/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

src/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

app/main.o: app/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) app/main.o $(TARGET)

.PHONY: all clean
