#include<stdlib.h>
#include <stdio.h>
#include "svp_structs.h"
// Implmentations for the functions described in svp_structs.h will be written here
void display_basis_matrix(double** basis_matrix, int numVectors, int dimension) {
    printf("Basis Matrix:\n");
    for (int i = 0; i < numVectors; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%.2f ", basis_matrix[i][j]);
        }
        printf("\n");
    }
}