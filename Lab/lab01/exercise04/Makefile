CC=gcc
CFLAGS=-g -std=c99
TARGET=segfault_ex
OBJS=segfault_ex.o
SRC=segfault_ex.c

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)