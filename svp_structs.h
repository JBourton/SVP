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
    double* vectorData;
} Vector;


Vector* declareVector(int dimension, double* vectorInputs);
void cleanupVector(Vector* vector);

// Basis matrix functions
void display_basis_matrix(double** basis_matrix, int numVectors, int dimension);

#endif