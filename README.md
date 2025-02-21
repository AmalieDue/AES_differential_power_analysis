# AES differential power analysis

> This repository contains our implementation of the differential power analysis on AES in the course 02255 Modern Cryptologu Spring 2021 at DTU. The group members are [Anders Lammert Hartmann](https://github.com/AndersHartmann) 
(Student ID: s153596) and [Amalie Due Jensen](https://github.com/AmalieDue) (Student ID: s160503).

## Structure

The project has been divided into the following files:

* `create_data_structures.c`: Contains all functions related to creating the H and T matrices.
* `pearson_correlation.c`: Contains all functions related to computing the Pearson correlation.
* `main.c`: The main program.

## Usage

A simple example of how to guess the correct key byte, given data files "T3.dat" and "inputs3.dat", is shown below.

```c

// Initialize T matrix (or array). It should contain TRACES = 600 rows and SAMPLES = 55 columns.
float T[TRACES*SAMPLES];

// Initialize H matrix (or array). It should contain TRACES = 600 rows and KEYS = 256 columns.
float H[TRACES*KEYS];

// Create T matrix and H matrix by inserting values in the T and H float arrays.
create_T_matrix(T, "T3.dat");

create_H_matrix(H, "inputs3.dat");

// Now, we want to guess the correct key byte by doing two experiements:

// First, we simply find the highest Pearson correlation and the corresponding key byte. We
// initialize the following float array with 2 elements, and the idea is then to pass the
// correct key and the highest Pearson correlation into the array.

float correct_key_and_correlation[2];
correct_key_and_correlation[0] = 0;
correct_key_and_correlation[1] = 0;

compute_correct_key_and_correlation(correct_key_and_correlation, H, T);

printf("Key %.0f has the best single correlation which is %f\n", correct_key_and_correlation[0],
correct_key_and_correlation[1]);

```

Output:
```c
Key 32 has the best single correlation which is 0.317993

````

Success! We found out that key byte 32 results in the highest single Pearson correlation which is 0.317993.

```

// We now verify the result from experiment 1 by doing experiment 2: Now, we compute the 
// accumulated correlation for each key byte, i.e. the sum of all 55 time point correlations 
// for each key byte. We initialize the following float array with KEYS = 256 elements in 
// which we store each of the sums of correlations. If key byte 32 gets the highest sum of 
// correlations, then it is even more likely that we found the correct key byte.

float correlations[KEYS];

for (int i = 0; i < KEYS; i++) {
    correlations[i] = 0;
}

compute_total_correlation_per_key(correlations, H, T);

printf("Total sum of all %d correlations for each key:\n\n", SAMPLES);
    
for (int i = 0; i < KEYS; i++) {
    printf("Key %d, correlation = %f\n", i, correlations[i]);
}

```

Output: (In a future version, this output will be sorted by accumulated correlation :-) )
```c

Key 0, accumulated correlation = 4.110390
Key 1, accumulated correlation = 3.103518
Key 2, accumulated correlation = 3.654654
Key 3, accumulated correlation = 1.582579
Key 4, accumulated correlation = 2.365894
Key 5, accumulated correlation = 2.079891
Key 6, accumulated correlation = 1.540060
Key 7, accumulated correlation = 3.594687
Key 8, accumulated correlation = 4.749499
Key 9, accumulated correlation = 1.437448
Key 10, accumulated correlation = 3.132227
Key 11, accumulated correlation = 2.128474
Key 12, accumulated correlation = 1.531137
Key 13, accumulated correlation = 2.947709
Key 14, accumulated correlation = 2.213795
Key 15, accumulated correlation = 2.380155
Key 16, accumulated correlation = 3.986348
Key 17, accumulated correlation = 2.369498
Key 18, accumulated correlation = 1.651677
Key 19, accumulated correlation = 5.510439
Key 20, accumulated correlation = 2.887330
Key 21, accumulated correlation = 1.759713
Key 22, accumulated correlation = 2.035779
Key 23, accumulated correlation = 1.501041
Key 24, accumulated correlation = 3.407341
Key 25, accumulated correlation = 1.920029
Key 26, accumulated correlation = 1.356786
Key 27, accumulated correlation = 0.964627
Key 28, accumulated correlation = 2.791588
Key 29, accumulated correlation = 1.867250
Key 30, accumulated correlation = 4.451157
Key 31, accumulated correlation = 1.744665
Key 32, accumulated correlation = 9.300139
Key 33, accumulated correlation = 1.676476
Key 34, accumulated correlation = 3.691625
Key 35, accumulated correlation = 2.707481
Key 36, accumulated correlation = 2.840777
Key 37, accumulated correlation = 2.050515
Key 38, accumulated correlation = 2.748684
Key 39, accumulated correlation = 4.124956
Key 40, accumulated correlation = 0.964175
Key 41, accumulated correlation = 1.433531
Key 42, accumulated correlation = 3.880003
Key 43, accumulated correlation = 2.187463
Key 44, accumulated correlation = 3.701668
Key 45, accumulated correlation = 2.667667
Key 46, accumulated correlation = 3.129574
Key 47, accumulated correlation = 2.613164
Key 48, accumulated correlation = 2.124789
Key 49, accumulated correlation = 2.332810
Key 50, accumulated correlation = 1.243155
Key 51, accumulated correlation = 6.292333
Key 52, accumulated correlation = 3.689503
Key 53, accumulated correlation = 3.095116
Key 54, accumulated correlation = 3.537881
Key 55, accumulated correlation = 4.605424
Key 56, accumulated correlation = 4.358179
Key 57, accumulated correlation = 1.376033
Key 58, accumulated correlation = 3.334212
Key 59, accumulated correlation = 1.536436
Key 60, accumulated correlation = 4.616679
Key 61, accumulated correlation = 2.137576
Key 62, accumulated correlation = 4.155435
Key 63, accumulated correlation = 1.712178
Key 64, accumulated correlation = 1.352310
Key 65, accumulated correlation = 1.829880
Key 66, accumulated correlation = 4.056080
Key 67, accumulated correlation = 1.841111
Key 68, accumulated correlation = 2.307950
Key 69, accumulated correlation = 2.855015
Key 70, accumulated correlation = 4.715668
Key 71, accumulated correlation = 1.746710
Key 72, accumulated correlation = 2.927251
Key 73, accumulated correlation = 2.904197
Key 74, accumulated correlation = 2.414705
Key 75, accumulated correlation = 4.598849
Key 76, accumulated correlation = 2.657319
Key 77, accumulated correlation = 3.803162
Key 78, accumulated correlation = 2.441079
Key 79, accumulated correlation = 1.971967
Key 80, accumulated correlation = 1.666647
Key 81, accumulated correlation = 1.805174
Key 82, accumulated correlation = 2.323725
Key 83, accumulated correlation = 2.767273
Key 84, accumulated correlation = 1.074866
Key 85, accumulated correlation = 3.773109
Key 86, accumulated correlation = 2.101257
Key 87, accumulated correlation = 4.373188
Key 88, accumulated correlation = 1.235176
Key 89, accumulated correlation = 1.183705
Key 90, accumulated correlation = 4.058776
Key 91, accumulated correlation = 2.097602
Key 92, accumulated correlation = 2.476257
Key 93, accumulated correlation = 1.676189
Key 94, accumulated correlation = 2.523772
Key 95, accumulated correlation = 0.813711
Key 96, accumulated correlation = 2.701888
Key 97, accumulated correlation = 2.247962
Key 98, accumulated correlation = 3.111981
Key 99, accumulated correlation = 2.109236
Key 100, accumulated correlation = 4.519819
Key 101, accumulated correlation = 3.131150
Key 102, accumulated correlation = 6.325235
Key 103, accumulated correlation = 1.553719
Key 104, accumulated correlation = 3.006049
Key 105, accumulated correlation = 2.898210
Key 106, accumulated correlation = 2.608227
Key 107, accumulated correlation = 3.109006
Key 108, accumulated correlation = 4.210349
Key 109, accumulated correlation = 3.047861
Key 110, accumulated correlation = 3.458291
Key 111, accumulated correlation = 2.365150
Key 112, accumulated correlation = 1.586775
Key 113, accumulated correlation = 3.115178
Key 114, accumulated correlation = 5.001569
Key 115, accumulated correlation = 1.763541
Key 116, accumulated correlation = 2.404994
Key 117, accumulated correlation = 4.206206
Key 118, accumulated correlation = 1.237096
Key 119, accumulated correlation = 3.383681
Key 120, accumulated correlation = 6.619181
Key 121, accumulated correlation = 0.659934
Key 122, accumulated correlation = 1.144801
Key 123, accumulated correlation = 1.861936
Key 124, accumulated correlation = 2.590694
Key 125, accumulated correlation = 1.953527
Key 126, accumulated correlation = 1.321712
Key 127, accumulated correlation = 1.869166
Key 128, accumulated correlation = 2.343958
Key 129, accumulated correlation = 1.554916
Key 130, accumulated correlation = 0.773012
Key 131, accumulated correlation = 0.690636
Key 132, accumulated correlation = 3.735188
Key 133, accumulated correlation = 3.705633
Key 134, accumulated correlation = 0.923924
Key 135, accumulated correlation = 1.774040
Key 136, accumulated correlation = 4.156878
Key 137, accumulated correlation = 2.735578
Key 138, accumulated correlation = 4.680037
Key 139, accumulated correlation = 3.077735
Key 140, accumulated correlation = 1.152177
Key 141, accumulated correlation = 3.937428
Key 142, accumulated correlation = 1.302693
Key 143, accumulated correlation = 1.507153
Key 144, accumulated correlation = 5.378863
Key 145, accumulated correlation = 3.592068
Key 146, accumulated correlation = 4.326121
Key 147, accumulated correlation = 4.002201
Key 148, accumulated correlation = 3.259526
Key 149, accumulated correlation = 2.879815
Key 150, accumulated correlation = 2.154117
Key 151, accumulated correlation = 3.154242
Key 152, accumulated correlation = 3.176828
Key 153, accumulated correlation = 2.526411
Key 154, accumulated correlation = 2.631249
Key 155, accumulated correlation = 4.291995
Key 156, accumulated correlation = 3.378729
Key 157, accumulated correlation = 4.072985
Key 158, accumulated correlation = 3.278760
Key 159, accumulated correlation = 1.197899
Key 160, accumulated correlation = 2.722443
Key 161, accumulated correlation = 2.328067
Key 162, accumulated correlation = 1.565787
Key 163, accumulated correlation = 1.272157
Key 164, accumulated correlation = 1.264755
Key 165, accumulated correlation = 2.264765
Key 166, accumulated correlation = 0.771317
Key 167, accumulated correlation = 2.046171
Key 168, accumulated correlation = 1.506431
Key 169, accumulated correlation = 2.462809
Key 170, accumulated correlation = 4.126848
Key 171, accumulated correlation = 0.584809
Key 172, accumulated correlation = 0.948009
Key 173, accumulated correlation = 2.659366
Key 174, accumulated correlation = 5.266645
Key 175, accumulated correlation = 1.746779
Key 176, accumulated correlation = 2.642457
Key 177, accumulated correlation = 1.672483
Key 178, accumulated correlation = 1.941523
Key 179, accumulated correlation = 1.469038
Key 180, accumulated correlation = 3.027889
Key 181, accumulated correlation = 2.246045
Key 182, accumulated correlation = 3.979262
Key 183, accumulated correlation = 1.702571
Key 184, accumulated correlation = 1.997653
Key 185, accumulated correlation = 3.820793
Key 186, accumulated correlation = 7.655247
Key 187, accumulated correlation = 2.970501
Key 188, accumulated correlation = 1.977456
Key 189, accumulated correlation = 2.548192
Key 190, accumulated correlation = 2.761188
Key 191, accumulated correlation = 1.701968
Key 192, accumulated correlation = 0.970445
Key 193, accumulated correlation = 4.327744
Key 194, accumulated correlation = 2.264120
Key 195, accumulated correlation = 5.673619
Key 196, accumulated correlation = 0.996428
Key 197, accumulated correlation = 7.084363
Key 198, accumulated correlation = 2.419037
Key 199, accumulated correlation = 3.670468
Key 200, accumulated correlation = 4.363183
Key 201, accumulated correlation = 3.815159
Key 202, accumulated correlation = 2.171218
Key 203, accumulated correlation = 1.711732
Key 204, accumulated correlation = 2.128683
Key 205, accumulated correlation = 2.965872
Key 206, accumulated correlation = 3.404493
Key 207, accumulated correlation = 5.653240
Key 208, accumulated correlation = 1.780922
Key 209, accumulated correlation = 3.884757
Key 210, accumulated correlation = 2.574562
Key 211, accumulated correlation = 2.130226
Key 212, accumulated correlation = 1.078500
Key 213, accumulated correlation = 2.838952
Key 214, accumulated correlation = 3.217292
Key 215, accumulated correlation = 4.891329
Key 216, accumulated correlation = 1.302648
Key 217, accumulated correlation = 1.245545
Key 218, accumulated correlation = 2.811243
Key 219, accumulated correlation = 5.154520
Key 220, accumulated correlation = 2.143839
Key 221, accumulated correlation = 4.942850
Key 222, accumulated correlation = 2.419013
Key 223, accumulated correlation = 5.925185
Key 224, accumulated correlation = 0.840306
Key 225, accumulated correlation = 7.278676
Key 226, accumulated correlation = 3.620003
Key 227, accumulated correlation = 1.472152
Key 228, accumulated correlation = 2.229624
Key 229, accumulated correlation = 5.419033
Key 230, accumulated correlation = 1.871252
Key 231, accumulated correlation = 1.606541
Key 232, accumulated correlation = 5.707773
Key 233, accumulated correlation = 2.317236
Key 234, accumulated correlation = 1.458257
Key 235, accumulated correlation = 3.215093
Key 236, accumulated correlation = 2.864774
Key 237, accumulated correlation = 1.740959
Key 238, accumulated correlation = 2.532872
Key 239, accumulated correlation = 3.537203
Key 240, accumulated correlation = 4.267267
Key 241, accumulated correlation = 2.377007
Key 242, accumulated correlation = 1.618935
Key 243, accumulated correlation = 1.902109
Key 244, accumulated correlation = 2.222570
Key 245, accumulated correlation = 2.206740
Key 246, accumulated correlation = 3.122188
Key 247, accumulated correlation = 3.784814
Key 248, accumulated correlation = 3.603813
Key 249, accumulated correlation = 1.323628
Key 250, accumulated correlation = 1.295807
Key 251, accumulated correlation = 4.580676
Key 252, accumulated correlation = 1.853292
Key 253, accumulated correlation = 2.689946
Key 254, accumulated correlation = 2.381989
Key 255, accumulated correlation = 4.001246

```

Success! We see that key byte 32 has the highest accumulated correlation which is 9.300139. By investigating the output further, it can be seen that that second highest accumulated correlation is 7.655247 for key byte 186.

## How to compile the program

Using the gcc compiler:

```c
gcc main.c create_data_structures.c pearson_correlation.c -o aes

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

### Pearson correlation functions

* `float compute_array_average (float array[], float average)`: Compute the average of a float array. The function takes the float array as well as a float called average in which the average should be saved, as inputs.

* `float pearson_correlation(float h[], float t[])`: Calculate the Pearson correlation between two float arrays, h and t. The function takes the two float arrays h and t as inputs.

### Functions for guessing the correct key byte

* `float * compute_correct_key_and_correlation (float correct_key_and_correlation[], float H[], float T[])`: Compute the key byte with the highest correlation.

* `float * compute_accumulated_correlation_per_key (float correlations[], float H[], float T[])`: Compute the sum of all 55 correlations for each key byte. In other words, the sum of the correlations for each time point.