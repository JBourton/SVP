#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "svp_structs.h"
#include "lll.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    // Take vector inputs for the basis from the command line
    if (argc < 2) {
        printf("Input the basis in the form: %s [v1] [v2] ... [vn]\n", argv[0]);
        return 0;
    }

    int open_brackets = 0;
    int closing_brackets = 0;

    // Make 1 big string from all the command line arguments
    size_t input_length = 0;

    // Check number of opening and closing brackets match
    for (int i=1; i<argc; i++) {
        if (strncmp(argv[i],"[", 1) == 0) {
            open_brackets += 1;
        }
        size_t input_item = strlen(argv[i]);
        input_length += input_item + 1;
        if (input_item > 0 && argv[i][input_item- 1] == ']') {
            closing_brackets += 1;
        }
    }
    if (open_brackets != closing_brackets) {
        printf("[INPUT ERROR] Number of openinig and closing brackets do not match\n");
        return 0;
    }

    // Assign dynamic memory to the string containing all the inputs
    char *mega_input = (char *)malloc(input_length);
    if (mega_input == NULL) {
        printf("[MEMORY ALLOCATION ERROR]\n");
        return 0;
    }

    // Put the inividaul commandl ine arguments into a single string
    for (int i = 1; i < argc; ++i) {
        strcat(mega_input, argv[i]);
        if (i < argc - 1) {
            strcat(mega_input, " ");
        }
    }
    printf("Concatenated String: %s\n", mega_input);



    free(mega_input);

    // Also need to validate instances where brackets could match count but be wrong e.g. []5[[]-]


    int numVectors;
    int dimension;
    printf("Enter the number of vectors: ");
    scanf("%d", &numVectors);
    printf("Enter the dimension: ");
    scanf("%d", &dimension);
    printf("\n");

    // Declare basis arrays (pre and post lll)  + dyanmically allocate memory
    double** basis_matrix;
    basis_matrix = (double**)malloc(numVectors * sizeof(double*));

    // Create specified number of vectors
    for (int i = 0; i < numVectors; ++i) {
        basis_matrix[i] = (double*)malloc(dimension * sizeof(double));
        printf("\n");
        printf("Input vector number %d:\n\n", i + 1);
        for (int j = 0; j < dimension; ++j) {
            printf("Input element %d\n", j + 1);
            scanf("%le", &basis_matrix[i][j]);
        }
    }
    printf("\n1. Original Basis Matrix\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Apply the lll algorithm to the basis
    lll_algorithm(basis_matrix, numVectors, dimension);
    printf("\n3. Final basis matrix after lll reduction:\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Free memory used up by the basis matrix and vectrs within
    for (int i = 0; i < numVectors; ++i) {
        free(basis_matrix[i]);
    }
    free(basis_matrix);
    return 0;
}