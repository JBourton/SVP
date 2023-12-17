// Define lattice & vector structures here
// Link with #include "structures.h" in .c files that use the defined structures

// Setup include gaurd
#ifndef SVP_STRUCTS_H
#define SVP_STRUCTS_H

// Define structure to represent vectors
typedef struct {
    int dimension;
    int vectorRows;
} Vector;

// Funciton prototypes for operations with vectors
// double euclideanDist()//basis vectors);

// Define lattice structures where SVP will be undertaken
typedef struct {
    int vectorCount;

    // Point to the array containing vectorsp resent in the lattice
    Vector* vectorArray;
} Lattice;

// Function prototypes for lattice-based operations

#endif