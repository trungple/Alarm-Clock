# Tên của tệp thực thi
TARGET = my_program

# Thư mục chứa các tệp nguồn và header
SRC_DIR = Source_file_C
INC_DIR = header_files
BUILD_DIR = build
BIN_DIR = bin
MAIN_DIR =main_file

# Tìm tất cả các tệp nguồn và tạo danh sách tệp đối tượng
SRCS = $(wildcard $(SRC_DIR)/*.c) $(MAIN_DIR)/testmock.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/testmock.o

# Cờ biên dịch
CC = gcc
CFLAGS = -Iheader_files -Wall
# Quy tắc mặc định
all: $(BIN_DIR)/$(TARGET)

# Quy tắc để tạo tệp thực thi
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# Quy tắc để biên dịch tệp nguồn thành tệp đối tượng
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)  # Tạo thư mục build nếu chưa tồn tại
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc riêng cho tệp testmock.c (do nó ở thư mục khác)
$(BUILD_DIR)/testmock.o: $(MAIN_DIR)/testmock.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc dọn dẹp
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN_DIR)/$(TARGET)

