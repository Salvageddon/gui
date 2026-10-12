#include "../../include/gui_baker_service.h"
#include <stdio.h>

void sizeControl(GUI_context * context){
    if(context->children.length > 0){
        for(int i = 0; i < context->children.length; i++){
            GUI_context * child = LST_get(context->children, i);

            sizeControl(child);

            switch(getOrientation(context->attributes)){
                case GUI_ORIENTATION_HORIZONTAL:
                    context->controlRect.w += child->marginRect.w;
                    context->controlRect.h = context->controlRect.h < child->marginRect.h ? child->marginRect.h : context->controlRect.h;
                break;

                case GUI_ORIENTATION_VERTICAL:
                    context->controlRect.h += child->marginRect.h;
                    context->controlRect.w = context->controlRect.w < child->marginRect.w ? child->marginRect.w : context->controlRect.w;
                break;
            }
        }
    }
    else{
        context->controlRect.w = 100;
        context->controlRect.h = 50;
    }

    Box padding = getPadding(context->attributes);
    Box margin = getMargin(context->attributes);

    context->paddingRect.w = context->controlRect.w + padding.left + padding.right;
    context->paddingRect.h = context->controlRect.h + padding.top + padding.bottom;

    context->marginRect.w = context->paddingRect.w + margin.left + margin.right;
    context->marginRect.h = context->paddingRect.h + margin.top + margin.bottom;
}

void positionControl(GUI_context * context){
    GUI_context * prevChild = NULL;

    int xpos = 0, ypos = 0;

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        Box childMargin = getMargin(child->attributes);
        Box childPadding = getPadding(child->attributes);

        child->marginRect.x += context->controlRect.x;
        child->marginRect.y += context->controlRect.y;

        child->paddingRect.x += child->marginRect.x + childMargin.left;
        child->paddingRect.y += child->marginRect.y + childMargin.top;

        child->controlRect.x += child->paddingRect.x + childPadding.left;
        child->controlRect.y += child->paddingRect.y + childPadding.top;

        switch(getOrientation(context->attributes)){
            case GUI_ORIENTATION_HORIZONTAL:
                if(prevChild){
                    child->controlRect.x += xpos;
                    child->paddingRect.x += xpos;
                    child->marginRect.x += xpos;
                }
            break;
            
            case GUI_ORIENTATION_VERTICAL:
                if(prevChild){
                    child->controlRect.y += ypos;
                    child->paddingRect.y += ypos;
                    child->marginRect.y += ypos;
                }
            break;
        }

        xpos += child->marginRect.w;
        ypos += child->marginRect.h;

        positionControl(child);

        prevChild = child;
    }
}

void bakeControl(GUI_context * context, SDL_PixelFormat format){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        SDL_DestroySurface(child->bakeResult);
        child->bakeResult = SDL_CreateSurface(child->paddingRect.w, child->paddingRect.h, format);

        if(child->renderer) child->renderer(child->bakeResult, child->paddingRect, child->generation);

        bakeControl(child, format);
    }
}

void bakeGui(GUI_context * context, SDL_PixelFormat format){
    sizeControl(context);
    positionControl(context);
    bakeControl(context, format);
}

void bakeResultToSurface(GUI_context * context, SDL_Surface * sur){
    int x1 = context->paddingRect.x < 0 ? 0 : context->paddingRect.x;
    int y1 = context->paddingRect.y < 0 ? 0 : context->paddingRect.y;
    
    int x2 = context->paddingRect.x + context->paddingRect.w;
    int y2 = context->paddingRect.y + context->paddingRect.h;

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