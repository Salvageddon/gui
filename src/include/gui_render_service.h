/*
    Shape rendering functions
    Violence
*/

#pragma once

#include "gui_pixel_service.h"
#include "gui_text_service.h"

//NV stands for No Validation

void drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void drawRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectG(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2);
void fillRectGNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2);
void fillTheme(SDL_Surface * sur, int x, int y, int w, int h, int absx, int absy, SDL_Surface * eventSurface, float imw, float imh);
void renderText(SDL_Surface * sur, TextRenderData renderData, int x, int y, int w, int h, Uint32 color);