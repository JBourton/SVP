// Setup 'include guard'
#ifndef LLL_H
#define LLL_H
void gram_schdmit(double** vectors, int numVectors, int dimension);
double find_magnitude(double* v, int dimension);
void subtract_vectors(double* v1, double* v2, int dimension, double* result);
double dot_product(double* v1, double* v2, int dimension);
void normalise(double* v, int dimension);
void project(double* v1, double* v2, int dimension);
#endif