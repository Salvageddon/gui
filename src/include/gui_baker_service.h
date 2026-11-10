/*
    GUI baking and rendering functions
    Layer 4
*/

#pragma once

#include "gui_context_service.h"

void bakeGui(GUI_context * context, SDL_PixelFormat format);
void renderGui(GUI_context * context, SDL_Surface * sur);
void bakeOnlyThisControl(GUI_context * context, SDL_PixelFormat format);