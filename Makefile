SRC_DIR := src
BUILD_DIR := build
DOC_DIR := doc
EXECUTABLE := 2D\ Minecraft
HEADER_FILES := $(wildcard $(SRC_DIR)/*.h)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES := $(filter-out $(BUILD_DIR)/main.o,$(OBJ_FILES)) $(BUILD_DIR)/test.o
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf
CXXFLAGS := -Wall -pedantic -std=c++17

all: compile doc

compile: dir build

dir:
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi

build: $(OBJ_FILES)
	g++ $^ -o $(EXECUTABLE) $(LDFLAGS) 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CXXFLAGS) -c -o $@ $<

run: compile
	./$(EXECUTABLE)

clean:
	if [ -d $(BUILD_DIR) ]; then rm -r $(BUILD_DIR); fi
	if [ -d $(DOC_DIR) ]; then rm -r $(DOC_DIR); fi
	if [ -f $(EXECUTABLE) ]; then rm $(EXECUTABLE); fi

doc: Doxyfile $(HEADER_FILES)
	if [ ! -d $(DOC_DIR) ]; then mkdir $(DOC_DIR); fi
	doxygen Doxyfile

test: dir build_test

build_test: $(TEST_OBJ_FILES)
	g++ $^ -o $(EXECUTABLE) $(LDFLAGS)

$(BUILD_DIR)/test.o: $(SRC_DIR)/tests/test.cpp
	g++ $(CXXFLAGS) -c -o $@ $<