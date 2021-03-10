# AES_differential_power_analysis

> This repository contains our implementation of the differential power analysis on AES in the course 02255 Modern Cryptologu Spring 2021 at DTU. The group members are [Anders Lammert Hartmann](https://github.com/AndersHartmann) 
(Student ID: s153596) and [Amalie Due Jensen](https://github.com/AmalieDue) (Student ID: s160503).

## Structure

The project has been divided into the following files:

* `create_data_structures.c`: Contains all functions related to creating the H and T matrices.
* `main.c`: The main program.

## Usage

A simple example of how to use the implementation is shown below.

```c

hej

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

* `FILE * open_file(char* filename, FILE *file)`:

* `void close_file(FILE *file)`:

* `float * create_T_matrix(float T[], char* filename)`:

* `int compute_hamming_weight(int a)`:

* `float * create_H_matrix(float H[], char* filename)`:

### Correlation functions

* `float compute_array_average (float array[], float average)`:

* `float pearson_correlation(float h[], float t[])`: