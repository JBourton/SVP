// Setup 'include guard'
#ifndef LLL_H
#define LLL_H
// Note: Need linearly indepdent vectors for this, so may need validation later
double** gram_schdmit(double** vectors, int numVectors, int dimension, double* proj_factor);
void subtract_vectors(double* v1, double* v2, int dimension, double* result);
double* minus_project(double* v1, double* v2, int dimension, double* proj_factor);
int lovasz_check(double* v1, double* v2, int dimension, double gs_coefficient);
double find_projection_fac(double* v1, double* v2, int dimension);
#endif