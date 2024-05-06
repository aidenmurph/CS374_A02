CC=gcc --std=c99 -g

all: load

load: main.c loadMovies.o  movies.o
	$(CC) main.c loadMovies.o movies.o -o load

loadMovies.o: loadMovies.c loadMovies.h
	$(CC) -c loadMovies.c

movies.: movies.c movies.h
	$(CC) -c movies.c

clean:
	rm -f *.o load 
