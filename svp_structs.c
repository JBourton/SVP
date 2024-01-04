#include<stdlib.h>
#include <stdio.h>
#include "svp_structs.h"

/*
Function purpose: To print the basis
Function inputs: 
- Basis matrix, 'basis_matrix', containing all the vectors in the basis
- The number of vectors in the basis 'num_vectors'
- The dimension of each vector 'dimension'
Function output: The basis printed to the screen
*/
void display_basis_matrix(double** basis_matrix, int numVectors, int dimension) {
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
double* multiply(double* v, double factor, int dimension) {
    double* product = malloc(dimension * sizeof(double));
    for (int i = 0; i < dimension; ++i) {
        product[i] = v[i] * factor;
    }
    return product;
}