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
Function purpose: Calculate the projection of one vector onto another
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors
Function output: An array representing the vector projection of v1 onto v2
*/
double* minus_project(double* v1, double* v2, int dimension, double* proj_factor) {
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
        *proj_factor = dp_result / mag_sq;
        //printf("Projection factor: %f\n", *proj_fac);
        for (int i = 0; i < dimension; ++i) {
            // The projection factor is then multiplied by each component
            double projection = *proj_factor * v2[i];
            project_v[i] += projection;
        } 
    } else {
        // Prevent /0 error
        printf("Error, v2 has magnitude 0");
        free(project_v);
        *proj_factor = 0;
        return 0;
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
double** gram_schdmit(double** vectors, int numVectors, int dimension, double* proj_factor) {
    // Dynamically declare 2d array holding copy of basis matrix
    double** U = (double**)malloc(numVectors * sizeof(double*));
    for (int i = 0; i < numVectors; ++i) {
        U[i] = (double*)malloc(dimension * sizeof(double));
    }

    // [DEBUG] Copy the input vectors to the new array
    for (int i = 0; i < numVectors; ++i) {
        for (int j = 0; j < dimension; ++j) {
            U[i][j] = vectors[i][j];
        }
    }

    // The first part of Gram-Schmidt involves setting u1 = v1
    //U[0] = vectors[0];

    /* Next, we apply the minus_project function, subtracting each repsective component from its projection
       Equation: uk = vk - sum(i=1 to k-1) of vk projecting onto ui, where k is the vector number */
    for (int k = 1; k < numVectors; ++k) {
        // For every vector in the 2d array of vectors
        //U[k] = vectors[k];
        // Calculate the sums of the projection vectors from 1 to k-1
        double* total_projection = malloc(dimension * sizeof(double));
        // Initialse to 0
        for (int i = 0; i < dimension; ++i) {
            total_projection[i] = 0;
        }
        // Note: v1 is vk and v2 is ui
        for (int i = 0; i < k; ++i) {  
            // Calculate one of the prjections
            double* row_projection = minus_project(U[k], U[i], dimension, proj_factor);

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

double** lll_algorithm(double** vectors, int numVectors, int dimension) {
    // proj_factor will track of the current projection factor for use in the size condition check
    double proj_factor;
    int k = 1;

    // Apply Gram Schmidt proccess
    double** Orthog_Basis;
    Orthog_Basis = gram_schdmit(vectors, numVectors, dimension, &proj_factor);
    display_basis_matrix(Orthog_Basis, numVectors, dimension);
    printf("Current projection factor: %f\n", proj_factor);
    printf("\n");

    while (k <= numVectors) {
        for (int j=k-1; j>=0; --j) {
            // Check size condition
            if (proj_factor > 0.5) {
                //  [DEBUG] Looks like vectors is being modified in the gram_schmidt funciton
                printf("[DEBUG] Original vector:");
                for (int y = 0; y < dimension; ++y) {
                    printf("%.2f ", vectors[k][y]);
                }
                printf("\n");

                // Math: vk = vk - proj_factor * bj 

                // Round down projection factor
                double rounded_proj_factor = floor(proj_factor);
                double* GS_Coefficient_Vector = multiply(vectors[j], rounded_proj_factor, dimension);

                printf("[DEBUG] Result of GS coefficient vector:");
                for (int y = 0; y < dimension; ++y) {
                    printf("%.2f ", GS_Coefficient_Vector[y]);
                }
                printf("\n");
                
                // here check it
                // int rounded_factor = (int)(proj_factor + 0.5);
                for (int i = 0; i < dimension; ++i) {
                    vectors[k][i] -= GS_Coefficient_Vector[i];
                    //vectors[k][i] -= rounded_factor -= GS_Coefficient_Vector[i];
                }


                free(GS_Coefficient_Vector);
                
                //  [DEBUG] Print the subtraction result
                printf("[DEBUG] Result of subtraction:");
                for (int y = 0; y < dimension; ++y) {
                    printf("%.2f ", vectors[k][y]);
                }
                printf("\n");

                display_basis_matrix(vectors, numVectors, dimension);
                printf("\n");
                // Progress: TEST THIS PART    
                // update gram schmidt         
            }
            // if not size_condition(i,j):
            // math stuff, update gram schmidt
        }
        k += 1;
        // Check lovasz condition
        // if true, incremenet k
        // else, perform swap, update gram schmidt and find new k-value
    }
    // return reduced basis
}