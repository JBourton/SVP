#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "svp_structs.h"
#include "command_line.h"

/*
Function purpose: Test if number of opening brackers = number of closing brackets
Function inputs:
- The number of arguments 'argc'
- The arguments themselves 'argv'
Function output: A boolean 1 for yes and 0 for no
*/
int check_brackets_match(int argc, char *argv[]) {
    int open_brackets = 0;
    int closing_brackets = 0;

    // Check number of opening and closing brackets match
    for (int i=1; i<argc; i++) {
        if (strncmp(argv[i], "[", 1) == 0) {
            open_brackets += 1;
        }
        size_t input_item = strlen(argv[i]);
        if (input_item > 0 && argv[i][input_item- 1] == ']') {
            closing_brackets += 1;
        }
    }
    if (open_brackets != closing_brackets) {
        printf("[INPUT ERROR] Number of opening and closing brackets do not "
       "match\n");
        return 0;
    } else {
        return 1;
    }
}

/*
Function purpose: To count how many opening brackets (and therefore vectors) are present
Function inputs: 
- The number of arguments 'argc'
- The arguments themselves 'argv'
Function output: A integer representing the count of opening brackets
*/
int get_bracket_count(int argc, char *argv[]) {
    int bracket_count = 0;
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "[", 1) == 0) {
            bracket_count += 1;
        }
    }
    return bracket_count;
}

/*
Function purpose: The find the total number of characters in the command line input (including spaces)
Function inputs:
- The number of arguments 'argc'
- The arguments themselves 'argv'
Function output: An integer represening the total number of characters
*/
size_t get_input_length(int argc, char *argv[]) {
    // Make 1 big string from all the command line arguments
    size_t input_length = 0;

    for (int i = 1; i < argc; i++) {
        size_t input_item = strlen(argv[i]);
        input_length += input_item + 1;
    }
    return input_length;
}

/*
Function purpose:
Function inputs:
Function output:
*/

/*
Function purpose:
Function inputs:
Function output:
*/
