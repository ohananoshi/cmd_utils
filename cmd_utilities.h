/* Header: cmd_utilities

   A set of possible useful functions for cmd.

   Author: Guilherme Arruda

   GitHub: https://github.com/ohananoshi/cmd_utilities

   Created in: 19/02/23

   Last Updated: 13/07/23
*/

#pragma once

//================================ HEADERS ======================================

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <windows.h>
#include <wincon.h>

//======================== TYPES AND DATA STRUCTURES ============================

typedef struct{
    uint16_t left_high_corner_chr;
    uint16_t right_high_corner_chr;
    uint16_t left_bottom_corner_chr;
    uint16_t right_botton_corner_chr;
    uint16_t horizontal_character;
    uint16_t vertical_character;
}border_shape;

enum colors{
    BLACK = 0,
    DARK_BLUE,
    DARK_GREEN,
    DARK_BLUE_GREEN,
    DARK_RED,
    DARK_PURPLE,
    DARK_BROWN,
    DARK_GRAY,
    LIGHT_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_BLUE_GREEN,
    LIGHT_RED,
    LIGHT_PURPLE,
    LIGHT_YELLOW,
    WHITE
};

//=========================== PRE-DEFINED SHAPES ======================================

border_shape DOUBLE_LINE = {201, 187, 200, 188, 205, 186},
             SINGLE_LINE = {218, 191, 192, 217, 196, 179};

//========================= PRE-DEFINE CHARACTERS =====================================

uint8_t HEAVY_SHADE = 178,
        MEDIUM_SHADE = 177,
        LIGHT_SHADE = 176,
        FULL_FILLED = 219;

//================================ FUNCTIONS ==========================================

bool set_to_fullscreen(){

    //Obter handle da janela atual
    HWND console_window_handle = GetConsoleWindow();
    if(console_window_handle == NULL) return 0;

    //Alterar o estilo da janela para tela cheia
    SetWindowLong(console_window_handle, GWL_STYLE, WS_POPUP | WS_VISIBLE);

    //Redimensionar a janela para as dimens�es da tela
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    if(SetWindowPos(console_window_handle, HWND_TOP, 0, 0, width, height, SWP_SHOWWINDOW)) return 0;

    return 1;
}

void set_color(uint16_t foreground_color, uint16_t background_color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (foreground_color + background_color*16));
}

void move_cursor(uint16_t column, uint16_t line){

	COORD coordinates;
	coordinates.X = column;
	coordinates.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);

}

void write_text(char *text, uint16_t column, uint16_t line){
    move_cursor(column, line);
    printf("%s", text);
}

void draw_box(border_shape shape, uint16_t width, uint16_t height, uint16_t column, uint16_t line){

    move_cursor(column, line);

    printf("%c", shape.left_high_corner_chr);

    for(uint16_t i = 0; i < (width - 2); i++){
        printf("%c",shape.horizontal_character);
    }

    printf("%c", shape.right_high_corner_chr);

    for(uint16_t j = 1; j < (height-2); j++){
        move_cursor(column, line + j);
        printf("%c", shape.vertical_character);
        move_cursor(column + (width - 1), line + j);
        printf("%c", shape.vertical_character);
    }

    move_cursor(column, line + height - 2);
    printf("%c", shape.left_bottom_corner_chr);

    for(uint16_t i = 0; i < (width - 2); i++){printf("%c",shape.horizontal_character);}

    printf("%c", shape.right_botton_corner_chr);
}

void fill_rectangle(uint16_t ascii_dec_character, uint16_t width, uint16_t height, uint16_t column, uint16_t line){
    for (uint16_t i = 0; i < height; i++){
        move_cursor(column, line + i);
        for(uint16_t j = 0; j < width; j++){
            printf("%c", ascii_dec_character);
        }
    }
}

void print_list(char **string_array, uint16_t string_counter, uint16_t column, uint16_t line, uint16_t space, bool direction){

    uint16_t offset = column;

    if(direction){
        for(uint16_t i = 0; i < string_counter; i++){
        write_text(string_array[i], column, line+i*space);
        }
    }else{
        for(uint16_t i = 0; i < string_counter; i++){
        write_text(string_array[i], column+offset + i*space, line);
        offset = offset + strlen(string_array[i]);
        }
    }
}
