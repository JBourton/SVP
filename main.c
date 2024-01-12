#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "svp_structs.h"
#include "lll.h"
#include "command_line.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    // Take vector inputs for the basis from the command line
    if (argc < 2) {
        printf("Input the basis in the form: %s [v1] [v2] ... [vn]\n", argv[0]);
        return 0;
    }

    int numVectors;
    int dimension;
    
    // Check that there's an equal number of closing brackets compared to opening brackets
    if (check_brackets_match(argc, argv) == 1) {
        // Number of bracket sets = number of vectors
        numVectors = get_bracket_count(argc, argv);
        dimension = numVectors;
    } else {
        return 0;
    }

    // Declare basis arrays  + dyanmically allocate memory
    double** basis_matrix;
    basis_matrix = (double**)malloc(numVectors * sizeof(double*));

    // Create specified number of vectors
    for (int i = 0; i < numVectors; ++i) {
        basis_matrix[i] = (double*)malloc(dimension * sizeof(double));
        if (basis_matrix[i] == NULL) {
            printf("[MEMORY ALLOCATION ERROR]\n");
            return 0;
        }
    }

    // Assign dynamic memory to the string containing all the inputs
    size_t input_length = get_input_length(argc, argv);
    char *mega_input = (char *)malloc(input_length);
    if (mega_input == NULL) {
        printf("[MEMORY ALLOCATION ERROR]\n");
        free_structs_mem(basis_matrix, numVectors, mega_input);
        return 0;
    }
    // Put the inividaul command line arguments into a single string
    for (int i = 1; i < argc; ++i) {
        strcat(mega_input, argv[i]);
        if (i < argc - 1) {
            strcat(mega_input, " ");
        }
    }
    printf("Concatenated String: %s\n", mega_input);

    // Megastring index keeps track of what part of the command line input to process
    int megastring_index = 0;

    // Extract vectors within square brackets
    for (int i = 0; i < numVectors; i++) {
        if (mega_input[megastring_index] != '[') {
            printf("[INPUT ERROR] Missing opening bracket '['\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            return 0;
        }

        // Initialisie an empty substring to hold the curent vector
        char *individual_vector = (char *)malloc(input_length);
        if (individual_vector == NULL) {
            printf("[MEMORY ALLOCATION ERROR]\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            return 0;
        }
        individual_vector[0] = '[';
        individual_vector[1] = '\0';

        // Extract a substring containing everything between (and including) the next set of square brackets
        for (size_t j = 1; j < input_length && mega_input[j] != '\0'; ++j) {     
            // Append the next character in the masterstring to the current vector substring
            strncat(individual_vector, &mega_input[megastring_index + 1], 1);
            if (mega_input[megastring_index + 1] == '[') {
                // An opening bracket has been found before a closing one        
                printf("[INPUT ERROR] Misalignment of open brackets\n");
                free_structs_mem(basis_matrix, numVectors, mega_input);
                return 0;
            } else if (mega_input[megastring_index + 1] == ']') {
                // A closing bracket has been found, exit loop
                megastring_index += 1;
                break;
            } else {
                megastring_index += 1;
            }
        }

        
        size_t vector_len = strlen(individual_vector);
        if (vector_len > 0 && individual_vector[vector_len- 1] == ']') {
            // Add one to the index to account for the closing square bracket
            megastring_index += 1;
            
            // Add individual_vector to the vector structure
            printf("\n[DEBUG] Individual_Vector: %s\n", individual_vector);

            if (vector_len < 3) {
                printf("[INPUT ERROR] Empty vectors not allowed\n");
                free_structs_mem(basis_matrix, numVectors, mega_input);
                return 0;
            }

            // Create a substring holding the new vector without the brackets
            char* values = (char*)malloc(vector_len);
            if (values == NULL) {
                printf("[MEMORY ALLOCATION ERROR]\n");
                free_structs_mem(basis_matrix, numVectors, mega_input);
                return 0;
            }

            strncpy(values, individual_vector + 1, vector_len - 2);
            values[vector_len - 2] = '\0';

            printf("[DEBUG] values substring: %s\n", values);

            // Now extract each space-seperated value and attempt to convert to double to store in a vector
            // int substring_index = 0;
            //for (k=0; k<dimension; k++) {
                
                // Find from position 0 up until when a space occurs
                // Then try to convert to double
                // Finally, assing that value to the vector
                // can do basis_matrix[i][k] to access the right element
            //}






        } else {
            printf("[INPUT ERROR] Missing closing bracket ']'\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            return 0;
        }

        // Progress pointer to next vector
        if(i < numVectors-1) {
            if (mega_input[megastring_index] == ' ' && mega_input[megastring_index + 1] == '[') {
                megastring_index += 1;
            } else {
                printf("[INPUT ERROR] Each vector must be seperated with a singular space\n");
                free_structs_mem(basis_matrix, numVectors, mega_input);
                return 0;
            }
        } else {
            // deal with the case of [][] where i = numvectors-1
        }
        free(individual_vector);
    }

    // check exactly the right amount of vectors are create
    // If a space appears in the string, count that as one of the inputs
    // Also need to validate instances where brackets could match count but be wrong e.g. []5[[]-]

    printf("\n1. Original Basis Matrix\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Apply the lll algorithm to the basis
    lll_algorithm(basis_matrix, numVectors, dimension);
    printf("\n3. Final basis matrix after lll reduction:\n");
    display_basis_matrix(basis_matrix, numVectors, dimension);
    printf("\n");

    // Free memory used up by the basis matrix and vectrs within
    free_structs_mem(basis_matrix, numVectors, mega_input);
    return 0;
}