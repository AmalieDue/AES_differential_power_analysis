//
// Created by Amalie Due Jensen s160503 and Anders Lammert Hartmann s153596
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"
#include "create_data_structures.h"

// AES S-Box - used within the create_H_matrix function
unsigned char S[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

/*
* Description: Read a file into a file pointer. If error, then the function returns an error message.
*
* Input: The filename and a file pointer in which the file should be opened.
*
* Output: The file pointer in which the file has been opened.
*/
FILE * open_file(char* filename, FILE *file) {
    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit;
    }

    return file;
}

/*
* Description: Close a file.
*
* Input: The file pointer that should be closed.
*
* Output: Nothing.
*/
void close_file(FILE *file) {
    fclose(file);
}

/*
* Description: Create the T matrix by reading the TX.dat file line by line as strings and converting each string line to 55 floats.
*
* Input: The float array T in which the data should be inserted and the filename TX.dat containing the data.
*
* Output: The T matrix (however, it is actually not stored as a matrix, but as a float array instead).
*/
float * create_T_matrix(float T[], char* filename) {
    int line_length = 55*8;
    char line[line_length];
    char* separate_by_comma;

    FILE *file;
    file = open_file(filename, file);

    int i = 0;
    for (int j = 0; j < TRACES; j++) {
        // Read one line at a time
        fgets(line, line_length, file);
        
        // Separate the line by comma and store in the T array
        separate_by_comma = strtok(line, ",");
        
        while (separate_by_comma != NULL) {
            T[i] = atof(separate_by_comma);
            separate_by_comma = strtok(NULL, ",");
            i++;
        }
    }

    close_file(file);

    return T;
}

/*
* Description: Compute the hamming weight of an integer, i.e. compute the number of 1's in the byte representation of the integer.
*
* Input: The integer.
*
* Output: The hamming weight of the integer.
*/
int compute_hamming_weight(int a) {
    int hamming_weight = 0;
    int current_bit = 0;

    for(int i = 0; i < BYTE_LENGTH; i++){
        current_bit = ((a >> i) & 0x01);
        if (current_bit == 1){
            hamming_weight++;
        }
    }

    return hamming_weight;
}


/*
* Description: Create the H matrix by first reading the inputsX.dat file as a string and then converting the string to 600 floats.
* The H matrix contains the expected values. Element H[i][j] contains HW(S[k_j XOR input_i]), or in other words: In order to create
* element H[i][j], we XOR the j'th key and the i'th input, then we pass the result through the AES S-box, and finally we compute the
* Hamming weight of the result.
*
* Input: The float array H in which the data should be inserted and the filename inputsX.dat containing the data.
*
* Output: The H matrix (however, it is actually not stored as a matrix, but as a float array instead).
*/
float * create_H_matrix(float H[], char* filename) {
    FILE *file;
    file = open_file(filename, file);

    int line_length = 600*4;
    char line[line_length];
    // Since this data file only contains one line of data, it is possible to read all the data at the same time
    fgets(line, line_length, file);
    char* separate_by_comma;
        
    // Separate the line of data by comma    
    separate_by_comma = strtok(line, ",");

    int plaintexts[TRACES];
    
    int i = 0;
    while (separate_by_comma != NULL) {
        plaintexts[i] = atof(separate_by_comma);
        separate_by_comma = strtok(NULL, ",");
        i++;
    }

    // Compute hamming weights of expected values
    for (int i = 0; i < TRACES; i++) {
        for (int j = 0; j < KEYS; j++) {
            H[i*KEYS+j] = S[plaintexts[i] ^ j];
            H[i*KEYS+j] = compute_hamming_weight(H[i*KEYS+j]);
        }
    }

    close_file(file);

    return H;
}
