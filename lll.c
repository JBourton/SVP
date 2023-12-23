#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lll.h"
#include "svp_structs.h"

// Perform the dot product on 2 vectors
double dot_product(double *v1, double *v2, int dimension) {
    double dp = 0;
    for (int i=0; i<dimension; ++i) {
        // Multiply consecutve rows
        dp += (v1[i] * v2[i]);
    }
    return dp;
}

// Calculate the magnitude of a vector
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

// Perform vector normalisaition
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
        // Deal with inablity to allocate
        printf("Error, memory not available to allocate");    
    }  
    return norm_v;
}

// Calculate the projection of one vector onto another one
double* minus_project(double* v1, double* v2, int dimension) {
    double* project_v = malloc(dimension * sizeof(double));
    // projection of v1 onto v2 = ((v1 dot v2) / (v2 mangitude)^2) * v2, which is applied below
    
    // First, we find v1 dot v2
    double dp_result = dot_product(v1, v2, dimension);
    printf("Dot product result: %f\n", dp_result);

    // Then we find the square of the magnitude of v2
    double mag_sq = find_magnitude(v2, dimension);
    mag_sq *= mag_sq;
    printf("mag_sq: %f\n", mag_sq);
    
    // Next, we divide those 2 values for each dimension
    if (mag_sq != 0) {
       double proj_fac = dp_result / mag_sq;
        for (int i = 0; i < dimension; ++i) {
            double projection = proj_fac * v2[i];
            // Subtract projection
            project_v[i] += projection;
        } 
    } else {
        // Prevent /0 error
        printf("Error, v1 has magnitude 0");
        return 0;
    }
    return project_v; 
}

// Perform Gram-Schmidt normalisation
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
        // INitialse to 0
        for (int i = 0; i < dimension; ++i) {
            total_projection[i] = 0;
        }
        printf("\nIn the first part of the loop\n");
        // Note: v1 is vk and v2 is ui
        for (int i = 0; i < k; ++i) {  
            // Calculate one of the prjections
            double* row_projection = minus_project(vectors[k], U[i], dimension);

            // Print the contents of row_projection
            printf("\nIn the second part of the loop\n");  
            printf("row_projection: ");
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
    return U;
}