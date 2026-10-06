/*
    Type prototypes and definitions visible to user
*/

#pragma once

#include <SDL3/SDL.h>

typedef struct GUI_CONTEXT GUI_context;

typedef struct{
    SDL_Window * win;
    SDL_Surface * sur;

    GUI_context * guiBase;

    int w, h;
} GUI_window;

typedef struct{
    Uint8 r, g, b;
} GUI_rgb;

typedef struct{
    Uint8 r, g, b, a;
} GUI_rgba;

typedef struct{
    int x, y, w, h;
} GUI_irect;

typedef struct{
    float x, y, w, h;
} GUI_frect;