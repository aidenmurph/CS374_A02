CC = gcc
CFLAGS = --std=c99 -g

all: load

load: main.c loadMovies.o movies.o
	$(CC) $(CFLAGS) main.c loadMovies.o movies.o -o load

loadMovies.o: loadMovies.c loadMovies.h
	$(CC) $(CFLAGS) -c loadMovies.c

movies.o: movies.c movies.h
	$(CC) $(CFLAGS) -c movies.c

clean:
	rm -f *.o load 