//
// Created by Amalie Due Jensen s160503 and Anders Lammert Hartmann s153596
//

#include <math.h>
#include "pearson_correlation.h"
#include "definitions.h"

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