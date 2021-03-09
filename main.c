#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "definitions.h"


/*
char * read_one_line(FILE *file, char line[], int line_length) {
    fgets(line, line_length, file);

    return line;
}
*/

float * create_T_matrix(float T[], char* filename) {
    int linelength = 55*8;
    char line[linelength];
    char* separate_by_comma;
    //char* string;

    FILE *file = fopen(filename, "r");

    if (file == NULL) 
    {
        perror("Error opening file");
        exit;
    }

    int i = 0;
    for (int j = 0; j < TRACES; j++) {
        fgets(line, linelength, file);
        //string = strdup(line);
        
        separate_by_comma = strtok(line, ",");
        
        while (separate_by_comma != NULL) {
            T[i] = atof(separate_by_comma);
            separate_by_comma = strtok(NULL, ",");
            i++;
        }
    }

    fclose(file);

    return T;
}

/*
int* generate_all_keys(int keys[], int number_of_keys) {
    keys[0] = 0;

    for(int i = 1; i < KEYS; i++) {
        keys[i] = keys[i-1] + 1;
    }

    return keys;
}
*/

int Hamming_weight(uint8_t a){
    int count=0;

    for(int i=0; i<8;i++){
        int x=((a >> i)  & 0x01);

        if (x==1){
            count+=1;
        }
    }

    return count;
}

float * create_H_matrix(float H[], char* filename) {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit;
    }

    int line_length = 600*4;
    char line[line_length];
    fgets(line, line_length, file);
    char* separate_by_comma;
        
    separate_by_comma = strtok(line, ",");

    int plaintexts[TRACES];
    
    int i = 0;
    while (separate_by_comma != NULL) {
        plaintexts[i] = atof(separate_by_comma);
        separate_by_comma = strtok(NULL, ",");
        i++;
    }

    for (int i = 0; i < TRACES; i++) {
        for (int j = 0; j < KEYS; j++) {
            H[i*KEYS+j] = S[plaintexts[i] ^ j];
            H[i*KEYS+j] = Hamming_weight(H[i*KEYS+j]);
        }
    }

    fclose(file);

    return H;
}

float pearson_correlation(float h[], float t[]) {
    float h_average = 0;
    float t_average = 0;

    for (int i = 0; i < TRACES; i++) {
        h_average += h[i];
        t_average += t[i];
    }
    h_average /= TRACES;
    t_average /= TRACES;


    float nominator = 0;
    float denominator = 0;

    float h_part = 0;
    float t_part = 0;

    for (int i = 0; i < TRACES; i++) {
        h_part += h[i] - h_average;
        t_part += t[i] - t_average;
        nominator += h_part * t_part;

    }
    
    printf("hpart: %f ", h_part);
    printf("tpart: %f ", t_part);
    denominator = sqrt(h_part * h_part * t_part * t_part);
    printf("%f / %f = %f\n", nominator, denominator, nominator / denominator);

    return nominator / denominator;
}

int main() {
    
    float T[SAMPLES*TRACES];

    float H[TRACES*KEYS];

    float H_column[TRACES];

    float T_column[TRACES];

    float correlations[KEYS];

    create_T_matrix(T, "T3.dat");

    //for (int i = 0; i < 600*55; i++) {
    //    printf("%f\n", T[i]);
    //}
    printf("%f", T[600*55-1]);

    create_H_matrix(H, "inputs3.dat");
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 600; j++) {
            H_column[j] = H[i+j*256];
            T_column[j] = T[i+j*55];
        }
        correlations[i] = pearson_correlation(H_column, T_column);
        printf("%f\n", correlations[i]);
    }
    
    
    return 0;
}