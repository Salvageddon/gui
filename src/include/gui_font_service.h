/*
    Font operation functions
    Violence
*/

#pragma once

#include "gui_color_service.h"

#define CHARCOUNT 96

typedef struct GUI_FONT{
    char * chars[CHARCOUNT], isAppended;
    int charWidth, charHeight;
} GUI_font;

GUI_font * createFont(const char * path, int charWidth, int charHeight, int charsPerRow, Uint32 mask);
void destroyFont(void * font);