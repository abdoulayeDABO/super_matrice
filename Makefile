CC = gcc
CFLAGS = -Wall
TARGET = supermat
SRCS = client.c supermat.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
