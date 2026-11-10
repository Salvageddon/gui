/*
    Control default listeners, style and functions
    Layer 6
*/

#pragma once

#include "gui_attribute_service.h"
#include "gui_handler_service.h"
#include "gui_mouse_service.h"
#include "gui_theme_service.h"

typedef struct{
    char isHovering, isClicked, isDisabled;
} ContextState;

typedef struct{
    SDL_Surface * sur; 
    GUI_irect rect; 
    int generation;
    Theme theme;
} RenderArgs;

typedef struct{
    SDL_Surface * sur;
    GUI_irect rect, controlRect; 
    int generation;
    TextRenderData renderData;
    ContextState contextState;
    Theme theme;
} ButtonRenderArgs;

typedef struct{
    GUI_context * context;
    Hashlist * eventHandlers;
    ContextState * contextState;
    SDL_Event event;
} ListenerData;

void renderView(void * renderArgs);
void renderButton(void * buttonRenderArgs);
void renderLinearView(void * renderArgs);
void buttonEventListener(ListenerData data);