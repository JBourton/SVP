#include <stdio.h>
#include <stdlib.h>
#include "known_svp_test.h"

void test_svp_functionality(double** test_basis) {

}


// Initiate the testing proccess
int main() {
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

    // [DEBUG] Test values are properly assigned
    for (int i = 0; i < dim; ++i) {
        printf("[");
        for (int j = 0; j < dim; ++j) {
            printf("%f ", test_basis[i][j]);
        }
        printf("]\n");
    }

    // Test using specified basis
    // test_svp_functionality(test_basis);

    // Free used structure memory
    for (int i = 0; i < dim; ++i) {
        free(test_basis[i]);
    }
    free(test_basis);
    return 0;
}