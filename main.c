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

    // Declare basis arrays (pre and post lll)  + dyanmically allocate memory
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
    printf("\n1. Original Basis Matrix\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Apply the lll algorithm to the basis
    lll_algorithm(basis_matrix, numVectors, dimension);
    printf("\n3. Final basis matrix after lll reduction:\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Free memory used up by the basis matrix and vectrs within
    for (int i = 0; i < numVectors; ++i) {
        free(basis_matrix[i]);
    }
    free(basis_matrix);
    return 0;
}