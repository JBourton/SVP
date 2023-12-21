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
        dp += v1[i] * v2[i];
    }
    return dp;
}

// Calculate the magnitude of a vector
double find_magnitude(double* v, int dimension) {
    double magnitude = 0;
    // Sum the squares
    for (int i=0;i<dimension;++i) {
        magnitude += v[i] * v[i];
    }
    // Root the result
    magnitude = sqrt(magnitude);
    return magnitude;
}

// Perform vector normalisaition
void normalise(double* v, int dimension) {
    double v_magnitude = 0;
    v_magnitude = find_magnitude(v, dimension);

    // Prevent /0 errors by testing for 0 mangitude
    if (v_magnitude != 0) {
        // Divide every component by its magnitude
        for (int i = 0; i < dimension; ++i) {
            v[i] /= v_magnitude;
        }
    }
}