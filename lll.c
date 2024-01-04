#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lll.h"
#include "svp_structs.h"

/*
Function purpose: Perform the dot product on 2 vectors
Function inputs: 
- 2 vectors to perform the dot product
- dimension of those vectors
Function output: An array representing the dot product of the 2 vectors
*/ 
double dot_product(double *v1, double *v2, int dimension) {
    double dp = 0;
    for (int i=0; i<dimension; ++i) {
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
    for (int i=0;i<dimension;++i) {
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
Function purpose: Calculate the projection of one vector onto another one
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors
Function output: An array representing the vector projection of v1 onto v2
*/
double* minus_project(double* v1, double* v2, int dimension) {
    // Setup return vector
    double* project_v = malloc(dimension * sizeof(double));
    for (int i = 0; i < dimension; ++i) {
        project_v[i] = 0;
    }
    // projection of v1 onto v2 = ((v1 dot v2) / (v2 mangitude)^2) * v2, which is applied below
    
    // First, we find v1 dot v2
    double dp_result = dot_product(v1, v2, dimension);

    // Then we find the square of the magnitude of v2
    double mag_sq = find_magnitude(v2, dimension);
    mag_sq *= mag_sq;
    
    // Next, we divide those 2 values for each dimension
    if (mag_sq != 0) {
       double proj_fac = dp_result / mag_sq;
       printf("Projection factor: %f\n", proj_fac);
        for (int i = 0; i < dimension; ++i) {
            // The projection factor is then multiplied by each component
            double projection = proj_fac * v2[i];
            project_v[i] += projection;
        } 
    } else {
        // Prevent /0 error
        printf("Error, v2 has magnitude 0");
        free(project_v);
        return 0;
    }
    return project_v; 
}

/*
Function purpose: To calculate the size 
*/
double get_size(double* old_second, double* new_first, int dimension) {
    // Calculate the size using mod((b1 x b0*) / (b0* x b0*))
    double numerator;
    double denominator;
    double v_size;

    numerator = dot_product(old_second, new_first, dimension);
    denominator = find_magnitude(new_first, dimension);
    denominator *= denominator;

    if (denominator != 0) {
        v_size = numerator / denominator;
        v_size = fabs(v_size);
    } else {
        // Note: here an error has occured due to /0 so should deal with it
        return 0;
    }
    return v_size;
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

    // The first part of Gram-Schmidt involves setting u1 = v1
    U[0] = vectors[0];

    // Next, we apply the minus_project function, subtracting each repsective component from its projection
    // Equation: uk = vk - sum(i=1 to k-1) of vk projecting onto ui, where k is the vector number
    for (int k = 1; k < numVectors; ++k) {
        // For every vector in the 2d array of vectors
        U[k] = vectors[k];
        // Calculate the sums of the projection vectors from 1 to k-1
        double* total_projection = malloc(dimension * sizeof(double));
        // Initialse to 0
        for (int i = 0; i < dimension; ++i) {
            total_projection[i] = 0;
        }
        // Note: v1 is vk and v2 is ui
        for (int i = 0; i < k; ++i) {  
            // Calculate one of the prjections
            double* row_projection = minus_project(vectors[k], U[i], dimension);

            // Print the contents of row_projection
            for (int j = 0; j < dimension; ++j) {
                printf("%f ", row_projection[j]);
            }
            printf("\n");

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
    /*
    // Finally, normalise the restulting U-matrix
    for (int i = 0; i < numVectors; ++i) {
        double* norm_u = normalise(U[i], dimension);
        if (norm_u != NULL) {
            for (int j = 0; j < dimension; ++j) {
                U[i][j] = norm_u[j];
            }
            free(norm_u);
        }
    }
    */
    return U;
}

double** lll_algorithm(double** vectors, int numVectors, int dimension) {
    int k = 1;

    // Apply Gram Schmidt proccess
    double** Orthog_Basis;
    Orthog_Basis = gram_schdmit(vectors, numVectors, dimension);
    display_basis_matrix(Orthog_Basis, numVectors, dimension);

    //while (k <= numVectors) {
    //    for (int j=k-1; j>=0; --j) {
            // if not size_condition(i,j):
            // math stuff, update gram schmidt
    //    }
        // Check lovasz condition
        // if true, incremenet k
        // else, perform swap, update gram schmidt and find new k-value
    //}
    // return reduced basis
}