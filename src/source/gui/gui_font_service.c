#include "../../include/gui_font_service.h"
#include <stdlib.h>
#include <stdio.h>

GUI_font * createFont(const char * path, int charWidth, int charHeight, int charsPerRow, Uint32 mask){
    GUI_font * font = malloc(sizeof(GUI_font));
    SDL_Surface * tmp = SDL_LoadBMP(path);

    Uint32 * tmpPixels, unfuckedMask;

    if(!tmp){
        setErrorMessage((char*)SDL_GetError());
        tmpPixels = NULL;
        unfuckedMask = mask;
    }
    else{
        tmpPixels = tmp->pixels;
        const SDL_PixelFormatDetails * details = SDL_GetPixelFormatDetails(tmp->format);
        unfuckedMask = mapRGB(getRGB(mask, details), details);
    }
     
    int charSize = charWidth * charHeight;
    
    int tx = 0, ty = 0, colIndex = 0;

    for(int i = 0; i < CHARCOUNT; i++){
        font->chars[i] = malloc(charSize);
        char * pseudoPixels = font->chars[i];

        if(tmpPixels){
            for(int y = 0; y < charHeight; y++){
                for(int x = 0; x < charWidth; x++){
                    char pixel = tmpPixels[(ty + y) * tmp->w + (tx + x)] != unfuckedMask;
                    pseudoPixels[y * charWidth + x] = pixel;
                }
            }
        }
        else{
            for(int j = 0; j < charSize; j++){
                pseudoPixels[j] = 1;
            }
        }

        colIndex++;
        if(colIndex == charsPerRow){
            colIndex = 0;
            tx = 0;
            ty += charHeight;
        }
        else{
            tx += charWidth;
        }
    }

    font->charWidth = charWidth;
    font->charHeight = charHeight;
    font->isAppended = 0;

    SDL_DestroySurface(tmp);

    return font;
}

void destroyFont(void * font){
    GUI_font * f = font;

    for(int i = 0; i < CHARCOUNT; i++){
        free(f->chars[i]);
    }

    free(font);
}