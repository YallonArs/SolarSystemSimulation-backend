CXX = g++
SRC = $(shell find src -name '*.cpp' ! -name '__*.cpp')
OBJ = $(patsubst src/%,build/%,$(SRC:.cpp=.o))
TARGET = main.exe
CXXFLAGS = -std=c++23 -O2 -Wall -Iinclude -Isrc -Ilib -g
CXXFLAGSDEBUG = -std=c++23 -O0 -Wall -Isrc -Ilib -g -fno-inline -fsanitize=undefined,address


.PHONY: build build-debug run re clean

build: build/$(TARGET)

build/$(TARGET): build/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^


build/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build


build-debug: CXXFLAGS=$(CXXFLAGSDEBUG)
build-debug: build/$(TARGET)

run: build/$(TARGET)
	clear; echo "========== RUNNING $(notdir $(CURDIR)) =========="; ./$(TARGET)

re: clean build

clean:
	rm -rf build $(TARGET) .run
	mkdir -p .run
