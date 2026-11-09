/*
    Shape rendering functions
    Heresy
*/

//NV stands for No Validation

#pragma once

#include "gui_pixel_service.h"
#include "gui_auto_service.h"
#include "gui_text_service.h"

#define ADDUINT8(a, b) (a + b < 0 ? 0 : (a + b > 255 ? 255 : a + b))

void drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void drawRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color);
void fillRectG(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2);
void fillRectGNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2);
void renderText(SDL_Surface * sur, TextRenderData renderData, int x, int y, int w, int h);