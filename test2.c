#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * read_one_line(FILE *file, char line[]) {
    fgets(line, 500, file);

    return line;
}

int main() {
    char line[500];
    float T[55*600];
    char* separate_by_comma;
    FILE *file = fopen("T3.dat", "r");

    if (file == NULL) 
    {
        perror("Error opening file");
        return 1;
    }
    int i = 0;
    
    while (!feof(file))
    {
        read_one_line(file, line);
        char* string = strdup(line);
        
        separate_by_comma = strtok(string, ",");
        
        while (separate_by_comma != NULL) {
            T[i] = atof(separate_by_comma);
            separate_by_comma = strtok(NULL, ",");
            i++;
        }
    }
    printf("Last value: %.3f\n", T[54+55*599]);
    
    fclose(file);
    
    return 0;
}