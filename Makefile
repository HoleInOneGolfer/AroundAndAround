.PHONY: all clean

# Configurable variables
PROJECT_NAME       ?= game
RAYLIB_VERSION     ?= 4.5.0
RAYLIB_DIR         ?= C:/raylib
PLATFORM           ?= PLATFORM_DESKTOP
BUILD_MODE         ?= DEBUG
MY_RC              ?= game.rc
USE_EXTERNAL_GLFW  ?= FALSE

# Build directory
BUILD_DIR          := build
OBJ_DIR            := $(BUILD_DIR)/obj
BIN_DIR            := $(BUILD_DIR)/bin

# Automatic resource data filename
MY_RC_DATA         := $(BUILD_DIR)/$(MY_RC:.rc=.rc.data)

# Export compiler path for Windows (MinGW)
export PATH := $(RAYLIB_DIR)/w64devkit/bin:$(PATH)

# Compiler and tools
CC                 := gcc
MAKE               := mingw32-make
RC                 := x86_64-w64-mingw32-windres

# Flags
CFLAGS             := -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces
LDFLAGS            := -L. -L$(RAYLIB_DIR)/raylib/src -L$(RAYLIB_DIR)/raylib/src/external
LDLIBS             := -lraylib -lopengl32 -lgdi32 -lwinmm

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else ifeq ($(BUILD_MODE),RELEASE)
    CFLAGS += -s -O1 -Wl,--subsystem,windows
endif

ifeq ($(USE_EXTERNAL_GLFW),TRUE)
    LDLIBS += -lglfw
endif

# Include paths
INCLUDE_PATHS      := -I$(RAYLIB_DIR)/raylib/src -I$(RAYLIB_DIR)/raylib/src/external -I./include

# Directories and files
SRC_DIR            := src
SRC                := $(wildcard $(SRC_DIR)/*.c)
OBJS               := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Default target
all: $(BIN_DIR)/$(PROJECT_NAME).exe

# Generate resource data
$(MY_RC_DATA): $(MY_RC) | $(BUILD_DIR)
	@echo "Compiling resource file: $< -> $@"
	$(RC) $< -o $@ --target=pe-x86-64

# Build the project executable
$(BIN_DIR)/$(PROJECT_NAME).exe: $(OBJS) $(MY_RC_DATA) | $(BIN_DIR)
	@echo "Linking executable: $@"
	$(CC) -o $@ $(OBJS) $(MY_RC_DATA) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling: $< -> $@"
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

# Ensure directories exist
$(BUILD_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

# Clean target
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR)
