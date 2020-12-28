//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

static SOutput OutData;

int ParseInput(const char* inPath)
{
    FILE* f = NULL;
    f = fopen(inPath, "r");

    if(f != NULL){
        int err = fscanf_s(f, "%d", &inData.n);

        if(err < 0){
            /* Read error handling */
        }else{
            inData.A = malloc(3*inData.n*sizeof(double*));
        }
    }else{
        /* Opening error handling */
    }
    return 0;
}

int FormOutput(char* outPath, double* data)
{
    return 0;
}

int lss_17_09(int n, double* A, double* B, double* X, double* tmp)
{
    int err_code = 0;
    if(IsDecompositionPossible(A, n) == TRUE){
        tmp[0] = A[0];
        
    }else{
        err_code = -1; // LU-decomposition is impossible
    }
    return err_code;
}

static BOOL IsDecompositionPossible(double* A, int n)
{
    BOOL exists = TRUE;

    for(int i = 0, j = 0; i < n && j < n - 1; i++, j++){
        exists = ( (fabs(A[i]) >= fabs(A[n + j] + A[2*n - 1 + j])) && NearlyEqual(A[2*n - 1 + j], 0, 1e-6) == FALSE) ? TRUE : FALSE;

        if(exists == FALSE){
            break;
        }
    }

    return exists;
}

static size_t lss_memsize_17_09(int n)
{
    return 3*n - 2;
}

static BOOL NearlyEqual(double a, double b, double tol)
{
    return (fabs(a - b) < tol) ? TRUE : FALSE;
}