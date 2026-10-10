/*
    Context operation functions
    Greed
*/

#pragma once

#include "gui_defaults_service.h"
#include "gui_enums.h"
#include <salvagames/list.h>
#include <salvagames/hashlist.h>

typedef struct GUI_CONTEXT{
    int type, generation;
    GUI_irect controlRect;
    SDL_Surface * bakeResult;
    GUI_context * parent;
    List children;
    Hashlist attributes;
    void (*renderer)(SDL_Surface * sur, GUI_irect rect, int generation);
} GUI_context;

GUI_context * createContext(GUI_context * parent, int type);
void destroyContext(void * context);