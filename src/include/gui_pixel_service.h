/*
    Pixel operation functions
    Layer 9
*/

#pragma once

#include "gui_color_service.h"
#include "gui_errors_service.h"
#include "gui_font_service.h"
#include "gui_utility_service.h"

void setPixel(SDL_Surface * sur, int x, int y, Uint32 pixel);
Uint32 getPixel(SDL_Surface * sur, int x, int y);