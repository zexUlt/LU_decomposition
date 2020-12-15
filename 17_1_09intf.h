//
// Created by ZexUlt on 14.12.2020.
//

#ifndef DIFFEQ_PRACTICE2020_TASK2_17_1_09INTF_H
#define DIFFEQ_PRACTICE2020_TASK2_17_1_09INTF_H

typedef struct {
    char* outPath;
}SOutput;

static SOutput OutData;

int ParseInput(char* inPath);
int FormOutput(char* outPath, double* data);

#endif //DIFFEQ_PRACTICE2020_TASK2_17_1_09INTF_H

