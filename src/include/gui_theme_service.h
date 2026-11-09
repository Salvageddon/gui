/*
    Theme operation functions
    Heresy
*/

#pragma once

#include "gui_render_service.h"
#include "gui_auto_service.h"

#define HOVERMOD 30
#define CLICKMOD -30
#define DISABLEDMOD -10

typedef struct{
    Uint32 normal, hover, click, disabled;
} EventColor;

typedef struct{
    SDL_Surface * normal, * hover, * click, * disabled;
} EventSurface;

typedef struct{
    EventColor primaryColor1, primaryColor2, 
               borderColor1, borderColor2,
               backgroundColor1, backgroundColor2,
               foregroundColor;

    EventSurface primaryGradient,
                 borderGradient,
                 backgroundGradient;

    int defaultTextSize, defaultBorderThickness, mapWidth, mapHeight;
    float invMapWidth, invMapHeight;
} Theme;

Theme createTheme(SDL_Surface * sur, Uint32 pColor1, Uint32 pColor2, Uint32 fg, int boMod, int bgMod, int defTextSize, int defBorderSize, int mapWidth, int mapHeight);
void destroyTheme(Theme * theme);