#include<stdlib.h>
#include <stdio.h>
#include "svp_structs.h"
// Implmentations for the functions described in svp_structs.h will be written here

// Function to find the euclidean norm of the shortest vector
// double euclideanNorm(Vector shortestVector) {}

Vector* declareVector(int dimension, double* vectorInputs) {
    // Attempt to dynamically assign memory to vectors
    Vector* vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        printf("Error, failed vector structure memory allocaiton\n");
        return NULL;
    }

    vector->dimension = dimension;

    // Allocate memory for the vector data
    vector->vectorData = malloc(sizeof(double) * dimension);
    if (vector->vectorData == NULL) {
        printf("Error, failed vector values memory allocation\n");
        free(vector); // Free allocated memory for Vector structure
        return NULL;
    }

    // Transfer user inputs into vector data
    for (int i = 0; i < dimension; ++i) {
        vector->vectorData[i] = vectorInputs[i];
    }

    return vector;
}

// Function to cleanup the memory of a vector
void cleanupVector(Vector* vector) {
    free(vector->vectorData);
}

void display_basis_matrix(double** basis_matrix, int numVectors, int dimension) {
    printf("Basis Matrix:\n");
    for (int i = 0; i < numVectors; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%.2f ", basis_matrix[i][j]);
        }
        printf("\n");
    }
}