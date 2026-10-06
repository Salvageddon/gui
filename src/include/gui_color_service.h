/*
    Color conversion functions
    Violence
*/

#pragma once

#include "gui_types.h"

GUI_rgb getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails);
Uint32 mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails);
GUI_rgba getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails);
Uint32 mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails);