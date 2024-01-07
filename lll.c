#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "lll.h"
#include "svp_structs.h"



/*
Function purpose: Calculate the projection of one vector onto another
Function inputs:
- A vector v1 to be project
- A vector v2 to prjected onto
- The dimension of those vectors
Function output: An array 'project_v' representing the vector projection of v1 onto v2
*/
double* minus_project(double* v1, double* v2, int dimension, double* proj_factor) {
    // Setup return vector
    double* project_v = malloc(dimension * sizeof(double));
    for (int i = 0; i < dimension; ++i) {
        project_v[i] = 0;
    }
    // projection of v1 onto v2 = ((v1 dot v2) / (v2 mangitude)^2) * v2, which is applied below
    
    // First, we find v1 dot v2
    double dp_result = dot_product(v1, v2, dimension);

    // Then we find the square of the magnitude of v2
    double mag_sq = find_magnitude(v2, dimension);
    mag_sq *= mag_sq;
    
    // Next, we divide those 2 values for each dimension
    if (mag_sq != 0) {
        *proj_factor = dp_result / mag_sq;
        //printf("Projection factor: %f\n", *proj_fac);
        for (int i = 0; i < dimension; ++i) {
            // The projection factor is then multiplied by each component
            double projection = *proj_factor * v2[i];
            project_v[i] += projection;
        } 
    } else {
        // Prevent /0 error
        printf("Error, v2 has magnitude 0");
        free(project_v);
        *proj_factor = 0;
        return 0;
    }
    return project_v; 
}

/*
Function purpose: Perform Gram-Schmidt normalisation
Function inputs: 
- The basis matrix 'vectors'
- The number of vectors in hte basis matrix 'numVectors'
- The dimension of those vectors 'dimension'
Function output: A 2d array 'U' representing the orthogonal basis of the orginal basis matrix
*/
double** gram_schdmit(double** vectors, int numVectors, int dimension, double* proj_factor) {
    // Dynamically declare 2d array holding copy of basis matrix
    double** U = (double**)malloc(numVectors * sizeof(double*));
    for (int i = 0; i < numVectors; ++i) {
        U[i] = (double*)malloc(dimension * sizeof(double));
    }
    // Here, input vectos are copied ot an ew array
    for (int i = 0; i < numVectors; ++i) {
         // This serves to also set u1 = v1
        for (int j = 0; j < dimension; ++j) {
            U[i][j] = vectors[i][j];
        }
    }

    /* Next, we apply the minus_project function, subtracting each repsective component from its projection
       Equation: uk = vk - sum(i=1 to k-1) of vk projecting onto ui, where k is the vector number */
    for (int k = 1; k < numVectors; ++k) {
        // For every vector in the 2d array of vectors
        //U[k] = vectors[k];
        // Calculate the sums of the projection vectors from 1 to k-1
        double* total_projection = malloc(dimension * sizeof(double));
        // Initialse to 0
        for (int i = 0; i < dimension; ++i) {
            total_projection[i] = 0;
        }
        // Note: v1 is vk and v2 is ui
        for (int i = 0; i < k; ++i) {  
            // Calculate one of the prjections
            double* row_projection = minus_project(U[k], U[i], dimension, proj_factor);

            // Add it to the running total
            for (int j = 0; j < dimension; ++j) {
                total_projection[j] += row_projection[j];
            }
            free(row_projection);
        }

        // Subtract the sum of the projections form each row
        for (int i = 0; i < dimension; ++i) {
            U[k][i] -= total_projection[i];
        }
        free(total_projection);
    }
    return U;
}

/*
Function purpose: To calculate whether the basis meets the lovasz condition
Function inputs:
Function output: A boolean int (1/0)
*/
int lovasz_check(double* v1, double* v2, int dimension, double gs_coefficient) {
    // vk is the mangitude of the kth vector in the basis matrix
    // basically square without the square rooting
    double vk = find_magnitude(v1, dimension);
    vk = pow(vk, 2);
    double vk_minus_one = find_magnitude(v2, dimension);
    vk_minus_one = pow(vk_minus_one, 2);

    // This will be multipleid by the (k-1)th vector magnitude for compairson
    double lovasz_multiplier = pow(0.75 - gs_coefficient, 2);
    printf("lovasz multplier before multiplication: %f\n", lovasz_multiplier);
    lovasz_multiplier *= vk_minus_one;
    
    printf("vk magnitude: %f\n", vk);
    printf("vk-1 magnitude: %f\n", vk_minus_one);
    printf("gs_coefficient: %f\n", gs_coefficient);
    printf("Lovasz multiplier: %f\n", lovasz_multiplier);

    return (vk >= lovasz_multiplier);
};

double** lll_algorithm(double** vectors, int numVectors, int dimension) {
    // proj_factor will track of the current projection factor for use in the size condition check
    double proj_factor;
    double rounded_proj_factor;
    int k = 1;

    // Apply Gram Schmidt proccess
    double** Orthog_Basis;
    Orthog_Basis = gram_schdmit(vectors, numVectors, dimension, &proj_factor);
    display_basis_matrix(Orthog_Basis, numVectors, dimension);
    printf("Current projection factor: %f\n", proj_factor);
    printf("\n");

    while (k <= numVectors) {
        for (int j=k-1; j>=0; --j) {
            // Check size condition
            if (proj_factor > 0.5) {
                // Round down projection factor. Math: vk = vk - proj_factor * bj 
                rounded_proj_factor = floor(proj_factor);
                double* GS_Coefficient_Vector = multiply(vectors[j], rounded_proj_factor, dimension);
                
                for (int i = 0; i < dimension; ++i) {
                    vectors[k][i] -= GS_Coefficient_Vector[i];
                }

                free(GS_Coefficient_Vector);

                display_basis_matrix(vectors, numVectors, dimension);
                printf("\n");   
                // update gram schmidt         
            }
            // if not size_condition(i,j):
            // math stuff, update gram schmidt
        }
        // Increment k by 1 if lovasz condition True
        if (lovasz_check(Orthog_Basis[k], Orthog_Basis[k-1], dimension, rounded_proj_factor)) {
            k += 1;
        } else {
            k+=1;
        }
        
        
        // if true, incremenet k
        // else, perform swap, update gram schmidt and find new k-value
    }
    // return reduced basis
}