CC=gcc
CFLAGS=-g -std=c99
TARGET=test_ll_cycle
OBJS=ll_cycle.o test_ll_cycle.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

ll_cycle.o: ll_cycle.c ll_cycle.h
	$(CC) $(CFLAGS) -c ll_cycle.h ll_cycle.c

test_ll_cycle.o: test_ll_cycle.c
	$(CC) $(CFLAGS) -c test_ll_cycle.c

clean:
	rm -f $(OBJS) $(TARGET)

run:
	./$(TARGET)