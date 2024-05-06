/*
* Name: Aiden Murphy
* Student Number: 934475534
* CS374: Operating Systems 1
* Assignment 2: Files and Directories
* Due Date: 04/17/2024
* Description: Depending on user input, this program will load a file and display its contents
*/

#include "loadMovies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>

bool fileExists(char* fileName)
{
    FILE* file = fopen(fileName, "r");
    if(file != NULL)
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

char* largestFile(DIR* dir, struct dirent* entry, struct stat fileStats, off_t maxSize, char maxFileName[256])
{
    while((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }
        //debug print
        printf("Checking file %s\n", entry->d_name);
        //if the file has the right prefix and suffix,
        if(strncmp(entry->d_name, "movies_", 7) == 0 && strstr(entry->d_name, ".csv") != NULL)
        {
            //get the file size
            stat(entry->d_name, &fileStats);
            //if the file size is larger than the current max size, update the max size and file name
            if(fileStats.st_size > maxSize)
            {
                maxSize = fileStats.st_size;
                strcpy(maxFileName, entry->d_name);            
            }
        }
    }
    printf("Largest file is %s\n", maxFileName);
    return maxFileName;
}

char* smallestFile(DIR* dir, struct dirent* entry, struct stat fileStats, off_t minSize, char minFileName[256])
{
    while((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
        {
            continue;
        }
        //debug print
        printf("Checking file %s\n", entry->d_name);
        //if the file has the right prefix and suffix,
        if(strncmp(entry->d_name, "movies_", 7) == 0 && strstr(entry->d_name, ".csv") != NULL)
        {
            //get the file size
            stat(entry->d_name, &fileStats);
            //if the file size is larger than the current max size, update the max size and file name
            if(fileStats.st_size > minSize)
            {
                minSize = fileStats.st_size;
                strcpy(minFileName, entry->d_name);          
            }
        }
    }
    printf("Smallest file is %s\n", minFileName);
    return minFileName;
}

char* createNewDirectory()
{
    //get info for directory name
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    //printf("uid = %d\n", uid);
    //printf("pw_name = %s\n", pw->pw_name);
    long randomNum = (random() % 99999) + 1;
    char randomNumStr[4];
    sprintf(randomNumStr, "%ld", randomNum);
    //printf("randomNum = %ld\n", randomNum);

    //create the new directory name
    char newDirName[256]; 
    strcpy(newDirName, pw->pw_name);
    strcat(newDirName, ".movies.");
    strcat(newDirName, randomNumStr);
    //make directory
    mkdir(newDirName, 750);
    printf("Created new directory %s\n", newDirName);
    return newDirName;
}

void parseFiles(char* dirName, )
{
    DIR* dirIn = opendir(".");
    DIR* dirOut = opendir(dirName);
    struct list *movieList = createList();
    // readCSVFile(, movieList);


}

