#include "../../include/gui_text_service.h"
#include <stdlib.h>

RenderToken * createRenderToken(char * value, int length, int w, int h){
    RenderToken * o = malloc(sizeof(RenderToken));

    o->value = value;
    o->length = length;
    o->w = w;

    return o;
}

void destroyRenderToken(void * token){
    RenderToken * t = token;

    free(t->value);
    free(token);
}

TextRenderData createTextData(void){
    return (TextRenderData){ LST_createList(), 0, 0, 0, 0, 0, (GUI_irect){0, 0, 0, 0}, 0};
}

void makeRenderToken(char * value, int length, int oldIndex, int textSize, float invCharHeight, GUI_font * font, List * o){
    char * token = malloc(length + 1);
    strncpy(token, &value[oldIndex], length);
    token[length] = '\0';

    int w = length * font->charWidth * textSize * invCharHeight;
    int h = textSize;

    RenderToken * renderToken = createRenderToken(token, length, w, h);

    LST_add(o, renderToken, &destroyRenderToken);
}

List renderTokenize(TextRenderData * renderData, char * value, GUI_font * font, int textSize, float invCharHeight){
    List o = LST_createList();

    int index = 0, oldIndex = 0;
    int length = 0;

    while(value[index] != '\0'){
        if((value[index] == ' ' || value[index] == '\n' || value[index] == '\t') && length > 0){
            makeRenderToken(value, length, oldIndex, textSize, invCharHeight, font, &o);
            oldIndex = index + 1;
            renderData->length += length + 1;
            length = 0;
        }
        else{
            length++;
        }

        index++;
    }

    makeRenderToken(value, length, oldIndex, textSize, invCharHeight, font, &o);
    renderData->length += length;

    return o;
}

void getTextRect(TextRenderData * renderData, char * text, int textSize, GUI_font * font, char forceRerender){
    if(!renderData->tokenized || forceRerender){
        int lineWidth = 0;
        float invCharHeight = 1.0F / font->charHeight;

        LST_clear(&renderData->tokens, 1);
        renderData->tokens = renderTokenize(renderData, text, font, textSize, invCharHeight);
        renderData->tokenized = 1;

        renderData->cw = invCharHeight * font->charWidth * textSize;
        renderData->ch = textSize;

        renderData->textRect.w = renderData->length * renderData->cw;
        renderData->textRect.h = renderData->ch;

        renderData->cwInv = font->charWidth / (float)renderData->cw;
        renderData->chInv = font->charHeight / (float)renderData->ch;

        renderData->font = font;
    }
}