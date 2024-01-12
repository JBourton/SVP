#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "svp_structs.h"
#include "lll.h"
// Pre-declare recursive function to be used later on
void eunum_with_recursion(double** basis_matrix, int numVectors, int dimension, int working_lvl, double* shortest_vector, double* working_vector, double* shortest_length);


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
    double shortest_length = DBL_MAX;
    double* working_vector = malloc(dimension * sizeof(double));
    if (shortest_vector == NULL || working_vector == NULL) {
        printf("[MEMORY ALLOCATION ERROR]\n");
        return 0;
    }

    // Kickstart the recursive enumaration of shortest vector caluclation
    eunum_with_recursion(basis_matrix, numVectors, dimension, 0, shortest_vector, working_vector, &shortest_length);
    // Free the memory used by the vectors
    free(working_vector);
    free(shortest_vector);

    printf("Reached the end of svp_enumaration and shortest_length is: %f\n", shortest_length);

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
void eunum_with_recursion(double** basis_matrix, int numVectors, int dimension, int working_lvl, double* shortest_vector, double* working_vector, double* shortest_length) {
    printf("[DEBUG] Working level: %d\n", working_lvl);
    printf("[DEBUG] Dimension is: %d\n", dimension);
    // If the chain has the conditoin recursion level = dimension (i.e. everyting all 3 dimensions have been explored), begin return
    if (working_lvl == dimension) {
        printf("[DEBUG] Working level == dimension");
        // Test the final vector for size
        double final_length = find_magnitude(working_vector, dimension);
        if (final_length < *shortest_length) {
            *shortest_length = final_length;

            // Update current value of the shortest vector
            for (int i = 0; i < dimension; ++i) {
                shortest_vector[i] = working_vector[i];
            }
        }
        // Move up a recursion level
        return;
    }

    // Explore every coeficients within the range -8 to 8
    for (int i=-8;i<=8;++i) {
        printf("[DEBUG] i is: %d\n", i);
        // Update value at current position for working vector with the coeficient multiled by the corresponding latice value
        working_vector[working_lvl] += i * basis_matrix[working_lvl][working_lvl];

        // Here, if the current working length is >= the shortest length already, backtracking can safely ocur and the branch can be skipped
        if (find_magnitude(working_vector, dimension) >= *shortest_length) {
            working_vector[working_lvl] -= i * basis_matrix[working_lvl][working_lvl];
            continue;
        }
        // Recursively explore + backtrack
        // working_lvl += 1;
        eunum_with_recursion(basis_matrix, numVectors, dimension, working_lvl+1, shortest_vector, working_vector, shortest_length);
        working_vector[working_lvl] -= i * basis_matrix[working_lvl][working_lvl];
    }
}