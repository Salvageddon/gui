#include "../../include/gui_render_service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char * value;
    int length, line, w, h;
} RenderToken;

typedef struct{
    List tokens;
    int w, h, cw, ch;
} TextRenderData;

RenderToken * createRenderToken(char * value, int length, int w, int h){
    RenderToken * o = malloc(sizeof(RenderToken));

    o->value = value;
    o->length = length;
    o->line = 0;
    o->w = w;
    o->h = h;

    return o;
}

void destroyRenderToken(void * token){
    RenderToken * t = token;

    free(t->value);
    free(token);
}

TextRenderData createTextData(void){
    return (TextRenderData){ LST_createList(), 0, 0, 0, 0 };
}

void drawRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    int x1 = x < 0 ? 0 : x;
    int y1 = y < 0 ? 0 : y;
    
    int x2 = x + w;
    int y2 = y + h;

    x2 = x2 >= sur->w ? sur->w : x2;
    y2 = y2 >= sur->h ? sur->h : y2;

    int x2m1 = x2 - 1;
    int y2m1 = y2 - 1;

    for(int xx = x1; xx < x2m1; xx++) setPixel(sur, xx, y1, color);
    for(int xx = x1; xx < x2; xx++) setPixel(sur, xx, y2m1, color);
    for(int yy = y1; yy < y2m1; yy++) setPixel(sur, x1, yy, color);
    for(int yy = y1; yy < y2; yy++) setPixel(sur, x2m1, yy, color);
}

void drawRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    int x2 = x + w;
    int y2 = y + h;
    
    int x2m1 = x2 - 1;
    int y2m1 = y2 - 1;

    for(int xx = x; xx < x2m1; xx++) setPixel(sur, xx, y, color);
    for(int xx = x; xx < x2; xx++) setPixel(sur, xx, y2m1, color);
    for(int yy = y; yy < y2m1; yy++) setPixel(sur, x, yy, color);
    for(int yy = y; yy < y2; yy++) setPixel(sur, x2m1, yy, color);
}

void fillRect(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    int x1 = x < 0 ? 0 : x;
    int y1 = y < 0 ? 0 : y;
    
    int x2 = x + w;
    int y2 = y + h;

    x2 = x2 >= sur->w ? sur->w : x2;
    y2 = y2 >= sur->h ? sur->h : y2;

    for(int yy = y1; yy < y2; yy++){
        for(int xx = x1; xx < x2; xx++){
            setPixel(sur, xx, yy, color);
        }
    }
}

void fillRectNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color){
    int x2 = x + w;
    int y2 = y + h;

    for(int yy = y; yy < y2; yy++){
        for(int xx = x; xx < x2; xx++){
            setPixel(sur, xx, yy, color);
        }
    }
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

List renderTokenize(char * value, GUI_font * font, int textSize, float invCharHeight){
    List o = LST_createList();

    int index = 0, oldIndex = 0;
    int length = 0;

    while(value[index] != '\0'){
        if((value[index] == ' ' || value[index] == '\n' || value[index] == '\t') && length > 0){
            makeRenderToken(value, length, oldIndex, textSize, invCharHeight, font, &o);
            oldIndex = index + 1;
            length = 0;
        }
        else{
            length++;
        }

        index++;
    }

    makeRenderToken(value, length, oldIndex, textSize, invCharHeight, font, &o);

    return o;
}

void renderText(SDL_Surface * sur, char * text, int textSize, int x, int y, int w, int h, GUI_font * font){
    int lineWidth = 0;
    float invCharHeight = 1.0F / font->charHeight;
    TextRenderData renderData = createTextData();
    renderData.tokens = renderTokenize(text, font, textSize, invCharHeight);

    int renderedTokenCount = 0, currentLine = 0;
    renderData.cw = invCharHeight * font->charWidth * textSize;
    renderData.ch = textSize;

    renderData.h = renderData.ch;

    for(int i = 0; i < renderData.tokens.length; i++){
        RenderToken * token = LST_get(renderData.tokens, i);

        int newLineWidth = lineWidth + token->w;

        if(newLineWidth < w){
            lineWidth = newLineWidth;
            if(lineWidth > renderData.w) renderData.w = lineWidth;
        }
        else{
            lineWidth = 0;
            int newH = renderData.h + token->h;

            if(newH < h){
                renderData.h = newH;
                token->line = ++currentLine;
            }
            else{
                break;
            }
        }

        renderedTokenCount++;
    }

    int xStart = (w - renderData.w) * 0.5;
    int yStart = (h - renderData.h) * 0.5;

    float cwInv = font->charWidth / (float)renderData.cw;
    float chInv = font->charHeight / (float)renderData.ch;

    int tx = xStart, ty = yStart;

    Uint32 * pixels = sur->pixels;

    for(int i = 0; i < renderedTokenCount; i++){
        RenderToken * token = LST_get(renderData.tokens, i);

        for(int j = 0; j < token->length; j++){
            char id = token->value[j] - ' ';

            if(id < 0) break;

            char * pseudoPixels = font->chars[id];

            for(int y = 0; y < renderData.ch; y++){
                for(int x = 0; x < renderData.cw; x++){
                    int xx = (int)(cwInv * x);
                    int yy = (int)(chInv * y);
                    
                    if(pseudoPixels[yy * font->charWidth + xx]){
                        pixels[(ty + y) * sur->w + (tx + x)] = 0xFFFFFF;
                    }
                }
            }

            tx += renderData.cw;
        }

        tx += renderData.cw;

        if(tx - xStart >= renderData.w){
            tx = xStart;
            ty += renderData.ch;
        }
    }

    LST_clear(&renderData.tokens, 1);
}