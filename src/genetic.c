/**
 * @file genetic.c
 * @author Laborde Quentin & Kies Remy
 * @brief Functions used in genetic programming
 * @date 27-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/init.h"
#include "../include/graphic.h"
#include "../include/io.h"
#include "../include/genetic.h"

Visit duplicate_visit(Visit visit) {
    Visit new;
    new.cities = (City**)malloc(sizeof(City*) * visit.length);
    if (!(new.cities)) {
        new.length = 0;
        new.distance = 0;
        return new;
    }
    for (int i = 0; i < visit.length; i++) {
        new.cities[i] = visit.cities[i];
    }
    new.length = visit.length;
    new.distance = visit.distance;
    return new;
}

City** mix_cities(City** cities, int length) {
    City** new = (City**)calloc(length, sizeof(City*));
    if (!new) {
        return NULL;
    }

    // keeping the same starting point 
    new[0] = cities[0];

    int n;
    for (int i = 1; i < length; i++) {
        do {
            n = random_int(1, length - 1);
        } while (new[n]);
        new[n] = cities[i];
    }
    return new;
}

Visit mut(Visit visit) {
    int l = random_int(0, (visit.length - 1) / 2);
    int i = random_int(1, visit.length - 2 * l);
    int j = random_int(i + l, visit.length - l);

    Visit new = duplicate_visit(visit);

    City* temp;
    for (int k = 0; k < l; k++) {
        temp = (new.cities)[i + k];
        (new.cities)[i + k] = (new.cities)[j + k];
        (new.cities)[j + k] = temp; 
    }
    new.distance = distance(new.cities, new.length);
    return new;
}

int compare_visits(const void* a, const void* b) {
    Visit* v1 = (Visit*)a;
    Visit* v2 = (Visit*)b;
    return v1->distance - v2->distance;
}

void sort_population(Population* pop) {
    qsort(pop->visits, pop->length, sizeof(Visit), compare_visits);
}

Population create_population(Map map, int length) {
    Population pop;
    pop.map = map;
    pop.length = 0;
    pop.visits = (Visit*)malloc(sizeof(Visit) * length);
    if (!(pop.visits)) {
        return pop;
    }

    City** cities;
    for (int i = 0; i < length; i++) {
        cities = mix_cities(map.cities, map.length);
        if (!cities) {
            free_visits(&(pop.visits), i);
            return pop;
        }
        pop.visits[i] = create_visit(cities, map.length);
    }
    pop.length = length;
    pop.nb_mut = (45 * length) / 100;
    pop.nb_copy = (10 * length) / 100;
    pop.nb_random = (45 * length) / 100;
    if (pop.nb_mut + pop.nb_copy + pop.nb_random != length) {
        pop.nb_mut += (length - (pop.nb_copy + pop.nb_mut + pop.nb_random));
    }
    sort_population(&pop);
    return pop;
}

void _inherit(Population* pop) {
    Visit* new_visits = (Visit*)malloc(sizeof(Visit) * pop->length);
    if (!new_visits) {
        return;
    }
    int i = 0;
    City** cities;
    for (int j = 0; j < pop->nb_mut; i++, j++) {
        new_visits[i] = mut(pop->visits[j]);
        if (!(new_visits[i].cities)) {
            free_visits(&new_visits, i);
            return;
        }
    }
    for (int j = 0; j < pop->nb_copy; i++, j++) {
        new_visits[i] = duplicate_visit(pop->visits[j]);
        if (!(new_visits[i].cities)) {
            free_visits(&new_visits, i);
            return;
        }
    }
    for (int j = 0; j < pop->nb_random; i++, j++) {
        cities = mix_cities(pop->map.cities, pop->map.length);
        if (!cities) {
            free_visits(&new_visits, i);
            return;
        }
        new_visits[i] = create_visit(cities, pop->map.length);
    }
    free_visits(&(pop->visits), pop->length);
    pop->visits = new_visits;
}

void inherit(Population* pop) {
    _inherit(pop);
    sort_population(pop);
}

void solve(Map map, int length, Window win, int* stop, bool verbose) {
    Population pop = create_population(map, length);
    if (!(pop.visits)) {
        return;
    }
    float dist_min = pop.visits[0].distance;
    
    bool display_name = true;
    bool is_s_pressed = false;
    bool pause = false;
    bool is_p_pressed = false;

    draw_population(&pop, win, display_name);

    while (!(*stop)) {
        MLV_update_window();
        
        if (is_pressed(MLV_KEYBOARD_p, MLV_PRESSED) && !is_p_pressed) {
            pause = !pause;
            is_p_pressed = true;
        } else if (is_pressed(MLV_KEYBOARD_p, MLV_RELEASED) && is_p_pressed) {
            is_p_pressed = false;
        }
        
        if (pause) {
            continue;
        }

        if (is_pressed(MLV_KEYBOARD_s, MLV_PRESSED) && !is_s_pressed) {
            display_name = !display_name;
            is_s_pressed = true;
        } else if (is_pressed(MLV_KEYBOARD_s, MLV_RELEASED) && is_s_pressed) {
            is_s_pressed = false;
        }
        
        inherit(&pop);
        if (dist_min > pop.visits[0].distance) {
            dist_min = pop.visits[0].distance; 
            draw_population(&pop, win, display_name);
            if (verbose) {
                print_visit(pop.visits[0]);
            }
        }
    }
}
