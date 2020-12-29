#ifndef DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H
#define DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/**
 * Utility enum since C doesn't have bool-type
 */
typedef enum{
    FALSE = 0,
    TRUE = 1
}BOOL;

/**
 * Singletone structure, which stores data for output file
 */
typedef struct {
    char* outPath; /** Path to output file */
    int err_code; /** Execution code */
    double* X; /** Solution vector */
}SOutput;

static SOutput OutData;

/**
 * Singletone structure, which stores data from input file
 */
typedef struct 
{
    int n; /** Equation amount */
    double* A; /** Matrix of linear system's coefficients */
    double* B; /** Vector of free coefficients */
}SInput;

static SInput inData;

/** When TRUE enables debug logging into stdout */
extern BOOL isDebugModeEnabled; 
/** When TRUE shows evaluation time at the end of execution */
extern BOOL isEvaluationTimeNeeded;
/** When FALSE disables error messages in stdout */ 
extern BOOL SuppressErrorMessages; 

/**
 * @brief Function parses file on given path and gets initial data
 *
 * @param inPath Path to input file
 * @return Error code
 */
int ParseInput(const char* inPath);

/**
 * @brief Function forms output of the program and writes it to the file on given path
 *
 * @param outPath Path to the output file
 * @param data
 * @return Error code
 */
int FormOutput(const char* outPath, double* data);


/**
 * @brief Function which solves system of linear equations by LU-decomposition method
 *
 * @param n Equations amount (array size).
 * @param A Flattened matrix of equation coefficients.
 * @param B Free coefficients vector.
 * @param X Solution vector.
 * @param tmp Temporary memory.
 * @return Error code:
 * @arg 0 - Successful execution. Solution found. 
 * @arg 1 - Successful execution. Solution does not exist. 
 * @arg -1 - This method does not fit the given system.
 */
int lss_17_09(int n, double* A, double* B, double* X, double* tmp);

/**
 * @brief Function calculates temporary memory.
 * 
 * Since initial matrix will be used only once in @c lss_17_09 function, we can optimize memory usage by storing matrixes @b L and @b U in the same memory as initial matrix were.
 * (This also saves time since it is easier for us to calculate decomposition formulas). 
 * Thus, we only need @c O(n) additional memory to store @b y vector after straight pass of the algorithm.
 *
 * @param n Equations amount
 * @return Memory size to allocate
 */
static size_t lss_memsize_17_09(int n);

/**
 * @brief Function checks diagonal domination of matrix elements:
 * @arg @c |a_i| @c >= @c |d_i| @c + @c |c_i|,
 * @arg @c |d_i| @c != @c 0,
 * where @c a_i - main diagonal elements, @c d_i - lower diagonal elements, @c c_i - upper diagonal elements.
 * This need to determine whether @b LU-decomposition even possible.
 *
 * @param A Matrix of linear system's coefficients.
 * @param n Equations amount.
 * @return
 * @arg @b TRUE, if LU-decomposition possible.
 * @arg @b FALSE, otherwise.
 */
static BOOL IsDecompositionPossible(double* A, int n);

/**
 * @brief Utility function to make double comparison more accurate.
 * 
 * Compares @c a and @c b with given tolerance
 * 
 * @param a left number
 * @param b right number
 * @param tolerance precision with which numbers are compared
 * 
 * @return @b TRUE or @b FALSE
 */ 
static BOOL NearlyEqual(double a, double b, double tolerance);

#endif //DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

