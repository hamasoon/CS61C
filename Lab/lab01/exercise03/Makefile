CC=gcc
CFLAGS=-g -std=c99
TARGET=int_hello
OBJS=interactive_hello.o
SRC=interactive_hello.c

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)