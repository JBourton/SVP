// Setup 'include guard'
#ifndef SVP_APP_H
#define SVP_APP_H
double svp_enumaration(double** basis_matrix, int numVectors, int dimension);
void eunum_with_recursion(double** basis_matrix, int numVectors, int dimension, double* shortest_vector, double* working_vector, double shortest_length);
#endif