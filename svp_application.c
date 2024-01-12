#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "svp_structs.h"
#include "lll.h"

/*
Function purpose: To search all possible vectors in the solution space for the shortest possible vector
Function inputs:
- basis_matrix: The (lll-reduced) basis matrix
- numVectors: The number of vectors in the basis matrix
- dimension: The dimension of each vector
Function output: A numeric solution to the shortest vector problem
*/
double svp_enumaration(double** basis_matrix, int numVectors, int dimension) {
    double* shortest_vector = malloc(dimension * sizeof(double));
    double shortest_length = 0.0;
    double* working_vector = malloc(dimension * sizeof(double));

    // Free the memory used by the vectors
    free(working_vector);
    free(shortest_vector);

    return shortest_length;
}

/*
Function purpose: To apply pruning techniqeus to reduce the necessary compuatoin of the shortest vector
Function inputs:
- basis_matrix: The (lll-reduced) basis matrix
- numVectors: The number of vectors in the basis matrix
- dimension: The dimension of each vector
Function output: A solution to the shortest vector problem
*/
void eunum_with_recursion(double** basis_matrix, int numVectors, int dimension, double* shortest_vector, double* working_vector, double shortest_length) {

    // Looping through all possible combinations for coeficients form -8 to 8
    for (int i = -10; i <= 10; ++i) {
        for (int j = -10; j <= 10; ++j) {
            for (int k = -10; k <= 10; ++k) {
                
            }
        }
    }
}