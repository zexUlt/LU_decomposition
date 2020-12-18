//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

static SOutput OutData;

int ParseInput(char* inPath)
{
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

    }else{
        err_code = -1; // LU-decomposition is impossible
    }
    return err_code;
}

BOOL IsSolutionExists(double* A, int n)
{
    BOOL exists = TRUE;

    for(int i = 0, j = 0; i < n && j < n - 1; i++, j++){
        exists = ( (A[i] >= A[n + j] + A[2*n - 1 + j]) && A[2*n - 1 + j] != 0) ? TRUE : FALSE;

        if(exists == FALSE){
            break;
        }
    }

    return exists;
}