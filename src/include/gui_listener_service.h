/*
    GUI listening for events functions
    Gluttony
*/

#pragma once

#include "gui_context_service.h"

void updateHover(GUI_context * context);
void listenForEvents(GUI_context * context, SDL_Event event);
void setEventHandler(GUI_context * context, unsigned int eventType, void (*handler)(GUI_context * context));