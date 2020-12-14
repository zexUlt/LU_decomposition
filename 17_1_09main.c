//
// Created by ZexUlt on 14.12.2020.
//

#include "17_1_09intf.h"

#include <stdlib.h>
#include <stdio.h>

#define PARAM_IN "-i"
#define PARAM_OUT "-o"
#define PARAM_HELP "-help"

static char* error_messages[] = {
        "...",
        "Incorrect commandline arguments.\n"
        "Please, see \"-help\" for additional information.\n",
        ""
};

static char help_message[] = ""
                             "Synopsis\n"
                             "========\n"
                             "\n"
                             "\n"
                             "task2.exe <options> [parameters]\n"
                             "\n"
                             "\n"
                             "Options\n"
                             "=======\n"
                             "\n"
                             "-i -- Specifies input file path\n"
                             "-o -- Specifies output file path\n"
                             "\n"
                             "-------"
                             "If none of the parameters were specified the default ones will be used.\n";
/**
 * This is a starting point of a program
 * @param argc - Amount of commandline arguments
 * @param argv - To distinguish between omitting one of the two arguments, use the options:
 * >>> -i for input-file path
 * >>> -o for output-file path
 * If none were mentioned the default path's will be used
 * @return - Exit code
 *
 */
int main(int argc, char* argv[])
{
    char* inPath, outPath;
    int err = 0;
    switch (argc) {
        case 1:
#define DEFAULT_IN "17_1_09in.txt"
#define DEFAULT_OUT "17_1_09out.txt"
            break;
        case 2:
            if(argv[1] == PARAM_HELP){
                printf_s("%s", help_message);
                err = -1;
            }else{
                err = 1;
            }
            break;
        case 3:
            if(argv[1] == PARAM_IN){
#define DEFAULT_OUT "17_1_09out.txt"
            }else if(argv[1] == PARAM_OUT){
#define DEFAULT_IN "17_1_09in.txt"
            }else err = 1;
            break;
        case 4:
            err = 1;
            break;
    }

    if(err == 1){
        printf_s("%s", error_messages[err]);
    }else if(err == -1){
        return err;
    }else{
#ifndef DEFAULT_IN

#endif
    }
    return err;
}