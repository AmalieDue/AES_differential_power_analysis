//
// Created by Amalie Due Jensen s160503 and Anders Lammert Hartmann s153596
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "definitions.h"
#include "create_data_structures.h"

/*
* Description: Compute the average of a float array.
*
* Input: The float array and a float called average in which the average is saved.
*
* Output: The average of the array.
*/
float compute_array_average (float array[], float average) {
    for (int i = 0; i < TRACES; i++) {
        average += array[i];
    }

    return average /= TRACES;
}

/*
* Description: Calculate the Pearson correlation between two float arrays, h and t.
*
* Input: The two float arrays h and t.
*
* Output: The pearson correlation as a float.
*/
float pearson_correlation(float h[], float t[]) {
    float h_average = 0;
    float t_average = 0;

    h_average = compute_array_average(h, h_average);
    t_average = compute_array_average(t, t_average);

    float nominator = 0;
    float denominator = 0;

    float h_part = 0;
    float h_part_squared = 0;
    float t_part = 0;
    float t_part_squared = 0;

    for (int i = 0; i < TRACES; i++) {
        h_part = h[i] - h_average;
        t_part = t[i] - t_average;
        nominator += h_part * t_part;
        h_part_squared += h_part * h_part;
        t_part_squared += t_part * t_part; 
    }
    
    denominator = sqrt(h_part_squared * t_part_squared);

    return nominator / denominator;
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
    * correlations. Then, we check that the greatest of these values corresponds to the key byte guess from experiment 1.
    * 
    */
    float T[TRACES*SAMPLES];

    float H[TRACES*KEYS];

    float H_column[TRACES];

    float T_column[TRACES];

    float correlations[KEYS];

    for (int i = 0; i < KEYS; i++) {
        correlations[i] = 0;
    }

    float best_correlation;

    int best_correlation_key = 0;
    
    create_T_matrix(T, "T3.dat");

    create_H_matrix(H, "inputs3.dat");

    for (int i = 0; i < KEYS; i++) {
        for (int j = 0; j < TRACES; j++) {
            H_column[j] = H[i+j*KEYS];
        }

        for (int k = 0; k < SAMPLES; k++) { 
            for (int j = 0; j < TRACES; j++) {
                T_column[j] = T[k+j*SAMPLES];
            }

            if (fabs(pearson_correlation(H_column, T_column)) > best_correlation) {
                best_correlation = fabs(pearson_correlation(H_column, T_column));
                best_correlation_key = i;
            }
            correlations[i] += fabs(pearson_correlation(H_column, T_column));
        }
    }

    printf("Key %d has the best correlation which is %f\n", best_correlation_key, best_correlation);

    printf("Total sum of all %d correlations for each key:\n\n", SAMPLES);

    for (int i = 0; i < KEYS; i++) {
        printf("Key %d, correlation = %f\n", i, correlations[i]);
    }

    // The correct key byte is 32. Key 32 has the best correlation which is 0.317993,
    // and this key also has the greatest sum of all its 55 correlations, which is 9.300139.

    return 0;
}