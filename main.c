#include "loadMovies.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>





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