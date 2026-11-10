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

void fillRectG(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2){
    int xstart, ystart, x1, y1;

    if(x < 0){
        x1 = -x;
        xstart = 0;
    }
    else{
        x1 = 0;
        xstart = x;
    }

    if(y < 0){
        y1 = -y;
        ystart = 0;
    }
    else{
        y1 = 0;
        ystart = y;
    }

    int xstartfirst = x1;
    
    int x2 = x + w;
    int y2 = y + h;

    x2 = x2 >= sur->w ? sur->w : x2;
    y2 = y2 >= sur->h ? sur->h : y2;

    const SDL_PixelFormatDetails * details = SDL_GetPixelFormatDetails(sur->format);

    GUI_rgb col1 = getRGB(color1, details);
    GUI_rgb col2 = getRGB(color2, details);

    int rDiff = col2.r - col1.r;
    int gDiff = col2.g - col1.g;
    int bDiff = col2.b - col1.b;

    float wInv = 1.0F / (float)w, hInv = 1.0F / (float)h;

    for(int yy = ystart; yy < y2; yy++){
        for(int xx = xstart; xx < x2; xx++){
            float xa = x1 * wInv, 
                  ya = y1 * hInv, 
                  avg = (xa + ya) * 0.5F;

            GUI_rgb color = {
                ADDUINT8(col1.r, (avg * rDiff)),
                ADDUINT8(col1.g, (avg * gDiff)),
                ADDUINT8(col1.b, (avg * bDiff))
            };

            setPixel(sur, xx, yy, mapRGB(color, details));

            x1++;
        }
        
        x1 = xstartfirst;
        y1++;
    }
}

void fillRectGNV(SDL_Surface * sur, int x, int y, int w, int h, Uint32 color1, Uint32 color2){
    int x2 = x + w;
    int y2 = y + h;

    const SDL_PixelFormatDetails * details = SDL_GetPixelFormatDetails(sur->format);

    GUI_rgb col1 = getRGB(color1, details);
    GUI_rgb col2 = getRGB(color2, details);

    int rDiff = col2.r - col1.r;
    int gDiff = col2.g - col1.g;
    int bDiff = col2.b - col1.b;

    int x1 = 0, y1 = 0;
    float wInv = 1.0F / (float)w, hInv = 1.0F / (float)h;

    for(int yy = y; yy < y2; yy++){
        for(int xx = x; xx < x2; xx++){
            float xa = x1 * wInv, 
                  ya = y1 * hInv, 
                  avg = (xa + ya) * 0.5F;

            GUI_rgb color = {
                ADDUINT8(col1.r, (avg * rDiff)),
                ADDUINT8(col1.g, (avg * gDiff)),
                ADDUINT8(col1.b, (avg * bDiff))
            };

            setPixel(sur, xx, yy, mapRGB(color, details));

            x1++;
        }
        
        x1 = 0;
        y1++;
    }
}

void fillTheme(SDL_Surface * sur, int x, int y, int w, int h, int absx, int absy, SDL_Surface * eventSurface, float imw, float imh){
    int x2 = x + w;
    int y2 = y + h;

    for(int yy = y; yy < y2; yy++){
        for(int xx = x; xx < x2; xx++){
            int xMap = (int)((absx + xx) * imw);
            int yMap = (int)((absy + yy) * imh);

            setPixel(sur, xx, yy, getPixel(eventSurface, xMap, yMap));
        }
    }
}

void renderText(SDL_Surface * sur, TextRenderData renderData, int x, int y, int w, int h, Uint32 color){
    int xStart = (w - renderData.textRect.w) * 0.5F;
    int yStart = (h - renderData.textRect.h) * 0.5F;
    
    int tx = xStart, ty = yStart;

    Uint32 * pixels = sur->pixels;

    if(renderData.font){
        for(int i = 0; i < renderData.tokens.length; i++){
            RenderToken * token = LST_get(renderData.tokens, i);

            for(int j = 0; j < token->length; j++){
                char id = token->value[j] - ' ';

                if(id < 0) break;

                char * pseudoPixels = renderData.font->chars[id];

                for(int y = 0; y < renderData.ch; y++){
                    for(int x = 0; x < renderData.cw; x++){
                        int xx = (int)(renderData.cwInv * x);
                        int yy = (int)(renderData.chInv * y);
                        
                        if(pseudoPixels[yy * renderData.font->charWidth + xx]){
                            pixels[(ty + y) * sur->w + (tx + x)] = color;
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
    else{
        for(int i = 0; i < renderData.tokens.length; i++){
            RenderToken * token = LST_get(renderData.tokens, i);

            for(int j = 0; j < token->length; j++){
                for(int y = 0; y < renderData.ch; y++){
                    for(int x = 0; x < renderData.cw; x++){
                        pixels[(ty + y) * sur->w + (tx + x)] = color;
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
}

void fillSurface(SDL_Surface * sur, Uint32 color){
    fillRectNV(sur, 0, 0, sur->w, sur->h, color);
}