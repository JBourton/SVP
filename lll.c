#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "lll.h"
#include "svp_structs.h"

/*
Function purpose: To find the projection factor for application in Gram Schmidt and LLL
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors
Function output: A factor 'proj_factor' of type double
*/
double find_projection_fac(double* v1, double* v2, int dimension) {
    double proj_factor;

    // First, we find v1 dot v2
    double dp_result = dot_product(v1, v2, dimension);

    // Then we find the square of the magnitude of v2
    double mag_sq = find_magnitude(v2, dimension);
    mag_sq *= mag_sq;

    if (mag_sq != 0) {
        proj_factor = dp_result / mag_sq;
    } else {
        // Prevent /0 error
        proj_factor = 0;
        return 0;
    }

    return proj_factor;
}

/*
Function purpose: Calculate the projection of one vector onto another
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors 'dimension'
- Projection factor globabl variable 'proj_factor'
Function output: An array 'project_v' representing the vector projection of v1 onto v2
*/
double* minus_project(double* v1, double* v2, int dimension) {
    // Setup return vector
    double* project_v = malloc(dimension * sizeof(double));
    for (int i = 0; i < dimension; ++i) {
        project_v[i] = 0;
    }
    // projection of v1 onto v2 = ((v1 dot v2) / (v2 mangitude)^2) * v2
    double proj_factor = find_projection_fac(v1, v2, dimension);

    // Next, we divide those 2 values for each dimension
    for (int i = 0; i < dimension; ++i) {
        // The projection factor is then multiplied by each component
        double projection = proj_factor * v2[i];
        project_v[i] += projection;
    }
    return project_v;
}

/*
Function purpose: Perform Gram-Schmidt normalisation
Function inputs: 
- The basis matrix 'vectors'
- The number of vectors in hte basis matrix 'numVectors'
- The dimension of those vectors 'dimension'
Function output: A 2d array 'U' representing the orthogonal basis of the orginal basis matrix
*/
double** gram_schdmit(double** vectors, int numVectors, int dimension) {
    // Dynamically declare 2d array holding copy of basis matrix
    double** U = (double**)malloc(numVectors * sizeof(double*));
    for (int i = 0; i < numVectors; ++i) {
        U[i] = (double*)malloc(dimension * sizeof(double));
    }
    // Here, input vectos are copied ot a new array
    for (int i = 0; i < numVectors; ++i) {
         // This serves to also set u1 = v1
        for (int j = 0; j < dimension; ++j) {
            U[i][j] = vectors[i][j];
        }
    }

    /* Next, we apply the minus_project function, subtracting each repsective component from its projection
       Equation: uk = vk - sum(i=1 to k-1) of vk projecting onto ui, where k is the vector number */
    for (int k = 1; k < numVectors; ++k) {
        // For every vector in the 2d array of vectors

        // Calculate the sums of the projection vectors from 1 to k-1
        double* total_projection = malloc(dimension * sizeof(double));
        if (total_projection == NULL) {
            return 0;
        }
        // Initialse to 0
        for (int i = 0; i < dimension; ++i) {
            total_projection[i] = 0;
        }

        // Note: v1 is vk and v2 is ui
        for (int i = 0; i < k; ++i) {
            // Calculate one of the prjections
            double* row_projection = minus_project(U[k], U[i], dimension);
            // Add it to the running total
            for (int j = 0; j < dimension; ++j) {
                total_projection[j] += row_projection[j];
            }
            free(row_projection);
        }

        // Subtract the sum of the projections form each row
        for (int i = 0; i < dimension; ++i) {
            U[k][i] -= total_projection[i];
        }
        free(total_projection);
    }
    return U;
}

/*
Function purpose: To calculate whether the basis meets the lovasz condition
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors
- The Gram Schmidt coeffcient 'gs_coefficient'
Function output: A boolean int (1/0)
*/
int lovasz_check(double* v1, double* v2, int dimension, double gs_coefficient) {
    // vk is the mangitude of the kth vector in the basis matrix
    double vk = find_magnitude(v1, dimension);
    vk = pow(vk, 2);
    double vk_minus_one = find_magnitude(v2, dimension);
    vk_minus_one = pow(vk_minus_one, 2);

    // This will be multipleid by the (k-1)th vector magnitude for compairson
    double lovasz_multiplier = 0.75 - pow(gs_coefficient, 2);
    lovasz_multiplier *= vk_minus_one;

    return (vk >= lovasz_multiplier);
}

/*
Funtion purpose: To apply the LLL algorithm on a basis matrix
Function inputs:
- The basis matrix 'vectors'
- The number of vectors in the basis matrix 'numVectors'
- The dimenson of each of those vecors, 'dimension'
Function output: The recued basis matrix
*/
void lll_algorithm(double** vectors, int numVectors, int dimension) {
    // proj_factor tracks current projection factor for size condition check
    int rounded_proj_factor;
    double size;
    int k = 1;

    // Apply Gram Schmidt proccess
    double** Orthog_Basis;
    Orthog_Basis = gram_schdmit(vectors, numVectors, dimension);

    while (k < numVectors) {
        for (int j = k-1; j >= 0; --j) {
            // Check size condition
            size = find_projection_fac(vectors[k], Orthog_Basis[j], dimension);
            if (size > 0.5) {
                // Apply vk = vk - proj_factor * bj
                rounded_proj_factor = round(size);
                double* GS_Coefficient_Vector = multiply(
                    vectors[j], rounded_proj_factor, dimension);

                for (int i = 0; i < dimension; ++i) {
                    vectors[k][i] -= GS_Coefficient_Vector[i];
                }

                free(GS_Coefficient_Vector);
                GS_Coefficient_Vector = NULL;
                // Update Gram-Shmit again
                // Free memory used by orthogonol basis
                for (int i = 0; i < numVectors; ++i) {
                    free(Orthog_Basis[i]);
                }
                free(Orthog_Basis);
                Orthog_Basis = gram_schdmit(vectors, numVectors, dimension);
            }
        }
        // Increment k by 1 if lovasz condition True
        size = find_projection_fac(vectors[k], Orthog_Basis[k-1], dimension);
        rounded_proj_factor = round(size);
        if (lovasz_check(Orthog_Basis[k], Orthog_Basis[k-1],
            dimension, rounded_proj_factor)) {
            k += 1;
        } else {
            // Swap vectors[k] with vectors[k-1]
            swap_vectors(vectors, dimension, k, k-1);

            // Update Gram Schmidt
            // Free memory used up by orthogonol basis
            for (int i = 0; i < numVectors; ++i) {
                free(Orthog_Basis[i]);
            }
            free(Orthog_Basis);
            Orthog_Basis = gram_schdmit(vectors, numVectors, dimension);

            // Set k = to the maxo f k-1 and 1
            k = fmax(k - 1, 1);
            }
    }

    // Free memory used up by orthogonol basis
    for (int i = 0; i < numVectors; ++i) {
        free(Orthog_Basis[i]);
    }
    free(Orthog_Basis);
}
