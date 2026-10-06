/*
    Pixel operation functions
    Violence
*/

#pragma once

#include "gui_color_service.h"

void setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel);
Uint32 getPixel(SDL_Surface * sur, int x, int y);