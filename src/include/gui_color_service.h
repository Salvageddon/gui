/*
    Color conversion functions
    Layer 10
*/

#pragma once

#include "gui_errors_service.h"
#include "gui_utility_service.h"

#include "gui_types.h"

#define ADDUINT8(a, b) (a + b < 0 ? 0 : (a + b > 255 ? 255 : a + b))

GUI_rgb getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails);
Uint32 mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails);
GUI_rgba getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails);
Uint32 mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails);