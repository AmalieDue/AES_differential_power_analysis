# AES_differential_power_analysis

> This repository contains our implementation of the differential power analysis on AES in the course 02255 Modern Cryptologu Spring 2021 at DTU. The group members are [Anders Lammert Hartmann](https://github.com/AndersHartmann) 
(Student ID: s153596) and [Amalie Due Jensen](https://github.com/AmalieDue) (Student ID: s160503).

## Structure

The project has been divided into the following files:

* `create_data_structures.c`: Contains all functions related to creating the H and T matrices.
* `main.c`: The main program.

## Usage

A simple example of how to guess the correct key byte, given data files "TX.dat" and "inputsX.dat", is shown below.

```c

// Initialize T matrix (or array). It should contain TRACES = 600 rows and SAMPLES = 55 columns.
float T[TRACES*SAMPLES];

// Initialize H matrix (or array). It should contain TRACES = 600 rows and KEYS = 256 columns.
float H[TRACES*KEYS];

// Create T matrix and H matrix by inserting values in the T and H float arrays.
create_T_matrix(T, "T3.dat");

create_H_matrix(H, "inputs3.dat");

```

## How to compile the program

Using the gcc compiler:

```c
gcc main.c create_data_structures.c -o aes

./aes
```

## API

### Constants

* `TRACES = 600`: The number of power traces which is N = 600.

* `SAMPLES = 55`: The number of samples which is 55.

* `KEYS = 256`: The number of different key bytes which is 2^8 = 256.

* `BYTE_LENGTH = 8`: The number of bits in a byte. This constant is used when computing Hamming weights.

### Create data structure functions

* `FILE * open_file(char* filename, FILE *file)`: Read a file into a file pointer. If error, then the function returns an error message. The function takes the file name and the file pointer as inputs.

* `void close_file(FILE *file)`: Close a file. The function takes the file pointer as input.

* `float * create_T_matrix(float T[], char* filename)`: Create the T matrix containing all the observed data. The function takes an empty float array T in which the values should be saved and the filename of the file with data, as inputs. Note that the function returns the T values as a float pointer and not as a matrix as we call it.

* `int compute_hamming_weight(int a)`: Compute the hamming weight of an integer, i.e. compute the number of 1's in the byte representation of the integer. The function takes the integer as input.

* `float * create_H_matrix(float H[], char* filename)`: Create the H matrix by first reading the inputsX.dat file as a string and then converting the string to 600 floats. The H matrix contains the expected values. Element H[i][j] contains HW(S[k_j XOR input_i]), or in other words: In order to create element H[i][j], we XOR the j'th key and the i'th input, then we pass the result through the AES S-box, and finally we compute the Hamming weight of the result. The function takes an empty float array H in which the values should be saved and the filename of the file with data, as inputs. Note that the function returns the H values as a float pointer and not as a matrix as we call it.

### Correlation functions

* `float compute_array_average (float array[], float average)`: Compute the average of a float array. The function takes the float array as well as a float called average in which the average should be saved, as inputs.

* `float pearson_correlation(float h[], float t[])`: Calculate the Pearson correlation between two float arrays, h and t. The function takes the two float arrays h and t as inputs.