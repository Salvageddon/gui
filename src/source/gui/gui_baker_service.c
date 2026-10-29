#include "../../include/gui_baker_service.h"
#include <stdio.h>

int stretchParentsWidth(GUI_context * context){
    if(context->parent){
        int parentWidthAttr = getWidth(context->parent->attributes);

        if(parentWidthAttr == GUI_SIZE_MIN){
            int parentWidth = stretchParentsWidth(context->parent);

            Box margin = getMargin(context->parent->attributes);
            Box padding = getPadding(context->parent->attributes);

            int paddingMargin = margin.left + margin.right + padding.left + padding.right;
            int wdiff = parentWidth - paddingMargin - context->parent->controlRect.w;

            context->parent->controlRect.w += wdiff;
            context->parent->paddingRect.w += wdiff;
            context->parent->marginRect.w += wdiff;
            context->parent->contentRect.w += wdiff;

            context->parent->renderData.allowWidthGrow = 0;
            context->parent->renderData.allowHorizontalBoxes = 1;

            return parentWidth - paddingMargin;
        }
        else{
            return context->parent->controlRect.w;
        }
    }
    else{
        return context->target->w;
    }
}

int stretchParentsHeight(GUI_context * context){
    if(context->parent){
        int parentHeightAttr = getHeight(context->parent->attributes);

        if(parentHeightAttr == GUI_SIZE_MIN){
            int parentHeight = stretchParentsHeight(context->parent);

            Box margin = getMargin(context->parent->attributes);
            Box padding = getPadding(context->parent->attributes);

            int paddingMargin = margin.top + margin.bottom + padding.top + padding.bottom;
            int hdiff = parentHeight - paddingMargin - context->parent->controlRect.h;

            context->parent->controlRect.h += hdiff;
            context->parent->paddingRect.h += hdiff;
            context->parent->marginRect.h += hdiff;
            context->parent->contentRect.h += hdiff;

            context->parent->renderData.allowHeightGrow = 0;
            context->parent->renderData.allowVerticalBoxes = 1;

            return parentHeight - paddingMargin;
        }
        else{
            return context->parent->controlRect.h;
        }
    }
    else{
        return context->target->h;
    }
}

void sizeControl(GUI_context * context){
    int width = getWidth(context->attributes);
    int height = getHeight(context->attributes);

    Box padding = getPadding(context->attributes);
    Box margin = getMargin(context->attributes);

    switch(width){
        case GUI_SIZE_MIN:
            context->renderData.allowWidthGrow = 1;
            context->renderData.allowHorizontalBoxes = 1;
        break;

        case GUI_SIZE_MAX:
            context->marginRect.w = stretchParentsWidth(context);
            context->paddingRect.w = context->marginRect.w - margin.left - margin.right;
            context->controlRect.w = context->paddingRect.w - padding.left - padding.right;

            context->renderData.allowWidthGrow = 0;
            context->renderData.allowHorizontalBoxes = 0;
        break;

        default:
            context->controlRect.w = width;
            context->renderData.allowWidthGrow = 1;
            context->renderData.allowHorizontalBoxes = 1;
    }

    switch(height){
        case GUI_SIZE_MIN:
            context->renderData.allowHeightGrow = 1;
            context->renderData.allowVerticalBoxes = 1;
        break;

        case GUI_SIZE_MAX:
            context->marginRect.h = stretchParentsHeight(context);
            context->paddingRect.h = context->marginRect.h - margin.top - margin.bottom;
            context->controlRect.h = context->paddingRect.h - padding.top - padding.bottom;

            context->renderData.allowHeightGrow = 0;
            context->renderData.allowVerticalBoxes = 0;
        break;

        default:
            context->controlRect.h = height;
            context->renderData.allowHeightGrow = 1;
            context->renderData.allowVerticalBoxes = 1;
    }

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        sizeControl(child);

        switch(getOrientation(context->attributes)){
            case GUI_ORIENTATION_HORIZONTAL:
                int stretchedWidth = context->contentRect.w + child->marginRect.w;
                context->contentRect.w = stretchedWidth;

                if(context->renderData.allowWidthGrow){
                    if(context->controlRect.w < stretchedWidth){
                        context->controlRect.w = stretchedWidth;   
                    }
                }

                if(context->controlRect.h < child->marginRect.h){
                    context->contentRect.h = child->marginRect.h;

                    if(context->renderData.allowHeightGrow){
                        context->controlRect.h = child->marginRect.h;
                    }
                }
            break;

            case GUI_ORIENTATION_VERTICAL:
                int stretchedHeight = context->contentRect.h + child->marginRect.h;
                context->contentRect.h = stretchedHeight;

                if(context->renderData.allowHeightGrow){
                    if(context->controlRect.h < stretchedHeight){
                        context->controlRect.h = stretchedHeight;   
                    }
                }

                if(context->controlRect.w < child->marginRect.w){
                    context->contentRect.w = child->marginRect.w;

                    if(context->renderData.allowWidthGrow){
                        context->controlRect.w = child->marginRect.w;
                    }
                }
            break;
        }
    }

    if(context->renderData.allowHorizontalBoxes){
        context->paddingRect.w = context->controlRect.w + padding.left + padding.right;
        context->marginRect.w = context->paddingRect.w + margin.left + margin.right;
    }

    if(context->renderData.allowVerticalBoxes){
        context->paddingRect.h = context->controlRect.h + padding.top + padding.bottom;
        context->marginRect.h = context->paddingRect.h + margin.top + margin.bottom;
    }

    if(context->paddingRect.w <= 0 || context->paddingRect.h <= 0){
        context->renderData.renderable = 0;
    }
}

void positionControl(GUI_context * context);

void positionHorizontally(GUI_context * context){
    GUI_context * prevChild = NULL;

    int xpos = 0, ypos = 0, xAlign = 0, yAlign = 0, xOff = 0, yOff = 0;
    Alignment alignment = getItemAlignment(context->attributes);

    switch(alignment.horizontal){
        case GUI_ALIGNMENT_CENTER:
            xAlign = (context->controlRect.w - context->contentRect.w) / 2;
        break;

        case GUI_ALIGNMENT_END:
            xAlign = context->controlRect.w - context->contentRect.w;
        break;

        case GUI_ALIGNMENT_STRETCH_BETWEEN:
            int count = context->children.length - 1;
            if(count) xOff = (context->controlRect.w - context->contentRect.w) / count;
        break;

        case GUI_ALIGNMENT_STRETCH_AROUND:
            count = context->children.length + 1;
            if(count) xAlign = (context->controlRect.w - context->contentRect.w) / count;
            xOff = xAlign;
        break;
    }

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        Box childMargin = getMargin(child->attributes);
        Box childPadding = getPadding(child->attributes);

        switch(alignment.vertical){
            case GUI_ALIGNMENT_CENTER:
                yAlign = (context->controlRect.h - child->marginRect.h) / 2;
            break;

            case GUI_ALIGNMENT_END:
                yAlign = context->controlRect.h - child->marginRect.h;
            break;

            case GUI_ALIGNMENT_STRETCH_BETWEEN:
                int count = context->children.length - 1;
                if(count) yOff = (context->controlRect.h - child->marginRect.h) / count;
            break;

            case GUI_ALIGNMENT_STRETCH_AROUND:
                count = context->children.length + 1;
                if(count) yAlign = (context->controlRect.h - child->marginRect.h) / count;
                yOff = yAlign;
            break;
        }

        child->marginRect.x += context->controlRect.x + xAlign;
        child->marginRect.y += context->controlRect.y + yAlign;

        child->paddingRect.x += child->marginRect.x + childMargin.left;
        child->paddingRect.y += child->marginRect.y + childMargin.top;

        child->controlRect.x += child->paddingRect.x + childPadding.left;
        child->controlRect.y += child->paddingRect.y + childPadding.top;

        if(prevChild){
            child->controlRect.x += xpos;
            child->paddingRect.x += xpos;
            child->marginRect.x += xpos;
        }

        if(i == context->children.length - 1){
            xOff = 0;
            yOff = 0;
        }

        xpos += child->marginRect.w + xOff;
        ypos += child->marginRect.h + yOff;

        positionControl(child);

        prevChild = child;
    }
}

void positionVertically(GUI_context * context){
    GUI_context * prevChild = NULL;

    int xpos = 0, ypos = 0, xAlign = 0, yAlign = 0, xOff = 0, yOff = 0;
    Alignment alignment = getItemAlignment(context->attributes);

    switch(alignment.vertical){
        case GUI_ALIGNMENT_CENTER:
            yAlign = (context->controlRect.h - context->contentRect.h) / 2;
        break;

        case GUI_ALIGNMENT_END:
            yAlign = context->controlRect.h - context->contentRect.h;
        break;

        case GUI_ALIGNMENT_STRETCH_BETWEEN:
            int count = context->children.length - 1;
            if(count) yOff = (context->controlRect.h - context->contentRect.h) / count;
        break;

        case GUI_ALIGNMENT_STRETCH_AROUND:
            count = context->children.length + 1;
            if(count) yAlign = (context->controlRect.h - context->contentRect.h) / count;
            yOff = yAlign;
        break;
    }

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        Box childMargin = getMargin(child->attributes);
        Box childPadding = getPadding(child->attributes);

        switch(alignment.horizontal){
            case GUI_ALIGNMENT_CENTER:
                xAlign = (context->controlRect.w - child->marginRect.w) / 2;
            break;

            case GUI_ALIGNMENT_END:
                xAlign = context->controlRect.w - child->marginRect.w;
            break;

            case GUI_ALIGNMENT_STRETCH_BETWEEN:
                int count = context->children.length - 1;
                if(count) xOff = (context->controlRect.w - child->marginRect.w) / count;
            break;

            case GUI_ALIGNMENT_STRETCH_AROUND:
                count = context->children.length + 1;
                if(count) xAlign = (context->controlRect.w - child->marginRect.w) / count;
                xOff = xAlign;
            break;
        }

        child->marginRect.x += context->controlRect.x + xAlign;
        child->marginRect.y += context->controlRect.y + yAlign;

        child->paddingRect.x += child->marginRect.x + childMargin.left;
        child->paddingRect.y += child->marginRect.y + childMargin.top;

        child->controlRect.x += child->paddingRect.x + childPadding.left;
        child->controlRect.y += child->paddingRect.y + childPadding.top;

        if(prevChild){
            child->controlRect.y += ypos;
            child->paddingRect.y += ypos;
            child->marginRect.y += ypos;
        }

        if(i == context->children.length - 1){
            xOff = 0;
            yOff = 0;
        }

        xpos += child->marginRect.w + xOff;
        ypos += child->marginRect.h + yOff;

        positionControl(child);

        prevChild = child;
    }
}

void positionControl(GUI_context * context){
    int orientation = getOrientation(context->attributes);

    switch(orientation){
        case GUI_ORIENTATION_VERTICAL: positionVertically(context); break;
        default: positionHorizontally(context);
    }
}

void bakeControl(GUI_context * context, SDL_PixelFormat format){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        SDL_DestroySurface(child->bakeResult);
        
        if(child->renderData.renderable){
            child->bakeResult = SDL_CreateSurface(child->paddingRect.w, child->paddingRect.h, format);
            if(child->renderer){
                void * renderArgs = getRenderArgs(child);
                child->renderer(renderArgs);
            }

            bakeControl(child, format);
        }
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

        if(child->renderData.renderable) bakeResultToSurface(child, sur);
        renderGui(child, sur);
    }
}