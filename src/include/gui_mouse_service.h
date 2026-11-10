/*
    Mouse operation functions
    Layer 7
*/

#pragma once

#include "gui_render_service.h"
#include "gui_auto_service.h"

#include <salvagames/hashlist.h>
#include "gui_enums.h"

#define CURSORCOUNT 3

typedef struct{
    float x, y;
    SDL_MouseButtonFlags buttons;
} Mouse;

typedef struct{
    Hashlist cursors;
    int currentCursorId;
} CursorData;

Mouse getMouseState(void);
CursorData createCursorData(void);
void setCursor(CursorData * cursorData, int id);