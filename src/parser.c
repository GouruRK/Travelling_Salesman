/**
 * @file parser.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#include "../include/parser.h"
#include "../include/errors.h"
#include "../include/tools.h"

Arguments init_arguments(void) {
    Arguments args;
    args.verbose = false;
    args.save = false;
    args.help = false;
    args.points_system = NULL;
    args.population_length = 128;
    return args;
}

Errors argument_parser(Arguments* args, int argc, char* argv[]) {
    opterr = 0;
    int opt, length;
    Errors err;
    while ((opt = getopt(argc, argv, "hsvp:k:")) != -1) {
        switch (opt) {
            case 'v':
                args->verbose = true;
                break;
            case 'k':
                args->population_length = char_to_int(optarg, &err);
                if (err != OK) {
                    return err;
                }
                if (args->population_length <= 0) {
                    return INVALID_INT;
                } 
                break;
            case 'p':
                length = strlen(optarg);
                args->points_system = (char*)malloc(sizeof(char) * (length + 1));
                if (!args->points_system) {
                    return MEMORY_ERROR;
                }
                strcpy(args->points_system, optarg);
                break;
            case 's':
                args->save = true;
                break;
            case 'h':
                args->help = true;
                break;
        }
    }
    return OK;
}

int parse_arguments(Arguments* args, int argc, char* argv[]) {
    if (argc == 1) {
        return 1;
    }

    Errors err = argument_parser(args, argc, argv);
    if (err == OK) {
        return 1;
    }
    print_err(err);
    free_arguments(args);
    return 0;
}

void free_arguments(Arguments* args) {
    if (args->points_system) {
        free(args->points_system);
    }
}
