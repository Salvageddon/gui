/*
    Context operation functions
    Greed
*/

#pragma once

#include "gui_defaults_service.h"
#include "gui_settings_service.h"

#include "gui_enums.h"
#include <salvagames/list.h>
#include <salvagames/hashlist.h>

#define CONTROLCOUNT 3

typedef struct{
    char allowWidthGrow,
        allowHeightGrow,
        allowHorizontalBoxes,
        allowVerticalBoxes,
        renderable;
} RenderData;

typedef struct GUI_CONTEXT{
    int type, generation;
    RenderData renderData;
    ContextState contextState;
    GUI_irect controlRect, paddingRect, marginRect, contentRect;
    SDL_Surface * bakeResult, * target;
    GuiSettings * settings;
    GUI_context * parent;
    List children;
    Hashlist attributes, eventHandlers;
    PossibleAttributes possibleAttributes;
    void (*renderer)(SDL_Surface * sur, GUI_irect rect, int generation);
    void (*listener)(ListenerData data);
} GUI_context;

typedef struct{
    char * name;
    int type;
} controlData;

extern controlData controlDefinitions[CONTROLCOUNT];

GUI_context * createContext(GUI_context * parent, int type);
void destroyContext(void * context);
int getControlType(char * controlName);