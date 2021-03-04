#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACES 600
#define SAMPLE 55


int main() {
    float T[TRACES*SAMPLE];
    char read_all_data[TRACES*SAMPLE];
    char* separate_by_comma;

    FILE *fptr;

    if ((fptr = fopen("./T3.dat", "r")) == NULL) {
        printf("Error");

        exit(1);
    }

    fgets(read_all_data, TRACES*SAMPLE, fptr);
    separate_by_comma = strtok(read_all_data, ",");
    int i = 0;
    for (int j = 0; j < TRACES; j++) {
        while (separate_by_comma != NULL) {
            T[i] = atof(separate_by_comma);
            printf("%.3f\n", T[i]);
            separate_by_comma = strtok(NULL, ",");
            i++;
        }
    }
    

    for (int i = 0; i < 601; i++) {
        printf("%.3f ", T[i]);
    }
    fclose(fptr);

    

    return 0;
}