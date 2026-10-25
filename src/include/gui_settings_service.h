/*
    GUI settings and data functions
    Wrath
*/

#pragma once

#include "gui_render_service.h"
#include "gui_attribute_service.h"
#include "gui_handler_service.h"
#include "gui_mouse_service.h"

#include <salvagames/hashlist.h>

typedef struct{
    Hashlist ids;
    GUI_context * hover, * oldHover;
    Mouse mouse;
} GuiSettings;

GuiSettings * createGuiSettings(void);
void destroyGuiSettings(GuiSettings * settings);
GUI_context * findContextById(GuiSettings * base, unsigned int id);