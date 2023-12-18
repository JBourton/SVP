#include<stdlib.h>
#include <stdio.h>
#include "svp_structs.h"
// Implmentations for the functions described in svp_structs.h will be written here

// Function to find the euclidean norm of the shortest vector
// double euclideanNorm(Vector shortestVector) {}

void declareVector(char* userVector) {
    printf("User vector is: ");
    printf(userVector);
}

// Function to cleanup the memory of a vector
void cleanupVector(Vector* vector) {
    free(vector->vectorData);
}