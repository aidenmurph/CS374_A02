#ifndef __MOVIES_H
#define __MOVIES_H

//structs
struct list;
struct node;
struct movie;
//list functions
struct list* createList();
void appendList(struct list* movieList, struct movie* newMovie);
//movie list creation functions
struct movie* createMovie(char* title, int year, char* languages[], double rating);
void parseLanguages(char* unparsedLanguages, char* languages[]);
void readCSVFile(char* inputFile, struct list* movieList);
//memory management
void freeMovie(struct movie* movie);
void freeList(struct list* movieList);


#endif