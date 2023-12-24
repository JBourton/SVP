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

    // Apply Gram Schmidt proccess
    double** Orthog_Basis;
    Orthog_Basis = gram_schdmit(basis_matrix, numVectors, dimension);
    printf("\n");
    display_basis_matrix(Orthog_Basis, numVectors, dimension);

    double size = get_size(basis_matrix[1], Orthog_Basis[0], dimension);
    printf("Size is: %f\n", size);

    // Free memory used up by basis matrix and vectors
    for (int i = 0; i < numVectors; ++i) {
        free(basis_matrix[i]);
    }
    free(basis_matrix);
    return 0;
}