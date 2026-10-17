/*
    Shape rendering functions
    Heresy
*/

//NV stands for No Validation

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"

void drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void drawRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);