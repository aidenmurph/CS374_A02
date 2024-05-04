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


bool fileExists()
{
    return false;
}

int chooseOutput()
{
    DIR* dir = opendir(".");
    struct dirent* entry;
    struct stat fileStats;
    off_t chosenSize = -1;
    char chosenFileName[256];
    int fileChoice;
            do
            {
                printf("\nWhich file you want to process?\n");
                printf("Enter 1 to pick the largest file\n");
                printf("Enter 2 to pick the smallest file\n");
                printf("Enter 3 to specify the name of a file\n");
                printf("Enter a choice from 1 to 3: ");
                if (scanf("%d", &fileChoice) != 1)
                {
                    printf("\nInvalid input. Please enter an integer.\n");
                    while (getchar() != '\n');
                    continue;
                }
                switch(fileChoice)
                {
                    case 1:
                        printf("\nLargest file chosen\n");
                        printf("Run largestFile()\n");
                        largestFile(dir, entry, fileStats, chosenSize, chosenFileName);
                        break;
                    case 2:
                        printf("\nSmallest file chosen\n");
                        printf("Run smallestFile()\n");
                        smallestFile(dir, entry, fileStats, chosenSize, chosenFileName);
                        break;
                    case 3:
                        printf("\nEnter the complete file name: ");
                        char fileName[100];
                        scanf("%s", fileName);
                        printf("User specified file chosen\n");
                        printf("Run userFile(%s)\n", fileName);
                        if(!fileExists())
                        {
                            printf("File does not exist, please try again\n");
                            fileChoice = 0;
                        }
                        break;
                    default:
                        printf("\nInvalid choice; please try again.\n");
                        break;
                }
            } while (fileChoice < 1 || fileChoice > 3);
            return 0;
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
