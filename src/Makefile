# Compiler và flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = 

# ===================================
# Directories
# ===================================
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TEST_DIR = tests
SAMPLES_DIR = samples

# Source directories
ALGORITHMS_DIR = $(SRC_DIR)/algorithms
CORE_DIR = $(SRC_DIR)/core
IO_DIR = $(SRC_DIR)/io
UI_DIR = $(SRC_DIR)/ui
UTILS_DIR = $(SRC_DIR)/utils

# ===================================
# Source Files (sẽ có sau)
# ===================================
# Algorithms
FCFS_SRC = $(ALGORITHMS_DIR)/fcfs.c
SJF_SRC = $(ALGORITHMS_DIR)/sjf.c
SRTF_SRC = $(ALGORITHMS_DIR)/srtf.c
PRIORITY_NP_SRC = $(ALGORITHMS_DIR)/priority_np.c
PRIORITY_P_SRC = $(ALGORITHMS_DIR)/priority_p.c
RR_SRC = $(ALGORITHMS_DIR)/round_robin.c

# Core
PROCESS_SRC = $(CORE_DIR)/process.c
METRICS_SRC = $(CORE_DIR)/metrics.c
QUEUE_SRC = $(CORE_DIR)/queue.c

# IO
INPUT_SRC = $(IO_DIR)/input.c
OUTPUT_SRC = $(IO_DIR)/output.c
FILE_HANDLER_SRC = $(IO_DIR)/file_handler.c

# UI
MENU_SRC = $(UI_DIR)/menu.c
DISPLAY_SRC = $(UI_DIR)/display.c
GANTT_SRC = $(UI_DIR)/gantt.c

# Utils
SORT_SRC = $(UTILS_DIR)/sort.c
VALIDATION_SRC = $(UTILS_DIR)/validation.c
COLORS_SRC = $(UTILS_DIR)/colors.c

# Main
MAIN_SRC = $(SRC_DIR)/main.c

# ===================================
# Object Files (sẽ tạo sau khi compile)
# ===================================
ALGORITHM_OBJS = $(BUILD_DIR)/algorithms/fcfs.o \
                 $(BUILD_DIR)/algorithms/sjf.o \
                 $(BUILD_DIR)/algorithms/srtf.o \
                 $(BUILD_DIR)/algorithms/priority_np.o \
                 $(BUILD_DIR)/algorithms/priority_p.o \
                 $(BUILD_DIR)/algorithms/round_robin.o

CORE_OBJS = $(BUILD_DIR)/core/process.o \
            $(BUILD_DIR)/core/metrics.o \
            $(BUILD_DIR)/core/queue.o

IO_OBJS = $(BUILD_DIR)/io/input.o \
          $(BUILD_DIR)/io/output.o \
          $(BUILD_DIR)/io/file_handler.o

UI_OBJS = $(BUILD_DIR)/ui/menu.o \
          $(BUILD_DIR)/ui/display.o \
          $(BUILD_DIR)/ui/gantt.o

UTILS_OBJS = $(BUILD_DIR)/utils/sort.o \
             $(BUILD_DIR)/utils/validation.o \
             $(BUILD_DIR)/utils/colors.o

MAIN_OBJ = $(BUILD_DIR)/main.o

# Tất cả object files
ALL_OBJS = $(ALGORITHM_OBJS) $(CORE_OBJS) $(IO_OBJS) $(UI_OBJS) $(UTILS_OBJS) $(MAIN_OBJ)

# ===================================
# Target
# ===================================
TARGET = $(BUILD_DIR)/cpu_scheduler

# ===================================
# Build Rules
# ===================================

# Default target
all: $(TARGET)

# Link executable (TODO: sẽ implement sau khi có đủ .o files)
$(TARGET): $(ALL_OBJS)
	@echo "Linking executable..."
	@echo "TODO: Implement linking when source files are ready"
	# $(CC) $(CFLAGS) $(ALL_OBJS) -o $(TARGET) $(LDFLAGS)

# Compile algorithms
$(BUILD_DIR)/algorithms/%.o: $(ALGORITHMS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/algorithms
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile core
$(BUILD_DIR)/core/%.o: $(CORE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/core
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile io
$(BUILD_DIR)/io/%.o: $(IO_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/io
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

# Compile main
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling main.c..."
	$(CC) $(CFLAGS) -c $< -o $@

# ===================================
# Run targets
# ===================================

# Run program
run: $(TARGET)
	@echo "Running program..."
	@./$(TARGET)

# Run with sample input
run-sample: $(TARGET)
	@echo "Running with sample input..."
	@./$(TARGET) $(SAMPLES_DIR)/sample_input.txt

# ===================================
# Clean targets
# ===================================

# Clean build files
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)/algorithms/*.o
	@rm -rf $(BUILD_DIR)/core/*.o
	@rm -rf $(BUILD_DIR)/io/*.o
	@rm -rf $(BUILD_DIR)/ui/*.o
	@rm -rf $(BUILD_DIR)/utils/*.o
	@rm -f $(BUILD_DIR)/*.o
	@rm -f $(TARGET)
	@echo "Clean complete"

# Clean all (including test results)
cleanall: clean
	@echo "Cleaning test results..."
	@rm -rf $(TEST_DIR)/test_results/*
	@echo "Deep clean complete"

# Rebuild
rebuild: clean all

# ===================================
# Test targets (TODO: sẽ implement sau)
# ===================================

# Run all tests
test:
	@echo "Running tests..."
	@echo "TODO: Implement test commands"

# Test FCFS
test-fcfs:
	@echo "Testing FCFS algorithm..."
	@echo "TODO: Implement FCFS test"

# Test SJF
test-sjf:
	@echo "Testing SJF algorithm..."
	@echo "TODO: Implement SJF test"

# Test SRTF
test-srtf:
	@echo "Testing SRTF algorithm..."
	@echo "TODO: Implement SRTF test"

# Test Priority (Non-preemptive)
test-priority-np:
	@echo "Testing Priority (Non-preemptive) algorithm..."
	@echo "TODO: Implement Priority NP test"

# Test Priority (Preemptive)
test-priority-p:
	@echo "Testing Priority (Preemptive) algorithm..."
	@echo "TODO: Implement Priority P test"

# Test Round Robin
test-rr:
	@echo "Testing Round Robin algorithm..."
	@echo "TODO: Implement RR test"

# ===================================
# Debug & Release builds
# ===================================

# Debug build
debug: CFLAGS += -g -DDEBUG
debug: clean all
	@echo "Debug build complete"

# Release build
release: CFLAGS += -O2
release: clean all
	@echo "Release build complete"

# ===================================
# Help
# ===================================

help:
	@echo "=== CPU Scheduling Algorithms - Makefile ==="
	@echo ""
	@echo "Build targets:"
	@echo "  all          - Build the project (default)"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build optimized version"
	@echo "  rebuild      - Clean and build"
	@echo ""
	@echo "Run targets:"
	@echo "  run          - Run the program"
	@echo "  run-sample   - Run with sample input file"
	@echo ""
	@echo "Test targets:"
	@echo "  test         - Run all tests"
	@echo "  test-fcfs    - Test FCFS algorithm"
	@echo "  test-sjf     - Test SJF algorithm"
	@echo "  test-srtf    - Test SRTF algorithm"
	@echo "  test-priority-np - Test Priority (Non-preemptive)"
	@echo "  test-priority-p  - Test Priority (Preemptive)"
	@echo "  test-rr      - Test Round Robin algorithm"
	@echo ""
	@echo "Clean targets:"
	@echo "  clean        - Remove build files"
	@echo "  cleanall     - Remove all generated files"
	@echo ""
	@echo "Other:"
	@echo "  help         - Show this help message"

# ===================================
# Phony targets
# ===================================
.PHONY: all run run-sample clean cleanall rebuild \
        test test-fcfs test-sjf test-srtf test-priority-np test-priority-p test-rr \
        debug release help