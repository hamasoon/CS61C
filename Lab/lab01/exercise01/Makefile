CC=gcc
CFLAGS=-g -Wall -std=c99
TARGET=eccentric
OBJS=eccentric.o
 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

eccentric.o : eccentric.c
	$(CC) $(CFLAGS) -c eccentric.c

clean:	
	rm $(OBJS) $(TARGET)

run:
	./eccentric