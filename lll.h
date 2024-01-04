// Setup 'include guard'
#ifndef LLL_H
#define LLL_H
// Note: Need linearly indepdent vectors for this, so may need validation later
double** gram_schdmit(double** vectors, int numVectors, int dimension, double* proj_factor);
double find_magnitude(double* v, int dimension);
void subtract_vectors(double* v1, double* v2, int dimension, double* result);
double dot_product(double* v1, double* v2, int dimension);
double* normalise(double* v, int dimension);
double* minus_project(double* v1, double* v2, int dimension, double* proj_factor);
#endif