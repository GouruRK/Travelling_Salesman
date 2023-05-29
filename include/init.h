/**
 * @file init.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_INIT__
#define __INIT_INIT__

#include "struct.h"

/**
 * @brief Create a city object
 * 
 * @param name 
 * @param x 
 * @param y 
 * @return City* 
 */
City* create_city(char* name, int x, int y);

/**
 * @brief Create a random city object
 * 
 * @param name 
 * @param win window dimensions
 * @return City* 
 */
City* create_random_city(char* name, Window win);

/**
 * @brief Create a random cities array
 * 
 * @param n 
 * @param win 
 * @return City** 
 */
City** create_random_cities(int n, Window win);

/**
 * @brief Create a map object
 * 
 * @param cities array of cities
 * @param length length of the array
 * @return Map 
 */
Map create_map(City** cities, int length);

/**
 * @brief Create a visit object
 * 
 * @param cities array of cities
 * @param length length of the array
 * @return Visit 
 */
Visit create_visit(City** cities, int length);

#endif
