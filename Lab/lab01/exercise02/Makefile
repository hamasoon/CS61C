CC=gcc
CFLAGS=-g -std=c99
TARGET=hello
OBJS=hello.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)