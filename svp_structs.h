// Define lattice & vector structures here
// Link with #include "structures.h" in .c files that use the defined structures

// Setup include gaurd
#ifndef SVP_STRUCTS_H
#define SVP_STRUCTS_H

// Define structure to represent vectors
typedef struct {
    // Could just ask the user to input the dimension and git rid of this
    int dimension;
    // A dynamic decimal array of vectors that span the vector space
    // Note: These should be linearly independent, so validation should be performed
    // These vectors should also have the same dimension
    float* basis;
} Vector;

// Funciton prototypes for operations with vectors
// Perform Gram-Schmidt orthogonalisation
// double gsOrthog();
double euclideanNorm(Vector shortestVector);
void cleanupVector(Vector* vector);

// Define lattice structures where SVP will be undertaken
typedef struct {
    int vectorCount;

    // Point to the array containing vectors in the lattice
    Vector* vectorArray;
} Lattice;

// Function prototypes for lattice-based operations

#endif