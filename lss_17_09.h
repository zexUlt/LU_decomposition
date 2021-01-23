#ifndef DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H
#define DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/**
 * Logger macro
 */
#define LOG(type, message) \
            log_(type, message)


#define ALPHA inData.n
#define BETA 0
#define GAMMA (2*inData.n - 1)

/**
 * Utility enum for logging purpose
 */
typedef enum{
    Debug = 0,
    Error = 1
}LogType;

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
    /** Path to output file */
    char outPath[255];
    /** Execution code */
    int err_code;
    /** Solution vector */
    double* X;
}SOutput;

extern SOutput OutData;

/**
 * Singletone structure, which stores data from input file
 */
typedef struct 
{
    /** Equation amount */
    int n;
    /** Matrix of linear system's coefficients */
    double* A;
    /** Vector of free coefficients */
    double* B;
}SInput;

static SInput inData;

/** When TRUE enables debug logging into stdout */
extern BOOL isDebugModeEnabled; 
/** When TRUE shows evaluation time at the end of execution */
extern BOOL isEvaluationTimeNeeded;
/** When FALSE disables error messages in stdout */ 
extern BOOL SuppressErrorMessages; 
/** When TRUE calls function to print input matrix */
extern BOOL PrintMatrix;

/**
 * @brief Function parses file on given path and gets initial data
 *
 * @param inPath Path to input file
 */
void ParseInput(const char* inPath);

/**
 * @brief Function forms output of the program and writes it to the file on given path. If solution of the equation system
 * was found it prints answer vector to the file. If not - it writes 0 to file.
 *
 * @param outPath Path to the output file
 * @param data
 */
void FormOutput(const char* outPath, double* data, int err);


/**
 * @brief Function which solves system of linear equations by LU-decomposition method
 *
 * @param n Equations amount (array size).
 * @param A Flattened matrix of equation coefficients (@c betas, @c alphas, @c gammas).
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


/**
 * @brief Decorator-function for initial data preparation
 *
 * @return Error code
 */
void lss_main();

/**
 * @brief Wrapper-function for logging
 *
 * @param mode
 * @arg @c Debug - for debug messages
 * @arg @c Error - for error messages
 * @param msg message to show
 */
void log_(LogType mode, const char* msg);

/**
 * @brief Function executes @c free() for each memory block which has been allocated during execution
 */
static void ReleaseMemory();

/**
 * @brief Fuction prints input matrix if @c PrintMatrix is set to @c TRUE
 */
static void printMatrix();

#endif //DIFFEQ_PRACTICE2020_TASK2_LSS_17_09_H

