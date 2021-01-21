//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

static SOutput OutData;

void ParseInput(const char* inPath)
{
    LOG(Debug, "Starting parsing input file\n");

    clock_t start = clock();

    FILE* f = NULL;
    int err_open = fopen_s(&f, inPath, "r");

    if(!err_open){
        int err = fscanf(f, "%d", &inData.n);

        if(err < 0){
            LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
            exit(-2);
        }else{
            inData.A = malloc(3*inData.n*sizeof(double*));
            inData.B = malloc(inData.n*sizeof(double*));
            err = fscanf(f, "%lf %lf", inData.A, (inData.A + 2*inData.n*sizeof(double*)) ); // first read to get odd line
            if(err < 2){
                LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                fclose(f);
                exit(-2);
            }else {
                for (int i = 1; i < inData.n - 1; i++) { // reading main lines which have same pattern
                    err = fscanf(f, "%lf %lf %lf", (inData.A + inData.n - 1 + i), // alpha
                                   (inData.A + i), // beta
                                   (inData.A + 2*inData.n - 1 + i)); // gamma
                    if(err < 3){
                        LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                        fclose(f);
                        exit(-2);
                    }
                }

                err = fscanf(f, "%lf %lf", (inData.A + 2 * inData.n - 1), (inData.A + inData.n - 1));

                if (err < 2) {
                    LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                    fclose(f);
                    exit(-2);
                }


                for(int i = 0; i < inData.n; i++){
                    err = fscanf(f, "%lf", (inData.B + i) );

                    if(err < 1){
                        LOG(Error, "Input file corrupted, does not have enough data or incorrect format.\n");
                        fclose(f);
                        exit(-2);
                    }
                }
            }
        }
    }else{
        /* Opening error handling */
        LOG(Error, "No such file or directory\n");
        fclose(f);
        exit(-1);
    }

    fclose(f);

    char buff[255];
    clock_t end = clock() - start;

    double time = (double) (end - start) / CLOCKS_PER_SEC;
    snprintf(buff, 255, "ParseInput finished  %.2lf sec\n", time);
    LOG(Debug, buff);
}
// TODO: Implementation
void FormOutput(const char* outPath, double* data, int err)
{
    LOG(Debug, "Forming output...\n");
    FILE* fptr = NULL;
    fopen_s(&fptr, outPath, "w");

    if(err == -1){
        fprintf(fptr, "%d", 0);
    }else{
        fprintf(fptr, "%d", inData.n);

        for(int i = 0; i < inData.n; i++){
            fprintf(fptr, "%1.9lf\n", data[i]);
        }
    }

    LOG(Debug, "Output formed. Terminating...\n");
}

void lss_main()
{
    LOG(Debug, "Entering lss_main\n");

    size_t size = lss_memsize_17_09(inData.n);

    double* tmp = malloc(size*sizeof(double*));
    OutData.X = malloc(inData.n*sizeof(double*));

    OutData.err_code = lss_17_09(inData.n, inData.A, inData.B, OutData.X, tmp);

    FormOutput(OutData.outPath, OutData.X, OutData.err_code);

    ReleaseMemory();
}

int lss_17_09(int n, double* A, double* B, double* X, double* tmp)
{
    int err_code = 0;
    if(IsDecompositionPossible(A, n) == TRUE){
        LOG(Debug, "LU-decomposition is possible. Decomposing...\n");

        clock_t start = clock();

        for(int i = 0; i < inData.n - 1; i++){
            A[2*n - 1 + i] /= A[i]; // gammas
            A[i + 1] -= A[n + i + 1] * A[2*n - 1 + i]; // betas
        }

        LOG(Debug, "Straight pass part started...\n");
        tmp[0] = B[0] / A[0];
        for(int i = 1; i < inData.n; i++){ // Straight pass
            tmp[i] = (B[i] - A[n + i] * tmp[i - 1]) / A[i];
        }
        LOG(Debug, "Straight pass finished\n");
        LOG(Debug, "Reverse pass part started...\n");
        X[n - 1] = tmp[n - 1];
        for(int i = inData.n - 2; i >= 0; i--){ // Reverse pass
            X[i] = tmp[i] - A[2*n - 1 + i] * X[i + 1];
        }
        LOG(Debug, "Reverse pass finished\n");

        clock_t end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        char buff[255];
        sprintf(buff, "LSE solution finished in %.2lf\n", time);
        LOG(Debug, buff);
    }else{
        LOG(Debug, "LU-decomposition is impossible\n");
        err_code = -1; // LU-decomposition is impossible
    }
    return err_code;
}

static BOOL IsDecompositionPossible(double* A, int n)
{
    LOG(Debug, "Checking if LU-decomposition even possible...\n");
    BOOL exists = TRUE;

    for(int i = 0, j = 0; i < n && j < n - 1; i++, j++){
        exists = ( (fabs(A[i]) >= fabs(A[n + j] + A[2*n - 1 + j])) &&
                NearlyEqual(A[2*n - 1 + j], 0, 1e-6) == FALSE) ? TRUE : FALSE;

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

void log_(LogType mode, const char* msg)
{
    if(mode == Debug){
        if(isDebugModeEnabled == TRUE){
            printf_s("LogMessage: %s", msg);
        }
    }else{
        if(SuppressErrorMessages == FALSE){
            printf("Error: %s", msg);
        }
    }
}

void ReleaseMemory()
{
    free(inData.A);
    free(inData.B);
    free(OutData.X);
}