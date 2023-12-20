// Define lattice & vector structures here
// Link with #include "structures.h" in .c files that use the defined structures

// Setup 'include gaurd'
#ifndef SVP_STRUCTS_H
#define SVP_STRUCTS_H

// Define structure to represent vectors
typedef struct {
    int dimension;
    // The actual vector
    // Note: These should be linearly independent, so validation should be performed
    // These vectors should also have the same dimension
    float* vectorData;
} Vector;

// Funciton prototypes for operations with vectors
// Perform Gram-Schmidt orthogonalisation
// double gsOrthog();
Vector* declareVector(int dimension, float* vectorInputs);
void cleanupVector(Vector* vector);

// Define lattice structures where SVP will be undertaken
typedef struct {
    int dimension;
    int vectorCount;

    // Point to the array containing vectors in the lattice
    Vector* vectorArray;
} Lattice;

// Function prototypes for lattice-based operations
Lattice* declareLattice(int dimension, int numVectors, vectors);

#endif