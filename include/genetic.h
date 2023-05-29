/**
 * @file genetic.h
 * @author Laborde Quentin & Kies Remy
 * @brief Functions used in genetic programming
 * @date 27-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_GENETIC__
#define __INIT_GENETIC__

#include "struct.h"

#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/init.h"
#include "../include/graphic.h"

/**
 * @brief Duplicate a visit.
 * 
 * @param visit visit to duplicate
 * @return Visit copy of visit
 */
Visit duplicate_visit(Visit visit);

/**
 * @brief Create an array of mixed cities from `cities` array.
 * 
 * @param cities array to mix
 * @param length length of this array
 * @return City** new array of cities
 */
City** mix_cities(City** cities, int length);

/**
 * @brief Mutate a visit : exchange two portions of the cities array and return the new array.
 * 
 * @param visit visit to mutate
 * @return Visit new visit
 */
Visit mut(Visit visit);

/**
 * @brief Compare two visits based on their distances.
 * 
 * @param a first visit to compare
 * @param b second visit to compare
 * @return int 0 if the distances are equals
 *             negative if the distance of `b` is greater than the distance of `a`
 *             positive if the distance of `a` is greater then the distance of `b`
 */
int compare_visits(const void* a, const void* b);

/**
 * @brief Sort visits of a population based on the distance of its visits.
 * 
 * @param pop population to sort the visits 
 */
void sort_population(Population* pop);

/**
 * @brief Create a population object
 * 
 * @param map based map
 * @param length length of the visits array
 * @return Population
 */
Population create_population(Map map, int length);

/**
 * @brief Inherit a population, to create one with a smaller distance
 * 
 * @param pop 
 */
void _inherit(Population* pop);

/**
 * @brief Inherit a population, to create one with a smaller distance.
 *        The visit with the smaller distance is placed on index 0.
 * 
 * @param pop 
 */
void inherit(Population* pop);

/**
 * @brief Solve the travelling salesman problem, and manage the associated window.
 * 
 * @param map Map to solve
 * @param length length of the population's visits
 * @param win window settings
 * @param stop stop arguments for the window. Set to '1' if the user close the window
 * @param verbose indicate to write in the stardard oupout all visits
 */
void solve(Map map, int length, Window win, int* stop, bool verbose);

#endif
