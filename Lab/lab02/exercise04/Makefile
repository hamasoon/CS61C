CC=gcc
CFLAGS=-g -std=c99
TARGET=vector_test
OBJS=vector.o vector_test.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.h vector.c

vector_test.o: vector.c
	$(CC) $(CFLAGS) -c vector_test.c

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)