#include <stdio.h>
#include <stdlib.h>

void multiplication(int **matrixA, int size, int degree)
{
    int **matrixCopy = (int **)malloc(size * sizeof(int *)); // allocate memory for matrixCopy
    int **matrixB = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrixCopy[i] = (int *)malloc(size * sizeof(int)); // allocate columns for matrixCopy
        matrixB[i] = (int *)malloc(size * sizeof(int)); // allocate columns for matrixB
    }
    // copy matrix A to matrixB
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixB[i][j] = matrixA[i][j];
        }
    }

    // perform matrix multiplication here
    for (int exp = 1; exp < degree; exp++) // this will dictate the number of times matrix multiplication is performed
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                matrixCopy[row][col] = 0;
                for (int k = 0; k < size; k++)
                {
                    matrixCopy[row][col] += matrixA[row][k] * matrixB[k][col];
                }
            }
        }
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            matrixB[i][j] = matrixCopy[i][j]; // update matrixB with the result of matrix multiplication
        }
    }
    }

    // printMatrix(matrixCopy, size, degree); // print the resulting matrix
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(j == size -1){
                printf("%d", matrixB[i][j]);
            } 
            else{
            printf("%d ", matrixB[i][j]);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++)
    {
        free(matrixCopy[i]);
        free(matrixB[i]);
    }

    free(matrixB);
    free(matrixCopy); // free the memory allocated for matrixCopy
}

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "r"); // open file in read mode
    int size;
    int degree;

    if (fptr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    // if (fscanf(fptr, "%d", &size) != -1) // read size of matrix
    // {
    //     printf("Error reading matrix size\n");
    //     //fclose(fptr);
    //     return 1;
    // }

    fscanf(fptr, "%d", &size); // read size of matrix

    // allocate memory for matrix
    int **matrix = (int **)malloc(size * sizeof(int *));
    // need to allocate memory for the matrix size
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int)); // allocate memory for each row
    }

    // read matrix data
    for (int i = 0; i < size; i++)
    { // outer loop for each row
        for (int j = 0; j < size; j++)
        {                                      // inner loop for each element in the row
            fscanf(fptr, "%d", &matrix[i][j]); // read elements of the matrix
        }
    }

    // read the degree of the matrix
    fscanf(fptr, "%d", &degree);

    multiplication(matrix, size, degree); // call the multiplication function
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    fclose(fptr); // close the file after reading data
    return 0;
}