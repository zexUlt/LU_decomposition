//
// Created by ZexUlt on 14.12.2020.
//

#ifndef DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H
#define DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

/**
 * Utility enum since C doesn't have bool-type
 */
typedef enum{
    FALSE = 0,
    TRUE = 1
}BOOL;



typedef struct {
    char* outPath;
}SOutput;

static SOutput OutData;

/**
 * @brief Function parses file on given path and getting initial data
 *
 * @param inPath - Path to input file
 * @return - Error code
 */
int ParseInput(char* inPath);

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
 * @brief Function calculates temporary memory
 *
 * @param n - Equations amount
 * @return - Memory size to allocate
 */
size_t lss_memsize_17_09(int n);

/**
 * @brief Function checks diagonal domination of matrix elements:
 * @arg |a_i| >= |d_i| + |c_i|,
 * @arg |d_i| != 0,
 * where \a a_i - main diagonal elements, \a d_i - lower diagonal elements, \a c_i - upper diagonal elements.
 * This need to determine whether LU-decomposition even possible.
 *
 * @param A - Matrix of linear system's coefficients.
 * @param n - Equations amount.
 * @return
 * @arg TRUE, if LU-decomposition possible.
 * @arg FALSE, otherwise.
 */
BOOL IsDecompositionPossible(double* A, int n);


#endif //DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

