/**
 * @file init.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <stdbool.h>

#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/init.h"

#define PANEL_MARGIN 15

City *create_city(char* name, int x, int y) {
    City *city = (City*)malloc(sizeof(City));
    if (city) {
        city->name = name;
        city->x = x;
        city->y = y;
    }
    return city;
}

City *create_random_city(char* name, Window win) {
    return create_city(name, random_int(0, win.width), random_int(0, win.curr_height - PANEL_MARGIN));
}

City **create_random_cities(int n, Window win) {
    City **cities = (City**)malloc(sizeof(City*) * n);
    if (cities) {
        for (int i = 0; i < n; i++) {
            char* name = int_to_char(i);
            if (name) {
                cities[i] = create_random_city(name, win);
            } else {
                free_cities_deep(&cities, i);
                return NULL;
            }
        }
    }
    return cities;
}

Map create_map(City **cities, int length) {
    Map map;
    map.cities = cities;
    map.length = length;
    return map;
}

Visit create_visit(City **cities, int length) {
    Visit visit;
    visit.cities = cities;
    visit.length = length;
    visit.distance = distance(cities, length);
    return visit;
}
