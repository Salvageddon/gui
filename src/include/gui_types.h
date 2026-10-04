/*
    Type prototypes and definitions visible to user
*/

#pragma once

#include <SDL3/SDL.h>

typedef struct{
    SDL_Window * win;
    SDL_Surface * sur;

    int w, h;
} GUI_window;

typedef struct{
    Uint8 r, g, b;
} GUI_rgb;

typedef struct{
    Uint8 r, g, b, a;
} GUI_rgba;