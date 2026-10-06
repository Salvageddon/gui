/*
    Context operation functions
    Greed
*/

#pragma once

#include "gui_defaults_service.h"
#include "gui_enums.h"
#include <salvagames/list.h>

typedef struct GUI_CONTEXT{
    int type;
    GUI_irect controlRect;
    SDL_Surface * bakeResult;
    GUI_context * parent;
    List children;
    void (*renderer)(SDL_Surface * sur, GUI_irect rect);
} GUI_context;

GUI_context * createContext(int type);
void destroyContext(void * context);