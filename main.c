#include <stdio.h>
#include<stdlib.h>
#include "svp_structs.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    // Validation to ensure at least 1 vector is input
    if (argc < 2) {
        printf("Invalid input, please enter in form: %s [vector1]...[vectorN]\n", argv[0]);
        return 1;
    }

    int totalVectors = argc - 1;
}