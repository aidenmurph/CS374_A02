#ifndef __LOADMOVIES_H
#define __LOADMOVIES_H

#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

bool fileExists(char*);
char* largestFile(DIR*, struct dirent*, struct stat, off_t, char[256]);
char* smallestFile(DIR*, struct dirent*, struct stat, off_t, char[256]);

char* createNewDirectory();
void parseFiles(char*);

#endif