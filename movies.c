/*
 * This code was writen by me, Aiden Murphy, for Assignment 01 of this course.
 * I have augmented the code slightly to fit the function of the class. 
 * Citation: https://github.com/aidenmurph/CS374_Assignment01
 */

#include "loadMovies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//strdup wasn't working correctly so I had to create my own
char* strdup(const char* s)
{
    size_t len = strlen(s);
    char* new = malloc(len + 1);
    if (new == NULL) return NULL;
    strcpy(new, s);
    return new;
}

//structs for the linked list
struct list {
  struct node* head;
};

struct node {
  struct movie* movie;
  struct node* next;
};

//struct for the movies
struct movie {
    // string with movie title, no assumed max length
    char* title;
    //int, between 1900 and 2021
    int year;
    // array of strings, max five languages of 20 characters allowed each
    char* languages[5];
    //decimal or int, between 1 and 10
    double rating;
    //pointer to the next movie in the list
};

struct list* createList()
{
    struct list* list = malloc(sizeof(struct list));
    list->head = NULL;
    return list;
}

void appendList(struct list* movieList, struct movie* newMovie)
{
    //create a new node
    printf ("appendList\n" );
    struct node* newNode = malloc(sizeof(struct node));
    printf ("appendList: have node\n" );
    //add the movie to the node
    newNode->movie = newMovie;
    printf ("appendList: set movie\n" );
    struct node* curr = movieList->head;
    if ( curr == NULL )
    {
        printf ("appendList: curr is nul\n" );
        movieList->head = newNode;
        return;
    }
    while(curr->next)
    {
        printf ("appendList: in while \n" );
        curr = curr->next;
    }
    curr->next = newNode;
    free(curr);
    printf ("appendList: out\n" );
    return;
}

struct movie* createMovie(char* title, int year, char* languages[], double rating)
{
    printf ("Title %s year %i rating  %f\n" , title, year, rating );
    struct movie* newMovie = malloc(sizeof(struct movie));
    printf ("createMovie: 1\n" );
    newMovie->title = strdup(title);
    printf ("createMovie: 2\n" );
    newMovie->year = year;
    printf ("createMovie: 3\n" );
    for (int i = 0; i < 5; i++) 
    {
        printf ("createMovie: i = %d\n", i );
        if (languages[i] != NULL) 
        {
            newMovie->languages[i] = strdup(languages[i]);
        } else 
        {
            newMovie->languages[i] = NULL;
        }
    }
    printf ("createMovie: rating = %f\n", rating );
    newMovie->rating = rating;
    printf ("createMovie: out\n" );
    return newMovie;
}


void parseLanguages(char* unparsedLanguages, char* languages[])
{
    //get rid of brackets
    printf( "parseLanguage: %s\n", unparsedLanguages );
    unparsedLanguages++;
    //create first language token
    char* token = strtok(unparsedLanguages, ";");
    printf( "parseLanguage: token %s\n", token );
    int counter = 0;
    while (token != NULL && counter < 5) {
        printf( "parseLanguage: pre token %s\n", token );
        languages[counter] = token;
        counter++;
        // Find the next semicolon
        token = strtok(NULL, ";");
    printf( "parseLanguage: post token %s\n", token );
    }
    printf( "parseLanguage: outie \n" );
    return;
}

void readCSVFile(char* pFile)
{ 
    //create years array to track which years have been added
    int years[2021-1900] = {0};
    //line max
    const int LINE_MAX = 1024;
    FILE *fptr;
    // Open a file in read mode
    fptr = fopen(pFile, "r");
    //create line and skip header line
    char line[LINE_MAX]; 
    fgets(line, LINE_MAX, fptr); 
    const char delim[2] = ","; 

    //loop variables
    char* title;
    int year;
    int fileDescriptor;
    //read the file
    while (fgets(line, 1024 , fptr))
    {
         //parse the line
         char* dupLine = strdup( line );
         char* tokens[2];
         tokens[0] = strtok( dupLine, delim );
         tokens[1] = strtok( NULL, delim );
         title = tokens[0];
         year = atoi( tokens[ 1 ] );
         printf ("Title %s ; Year %i\n" , tokens[0], year);
        //check if the year has been added
        char yearFile[9];
        if (!years[year-1900])
        {
            years[year-1900] = 1;
            strcpy(yearFile, tokens[1]);
            strcat(yearFile, ".txt\n");
            // printf ("Year file %s\n" , yearFile);
            fileDescriptor = open(yearFile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP);
            //check file existence
            if (fileDescriptor == -1) {
            fprintf(stderr, "Error: Unable to open or create the file %s\n", yearFile);
            exit(EXIT_FAILURE);
            }
            //check file permissions
            if (fchmod(fileDescriptor, S_IRUSR | S_IWUSR | S_IRGRP) == -1) {
            perror("Error setting file permissions");
            close(fileDescriptor);
            exit(EXIT_FAILURE);
            }
            write(fileDescriptor, title, strlen(title));
        }
        else
        {

        }
    }
    //close file
    fclose(fptr);
    return;

}


void freeMovie(struct movie* movie)
{
    //need to do this because I used strdup
    free(movie->title);
    for (int i = 0; i < 5; i++)
    {
        if(movie->languages[i])
        {
            free(movie->languages[i]);
        }
    }
    //free movie
    free(movie);
    return;
}

void freeList(struct list* list)
{
    //starting at the head
    struct node* curr = list->head;
    //delete the all the nodes
    while (curr != NULL) {
        //store the next node before deleting the current one
        struct node* next = curr->next;
        //free movie as well
        freeMovie(curr->movie);
        free(curr);
        curr = next;
    }
    free(list);
}
