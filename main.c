#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/time.h>
#include "svp_structs.h"
#include "lll.h"
#include "command_line.h"

// Main should be able to receive an arbitary number of input vectors
int main(int argc, char *argv[]) {
    // [DEBUG] Clock code
    struct timeval start, end;
    long seconds, microseconds;
    gettimeofday(&start, NULL);

    // Take vector inputs for the basis from the command line
    if (argc < 2) {
        printf("Input the basis in the form: %s [v1] [v2] ... [vn]\n", argv[0]);
        return 0;
    }

    int numVectors;
    int dimension;
    // Check num closing brackets = num opening brackets
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
    char *temp_buffer_input = (char *)malloc(input_length * 2);
    if (mega_input == NULL || temp_buffer_input == NULL) {
        printf("[MEMORY ALLOCATION ERROR]\n");
        free_structs_mem(basis_matrix, numVectors, mega_input);
        free(temp_buffer_input);
        return 0;
    }
    mega_input[0] = '\0';

    // Put the inividaul command line arguments into a single string
    for (int i = 1; i < argc; ++i) {
        snprintf(temp_buffer_input, input_length * 2,
                "%s%s", mega_input, argv[i]);
        if (i < argc - 1) {
            snprintf(mega_input, input_length, "%s ", temp_buffer_input);
        } else {
            strncpy(mega_input, temp_buffer_input, input_length - 1);
            mega_input[input_length - 1] = '\0';
        }
    }
    free(temp_buffer_input);

    // Track what part of the command line input to process
    int megastring_index = 0;

    // Extract vectors within square brackets
    for (int i = 0; i < numVectors; i++) {
        if (mega_input[megastring_index] != '[') {
            printf("[INPUT ERROR] Missing opening bracket '['\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            return 0;
        }

        // Initialisie an empty substring to hold the curent vector
        char *individual_vector = (char *)malloc(input_length + 1);
        if (individual_vector == NULL) {
            printf("[MEMORY ALLOCATION ERROR]\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            return 0;
        }
        individual_vector[0] = '[';
        individual_vector[1] = '\0';

        // Extract a substring containing everything between
        // (and including) the next set of square brackets
        for (size_t j = 1; j < input_length &&
                 mega_input[j] != '\0'; ++j) {
            // Append next masterstring char to current vector substring
            strncat(individual_vector, &mega_input[megastring_index + 1], 1);
            if (mega_input[megastring_index + 1] == '[') {
                // Opening bracket found before a closing one
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
                free(values);
                return 0;
            }

            strncpy(values, individual_vector + 1, vector_len - 2);
            free(individual_vector);
            values[vector_len - 2] = '\0';

            // Extract each space-seperated value and attempt to
            // convert to double to store in a vector in the basis
            int pos = 0;
            double num;
            char* original_values = values;
            while (sscanf(values, "%lf", &num) == 1) {
                basis_matrix[i][pos] = num;
                pos += 1;

                values++;
                while (*values && *values != ' ' && *values != ']') {
                    values++;
                }

                if (*values == ']') {
                    break;
                }
            }
            free(original_values);
            // Ensure the correct amount of vectors has been extracted
            if (pos != numVectors) {
                printf("[INPUT ERROR] Input n valid elements\n");
                return 0;
            }
        } else {
            printf("[INPUT ERROR] Missing closing bracket ']'\n");
            free_structs_mem(basis_matrix, numVectors, mega_input);
            free(individual_vector);
            return 0;
        }

        // Progress pointer to next vector
        if (i < numVectors - 1) {
            if (mega_input[megastring_index] == ' ' && \
                mega_input[megastring_index + 1] == '[') {
                megastring_index += 1;
            } else {
                printf("[INPUT ERROR] Use singular space "\
                        "to separate vectors\n");
                free_structs_mem(basis_matrix, numVectors, mega_input);
                return 0;
            }
        } else {
            // deal with the case of [][] where i = numvectors-1
            if (mega_input[megastring_index] != '\0') {
                printf("[INPUT ERROR] Double brackets invalid\n");
                return 0;
            }
        }
    }

    lll_algorithm(basis_matrix, numVectors, dimension);
    double shortest_euclidean_norm = find_shortest_v(basis_matrix, \
        numVectors, dimension);

    // Finally, the result of enumaratin on the reduced
    // basis is then written to a text file
    if (shortest_euclidean_norm == 0) {
        return 0;
    }
    FILE *result_file = fopen("./result.txt", "w");
    if (result_file != NULL) {
        fprintf(result_file, "%f\n", shortest_euclidean_norm);
        fclose(result_file);
    } else {
        printf("[FILE ERROR]: 'result.txt' could not be created");
    }

    gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    printf("Elapsed time: %f seconds\n", elapsed);

    // Free memory used up by the basis matrix and vectrs within
    free_structs_mem(basis_matrix, numVectors, mega_input);
    return 0;
}
