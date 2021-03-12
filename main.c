//
// Created by Amalie Due Jensen s160503 and Anders Lammert Hartmann s153596
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "definitions.h"
#include "create_data_structures.h"
#include "pearson_correlation.h"

/*
* Description: Compute the sum of all 55 correlations for each key byte. In other words,
* the sum of the correlations for each time point.
*
* Input: A float array correlations in which the sums of correlations are saved, and the H 
* and T float arrays.
*
* Output: The float array of all 256 sums of correlations.
*/
float * compute_accumulated_correlation_per_key (float correlations[], float H[], float T[]) {
    float H_column[TRACES];
    float T_column[TRACES];

    for (int i = 0; i < KEYS; i++) {
        for (int j = 0; j < TRACES; j++) {
            H_column[j] = H[i+j*KEYS];
        }

        for (int k = 0; k < SAMPLES; k++) { 
            for (int j = 0; j < TRACES; j++) {
                T_column[j] = T[k+j*SAMPLES];
            }
            // Keep adding the correlations for each time point. Hence, correlations[i] becomes the
            // accumulated correlation for key byte i.
            correlations[i] += fabs(pearson_correlation(H_column, T_column));
        }
    }

    return correlations;
}

/*
* Description: Compute the key byte with the highest correlation.
*
* Input: A float array correct_key_and_correlation of 2 elements in which the correct key
* and the its highest Pearson correlation are saved, and the H and T float arrays.
*
* Output: The float array correct_key_and_correlation with the correct key byte on index 0
* and the correlation on index 1.
*/
float * compute_correct_key_and_correlation (float correct_key_and_correlation[2], float H[], float T[]) {
    float H_column[TRACES];
    float T_column[TRACES];
    
    for (int i = 0; i < KEYS; i++) {
        for (int j = 0; j < TRACES; j++) {
            H_column[j] = H[i+j*KEYS];
        }

        for (int k = 0; k < SAMPLES; k++) { 
            for (int j = 0; j < TRACES; j++) {
                T_column[j] = T[k+j*SAMPLES];
            }

            // Check whether an even better correlation were found. If the current correlation is better than what
            // is stored in correct_key_and_correlation[1], then we update correct_key_and_correlation[1] with the
            // new correlation. Furthermore, correct_key_and_correlation[0] is updated with the new key byte guess.
            if (fabs(pearson_correlation(H_column, T_column)) > correct_key_and_correlation[1]) {
                correct_key_and_correlation[1] = fabs(pearson_correlation(H_column, T_column));
                correct_key_and_correlation[0] = i;
            }
        }
    }

    return correct_key_and_correlation;
}

int main() {
    
    /*
    * In the following example, we guess the key byte corresponding to the data files inputs3.dat and T3.dat.
    * Note that other data files can be passed as well by changing the input filenames to the functions
    * create_T_matrix(T, filename); and create_H_matrix(H, filename); .
    * 
    * Correctness: We check that the key byte guess is correct by doing two different experiments:
    * - Experiment 1: First, we simply find the highest correlation (the Pearson correlation closest to 1 or -1) and
    * print the corresponding key byte.
    * - Experiment 2: Afterwards, we sum all 55 correlations for each key byte, which means that in total we get 256 (sums of)
    * correlations. Then, we check that the highest of these values corresponds to the key byte guess from experiment 1.
    * 
    */
    float T[TRACES*SAMPLES];

    float H[TRACES*KEYS];

    create_T_matrix(T, "T3.dat");

    create_H_matrix(H, "inputs3.dat");

    float correct_key_and_correlation[2];
    correct_key_and_correlation[0] = 0;
    correct_key_and_correlation[1] = 0;

    compute_correct_key_and_correlation(correct_key_and_correlation, H, T);

    printf("Key %.0f has the best single correlation which is %f\n", correct_key_and_correlation[0], correct_key_and_correlation[1]);

    float correlations[KEYS];

    for (int i = 0; i < KEYS; i++) {
        correlations[i] = 0;
    }

    compute_accumulated_correlation_per_key(correlations, H, T);

    printf("Accumulated correlation per key:\n\n", SAMPLES);
    
    // In a future version, this output will be sorted by accumulated correlation :-)
    for (int i = 0; i < KEYS; i++) {
        printf("Key %d, accumulated correlation = %f\n", i, correlations[i]);
    }

    // The correct key byte is 32. Key 32 has the best correlation which is 0.317993,
    // and this key also has the greatest sum of all its 55 correlations, which is 9.300139.

    return 0;
}