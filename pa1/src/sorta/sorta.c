#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(char *stringArray[], int n)
{
    /*Write a program sorta that sorts and prints its arguments. sorta takes zero or more arguments,
sorts them lexicographically, and then prints each argument on its own line.*/
    char *temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(stringArray[j], stringArray[j + 1]) > 0)
            {
                temp = stringArray[j];
                stringArray[j] = stringArray[j + 1];
                stringArray[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        // %c
        printf("%s", stringArray[i]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    // argc represents the number of command-line arguments
    // char *argv[] contains the command-line arguments
    // reminder: argv is an array of pointers
    char **stringArray = malloc((argc - 1) * sizeof(char *));
    // char *stringArray[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        stringArray[i - 1] = argv[i];
    }
    bubbleSort(stringArray, argc - 1); // argv[1] is the first argument after the program name
    // argc - 1 because program name is first and not included in the argument count
    free(stringArray); // free the allocated memory
    return 0;
}