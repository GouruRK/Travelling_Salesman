/**
 * @file tools.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/tools.h"
#include "../include/errors.h"
#include "../include/struct.h"

#define ALLOCATION_PATTERN 10

int random_int(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int int_size(int n) {
    int res = 0;
    if (!n) {
        return 1;
    }
    while (n) {
        n /= 10;
        res++;
    }
    return res;
}

char* int_to_char(int n) {
    int len = int_size(n);
    char* res = (char*)malloc(sizeof(char) * (len + 1));
    if (!res) {
        return NULL;
    }
    if (!n) {
        res[0] = '0';
        res[1] = '\0';
        return res;
    }
    for (int i = 0; i < len; i++) {
        res[len - i - 1] = '0' + n % 10;
        n /= 10;
    }
    res[len] = '\0';
    return res;
}

int char_to_int(char* to_cast, Errors* err) {
    int i = 0;
    int res = 0;
    long int keep = 0;
    int sign = -1;
    while (res >= 0 && to_cast[i] != '\0' && keep == res) {
        if (to_cast[i] == '-' && i == 0) {
            sign = 1;
        } else if ('0' <= to_cast[i] && to_cast[i] <= '9') {
            res *= 10;
            res += to_cast[i] - '0';
            keep *= 10;
            keep += to_cast[i] - '0';
        } else {
            *err = NON_NUMERIC_VALUE;
            return -1;
        }
        i++;
    }
    if (keep != res) {
        *err = INT_OVERFLOW;
        return -1;
    }
    *err = OK;
    return (-1 * sign) * res;
}

char* strdup(const char* c) {
    char* dup = malloc(strlen(c) + 1);

    if (dup != NULL)
        strcpy(dup, c);

    return dup;
}

void realloc_cities(City ***cities, int* length) {
    City **temp = *cities;
    temp = realloc(temp, sizeof(City*) * (*length + ALLOCATION_PATTERN));
    if (!temp) {
        free_cities_deep(cities, *length);
    } else {
        *length += ALLOCATION_PATTERN;
        *cities = temp;
    }
}

void free_cities_deep(City ***cities, int length) {
    for (int i = 0; i < length; i++) {
        free((*cities)[i]->name);
        free((*cities)[i]);
    }
    free(*cities);
}

void free_map(Map *map) {
    free_cities_deep(&(map->cities), map->length);
}

void free_visits(Visit** visit_tab, int length) {
    for (int i = 0; i < length; i++) {
        free((*visit_tab)[i].cities);
    }
    free((*visit_tab));
}

float distance_between_cities(City* a, City* b) {
    int delta_x = a->x - b->x;
    int delta_y = a->y - b->y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

float distance(City** cities, int length) {
    float dist = 0;
    for (int i = 0; i < length - 1; i++) {
        float temp = distance_between_cities(cities[i], cities[i + 1]);
        dist += temp;
    }
    return dist;
}
