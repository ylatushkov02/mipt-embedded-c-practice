CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = temp_app
OBJS    = main.o temp_api.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c temp_api.h
	$(CC) $(CFLAGS) -c main.c

temp_api.o: temp_api.c temp_api.h
	$(CC) $(CFLAGS) -c temp_api.c

clean:
	rm -f $(OBJS) $(TARGET)
