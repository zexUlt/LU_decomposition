//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

static SOutput OutData;

int ParseInput(const char* inPath)
{
    FILE* f = NULL;
    int err_open = fopen_s(&f, inPath, "r");

    if(!err_open){
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

int FormOutput(const char* outPath, double* data)
{
    return 0;
}

int lss_17_09(int n, double* A, double* B, double* X, double* tmp)
{
    int err_code = 0;
    if(IsDecompositionPossible(A, n) == TRUE){

        for(int i = 0; i < inData.n - 1; i++){
            A[2*n - 1 + i] /= A[i]; // gammas
            A[i + 1] -= A[n + i + 1] * A[2*n - 1 + i]; // betas
        }

        tmp[0] = B[0] / A[0];
        for(int i = 1; i < inData.n; i++){ // Straight pass
            tmp[i] = (B[i] - A[n + i] * tmp[i - 1]) / A[i];
        }

        X[n - 1] = tmp[n - 1];
        for(int i = inData.n - 2; i >= 0; i--){ // Reverse pass
            X[i] = tmp[i] - A[2*n - 1 + i] * X[i + 1];
        }

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
    return n;
}

static BOOL NearlyEqual(double a, double b, double tol)
{
    return (fabs(a - b) < tol) ? TRUE : FALSE;
}