//
// Created by ZexUlt on 14.12.2020.
//

#include "17_1_09intf.h"

#include <stdlib.h>
#include <stdio.h>

#define STR_END '\0'

typedef enum{
    FALSE,
    TRUE
}BOOL;

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
 * @param l_str - first string
 * @param r_str - second string
 * 
 * @return - TRUE or FALSE enum values whether strings equal or not
 */
static BOOL IsStringsEqual(const char* l_str, const char* r_str);

/**
 * @brief This is a starting point of a program
 * 
 * @param argc - Amount of commandline arguments
 * @param argv - Commandline options array, possible options:
 * @arg -i for input-file path. Default path is "./17_1_09in.txt".
 * @arg -o for output-file path. Default path is "./17_1_09out.txt".
 * @arg -d for enabling debug logging. Disabled by default.
 * @arg -e for enabling error messages. Suppressed by default.
 * @arg -t for enabling execution time at the end of execution. Disabled by default. 
 * 
 * @return - Exit code.
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
            if(IsStringsEqual(argv[1], commandline_params[2])){
                printf_s("%s", help_message);
                err = -1;
            }else{
                err = 1;
            }
            break;
        case 3:
            if(IsStringsEqual(argv[1], commandline_params[0])){
#define DEFAULT_OUT "17_1_09out.txt"
            }else if(IsStringsEqual(argv[1], commandline_params[1])){
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

#ifdef DEFAULT_IN
#ifdef DEFAULT_OUT
    FormOutput(DEFAULT_OUT, NULL);
#else // ELSE DEFAULT_OUT
    FormOutput(argv[2], NULL);
#endif // DEFAULT_OUT
    ParseInput(DEFAULT_IN);
#else // ELSE DEFAULT_IN
#ifdef DEFAULT_OUT
    FormOutput(DEFAULT_OUT, NULL);
#else // ELSE DEFAULT_OUT
    FormOutput(argv[4], NULL);
#endif // DEFAULT_OUT
    ParseInput(argv[2]);
#endif // DEFAULT_IN
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