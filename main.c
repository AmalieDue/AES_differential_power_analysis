#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "definitions.h"
#include "create_data_structures.h"

float compute_array_average (float array[], float average) {
    for (int i = 0; i < TRACES; i++) {
        average += array[i];
    }

    return average /= TRACES;
}

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
    
    float T[SAMPLES*TRACES];

    float H[TRACES*KEYS];

    float H_column[TRACES];

    float T_column[TRACES];

    float correlations[KEYS];
    
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
            correlations[i] += fabs(pearson_correlation(H_column, T_column));
        }
        printf("corr: %f\n", correlations[i]);
        
    }
    
    return 0;
}