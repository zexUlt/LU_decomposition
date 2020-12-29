//
// Created by ZexUlt on 14.12.2020.
//

#include "lss_17_09.h"

#define STR_END '\0'

BOOL isDebugModeEnabled = FALSE;
BOOL isEvaluationTimeNeeded = FALSE;
BOOL SuppressErrorMessages = TRUE;


static const char* commandline_params[] = {
    "-i",
    "-o",
    "-h",
    "-d",
    "-e",
    "-t"
};

static const char* error_messages[] = {
        "...",
        "Incorrect commandline arguments.\n"
        "Please, see \"-h\" or \"-?\" for additional information.\n",
        ""
};

static const char help_message[] = ""
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
 * @brief A function that checks string's equality
 * 
 * @param l_str first string
 * @param r_str second string
 * 
 * @return @b TRUE or @b FALSE enum values whether strings equal or not
 */
static BOOL IsStringsEqual(const char* l_str, const char* r_str);

/**
 * @brief This is a starting point of a program
 * 
 * @param argc - Amount of commandline arguments
 * @param argv - Commandline options array, possible options:
 * @arg @c -i for input-file path. Default path is @c "./17_1_09in.txt".
 * @arg @c -o for output-file path. Default path is @c "./17_1_09out.txt".
 * @arg @c -d for enabling debug logging. Disabled by default.
 * @arg @c -e for enabling error messages. Suppressed by default.
 * @arg @c -t for enabling execution time at the end of execution. Disabled by default. 
 * 
 * @return - Exit code.
 *
 */
int main(int argc, char* argv[])
{
    char* inPath, outPath;
    const char* default_in_path = "lss_17_09_in.txt";
    const char* default_out_path = "lss_17_09_out.txt";
    BOOL shouldBeDefaultIn = FALSE;
    BOOL shouldBeDefaultOut = FALSE;
    int err = 0;
    switch (argc) {
        case 1:
        shouldBeDefaultIn = TRUE;
        shouldBeDefaultOut = TRUE;
            break;
        case 2:
            if(IsStringsEqual(argv[1], commandline_params[2])){
                printf_s("%s", help_message);
                err = -1;
            }else{
                err = 1;
            }
            break;
        case 3:
            if(IsStringsEqual(argv[1], commandline_params[0])){
                shouldBeDefaultOut = TRUE;
            }else if(IsStringsEqual(argv[1], commandline_params[1])){
                shouldBeDefaultIn = TRUE;
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

        if(shouldBeDefaultIn == TRUE){
            if(shouldBeDefaultOut == TRUE){
                FormOutput(default_out_path, NULL);
            }else{
                FormOutput(argv[2], NULL);
            }
            ParseInput(default_in_path);
        }else{
            if(shouldBeDefaultOut == TRUE){
                FormOutput(default_out_path, NULL);
            }else{
                FormOutput(argv[4], NULL);
            }
            ParseInput(argv[2]);
        }
    }

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