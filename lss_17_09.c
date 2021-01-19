//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

static SOutput OutData;

int ParseInput(const char* inPath)
{
    LOG(Debug, "Starting parsing input file\n");

    FILE* f = NULL;
    int err_open = fopen_s(&f, inPath, "r");
    int err_code = 0;

    if(!err_open){
        int err = fscanf_s(f, "%d", &inData.n);

        if(err < 0){
            LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
            err_code = -2;
        }else{
            inData.A = malloc(3*inData.n*sizeof(double*));
            err = fscanf_s(f, "%lf %lf", inData.A, (inData.A + 2*inData.n*sizeof(double*)) ); // first read to get odd line
            if(err < 2){
                LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                err_code = -2;
            }else {
                for (int i = 1; i < inData.n - 1; i++) { // reading main lines which have same pattern
                    err = fscanf_s(f, "%lf %lf %lf", (inData.A + inData.n - 1 + i), // alpha
                                   (inData.A + i), // beta
                                   (inData.A + 2*inData.n - 1 + i)); // gamma
                    if(err < 3){
                        LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                        err_code = -2;
                    }

                    if(err_code == -2){
                        break;
                    }
                }

                if(err_code != -2) {
                    err = fscanf_s(f, "%lf %lf", (inData.A + 2 * inData.n - 1), (inData.A + inData.n - 1));

                    if (err < 2) {
                        LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                        err_code = -2;
                    }
                }
            }
        }
    }else{
        /* Opening error handling */
        LOG(Error, "No such file or directory\n");
        err_code = -1;
    }
    return err_code;
}
// TODO: Implementation
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