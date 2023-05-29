/**
 * @file tools.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_TOOLS__
#define __INIT_TOOLS__

#include "struct.h"
#include "errors.h"

/**
 * @brief Random integrer between `min` and `max` include.
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int random_int(int min, int max);

/**
 * @brief Count the number of digits that compose an int.
 * 
 * @param n 
 * @return int 
 */
int int_size(int n);

/**
 * @brief Convert an integrer to a char.
 * 
 * @param n 
 * @return char* NULL if errer
 */
char* int_to_char(int n);

/**
 * @brief 
 * 
 * @param to_cast 
 * @param err 
 * @return int 
 */
int char_to_int(char* to_cast, Errors* err);

/**
 * @brief Duplicate a char*
 * 
 * @param c 
 * @return char* NULL if error
 */
char* strdup(const char* c);

/**
 * @brief Allocate more space to add cities in the `cities` array.
 * 
 * @param cities cities pointeur to realloc
 * @param length new length
 */
void realloc_cities(City ***cities, int* length);

/**
 * @brief Free memory allocated to cities and their names.
 * 
 * @param cities array of cities
 * @param length length of array
 */
void free_cities_deep(City ***cities, int length);

/**
 * @brief Free memory allocated to a map : its cities and their names.
 * 
 * @param map map to free
 */
void free_map(Map *map);

/**
 * @brief Free array of visits.
 * 
 * @param visit_tab array to free
 * @param length length of the array
 */
void free_visits(Visit** visit_tab, int length);

/**
 * @brief Calculate the distance between two cities.
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float distance_between_cities(City* a, City* b);

/**
 * @brief Calculate the total distance of an array of cities.
 * 
 * @param cities array of cities
 * @param length length of the array
 * @return float 
 */
float distance(City** cities, int length);

#endif
