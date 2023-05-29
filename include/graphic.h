/**
 * @file graphic.h
 * @author Laborde Quentin & Kies Remy
 * @brief 
 * @date 26-05-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INIT_GRAPHIC__
#define __INIT_GRAPHIC__

#include "struct.h"

/**
 * @brief Function triggerd when the user close the window.
 *        Sets `data` to '1'.
 * 
 * @param data indicate the window status
 */
void exit_function(void* data);

/**
 * @brief Check if the status of `key` of the keyboard is `expected`. 
 * 
 * @param key keyboard key
 * @param expected expected status
 * @return bool
 */
bool is_pressed(MLV_Keyboard_button key, MLV_Button_state expected);

/**
 * @brief Check if the status of `key` of the mouse is `expected`. 
 * 
 * @param key mouse key
 * @param expected expected status
 * @return bool
 */
bool is_clicked(MLV_Mouse_button button, MLV_Button_state expected);

/**
 * @brief Initiate the window dimensions.
 * 
 * @return Window 
 */
Window init_window(void);

/**
 * @brief Create a map where the cities are points clicked on screen by the user.
 * 
 * @param stop indicate the screen status
 * @return Map 
 */
Map select_cities_on_screen(int* stop);

/**
 * @brief Draw on screen the info panel.
 * 
 * @param win window
 * @param nb_cities 
 * @param dist 
 */
void draw_panel(Window win, int nb_cities, float dist);

/**
 * @brief Hide on screen the info panel.
 * 
 * @param win window
 */
void hide_panel(Window win);

/**
 * @brief Draw a city to the screen.
 * 
 * @param city city to draw
 * @param display_name indictate to display the name or not
 */
void draw_city(City* city, bool display_name);

/**
 * @brief Draw cities from array to the screen.
 * 
 * @param cities city array
 * @param lenght length of the array
 * @param display_name indicate to display the name of the cities or not
 */
void draw_cities(City** cities, int lenght, bool display_name);

/**
 * @brief Draw a map to the screen.
 * 
 * @param map map to draw
 * @param display_name indicate to display the name of the cities or not
 */
void draw_map(Map map, bool display_name);

/**
 * @brief Draw a visit to the screen.
 * 
 * @param visit visit to draw
 * @param display_name indicate to display the name of the cities or not
 */
void draw_visit(Visit visit, bool display_name);

/**
 * @brief Draw the first visit of a population to the screen.
 * 
 * @param pop population
 * @param win window
 * @param display_name indicate to display the name of the cities or not
 */
void draw_population(Population* pop, Window win, bool display_name);

#endif
