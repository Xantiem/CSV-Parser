CC = gcc
CFLAGS = -Wall -Wextra -std=c23

# Output and source files
TARGET = csv_reader
C_SRC = main.c

# Default target to build the executable
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(BIN)
	$(CC) $(C_SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run:
	./$(TARGET)

