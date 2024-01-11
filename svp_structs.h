// Setup 'include gaurd'
#ifndef SVP_STRUCTS_H
#define SVP_STRUCTS_H
void display_basis_matrix(double** basis_matrix, int numVectors, int dimension);
double* multiply(double* v, int factor, int dimension);
double find_magnitude(double* v, int dimension);
double* normalise(double* v, int dimension);
double dot_product(double* v1, double* v2, int dimension);
void swap_vectors(double** basis_matrix, int dimension, int pos1, int pos2);
void free_structs_mem(double ** basis_matrix, int num_vectors, char *mega_input);
#endif