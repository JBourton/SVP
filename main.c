#include <stdio.h>
#include<stdlib.h>
#include "svp_structs.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    int numVectors;
    int dimension;
    printf("Enter the number of vectors: ");
    scanf("%d", &numVectors);
    printf("Enter the dimension: ");
    scanf("%d", &dimension);
    printf("Number of vectors: %d, Dimension: %d\n", numVectors, dimension);

    // Declare an array to hold the vectors + dyanmically allocate memory
    Vector* vectors;
    vectors = malloc(sizeof(Vector) * numVectors);

    // Create specified number of vectors
    for (int i = 0; i < numVectors; ++i) {
        float vectorInputs[dimension];
        printf("Input vector number %d\n", i+1);
        for (int j = 0; j < dimension; ++j) {
            printf("Input element %d\n", j+1);
            scanf("%f", &vectorInputs[j]);
        }
        // Create vectors using the declareVector function by passing in user inputs for each vector
        vectors[i] = *declareVector(dimension, vectorInputs);
    }


    // Allocate memory for basis matrix
    // double basis_matrix[numVectors][dimension];
    double** basis_matrix = (double**)malloc(numVectors * sizeof(double*));
    for (int i = 0; i < numVectors; i++) {
        basis_matrix[i] = (double*)malloc(dimension * sizeof(double));
    }

    // Populate basis matrix
    for (int i = 0; i < numVectors; i++) {
        for (int j = 0; j < dimension; j++) {
        basis_matrix[i][j] = vectors[i].vectorData[j];
        }
    }

    // Print out the basis matrix populating with user-input values
    display_basis_matrix(basis_matrix, numVectors, dimension);

    // Free memory used up by basis matrix and vectors
    for (int i = 0; i < numVectors; ++i) {
        cleanupVector(&vectors[i]);
    }
    free(vectors);
    for (int i = 0; i < numVectors; i++) {
        free(basis_matrix[i]);
    }
    free(basis_matrix);
    return 0;
}