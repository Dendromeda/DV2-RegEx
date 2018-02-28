CC = gcc -std=c99
CFLAGS = -g -fno-omit-frame-pointer -Wall -Wextra

.PHONY: all
all: wordcount
wordcount: wordcount.o table-array.o
	$(CC) $(CFLAGS) -o $@ wordcount.o table-array.o

wordcount.o: wordcount.c wordcount.h
	$(CC) $(CFLAGS) -c wordcount.c

table-array.o: table-array.c table-array.h
	$(CC) $(CFLAGS) -c table-array.c

.PHONY: clean
clean:
	rm -fv *.o wordcount
