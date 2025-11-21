# ===================================
# CPU Scheduling Algorithms - Makefile
# ===================================

# Compiler và flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Iinclude
LDFLAGS :=

# ===================================
# Directories
# ===================================
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := tests
SAMPLES_DIR := samples

# Source directories
ALGORITHMS_DIR := $(SRC_DIR)/algorithms
CORE_DIR := $(SRC_DIR)/core
UI_DIR := $(SRC_DIR)/ui
UTILS_DIR := $(SRC_DIR)/utils

# ===================================
# Source Files
# ===================================
# Main
MAIN_SRC := $(SRC_DIR)/main.c

# Algorithms
ALGORITHMS_STUB_SRC := $(SRC_DIR)/algorithms.c
RR_SRC := $(ALGORITHMS_DIR)/round_robin.c
PRIORITY_P_SRC := $(ALGORITHMS_DIR)/priority_p.c
# FCFS_SRC := $(ALGORITHMS_DIR)/fcfs.c
# SJF_SRC := $(ALGORITHMS_DIR)/sjf.c
# SRTF_SRC := $(ALGORITHMS_DIR)/srtf.c
# PRIORITY_NP_SRC := $(ALGORITHMS_DIR)/priority_np.c

# Core
QUEUE_SRC := $(CORE_DIR)/queue.c
# PROCESS_SRC := $(CORE_DIR)/process.c
# METRICS_SRC := $(CORE_DIR)/metrics.c

# IO
IO_SRC := $(SRC_DIR)/io.c
INPUT_SRC := $(SRC_DIR)/input.c
OUTPUT_SRC := $(SRC_DIR)/output.c
FILE_HANDLER_SRC := $(SRC_DIR)/file_handler.c

# UI
MENU_SRC := $(UI_DIR)/menu.c
DISPLAY_SRC := $(UI_DIR)/display.c
GANTT_SRC := $(UI_DIR)/gantt.c
COMPARISON_SRC := $(UI_DIR)/comparison.c

# Utils
COLORS_SRC := $(UTILS_DIR)/colors.c
# SORT_SRC := $(UTILS_DIR)/sort.c
# VALIDATION_SRC := $(UTILS_DIR)/validation.c

# All source files (only those that exist)
SRCS := \
    $(MAIN_SRC) \
    $(ALGORITHMS_STUB_SRC) \
    $(RR_SRC) \
    $(PRIORITY_P_SRC) \
    $(QUEUE_SRC) \
    $(IO_SRC) \
    $(INPUT_SRC) \
    $(OUTPUT_SRC) \
    $(FILE_HANDLER_SRC) \
    $(MENU_SRC) \
    $(DISPLAY_SRC) \
    $(GANTT_SRC) \
    $(COMPARISON_SRC) \
    $(COLORS_SRC)

# ===================================
# Object Files
# ===================================
MAIN_OBJ := $(BUILD_DIR)/main.o

ALGORITHM_OBJS := \
    $(BUILD_DIR)/algorithms.o \
    $(BUILD_DIR)/algorithms/round_robin.o \
    $(BUILD_DIR)/algorithms/priority_p.o

CORE_OBJS := \
    $(BUILD_DIR)/core/queue.o

IO_OBJS := \
    $(BUILD_DIR)/io.o \
    $(BUILD_DIR)/input.o \
    $(BUILD_DIR)/output.o \
    $(BUILD_DIR)/file_handler.o

UI_OBJS := \
    $(BUILD_DIR)/ui/menu.o \
    $(BUILD_DIR)/ui/display.o \
    $(BUILD_DIR)/ui/gantt.o \
    $(BUILD_DIR)/ui/comparison.o

UTILS_OBJS := \
    $(BUILD_DIR)/utils/colors.o

# All object files
OBJS := $(MAIN_OBJ) $(ALGORITHM_OBJS) $(CORE_OBJS) $(IO_OBJS) $(UI_OBJS) $(UTILS_OBJS)

# ===================================
# Target
# ===================================
TARGET := $(BUILD_DIR)/scheduler

# ===================================
# Build Rules
# ===================================

# Default target
.PHONY: all
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	@echo "Linking executable: $@"
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile main
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile algorithms stub
$(BUILD_DIR)/algorithms.o: $(SRC_DIR)/algorithms.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile algorithms subdirectory
$(BUILD_DIR)/algorithms/%.o: $(ALGORITHMS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/algorithms
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile core
$(BUILD_DIR)/core/%.o: $(CORE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/core
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile io (top-level)
$(BUILD_DIR)/io.o: $(SRC_DIR)/io.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/input.o: $(SRC_DIR)/input.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/output.o: $(SRC_DIR)/output.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/file_handler.o: $(SRC_DIR)/file_handler.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ui
$(BUILD_DIR)/ui/%.o: $(UI_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/ui
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile utils
$(BUILD_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/utils
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# ===================================
# Run targets
# ===================================

.PHONY: run
run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET)

# Run with sample file automatically (feeds stdin)
.PHONY: run-sample
run-sample: $(TARGET)
	@echo "Running with samples/sample_input.txt (auto-input)"
	@printf "1\nsamples/sample_input.txt\n\n0\n" | ./$(TARGET)

# ===================================
# Test targets
# ===================================

# Test Round Robin with test cases
.PHONY: test-rr
test-rr:
	@echo "Building test program for Round Robin..."
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_rr \
		$(TEST_DIR)/test_round_robin.c \
		$(RR_SRC) \
		$(QUEUE_SRC) -lm
	@echo "Running Round Robin tests..."
	@echo "\n=== Test 1: test_rr_main.txt (TQ=3) ==="
	@./$(BUILD_DIR)/test_rr $(TEST_DIR)/test_cases/test_rr_main.txt 3
	@echo "\n=== Test 2: test_rr_basic.txt (TQ=2) ==="
	@./$(BUILD_DIR)/test_rr $(TEST_DIR)/test_cases/test_rr_basic.txt 2
	@echo "\n=== Test 3: sample_input.txt (TQ=2) ==="
	@./$(BUILD_DIR)/test_rr $(SAMPLES_DIR)/sample_input.txt 2

.PHONY: test
test: test-rr
	@echo "All tests completed"

# ===================================
# Clean targets
# ===================================

.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)/*.o
	@rm -rf $(BUILD_DIR)/algorithms/*.o
	@rm -rf $(BUILD_DIR)/core/*.o
	@rm -rf $(BUILD_DIR)/ui/*.o
	@rm -rf $(BUILD_DIR)/utils/*.o
	@rm -f $(TARGET)
	@rm -f $(BUILD_DIR)/test_rr
	@echo "Clean complete"

.PHONY: cleanall
cleanall: clean
	@echo "Cleaning test results..."
	@rm -rf $(TEST_DIR)/test_results/*
	@echo "Deep clean complete"

# Rebuild
.PHONY: rebuild
rebuild: clean all

# ===================================
# Debug & Release builds
# ===================================

# Debug build
.PHONY: debug
debug: CFLAGS += -g -DDEBUG
debug: clean all
	@echo "Debug build complete"

# Release build
.PHONY: release
release: CFLAGS += -O2
release: clean all
	@echo "Release build complete"

# ===================================
# Help
# ===================================

.PHONY: help
help:
	@echo "=== CPU Scheduling Algorithms - Makefile ==="
	@echo ""
	@echo "Build targets:"
	@echo "  make / all      - Build the project (default)"
	@echo "  make debug      - Build with debug symbols"
	@echo "  make release    - Build optimized version"
	@echo "  make rebuild    - Clean and build"
	@echo ""
	@echo "Run targets:"
	@echo "  make run        - Run the program interactively"
	@echo "  make run-sample - Run with samples/sample_input.txt"
	@echo ""
	@echo "Test targets:"
	@echo "  make test       - Run all tests"
	@echo "  make test-rr    - Test Round Robin algorithm"
	@echo ""
	@echo "Clean targets:"
	@echo "  make clean      - Remove build files"
	@echo "  make cleanall   - Remove all generated files"
	@echo ""
	@echo "Other:"
	@echo "  make help       - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make && make run              # Build and run"
	@echo "  make test-rr                  # Test Round Robin"
	@echo "  make clean && make release    # Clean build"

# ===================================
# Phony targets
# ===================================
.PHONY: all run run-sample test test-rr \
        clean cleanall rebuild \
        debug release help
