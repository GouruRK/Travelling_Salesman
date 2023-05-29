/**
 * @file errors.c
 * @author Laborde Quentin & Kies Remy
 * @brief Print errors messages
 * @date 26-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>

#include "../include/errors.h"

void print_err(Errors err) {
    fprintf(stderr, "%sError%s - %s", RED, RESET, PURPLE);
    if (err == MEMORY_ERROR) {
        fprintf(stderr, "MemoryError%s\n", RESET);
    } else if (err == NON_NUMERIC_VALUE) {
        fprintf(stderr, "NonNumericValue%s : -k must be a positive integrer greater than 0\n", RESET);
    } else if (err == INT_OVERFLOW) {
        fprintf(stderr, "IntOverflow%s : -k must be a positive integrer greater than 0\n", RESET);
    } else if (err == INVALID_INT) {
        fprintf(stderr, "InvalidInt%s : -k must be a positive integrer greater than 0\n", RESET);
    } else if (err == FILE_NOT_FOUND) {
        fprintf(stderr, "FileNotFound%s : -p must be a valid filename or an integrer greater than 0\n", RESET);
    } else if (err == NO_POINTS) {
        fprintf(stderr, "NoPoints%s : user must select at least one point\n", RESET);
    }
}