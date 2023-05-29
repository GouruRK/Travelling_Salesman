/**
 * @file graphic.c
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 26-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../include/graphic.h"
#include "../include/init.h"
#include "../include/tools.h"

#define CITY_RADIUS 1
#define TEXT_MARGIN 10

void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

bool is_pressed(MLV_Keyboard_button key, MLV_Button_state expected) {
    return MLV_get_keyboard_state(key) == expected;
}

bool is_clicked(MLV_Mouse_button button, MLV_Button_state expected) {
    return MLV_get_mouse_button_state(button) == expected;
}

Window init_window(void) {
    Window win;
    MLV_get_desktop_size(&(win.width), &(win.height));
    win.panel_height = 50;
    win.height -= 100;
    win.width -= 50;
    win.curr_height = win.height - win.panel_height;
    return win;
}

Map select_cities_on_screen(int* stop) {
    Window win = init_window();
    MLV_create_window("Travelling Salesman", "", win.width, win.height);
    MLV_clear_window(MLV_COLOR_WHITE);
    draw_panel(win, 0, 0);
    MLV_update_window();
    
    int max_len = 10, x, y;
    char* name;
    
    Map map;
    map.length = 0;
    map.cities = (City**)malloc(sizeof(City*) * max_len);
    if (!(map.cities)) {
        return map;
    }

    bool is_click = false;
    while (!(*stop)) {
        if (is_clicked(MLV_BUTTON_LEFT, MLV_PRESSED) && !is_click) {
            is_click = true;
            MLV_get_mouse_position(&x, &y);
            name = int_to_char(map.length);
            if (!name) {
                free_cities_deep(&(map.cities), map.length);
                map.cities = NULL;
                map.length = 0;
                return map;
            }
            map.cities[map.length] = create_city(name, x, y);
            if (!map.cities[map.length]) {
                free_cities_deep(&(map.cities), map.length);
                map.cities = NULL;
                map.length = 0;
                return map;
            }

        
            draw_city(map.cities[map.length], false);
            hide_panel(win);
            draw_panel(win, map.length, 0);
            MLV_update_window();

            map.length++;

            if (map.length == max_len) {
                realloc_cities(&(map.cities), &max_len);
                if (!map.cities) {
                    map.length = 0;
                    return map;
                }
            }
        } else if (is_clicked(MLV_BUTTON_LEFT, MLV_RELEASED)) {
            is_click = false;
        }
        if (is_pressed(MLV_KEYBOARD_SPACE, MLV_PRESSED)) {
            if (!(map.length)) {
                free_map(&map);
                map.length = 0;
                return map;
            }
            return map;
        }
    }
    return map;
}

void draw_panel(Window win, int nb_cities, float dist) {
    MLV_draw_line(0, win.height - win.panel_height, win.width, win.height - win.panel_height, MLV_COLOR_BLACK);
    int width = win.width / 2, height = win.curr_height + win.panel_height / 2;
    int t_width, t_height;
    
    MLV_get_size_of_text("Number of Cities : %3d", &t_width, &t_height, nb_cities);
    MLV_draw_text(width / 2 - t_width / 2, height - t_height / 2, "Number of Cities : %3d", MLV_COLOR_BLACK, nb_cities);

    MLV_get_size_of_text("Distance : %3.2f", &t_width, &t_height, dist);
    MLV_draw_text(width + width / 2 - t_width / 2, height - t_height / 2, "Distance : %3.2f", MLV_COLOR_BLACK, dist);
}

void hide_panel(Window win) {
    MLV_draw_filled_rectangle(0, win.curr_height, win.width, win.panel_height, MLV_COLOR_WHITE);
}

void draw_city(City* city, bool display_name) {
    MLV_draw_filled_circle(city->x, city->y, CITY_RADIUS, MLV_COLOR_BLACK);
    if (display_name) {
        int width, height;
        MLV_get_size_of_text(city->name, &width, &height);
        MLV_draw_text(city->x - width / 2, city->y + TEXT_MARGIN - height / 2, city->name, MLV_COLOR_BLACK);
    }
}

void draw_cities(City** cities, int lenght, bool display_name) {
    for (int i = 0; i < lenght; i++) {
        draw_city(cities[i], display_name);
    }
}

void draw_map(Map map, bool display_name) {
    draw_cities(map.cities, map.length, display_name);
}

void draw_visit(Visit visit, bool display_name) {
    draw_cities(visit.cities, visit.length, display_name);

    for (int i = 0; i < visit.length - 1; i++) {
        MLV_draw_line(visit.cities[i]->x,
                      visit.cities[i]->y,
                      visit.cities[i + 1]->x,
                      visit.cities[i + 1]->y,
                      MLV_COLOR_BLACK);
    }
}

void draw_population(Population* pop, Window win, bool display_name) {
    Visit visit_min = pop->visits[0];
    float dist_min = visit_min.distance;

    MLV_clear_window(MLV_COLOR_WHITE);
    draw_panel(win, pop->map.length, dist_min);
    draw_visit(visit_min, display_name);
    MLV_update_window();
}
