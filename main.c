#include <stdio.h>
#include<stdlib.h>
#include "svp_structs.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    int numVectors;
    int dimension;
    printf("Enter the number of vectors: ");
    scanf("%d", &numVectors);
    printf("Enter the dimension: ");
    scanf("%d", &dimension);
    printf("Number of vectors: %d, Dimension: %d\n", numVectors, dimension);

    // Declare an array to hold the vectors + dyanmically allocate memory
    Vector* vectors;
    vectors = malloc(sizeof(Vector) * numVectors);

    // Create specified number of vectors
    for (int i = 0; i < numVectors; ++i) {
        float vectorInputs[dimension];
        printf("Input vector number %d\n", i+1);
        for (int j = 0; j < dimension; ++j) {
            printf("Input element %d\n", j+1);
            scanf("%f", &vectorInputs[j]);
        }
        // Create vectors using the declareVector function by passing in user inputs for each vector
        vectors[i] = *declareVector(dimension, vectorInputs);
    }

    // Test access
    printf("Elements of the first vector:\n");
    Vector* chosenVector = &vectors[0];
    for (int i = 0; i < chosenVector->dimension; ++i) {
        printf("Element %d: %f\n", i + 1, chosenVector->vectorData[i]);
    }



    // Free memory used up by vectors and the array they're stored in
    // for (int i = 0; i < totalVectors; ++i) {
    //    cleanupVector(&vectors[i]);
    //}
    //free(vectors);
    return 0;
}