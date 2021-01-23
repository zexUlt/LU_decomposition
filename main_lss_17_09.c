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
    "-i", // 0
    "-o", // 1
    "-h", // 2
    "-d", // 3
    "-e", // 4
    "-t", // 5
    "-p" // 6
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
                             "-i -- Specifies input file path\n"
                             "-o -- Specifies output file path\n"
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
static int StrFind(const char* in_str[], int in_str_size, const char* str_to_find);

int main(int argc, char* argv[])
{
    clock_t start = clock();

    char* inPath, *outPath;
    const char* default_in_path = "lss_17_09_in.txt";
    const char* default_out_path = "lss_17_09_out.txt";
    BOOL shouldBeDefaultIn = TRUE;
    BOOL shouldBeDefaultOut = TRUE;
    int err = 0;

//    printf("%s\n%s", argv[0], argv[1]);

    if(argc > 1){
        for(int i = 1; i < argc; i++){
            int test_pos;
            int pos = StrFind(commandline_params, sizeof(commandline_params)/sizeof(char*), argv[i]);
            switch(pos){
                case 0: // -i
                    // Test if there is filepath provided
                    test_pos = StrFind(commandline_params, sizeof(commandline_params)/sizeof(char*), argv[i+1]);
                    if(test_pos == -1){
                        inPath = argv[++i];
                        shouldBeDefaultIn = FALSE;
                    }else{
                        err = 1;
                    }
                    break;
                case 1: // -o
                    test_pos = StrFind(commandline_params, sizeof(commandline_params)/sizeof(char*), argv[i+1]);
                    if(test_pos == -1){
                        outPath = argv[++i];
                        shouldBeDefaultOut = FALSE;
                    }else{
                        err = 1;
                    }
                    break;
                case 2: // -h
                    printf_s("%s", help_message);
                    err = 2;
                    break;
                case 3: // -d
                    isDebugModeEnabled = TRUE;
                    break;
                case 4: // -e
                    SuppressErrorMessages = FALSE;
                    break;
                case 5: // -t
                    isEvaluationTimeNeeded = TRUE;
                    break;
                case 6: // -p
                    PrintMatrix = TRUE;
                    break;
                default:
                    err = -1;
                    printf("%s\n", error_messages[1]);
            }
            if(err == -1){
                break;
            }
            
        }
    }
    
    // User made bad decision so show him up error message
    if(err == 1){
        LOG(Error, error_messages[err]);
    }else if(err == -1){
        return err;
    }else{
        // err set to 0. So checking if default paths are needed
        if(shouldBeDefaultIn == TRUE){
            if(shouldBeDefaultOut == TRUE){
                sprintf(OutData.outPath, "%s", default_out_path);
            }else{
                sprintf(OutData.outPath, "%s", outPath);
            }
            ParseInput(default_in_path);
        }else{
            if(shouldBeDefaultOut == TRUE){
                sprintf(OutData.outPath, "%s", default_out_path);
            }else{
                sprintf(OutData.outPath, "%s", outPath);
            }
            ParseInput(inPath);
        }

        lss_main();
    }

    if(err == 2){ // Help option was chosen so no possible errors here. Changing err back to 0
        err = 0;
    }

    clock_t end = clock();

    char buff[255];

    double time = (double) (end - start) / CLOCKS_PER_SEC;
    snprintf(buff, 255, "Total execution time %.2lf sec\n", time);
    LOG(Debug, buff);

    return err;
}

static BOOL IsStringsEqual(const char* l_str, const char* r_str)
{
    BOOL equal = TRUE;
    if(l_str != NULL && r_str != NULL){
        int i = 0;
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

static int StrFind(const char* in_str[], int in_str_size, const char* str_to_find)
{
    int result = -1;
    for(int i = 0; i < in_str_size; i++){
        if(IsStringsEqual(in_str[i], str_to_find) == TRUE){
            result = i;
            break;
        }
    }

    return result;
}