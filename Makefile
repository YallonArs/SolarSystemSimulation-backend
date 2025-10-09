CXX = g++
# Find all .cpp files except those matching ./__*.cpp
SRC = $(shell find src -name '*.cpp' ! -name '__*.cpp')
HDR = $(shell find src -name '*.h')
OBJ = $(patsubst src/%,build/%,$(SRC:.cpp=.o))
TARGET = main.exe
# Recursively add all src/ subdirectories to the include path
CXXFLAGS = -std=c++23 -Wall -Iinclude -Isrc -Ilib -g -fno-rtti

all: $(TARGET)

$(TARGET): build/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/main.o: main.cpp | build
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

build/%.o: src/%.cpp | build
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(TARGET) .run

re: clean all
rer: clean all run

run: $(TARGET)
	clear; ./$(TARGET)

.PHONY: all clean build run re
