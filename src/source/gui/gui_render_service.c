#include "../../include/gui_render_service.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

void renderText(SDL_Surface * sur, TextRenderData renderData, int x, int y, int w, int h){
    int xStart = (w - renderData.textRect.w) * 0.5F;
    int yStart = (h - renderData.textRect.h) * 0.5F;
    
    int tx = xStart, ty = yStart;

    Uint32 * pixels = sur->pixels;

    for(int i = 0; i < renderData.tokens.length; i++){
        RenderToken * token = LST_get(renderData.tokens, i);

        for(int j = 0; j < token->length; j++){
            char id = token->value[j] - ' ';

            if(id < 0) break;

            if(renderData.font){
                char * pseudoPixels = renderData.font->chars[id];

                for(int y = 0; y < renderData.ch; y++){
                    for(int x = 0; x < renderData.cw; x++){
                        int xx = (int)(renderData.cwInv * x);
                        int yy = (int)(renderData.chInv * y);
                        
                        if(pseudoPixels[yy * renderData.font->charWidth + xx]){
                            pixels[(ty + y) * sur->w + (tx + x)] = 0xFFFFFF;
                        }
                    }
                }
            }
            else{
                for(int y = 0; y < renderData.ch; y++){
                    for(int x = 0; x < renderData.cw; x++){
                        pixels[(ty + y) * sur->w + (tx + x)] = 0xFFFFFF;
                    }
                }
            }

            tx += renderData.cw;
        }

        tx += renderData.cw;

        if(tx - xStart >= renderData.textRect.w){
            tx = xStart;
            ty += renderData.ch;
        }
    }
}