# Simple Makefile for current project layout

CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Iinclude
LDFLAGS :=

# Output
BUILD_DIR := build
TARGET := $(BUILD_DIR)/scheduler

# Sources (match actual files present)
SRCS := \
    src/main.c \
    src/algorithms.c \
    src/io.c \
    src/input.c \
    src/file_handler.c \
    src/output.c \
    src/ui/display.c \
    src/ui/menu.c

# Object files under build/, mirroring src/ tree
OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Pattern rule for compiling .c to .o under build/
$(BUILD_DIR)/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	@echo "Running $(TARGET)"
	@./$(TARGET)

# Run with sample file automatically (feeds stdin)
.PHONY: run-sample
run-sample: $(TARGET)
	@echo "Running with samples/sample_input.txt (auto-input)"
	@printf "1\nsamples/sample_input.txt\n\n0\n" | ./$(TARGET)

.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: help
help:
	@echo "Targets:"
	@echo "  make            - Build (default)"
	@echo "  make run        - Run the program"
	@echo "  make run-sample - Run with samples/sample_input.txt (piped input)"
	@echo "  make clean      - Remove build artifacts"
