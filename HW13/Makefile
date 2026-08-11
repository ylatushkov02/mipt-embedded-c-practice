CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -O2
TARGET  = report
OBJS    = main.o temp_functions.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c temp_functions.h
	$(CC) $(CFLAGS) -c main.c

temp_functions.o: temp_functions.c temp_functions.h
	$(CC) $(CFLAGS) -c temp_functions.c

clean:
	rm -f $(OBJS) $(TARGET)
