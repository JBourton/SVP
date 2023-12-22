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
void minus_project(double* v1, double* v2, int dimension) {
    // projection of v1 onto v2 = ((v1 dot v2) / (v2 mangitude)^2) * v2, which is applied below
    
    // First, we find v1 dot v2
    double dp_result = dot_product(v1, v2, dimension);

    // Then we find the square of the magnitude of v2
    double mag_sq = find_magnitude(v2, dimension);
    mag_sq *= mag_sq;
    //printf("mag_sq is: %f\n", mag_sq);
    
    // Next, we divide those 2 values for each dimension
    if (mag_sq != 0) {
       double proj_fac = dp_result / mag_sq;
       //printf("projection factor: %f\n", proj_fac);
        for (int i = 0; i < dimension; ++i) { 
            //printf("v2[i]: %f\n", v2[i]);
            //printf("projection factor * v2[i]: %f\n", proj_fac * v2[i]);
            v1[i] -= (proj_fac * v2[i]);
        } 
    } else {
        // Prevent /0 error
        printf("Error, v1 has magnitude 0");
    }  
}

// Note: Figure out the best way to pass in the basis matrix, because there seems to be issues with it
// Perform Gram-Schmidt normalisation
void gram_schdmit(double** vectors, int numVectors, int dimension) {
    // Apply projection to every vector in the set
    for (int i = 0; i < numVectors; ++i) {
        // Apply the Gram-Schmidt process to the current vector
        for (int j = 0; j < i; ++j) {
            // Project the current vector onto the subspace spanned by previous vectors
            minus_project(vectors[i], vectors[j], dimension);
        }
          // Optionally, normalize the vector after orthogonalization
        double* norm_vector = normalise(vectors[i], dimension);

        // Replace the original vector with the normalized one
        if (norm_vector != NULL) {
            for (int k = 0; k < dimension; ++k) {
                vectors[i][k] = norm_vector[k];
            }
            free(norm_vector);
        }
    }
}