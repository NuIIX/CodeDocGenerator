APP_NAME = codedocgenerator
DOC_LIB_NAME = docparserlib
HTML_LIB_NAME = htmlgeneratorlib

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
DEPS_DIR = deps

CXX = g++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I $(SRC_DIR) -MP -MMD -std=c++11
LDFLAGS = 
LDLIBS = 

APP_PATH = $(BIN_DIR)/$(APP_NAME)
DOC_LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(DOC_LIB_NAME)/$(DOC_LIB_NAME).a
HTML_LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(HTML_LIB_NAME)/$(HTML_LIB_NAME).a

SRC_EXT = cpp

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DOC_LIB_NAMES = $(DOC_LIB_NAME)
DOC_LIB_SOURCES = $(shell find $(SRC_DIR)/$(DOC_LIB_NAMES) -name '*.$(SRC_EXT)')
DOC_LIB_OBJECTS = $(DOC_LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

HTML_LIB_NAMES = $(HTML_LIB_NAME)
HTML_LIB_SOURCES = $(shell find $(SRC_DIR)/$(HTML_LIB_NAMES) -name '*.$(SRC_EXT)')
HTML_LIB_OBJECTS = $(HTML_LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

$(APP_PATH): $(APP_OBJECTS) $(DOC_LIB_PATH) $(HTML_LIB_PATH)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(DOC_LIB_PATH): $(DOC_LIB_OBJECTS)
	mkdir -p $(dir $@)
	ar rcs $@ $^

$(HTML_LIB_PATH): $(HTML_LIB_OBJECTS)
	mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(DOC_LIB_PATH) $(HTML_LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

-include $(DEPS)
