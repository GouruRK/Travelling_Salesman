/**
 * @file io.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_IO__
#define __INIT_IO__

#include <stdio.h>

#include "struct.h"

/**
 * @brief Count the lines of the file `file`.
 * 
 * @param file 
 * @return int 
 */
int count_lines(FILE* file);

/**
 * @brief Insert City* in the cities array of length `length` from the source file `file`.
 * 
 * @param cities array to insert cities
 * @param length length of the array
 * @param file source file
 * @return int 
 */
int insert_cities(City*** cities, int length, FILE* file);

/**
 * @brief Create a map based of the file `file`.
 * 
 * @param file 
 * @return Map 
 */
Map file_to_map(FILE* file);

/**
 * @brief Print in stdout cities and the distance.
 * 
 * @param visit 
 */
void print_visit(Visit visit);

/**
 * @brief Write in the file `file` the map information.
 * 
 * @param map 
 * @param file file to write
 */
void write_map(Map map, FILE* file);

/**
 * @brief Print in stdout the help message.
 * 
 */
void print_help(void);

#endif
