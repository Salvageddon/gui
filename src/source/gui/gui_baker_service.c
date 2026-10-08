#include "../../include/gui_baker_service.h"
#include <stdio.h>

void sizeControl(GUI_context * context){
    if(context->children.length > 0){
        for(int i = 0; i < context->children.length; i++){
            GUI_context * child = LST_get(context->children, i);

            sizeControl(child);

            context->controlRect.w += child->controlRect.w + 10;
            context->controlRect.h = context->controlRect.h < child->controlRect.h ? child->controlRect.h : context->controlRect.h;
        }

        context->controlRect.w += 10;
        context->controlRect.h += 20;
    }
    else{
        context->controlRect.w = 100;
        context->controlRect.h = 50;
    }
}

void positionControl(GUI_context * context){
    GUI_context * prevChild = NULL;

    int xpos = 0, ypos = 0;

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        child->controlRect.x += 10;
        if(prevChild) child->controlRect.x += xpos;
        child->controlRect.y += 10;

        child->controlRect.x += context->controlRect.x;
        child->controlRect.y += context->controlRect.y;

        xpos += child->controlRect.w + 10;
        ypos += child->controlRect.h;

        positionControl(child);

        prevChild = child;
    }
}

void bakeControl(GUI_context * context, SDL_PixelFormat format){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        SDL_DestroySurface(child->bakeResult);
        child->bakeResult = SDL_CreateSurface(child->controlRect.w, child->controlRect.h, format);

        if(child->renderer) child->renderer(child->bakeResult, child->controlRect, child->generation);

        bakeControl(child, format);
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
            setPixel(sur, xx, yy, getPixel(context->bakeResult, xBake, yBake));
            xBake++;
        }

        xBake = 0;
        yBake++;
    }
}

void renderGui(GUI_context * context, SDL_Surface * sur){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        bakeResultToSurface(child, sur);
        renderGui(child, sur);
    }
}