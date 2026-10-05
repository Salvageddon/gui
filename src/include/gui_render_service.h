/*
    Shape rendering functions
    Limbo
*/

//NV stands for No Validation

#pragma once

#include "gui_init_service.h"
#include "gui_pixel_service.h"

void drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void drawRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);