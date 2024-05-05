/*
* Name: Aiden Murphy
* Student Number: 934475534
* CS374: Operating Systems 1
* Assignment 1: Movies
* Due Date: 04/17/2024
* Description: Read a CSV file and process the data for the user to interact with
*/

----------------------- For Grading -----------------------

To compile:
gcc --std=c99 -o load loadMovies.c

To run:
./load

To clean:
make clean

---------------------- The Assignment ---------------------

Introduction

In this assignment, you'll write a program that will get you familiar with reading and writing files and directories on Unix.
Learning Outcomes

    Describe the API for different operations related to files (Module 3 MLO 3)
    Describe the API for different operations related to directories (Module 3 MLO 6)
    What are scopes and types of permissions associated with files and directories? (Module 3 MLO 7)

Instructions

Write a program that:

    Reads directory entries
    Finds a file in the current directory based on user specified criteria
    Reads and processes the data in the chosen file
    Creates a directory
    Creates new files in the newly created directory and writes processed data to these files

Format of the CSV File

Here is a sample file  whose format corresponds to the format of the CSV file your program will be tested with (this is exactly the same file format as in Assignment 1).

    The first row in the file contains the column headers, and not movie data.
    All other rows have the same format and no columns are missing in any row.
    Commas appear as delimiters between columns, but will not appear in the values of any columns.

This file has the following columns:

    Title
        This is a string with the movie title.
        e.g., Iron Man 2
    Year
        This is a 4 digit integer value for the year the movie was released
        e.g., 2010
    Languages
        The language or languages in which the movie was released.
        One or more string values that are always enclosed within []
        Multiple values are separated by semi-colons.
        e.g,
            [English;Portuguese;Spanish]
            [English;French]
            [English]
        You can assume that the maximum number of languages any movie can be released in is 5.
        You can assume that the maximum length of a language string is 20 characters.
    Rating Value
        A number between 1 and 10 (inclusive of both 1 and 10)
        It can be an integer or a double with one digit after the decimal point
        e.g.,
            5
            8.7
