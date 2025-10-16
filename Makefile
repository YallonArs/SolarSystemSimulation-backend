CXX = g++
TARGET = main.exe
MAINFILE = examples/main/main.cpp
BUILDFOLDER = .build
SRC = $(shell find src -name '*.cpp' ! -name '__*.cpp')
OBJ = $(patsubst src/%, $(BUILDFOLDER)/%,$(SRC:.cpp=.o))
CXXFLAGS = -std=c++23 -O2 -Wall -Iinclude -Isrc -Ilib -g
CXXFLAGSDEBUG = -std=c++23 -O0 -Wall -Isrc -Ilib -g -fno-inline -fsanitize=undefined,address


.PHONY: build build-debug run re clean


build: $(BUILDFOLDER)/$(TARGET)

$(BUILDFOLDER)/$(TARGET): $(BUILDFOLDER)/main.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

$(BUILDFOLDER)/main.o: $(MAINFILE)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $(MAINFILE) -o $@

$(BUILDFOLDER)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p $(BUILDFOLDER)

build-debug: CXXFLAGS=$(CXXFLAGSDEBUG)
build-debug: $(BUILDFOLDER)/$(TARGET)

run: $(BUILDFOLDER)/$(TARGET)
	clear; echo "========== RUNNING $(notdir $(CURDIR)) =========="; ./$(TARGET)

re: clean build

clean:
	rm -rf $(BUILDFOLDER) $(TARGET) .run
	mkdir -p .run
