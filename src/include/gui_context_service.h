/*
    Context operation functions
    Greed
*/

#pragma once

#include "gui_defaults_service.h"
#include "gui_enums.h"
#include <salvagames/list.h>
#include <salvagames/hashlist.h>

#define CONTROLCOUNT 2

typedef struct GUI_CONTEXT{
    int type, generation;
    GUI_irect controlRect;
    SDL_Surface * bakeResult;
    GUI_context * parent;
    List children;
    Hashlist attributes;
    possibleAttributes possibleAttributes;
    void (*renderer)(SDL_Surface * sur, GUI_irect rect, int generation);
} GUI_context;

typedef struct{
    char * name;
    int type;
} controlData;

extern controlData controlDefinitions[CONTROLCOUNT];

GUI_context * createContext(GUI_context * parent, int type);
void destroyContext(void * context);
int getControlType(char * controlName);