/*
    Control default listeners, style and functions
    Wrath
*/

#pragma once

#include "gui_render_service.h"
#include "gui_attribute_service.h"
#include "gui_handler_service.h"
#include "gui_mouse_service.h"

typedef struct{
    char isHovering;
} ContextState;

typedef struct{
    GUI_context * context;
    Hashlist * eventHandlers;
    ContextState contextState;
    SDL_Event event;
} ListenerData;

void renderView(SDL_Surface * sur, GUI_irect rect, int generation);
void renderButton(SDL_Surface * sur, GUI_irect rect, int generation);
void renderLinearView(SDL_Surface * sur, GUI_irect rect, int generation);
void buttonEventListener(ListenerData data);