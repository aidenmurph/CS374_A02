CC=gcc --std=c99 -g

all: load

load: main.c loadMovies.o 
	$(CC) main.c loadMovies.o -o load

loadMovies.o: loadMovies.c loadMovies.h
	$(CC) -c loadMovies.c

clean:
	rm -f *.o load 
