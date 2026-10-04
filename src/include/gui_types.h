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