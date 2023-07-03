CC=gcc
CFLAGS=-g -std=c99
TARGET=test_list
OBJS=list.o test_list.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.h list.c

test_list.o: test_list.c
	$(CC) $(CFLAGS) -c test_list.c

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)