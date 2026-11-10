/*
    Text operation functions
    Layer 9
*/

#pragma once

#include "gui_color_service.h"
#include "gui_font_service.h"

typedef struct{
    char * value;
    int length, w;
} RenderToken;

typedef struct{
    List tokens;
    int cw, ch, length;
    float cwInv, chInv;
    GUI_irect textRect;
    char tokenized;
    GUI_font * font;
} TextRenderData;

RenderToken * createRenderToken(char * value, int length, int w, int h);
void destroyRenderToken(void * token);
TextRenderData createTextData(void);
void getTextRect(TextRenderData * renderData, char * text, int textSize, GUI_font * font, char forceRerender);