// Setup 'include gaurd'
#ifndef SVP_STRUCTS_H
#define SVP_STRUCTS_H
void display_basis_matrix(double** basis_matrix, int numVectors, int dimension);
double* multiply(double* v, double factor, int dimension);
double find_magnitude(double* v, int dimension);
double* normalise(double* v, int dimension);
double dot_product(double* v1, double* v2, int dimension);
#endif