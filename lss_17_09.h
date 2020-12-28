//
// Created by ZexUlt on 14.12.2020.
//

#ifndef DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H
#define DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

#include <stdio.h>
#include <math.h>

/**
 * Utility enum since C doesn't have bool-type
 */
typedef enum{
    FALSE = 0,
    TRUE = 1
}BOOL;

/**
 * Utility typedef since C doesn't have size_t
 */
typedef unsigned long long size_t;

/**
 * Singletone structure, which stores data for output file
 */
typedef struct {
    char* outPath;
    int err_code;
    double* X;
    int n;
}SOutput;

static SOutput OutData;

/**
 * Singletone structure, which stores data from input file
 */
typedef struct 
{
    int n;
    double* A;
    double* B;
}SInput;

static SInput inData;


/**
 * @brief Function parses file on given path and gets initial data
 *
 * @param inPath - Path to input file
 * @return - Error code
 */
int ParseInput(const char* inPath);

/**
 * @brief Function forms output of the program and writes it to the file on given path
 *
 * @param outPath - Path to the output file
 * @param data
 * @return - Error code
 */
int FormOutput(char* outPath, double* data);


/**
 * @brief Function which solves system of linear equations by LU-decomposition method
 *
 * @param n - Equations amount (array size).
 * @param A - Flattened matrix of equation coefficients.
 * @param B - Free coefficients vector.
 * @param X - Solution vector.
 * @param tmp - Temporary memory.
 * @return - Error code:
 * @arg 0 - Successful execution. Solution found. 
 * @arg 1 - Successful execution. Solution does not exist. 
 * @arg -1 - This method does not fit the given system.
 */
int lss_17_09(int n, double* A, double* B, double* X, double* tmp);

/**
 * @brief Function calculates temporary memory.
 * 
 * According to method description and assingment limitations, only (3n-2) bytes of memory needed to store 
 *
 * @param n - Equations amount
 * @return - Memory size to allocate
 */
static size_t lss_memsize_17_09(int n);

/**
 * @brief Function checks diagonal domination of matrix elements:
 * @arg |a_i| >= |d_i| + |c_i|,
 * @arg |d_i| != 0,
 * where \a a_i - main diagonal elements, \a d_i - lower diagonal elements, \a c_i - upper diagonal elements.
 * This need to determine whether LU-decomposition even possible.
 *
 * @param A Matrix of linear system's coefficients.
 * @param n Equations amount.
 * @return
 * @arg TRUE, if LU-decomposition possible.
 * @arg FALSE, otherwise.
 */
static BOOL IsDecompositionPossible(double* A, int n);

/**
 * @brief Utility function to make double comparison more accurate.
 * 
 * Compares \a a and \a b with given tolerance
 * 
 * @param a left number
 * @param b right number
 * @param tolerance precision with which numbers are compared
 * 
 * @return TRUE or FALSE
 */ 
static BOOL NearlyEqual(double a, double b, double tolerance);

#endif //DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

