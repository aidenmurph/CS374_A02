/*
* Name: Aiden Murphy
* Student Number: 934475534
* CS374: Operating Systems 1
* Assignment 2: Files and Directories
* Due Date: 04/17/2024
* Description: Depending on user input, this program will load a file and display its contents
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

int main()
{
    bool again = false;
    int choice;
    do
    {
        printf("1. Select file to process\n2. Exit the program\nEnter a choice 1 or 2: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter an integer.\n");
            // Clear the input buffer
            while (getchar() != '\n');
            continue; // Restart the loop
        }
        else if(choice == 1)
        {
            printf("Which file you want to process?\n");
            printf("Enter 1 to pick the largest file\n");
            printf("Enter 2 to pick the smallest file\n");
            printf("Enter 3 to specify the name of a file\n");
            printf("Enter a choice from 1 to 3: ");
            int fileChoice;
            
            scanf("%d", &fileChoice);
            again = false;
        }
        else if(choice == 2)
        {
            printf("Exiting the program\n");
            again = false;
        }
        else
        {
            printf("Invalid choice; please try again.\n");
            again = true;
        }
    } while (again);
    return 0;
}