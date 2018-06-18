CC = gcc
CFLAGS = -g -Wall
LINKS = -lncurses -lmenu -lform
SIGWINCH = --enable-sigwinch
TARGET = todo
SRC_FILES = $(wildcard *.c)
OBJS = ${SRC_FILES:.c=.o}

all:
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	$(CC) $(CFLAGS) $(LINKS) $(OBJS) -o $(TARGET)

debug:
	$(CC) $(CFLAGS) -g -c $(SRC_FILES)
	$(CC) $(CFLAGS) -g $(LINKS) $(OBJS) -o $(TARGET)

sigwinch:
	$(CC) $(CFLAGS) $(SIGWINCH) -g -c $(SRC_FILES)
	$(CC) $(CFLAGS) -g $(LINKS) $(OBJS) -o $(TARGET)

clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
