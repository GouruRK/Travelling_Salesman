/**
 * @file io.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 26-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/init.h"
#include "../include/io.h"

#define BUFFER_CHAR 256

int count_lines(FILE *file) {
    char c[BUFFER_CHAR];
    int x, y, acc = 0;
    while (fscanf(file, "%s %d %d\n", c, &x, &y) != EOF) {
        acc++;
    }
    return acc;
}

int insert_cities(City ***cities, int length, FILE *file) {
    char c[BUFFER_CHAR], *name;
    int x, y, acc = 0;
    while (fscanf(file, "%s %d %d\n", c, &x, &y) != EOF) {
        name = strdup(c);
        if (!name) {
            free_cities_deep(cities, acc);
            *cities = NULL;
            return 0;
        }

        (*cities)[acc] = create_city(name, x, y);
        if (!(*cities)[acc]) {
            free_cities_deep(cities, acc);
            *cities = NULL;
            return 0;
        }

        acc++;
    }
    return 1;
}

Map file_to_map(FILE* file) {
    int lines = count_lines(file);
    
    Map map;
    map.length = lines;
    map.cities = (City**)malloc(sizeof(City*) * lines);
    if (!(map.cities)) {
        return map;
    }

    fseek(file, 0, SEEK_SET);

    if (!insert_cities(&(map.cities), lines, file)) {
        map.length = 0;
    }
    return map;
}

void print_visit(Visit visit) {
    for (int i = 0; i < visit.length; i++) {
        if (i == visit.length - 1) {
            printf("%s : ", visit.cities[i]->name);
        } else {
            printf("%s -> ", visit.cities[i]->name);
        }
    }
    printf("%.2f\n", visit.distance);
}

void write_map(Map map, FILE* file) {
    City *city;
    for (int i = 0; i < map.length; i++) {
        city = map.cities[i];
        fprintf(file, "%s %d %d\n", city->name, city->x, city->y);
    }
}

void print_help(void) {
    printf("./travelling_salesman [-p arg] [-k arg] [-v] [-s] [-h]\n");
    printf("\t[-p] Define the point system to use\n");
    printf("\t\tRequire an integrer greather than 0 for the number of points, or a path to a file with points coordinates\n");
    printf("\t\tNo [-p] allows the user to select manually his points\n");
    printf("\t\tDefault : NULL\n\n");
    printf("\t[-k] Define the number of differents visits\n");
    printf("\t\tRequire an integrer greather than 0\n");
    printf("\t\tDefault : 128\n\n");
    printf("\t[-v] Indicate to print the best path between points\n");
    printf("\t\tDefault : false\n\n");
    printf("\t[-s] Indicate to save the points coordinates in a file called 'map.txt'\n");
    printf("\t\tDefault : false\n\n");
    printf("\t[-h] Print this message\n");
    printf("\t\tDefault : false\n");
}
