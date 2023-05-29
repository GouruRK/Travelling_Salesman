/**
 * @file main.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 25-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>

#include "include/struct.h" 
#include "include/parser.h"
#include "include/io.h"
#include "include/tools.h"
#include "include/errors.h"
#include "include/graphic.h"
#include "include/init.h"
#include "include/genetic.h"

Map strategy(Arguments args) {
    Map map;
    map.length = 0;
    map.cities = NULL;
    
    // begin by testing if args.points_system is a path
    FILE* file = fopen(args.points_system, "r");
    if (file) {
        map = file_to_map(file);
        fclose(file);
        return map;
    } else {
        // if not, test if it correspond to a number : the number of cities to generate
        Errors err;
        int nb_cities = char_to_int(args.points_system, &err);
        if (err != OK || !nb_cities) {
            print_err(FILE_NOT_FOUND);
            return map;
        }
        // generate nb_cities
        Window win = init_window();
        map.length = nb_cities;
        map.cities = create_random_cities(nb_cities, win);
        if (!(map.cities)) {
            map.length = 0;
        }
    }
    return map;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    Arguments args = init_arguments();
    if (!parse_arguments(&args, argc, argv)) {
        return 1;
    }

    if (args.help) {
        print_help();
        free_arguments(&args);
        return 0;
    }
    
    int stop = 0;
    MLV_execute_at_exit(exit_function, &stop);

    Map map;
    Window win = init_window();
    if (args.points_system) {
        map = strategy(args);
        if (!map.cities) {
            free_arguments(&args);
            return 1;
        }
        MLV_create_window("Travelling Salesman", "", win.width, win.height);
        MLV_clear_window(MLV_COLOR_WHITE);
        draw_panel(win, map.length, 0);
        draw_map(map, true);
        MLV_update_window();
    } else {
        map = select_cities_on_screen(&stop);
        if (stop) {
            free_arguments(&args);
            free_map(&map);
            MLV_free_window();
            return 0;
        }
        if (!map.cities) {
            free_arguments(&args);
            MLV_free_window();
            return 1;
        }
        if (!map.length) {
            free_arguments(&args);
            print_err(NO_POINTS);
            MLV_free_window();
            return 1;
        }
    }

    if (args.save) {
        FILE* file = fopen("map.txt", "w");
        write_map(map, file);
        fclose(file);
    }

    solve(map, args.population_length, win, &stop, args.verbose);

    free_arguments(&args);
    free_map(&map);
    MLV_free_window();
    return 0;
}
