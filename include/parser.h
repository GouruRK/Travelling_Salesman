/**
 * @file parser.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_PARSER__
#define __INIT_PARSER__

#include "errors.h"

typedef struct {
    bool verbose;
    bool save;
    bool help;
    char* points_system;
    int population_length;
} Arguments;

/**
 * @brief Set default parameters to an Arguments object.
 * 
 * @return Arguments 
 */
Arguments init_arguments(void);

/**
 * @brief Parse `argv` input from command line and modify `args` in consequence. 
 * 
 * @param args contains default arguments
 * @param argc number of arguments in `argv`
 * @param argv command line arguments
 * @return Errors 
 */
Errors argument_parser(Arguments* args, int argc, char* argv[]);

int parse_arguments(Arguments* args, int argc, char* argv[]);

/**
 * @brief Free memory allocated to `args.point_system`
 * 
 * @param args 
 */
void free_arguments(Arguments* args);

#endif
