#include <stdio.h>
#include <stdlib.h>
#include "known_svp_test.h"
#include "lll.h"
#include "svp_application.h"
#include "svp_structs.h"
double svp_enumaration(double** basis_matrix, int numVectors, int dimension);

int test_svp_functionality() {
    // Specify a basis matrix for testing
    double** test_basis;
    // Change vector count/dimension as required
    int dim = 3;
    test_basis = (double**)malloc(dim * sizeof(double*));

    // Create specified number of vectors
    for (int i = 0; i < dim; ++i) {
        test_basis[i] = (double*)malloc(dim * sizeof(double));
        if (test_basis[i] == NULL) {
            printf("[MEMORY ALLOCATION ERROR]\n");
            return 0;
        }
    }

    // These are the test values to be copied to the basis
    // Currently the test is for lattice Dn - change as required
    double test_values[3][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}
    };

    // Save test values in testing basis
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            test_basis[i][j] = test_values[i][j];
        }
    }

    // Display testing basis
    printf("The basis used for testing is as follows:\n");
    display_basis_matrix(test_basis, dim, dim);
    printf("\n");
    printf("The known shortest vector in this lattice is 1\n");
    printf("The svp code outputs the following value:\n");

    // Test using specified basis
    svp_enumaration(test_basis, dim, dim);

    // Free used structure memory
    for (int i = 0; i < dim; ++i) {
        free(test_basis[i]);
    }
    free(test_basis);
}


// Initiate the testing proccess
int main() {
    return test_svp_functionality();
}
