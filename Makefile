# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99
LDFLAGS :=

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

# Source files
MAIN_SRC := $(SRC_DIR)/main.c
MAP_SRC := $(SRC_DIR)/map.c
CONSOLE_HELP_SRC := $(SRC_DIR)/console_help.c
TREE_SRC := $(SRC_DIR)/tree.c
ANIMAL_SRC := $(SRC_DIR)/animal.c

# Object files
MAIN_OBJ := $(BUILD_DIR)/main.o
MAP_OBJ := $(BUILD_DIR)/map.o
CONSOLE_HELP_OBJ := $(BUILD_DIR)/console_help.o
TREE_OBJ := $(BUILD_DIR)/tree.o
ANIMAL_OBJ := $(BUILD_DIR)/animal.o

# Targets
TARGET := clife

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(MAP_OBJ) $(CONSOLE_HELP_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(MAIN_OBJ): $(MAIN_SRC) $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/tree.h $(INCLUDE_DIR)/animal.h
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

$(MAP_OBJ): $(MAP_SRC) $(INCLUDE_DIR)/map.h $(INCLUDE_DIR)/console_help.h $(INCLUDE_DIR)/tree.h $(INCLUDE_DIR)/animal.h
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

$(CONSOLE_HELP_OBJ): $(CONSOLE_HELP_SRC) $(INCLUDE_DIR)/console_help.h
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

$(TREE_OBJ): $(TREE_SRC) $(INCLUDE_DIR)/tree.h
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
