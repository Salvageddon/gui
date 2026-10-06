#include "../../include/gui_baker_service.h"
#include <stdio.h>

void sizeControl(GUI_context * context){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        child->controlRect.w = 100;
        child->controlRect.h = 50;
    }
}

void positionControl(GUI_context * context){
    GUI_context * prevChild = NULL;

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        child->controlRect.x += 10;
        if(prevChild) child->controlRect.x += prevChild->controlRect.w + prevChild->controlRect.x;
        child->controlRect.y = 10;

        prevChild = child;
    }
}

void bakeControl(GUI_context * context, SDL_PixelFormat format){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        SDL_DestroySurface(child->bakeResult);
        child->bakeResult = SDL_CreateSurface(child->controlRect.w, child->controlRect.h, format);

        if(child->renderer) child->renderer(child->bakeResult, child->controlRect);
    }
}

void bakeGui(GUI_context * context, SDL_PixelFormat format){
    sizeControl(context);
    positionControl(context);
    bakeControl(context, format);
}

void bakeResultToSurface(GUI_context * context, SDL_Surface * sur){
    int x1 = context->controlRect.x < 0 ? 0 : context->controlRect.x;
    int y1 = context->controlRect.y < 0 ? 0 : context->controlRect.y;
    
    int x2 = context->controlRect.x + context->controlRect.w;
    int y2 = context->controlRect.y + context->controlRect.h;

    x2 = x2 >= sur->w ? sur->w : x2;
    y2 = y2 >= sur->h ? sur->h : y2;

    int xBake = 0;
    int yBake = 0;

    for(int yy = y1; yy < y2; yy++){
        for(int xx = x1; xx < x2; xx++){
            setPixel(sur, xx, yy, 0x0000FF);
            xBake++;
        }

        yBake++;
    }
}

void renderGui(GUI_context * context, SDL_Surface * sur){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        bakeResultToSurface(child, sur);
    }
}