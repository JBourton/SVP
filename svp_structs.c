#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "svp_structs.h"

// This file contains basic functions to be performed on the basis matrix
// and the vectors within it

/*
Function purpose: To print the basis
Function inputs: 
- Basis matrix, 'basis_matrix', containing all the vectors in the basis
- The number of vectors in the basis 'num_vectors'
- The dimension of each vector 'dimension'
Function output: The basis printed to the screen
*/
void display_basis_matrix(double** basis_matrix,
                            int numVectors,
                            int dimension) {
    printf("Basis Matrix:\n");
    for (int i = 0; i < numVectors; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%.2f ", basis_matrix[i][j]);
        }
        printf("\n");
    }
}

/*
Function purpose: To multiply a vector by a constant
Function inputs:
- The vector to multiply, 'v'
- The factor by which to multiply the vector, 'factor'
- The dimension of the vector, 'dimension'
Function output: A vector reprresenting the product of the vector an the constant
*/
double* multiply(double* v, int factor, int dimension) {
    double* product = malloc(dimension * sizeof(double));
    for (int i = 0; i < dimension; ++i) {
        product[i] = v[i] * factor;
    }
    return product;
}

/*
Function purpose: Perform the dot product on 2 vectors
Function inputs: 
- 2 vectors to perform the dot product
- dimension of those vectors
Function output: An array representing the dot product of the 2 vectors
*/ 
double dot_product(double *v1, double *v2, int dimension) {
    double dp = 0;
    for (int i = 0; i < dimension; ++i) {
        // Multiply consecutve rows
        dp += (v1[i] * v2[i]);
    }
    return dp;
}

/*
Function purpose: To calculate the magnitude of a vector
Function inputs: 
- The vector for which to claculate the magnitude
- The dimension of that vector
Function output: The magnitude of that vector, as a decimal
*/
double find_magnitude(double* v, int dimension) {
    double mangitude = 0;
    // Sum the squares
    for (int i = 0; i < dimension; ++i) {
        mangitude += (v[i] * v[i]);
    }
    // Root the result
    mangitude = sqrt(mangitude);
    return mangitude;
}

/*
Function purpose: Perform vector normalisaition
Function inputs:
- The vector to normalise
- The dimension of that vector
Function output: An array represnting the normalised version of the input vector
*/
double* normalise(double* v, int dimension) {
    // Dynamically allocate memoery to normalised vector
    double* norm_v = malloc(dimension * sizeof(double));
    double v_magnitude = 0;

    if (norm_v != NULL) {
        v_magnitude = find_magnitude(v, dimension);

        // Prevent /0 errors by testing for 0 mangitude
        if (v_magnitude != 0) {
            // Divide every component by its magnitude
            for (int i = 0; i < dimension; ++i) {
                norm_v[i] = v[i] / v_magnitude;
            }
        }
    } else {
        printf("Error, memory not available to allocate");
        return NULL;
    }
    return norm_v;
}

/*
Function purpose: To swap 2 vectors in a matrix
Funciton inputs:
- Basis matrix, 'basis_matrix', containing all the vectors in the basis
- The dimension of each vector 'dimension'
- The position of the vectors to swap, 'pos1/2'
Funciton autput: The modified basis matrix with the swap performed
*/
void swap_vectors(double** basis_matrix, int dimension, int pos1, int pos2) {
    // First, declare a temp varaible
    double* temp_vector = (double*)malloc(dimension * sizeof(double));

    memcpy(temp_vector, basis_matrix[pos1], dimension * sizeof(double));
    memcpy(basis_matrix[pos1], basis_matrix[pos2], dimension * sizeof(double));
    memcpy(basis_matrix[pos2], temp_vector, dimension * sizeof(double));

    free(temp_vector);
}

void free_structs_mem(double **basis_matrix,
                      int num_vectors,
                      char *mega_input) {
    if (mega_input != NULL) {
        free(mega_input);
    }
    for (int i = 0; i < num_vectors; ++i) {
        free(basis_matrix[i]);
    }
    free(basis_matrix);
}

/*
Function purpose: To find the shortest basis vector
Function inputs:
- basis_matrix: The (lll-reduced) basis matrix
- numVectors: The number of vectors in the basis matrix
- dimension: The dimension of each vector
Function output: A numeric value for shortest distance
*/
double find_shortest_v(double** basis_matrix, int numVectors, int dimension) {
    // Find the magnitude of the first basis vector as a baseline
    double shortest_dist = find_magnitude(basis_matrix[0], dimension);
    for (int i = 1; i < numVectors; i++) {
        double current_length = find_magnitude(basis_matrix[i], dimension);
        if (current_length < shortest_dist || shortest_dist == 0) {
            shortest_dist = current_length;
        }
    }
    return shortest_dist;
}
