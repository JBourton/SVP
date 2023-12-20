#include<stdlib.h>
#include <stdio.h>
#include "svp_structs.h"
// Implmentations for the functions described in svp_structs.h will be written here

// Function to find the euclidean norm of the shortest vector
// double euclideanNorm(Vector shortestVector) {}

Vector* declareVector(int dimension, float* vectorInputs) {
    // Attempt to dynamically assign memory to vectors
    Vector* vector = malloc(sizeof(Vector));
    if (vector == NULL) {
        printf("Error, failed vector structure memory allocaiton\n");
        return NULL;
    }

    vector->dimension = dimension;

    // Allocate memory for the vector data
    vector->vectorData = malloc(sizeof(float) * dimension);
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

Lattice* declareLattice(int dimension, int numVectors, Vector vectors) {
    // Attempt to dynamically assign memory to lattice structure
    Lattice* lattice = malloc(sizeof(Lattice));
    if (lattice == NULL) {
        printf("Error, failed lattice structure memory allocaiton\n");
        return NULL;
    }

    // Set fixed values
    lattice->dimensions = dimension;
    lattice->numBasisVectors = numVectors;

    // Assign memory too, and set, basis vectors in the lattice
    lattice->basisVectors = malloc(dimensions * numVectors * sizeof(double));
    if (lattice->basisVectors == NULL) {
        free(lattice);
        return NULL;
   }
   for (int i = 0; i < numVectors; ++i) {
     for (int j = 0; j < dimensions; ++j) {
       lattice->basisVectors[i * dimension + j] = vectors[i].vectorData[j];
     }
   }

    return lattice;
}

// Function to cleanup the memory of a vector
void cleanupVector(Vector* vector) {
    free(vector->vectorData);
}