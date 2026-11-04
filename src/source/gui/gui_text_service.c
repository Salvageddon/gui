#include "../../include/gui_text_service.h"
#include <stdlib.h>
#include <stdio.h>

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
    return (TextRenderData){ LST_createList(), 0, 0, 0, 0, 0, (GUI_irect){0, 0, 0, 0}, 0, NULL};
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

int makeNullFontText(TextRenderData * renderData, char * text, int textSize){
    List tokens = tokenize(text);
    int length = 0;

    LST_clear(&renderData->tokens, 1);

    for(int i = 0; i < tokens.length; i++){
        char * token = LST_get(tokens, i);
        int tokenLength = strlen(token);

        RenderToken * rToken = createRenderToken(rewriteString(token), tokenLength, tokenLength * textSize, textSize);
        LST_add(&renderData->tokens, rToken, &destroyRenderToken);
        
        length += tokenLength + 1;
    }

    LST_clear(&tokens, 1);

    return length - 1;
}

void getTextRect(TextRenderData * renderData, char * text, int textSize, GUI_font * font, char forceRerender){
    if(!renderData->tokenized || forceRerender){
        if(!font){
            int length = makeNullFontText(renderData, text, textSize);

            renderData->textRect.w = length * textSize;
            renderData->textRect.h = textSize;

            renderData->length = length;

            renderData->cw = textSize;
            renderData->ch = textSize;  

            renderData->cwInv = 1;
            renderData->chInv = 1;
            return;
        }

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