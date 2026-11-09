/*
    Mouse operation functions
    Heresy
*/

#pragma once

#include "gui_render_service.h"
#include "gui_auto_service.h"

typedef struct{
    float x, y;
    SDL_MouseButtonFlags buttons;
} Mouse;

Mouse getMouseState(void);