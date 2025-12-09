# Makefile for NetBSD/Linux
# Compiler
CC = gcc

# Compiler Flags
# -Iinclude: Tìm file .h trong thư mục include
# -Wall: Hiện tất cả cảnh báo
# -g: Thêm thông tin debug (gdb)
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g

# Linker Flags (math library nếu cần)
LDFLAGS = -lm

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source Files
# Liệt kê thủ công hoặc dùng wildcard (nhưng thủ công an toàn hơn để tránh file rác)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/core/process.c \
       $(SRC_DIR)/core/metrics.c \
       $(SRC_DIR)/core/queue.c \
       $(SRC_DIR)/io/input.c \
       $(SRC_DIR)/io/output.c \
       $(SRC_DIR)/io/file_handler.c \
       $(SRC_DIR)/ui/menu.c \
       $(SRC_DIR)/ui/display.c \
       $(SRC_DIR)/ui/gantt.c \
       $(SRC_DIR)/ui/comparison.c \
       $(SRC_DIR)/utils/colors.c \
       $(SRC_DIR)/utils/sort.c \
       $(SRC_DIR)/utils/validation.c \
       $(SRC_DIR)/algorithms/fcfs.c \
       $(SRC_DIR)/algorithms/sjf.c \
       $(SRC_DIR)/algorithms/srtf.c \
       $(SRC_DIR)/algorithms/priority_np.c \
       $(SRC_DIR)/algorithms/priority_p.c \
       $(SRC_DIR)/algorithms/round_robin.c

# Object Files (tự động tạo tên file .o từ .c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target Executable
TARGET = $(BUILD_DIR)/scheduler

# --- Rules ---

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Run
run: all
	./$(TARGET)

.PHONY: all clean run