#include "loadMovies.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


int chooseOutput();

int main()
{
    srandom(time(0));
    bool again = false;
    int choice;
    do
    {
        printf("1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n');
            continue; 
        }
        else if(choice == 1)
        {
            again = chooseOutput();
        }
        else if(choice == 2)
        {
            printf("\nExiting the program\n");
            again = false;
        }
        else
        {
            printf("Invalid choice; please try again.\n");
            again = true;
        }
    } while (again);
    printf("\nClosing program...\n");
    return 0;
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
                        char fileName[256];
                        scanf("%s", fileName);
                        printf("User specified file chosen\n");
                        printf("Run userFile(%s)\n", fileName);
                        if(!fileExists(fileName))
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
            char* newDir = createNewDirectory();
            printf("Chosen file name: %s\n", chosenFileName);
            parseFiles(newDir);
            return 0;
}