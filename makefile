APP_NAME = codedocgenerator
DOC_LIB_NAME = docparserlib

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
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(DOC_LIB_NAME)/$(DOC_LIB_NAME).a

SRC_EXT = cpp

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_NAMES = $(DOC_LIB_NAME)
LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAMES) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH) $(LIB_PATH)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	mkdir -p $(dir $@)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

-include $(DEPS)