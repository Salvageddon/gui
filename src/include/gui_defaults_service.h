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
    SDL_Surface * sur; 
    GUI_irect rect; 
    int generation;
} RenderArgs;

typedef struct{
    SDL_Surface * sur;
    GUI_irect rect, controlRect; 
    int generation;
    char * text;
    int textSize;
    GUI_font * font;
} ButtonRenderArgs;

typedef struct{
    char isHovering;
} ContextState;

typedef struct{
    GUI_context * context;
    Hashlist * eventHandlers;
    ContextState contextState;
    SDL_Event event;
} ListenerData;

void renderView(void * renderArgs);
void renderButton(void * buttonRenderArgs);
void renderLinearView(void * renderArgs);
void buttonEventListener(ListenerData data);