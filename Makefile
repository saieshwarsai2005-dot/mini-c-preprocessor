CC = gcc
CFLAGS = -Wall -Wextra
TARGET = mypreprocessor
SRCS = mypreprocessor.c cmtremove.c file_inclusion.c macro_handler.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) *.i
