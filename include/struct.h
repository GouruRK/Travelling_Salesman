/**
 * @file struct.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

#include <stdbool.h>

typedef struct {
    int x;
    int y;
    char* name;
} City;

typedef struct {
    City** cities;
    int length;
} Map;

typedef struct {
    City** cities;
    int length;
    float distance;
} Visit;

typedef struct {
    Visit* visits;
    int length;
    Map map;
    int nb_mut;
    int nb_copy;
    int nb_random;
} Population;

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int panel_height;
    unsigned int curr_height;
} Window;

#endif
