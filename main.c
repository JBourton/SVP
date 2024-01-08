#include <stdio.h>
#include <stdlib.h>
#include "svp_structs.h"
#include "lll.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    int numVectors;
    int dimension;
    printf("Enter the number of vectors: ");
    scanf("%d", &numVectors);
    printf("Enter the dimension: ");
    scanf("%d", &dimension);
    printf("\n");

    // Declare an array to hold the vectors + dyanmically allocate memory
    double** basis_matrix;
    basis_matrix = (double**)malloc(numVectors * sizeof(double*));

    // Create specified number of vectors
    for (int i = 0; i < numVectors; ++i) {
        basis_matrix[i] = (double*)malloc(dimension * sizeof(double));
        printf("\n");
        printf("Input vector number %d:\n\n", i + 1);
        for (int j = 0; j < dimension; ++j) {
            printf("Input element %d\n", j + 1);
            scanf("%le", &basis_matrix[i][j]);
        }
    }
    printf("\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Create a copy of basis to hold result of lll algoritjm application
    double** lll_basis = malloc(numVectors * sizeof(double*));
    for (int i = 0; i < numVectors; ++i) {
        copy[i] = malloc(dimension * sizeof(double));
        memcpy(copy[i], basis_matrix[i], dimension * sizeof(double));
    }

    // Apply the lll algorithm to the basis
    basis_matrix = lll_algorithm(copy, numVectors, dimension);
    printf("Final basis matrix after lll reduction:\n");
    display_basis_matrix(copy, numVectors, dimension);
    printf("\n");

    // Free memory used up by basis matrices and vectors within
    for (int i = 0; i < numVectors; ++i) {
        free(basis_matrix[i]);
        free(lll_basis[i]);
    }
    free(basis_matrix);
    free(lll_basis);

    return 0;
}