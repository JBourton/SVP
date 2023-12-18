#include <stdio.h>
#include<stdlib.h>
#include "svp_structs.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    // Validate that least 1 vector is input
    if (argc < 2) {
        printf("Empty input. Please input vectors in form: %s [vector1]...[vectorN]\n", argv[0]);
        return 1;
    }

    // Dynamically allocate memory to input vectors
    int totalVectors = argc - 1;
    Vector* vectors = (Vector*)malloc(totalVectors * sizeof(Vector));

    // Validate successful memory allocation
    if (vectors == NULL) {
        printf("Unsucsessful memory allocation. Closing program...\n");
        return EXIT_FAILURE;
    }

    // As all vectors must be the same dimension, calculate dim of first vector and determine if the rest match up
    printf("First input vector: %s\n", argv[1]);
    // NOTE: NOW DECLARE THE VECTOR AND CALCULATE ITS DIMENSION

    // Free memory used up by vectors and the array they're stored in
     for (int i = 0; i < totalVectors; ++i) {
        cleanupVector(&vectors[i]);
    }
    free(vectors);
}