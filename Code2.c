/*
Drew franke
3131934
Lab session: Wednesday 1:00pm
Lab Assignment: 05-2
Description: program reads input from two text files for two matrices
and execute the functions for the following matrix manipulations:
1. Add Two Matrices: This function takes two matrices as input and returns their sum.
2. Multiply Two Matrices: This function takes two matrices as input and returns their product.
3. Transpose a Matrix: This function takes a matrix as input and returns its transpose.
4. Print a Matrix: This function takes a matrix as input and prints it in a user-friendly format.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// function prototypes
void addMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]);
void multiplyMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]);
void transposeMatrix(int matrix[SIZE][SIZE], int result[SIZE][SIZE]);
void printMatrix(int matrix[SIZE][SIZE]);
void readMatrixFromFile(const char* filename, int matrix[SIZE][SIZE]);

int main() {
    // declare matrices
    int m1[SIZE][SIZE];
    int m2[SIZE][SIZE];
    int result[SIZE][SIZE];

    // read matrices from files
    readMatrixFromFile("matrix1.txt", m1);
    readMatrixFromFile("matrix2.txt", m2);

    // add matrices
    printf("Sum of the matrices:\n");
    addMatrices(m1, m2, result);
    printMatrix(result);

    // multiply matrices
    printf("\nProduct of the matrices:\n");
    multiplyMatrices(m1, m2, result);
    printMatrix(result);

    // transpose first matrix
    printf("\nTranspose of the first matrix:\n");
    transposeMatrix(m1, result);
    printMatrix(result);

    return 0;
}

// add two matrices (function)
void addMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

// multiply two matrices (function)
void multiplyMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;  // initialize the result matrix element
            for (int k = 0; k < SIZE; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

// transpose a matrix (function)
void transposeMatrix(int matrix[SIZE][SIZE], int result[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// print a matrix (function)
void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// read a matrix from a file
void readMatrixFromFile(const char* filename, int matrix[SIZE][SIZE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);  // exit program if the file can't be opened
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                printf("Error: Invalid matrix format in file %s\n", filename);
                fclose(file);
                exit(1);  // exit if there's a format error
            }
        }
    }

    fclose(file);  // close the file after reading
}