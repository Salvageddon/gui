/*
    Font operation functions
    Fraud
*/

#pragma once

#include "gui_utility_service.h"
#include "gui_errors_service.h"
#include "gui_color_service.h"

#define CHARCOUNT 96

typedef struct GUI_FONT{
    char * chars[CHARCOUNT], isAppended;
    int charWidth, charHeight;
} GUI_font;

GUI_font * createFont(const char * path, int charWidth, int charHeight, int charsPerRow, Uint32 mask);
void destroyFont(void * font);