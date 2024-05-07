/*
* Name: Aiden Murphy
* Student Number: 934475534
* CS374: Operating Systems 1
* Assignment 2: Files and Directories
* Due Date: 04/17/2024
* Description: Depending on user input, this program will load a file and display its contents
*/

#include "loadMovies.h"
#include "movies.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
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
        //printf("Checking file %s\n", entry->d_name);
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
        //printf("Checking file %s\n", entry->d_name);
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

char* createNewDirectory() {
    // Get info for directory name
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    long randomNum = (random() % 99999) + 1;
    char randomNumStr[6];
    sprintf(randomNumStr, "%ld", randomNum);

    // Create the new directory name
    char *newDirName = malloc(strlen(pw->pw_name) + strlen(randomNumStr) + 11); // Length of ".movies." + 1 for null terminator
    if (newDirName == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for directory name\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newDirName, pw->pw_name);
    strcat(newDirName, ".movies.");
    strcat(newDirName, randomNumStr);

    // Make directory
    if (mkdir(newDirName, 0750) != 0) {
        fprintf(stderr, "Error: Failed to create directory %s\n", newDirName);
        free(newDirName);
        exit(EXIT_FAILURE);
    }
    printf("Created new directory %s\n", newDirName);
    return newDirName;
}


void parseFiles(char* dirName, char* pFile)
{
    //create years array to track which years have been added
    int *years = NULL;
    int size = 0;

    // Open a file in read mode
    FILE *fptr;
    fptr = fopen(pFile, "r");

    //create line and skip header line
    char line[1024]; 
    fgets(line, 1024, fptr); 
    const char delim[2] = ","; 

    //loop variables
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
         year = atoi( tokens[ 1 ] );
         printf ("Title %s ; Year %i\n" , tokens[0], year);

        //create the year file name
        char yearFileName[10];
        strcpy(yearFileName, tokens[1]);
        strcat(yearFileName, ".txt");
        printf ("Year file %s\n" , yearFileName);

        //concat with the directory name
        char filePath[256];
        strcpy(filePath, "./");
        strcat(filePath, dirName);
        strcat(filePath, "/");
        strcat(filePath, yearFileName);
        printf ("Year file path %s\n" , filePath);

        //check if the year has been added
        bool added = false;
        for(int i = 0; i < size; i++)
        {
            if(years[i] == year)
            {
                FILE* of = fopen(filePath, "a");
                if (of == NULL) 
                {
                    fprintf(stderr, "Error opening file: %s\n", filePath);
                    fclose(fptr);
                    return;
                }
                fprintf(of, "%s\n", tokens[0]);
                fclose(of);
                added = true;
            }
        }
        if(!added)
        {
            FILE* of = fopen(filePath, "w");
            if (of == NULL) 
            {
                    fprintf(stderr, "Error opening file: %s\n", filePath);
                    fclose(fptr);
                    return;
            }
            fprintf(of, "%s\n", tokens[0]);
            fclose(of);
            size++;
            years = realloc(years, size * sizeof(int));
            years[size - 1] = year;

            //if year not found, add it to the array
                years = realloc(years, (size + 1) * sizeof(int));
                years[size] = year;
                size++;
                //create the file
                fileDescriptor = open(filePath, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP);
                //check file existence
                if (fileDescriptor == -1) {
                fprintf(stderr, "Error: Unable to open or create the file %s\n", filePath);
                exit(EXIT_FAILURE);
                }
                //check file permissions
                if (fchmod(fileDescriptor, S_IRUSR | S_IWUSR | S_IRGRP) == -1) {
                perror("Error setting file permissions");
                close(fileDescriptor);
                exit(EXIT_FAILURE);
                }
                write(fileDescriptor, tokens[0], strlen(tokens[0]));
        }
    }
    //close file
    fclose(fptr);
    //free mem
    free(years);

    return;
}

