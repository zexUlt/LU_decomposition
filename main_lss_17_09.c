//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

#define STR_END '\0'

BOOL isDebugModeEnabled = FALSE;
BOOL isEvaluationTimeNeeded = FALSE;
BOOL SuppressErrorMessages = TRUE;
BOOL PrintMatrix = FALSE;

SOutput OutData = {0};


static const char* commandline_params[] = {
    "-h", // 0
    "-d", // 1
    "-e", // 2
    "-t", // 3
    "-p" // 4
};

static const char* error_messages[] = {
        "...",
        "Incorrect commandline arguments.\n"
        "Please, see \"-h\" or \"-?\" for additional information.\n"
};

static const char help_message[] = "\n\n"
                             "Synopsis\n"
                             "========\n"
                             "\n"
                             "\n"
                             "./lss <options> [parameters]\n"
                             "\n"
                             "\n"
                             "Options\n"
                             "=======\n"
                             "\n"
                             "-h -- Shows list of available commands\n"
                             "-e -- Enables error messages during execution\n"
                             "-t -- Shows execution time at the end of execution\n"
                             "-d -- Enables printing debug messages\n"
                             "-p -- Shows input matrix\n"
                             "\n"
                             "-------\n"
                             "If none of the parameters were specified the default ones will be used.\n";

/**
 * @brief A function that checks string's equality
 * 
 * @param l_str first string
 * @param r_str second string
 * 
 * @return @b TRUE or @b FALSE enum values whether strings equal or not
 */
static BOOL IsStringsEqual(const char* l_str, const char* r_str);

/** 
 * @brief Function searches for specified string in given array of strings and returns index of that string, if found. 
 * 
 * @param in_str array of strings
 * @param in_str_size size of array of strings
 * @param str_to_find string which we are searching for
 * 
 * @return 
 * @arg index of @c str_to_find in @c in_str array, if success.
 * @arg -1, if given string is not presented in array.
 */
static short StrFind(const char* in_str[], int in_str_size, const char* str_to_find);

int main(int argc, char* argv[])
{
    clock_t start = clock();

    char inPath, outPath;
    BOOL shouldBeDefaultOut = TRUE;
    BOOL shouldBeDefaultIn = FALSE;
    short err = 0;


    if(argc > 1){
        for(int i = 1; i < argc; i++){
            BOOL isParsingFilePath = FALSE;
            short pos = StrFind(commandline_params, sizeof(commandline_params)/sizeof(char*), argv[i]);
            short pos_counter = 0;
            switch(i){
                case 1:
                    if(pos == -1){
                        inPath = i;
                        pos_counter++;
                        isParsingFilePath = TRUE;
                    }
                    break;
                case 2:
                    if(pos == -1){
                        if(pos_counter == 0){
                            outPath = i;
                            shouldBeDefaultOut = FALSE;
                            isParsingFilePath = TRUE;
                        }else{
                            err = 1;
                        }
                    }

                    break;
                default:
                    break;
            }
            if(isParsingFilePath == FALSE) {
                switch (pos) {
                    case 0: // -h
                        printf("%s", help_message);
                        err = 2;
                        break;
                    case 1: // -d
                        isDebugModeEnabled = TRUE;
                        break;
                    case 2: // -e
                        SuppressErrorMessages = FALSE;
                        break;
                    case 3: // -t
                        isEvaluationTimeNeeded = TRUE;
                        break;
                    case 4: // -p
                        PrintMatrix = TRUE;
                        break;
                    default:
                        err = -1;
                        printf("%s\n", error_messages[1]);
                }
            }
            if (err == -1) {
                break;
            }

        }
    }else{
        shouldBeDefaultOut = TRUE;
        shouldBeDefaultIn = TRUE;
    }
    
    // User made bad decision so show him up error message
    if(err == -1){
        LOG(Error, error_messages[err]);
        exit(INCORRECT_ARGS);
    }else{
        // err set to 0. So checking if default paths are needed
        if(shouldBeDefaultOut == TRUE){
            sprintf(OutData.outPath, "%s", "lss_00_00_out.txt");
        }else{
            sprintf(OutData.outPath, "%s", argv[outPath]);
        }
        if(shouldBeDefaultIn == TRUE){
            ParseInput("lss_00_00_in.txt");
        }else{
            ParseInput(argv[inPath]);
        }

        lss_main();
    }

    if(err == 2){ // Help option was chosen so no possible errors here. Changing err back to 0
        err = 0;
    }

    clock_t end = clock();

    if(isEvaluationTimeNeeded == TRUE) {
        float time = (float) (end - start) / CLOCKS_PER_SEC;
        printf("Total execution time %.2f sec\n", time);
    }
    return err;
}

static BOOL IsStringsEqual(const char* l_str, const char* r_str)
{
    BOOL equal = TRUE;
    if(l_str != NULL && r_str != NULL){
        short i = 0;
        while(l_str[i] != STR_END || r_str[i] != STR_END){
            
            equal = l_str[i] == r_str[i] ? TRUE : FALSE;
            i++;    
            
            if(equal == FALSE){
                break;
            }
        }
    }else{
        equal = FALSE;
    }

    return equal;
}

static short StrFind(const char* in_str[], int in_str_size, const char* str_to_find)
{
    short result = -1;
    for(int i = 0; i < in_str_size; i++){
        if(IsStringsEqual(in_str[i], str_to_find) == TRUE){
            result = i;
            break;
        }
    }

    return result;
}