/**
 * @file errors.h
 * @author Laborde Quentin & Kies Remy
 * @brief Print errors messages
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_ERRORS__
#define __INIT_ERRORS__

typedef enum {
    OK = 1,
    MEMORY_ERROR,
    NON_NUMERIC_VALUE,
    INT_OVERFLOW,
    FILE_NOT_FOUND,
    INVALID_INT,
    NO_POINTS,
} Errors;

#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define PURPLE "\x1b[35m"

/**
 * @brief Print an error message depending on the error code `err`.
 * 
 * @param err error code
 */
void print_err(Errors err);

#endif
