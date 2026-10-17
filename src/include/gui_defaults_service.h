/*
    Control default listeners, style and functions
    Wrath
*/

#pragma once

#include "gui_render_service.h"
#include "gui_attribute_service.h"

void renderView(SDL_Surface * sur, GUI_irect rect, int generation);
void renderButton(SDL_Surface * sur, GUI_irect rect, int generation);
void renderLinearView(SDL_Surface * sur, GUI_irect rect, int generation);