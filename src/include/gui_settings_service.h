/*
    GUI settings and data functions
    Wrath
*/

#pragma once

#include "gui_attribute_service.h"
#include "gui_handler_service.h"
#include "gui_mouse_service.h"
#include "gui_theme_service.h"

#include <salvagames/hashlist.h>

typedef struct{
    Hashlist ids, fonts;
    GUI_context * hover, * oldHover;
    Mouse mouse;
    unsigned int focusedFont;
    char isBaked, hasTheme;
    Theme theme;
} GuiSettings;

GuiSettings * createGuiSettings(void);
void setTheme(GuiSettings * settings, SDL_Surface * sur, Uint32 pColor1, Uint32 pColor2, Uint32 fg, int boMod, int bgMod, int defTextSize, int defBorderSize, int mapWidth, int mapHeight);
void destroyGuiSettings(GuiSettings * settings);
GUI_context * findContextById(GuiSettings * base, unsigned int id);