#include "../../include/gui_listener_service.h"
#include <stdio.h>

int isHovering(GUI_context * context){
    if(!context) return 0;
    
    int x2 = context->paddingRect.x + context->paddingRect.w;
    int y2 = context->paddingRect.y + context->paddingRect.h;
    
    Mouse mouse = context->settings->mouse;
    
    return mouse.x >= context->paddingRect.x && mouse.x < x2 && mouse.y >= context->paddingRect.y && mouse.y < y2;
}

void callListener(GUI_context * context, SDL_Event event){
    context->listener((ListenerData){context, &context->eventHandlers, &context->contextState, event});
}

void updateHoverLoop(GUI_context * context){
    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);

        if(isHovering(child)){
            context->settings->hover = child;
            updateHoverLoop(child);
        }
    }
}

void updateHover(GUI_context * context){
    context->settings->mouse = getMouseState();

    if(context->settings->hover){
        if(!isHovering(context->settings->hover)){
            callEventHandler(context->settings->oldHover, &context->settings->hover->eventHandlers, GUI_EVENT_LEAVE);
            context->settings->hover->contextState.isHovering = 0;
            context->settings->hover->contextState.isClicked = 0;
            setCursor(&context->settings->cursorData, GUI_CURSOR_ARROW);
            context->settings->hover = NULL;
        }
    }
    
    context->settings->oldHover = context->settings->hover;
    updateHoverLoop(context);

    if(context->settings->oldHover != context->settings->hover){
        if(context->settings->oldHover){
            callEventHandler(context->settings->oldHover, &context->settings->oldHover->eventHandlers, GUI_EVENT_LEAVE);
            context->settings->oldHover->contextState.isHovering = 0;
            context->settings->oldHover->contextState.isClicked = 0;
            bakeOnlyThisControl(context->settings->oldHover, context->target->format);
            setCursor(&context->settings->cursorData, GUI_CURSOR_ARROW);
        }

        if(context->settings->hover){
            callEventHandler(context->settings->hover, &context->settings->hover->eventHandlers, GUI_EVENT_ENTER);
            context->settings->hover->contextState.isHovering = 1;
            bakeOnlyThisControl(context->settings->hover, context->target->format);
            if(!context->settings->hover->contextState.isDisabled) setCursor(&context->settings->cursorData, context->settings->hover->defaultCursorId);
        }
    }
}

void eventLoop(GUI_context * context, SDL_Event event){
    callListener(context, event);
    bakeOnlyThisControl(context, context->target->format);

    for(int i = 0; i < context->children.length; i++){
        GUI_context * child = LST_get(context->children, i);
        eventLoop(child, event);
    }
}

void listenForEvents(GUI_context * context, SDL_Event event){
    switch(event.type){
        case SDL_EVENT_MOUSE_MOTION:
            updateHover(context);
        break;
    }

    eventLoop(context, event);
}

void fakeDestructor(void * yiff){}

void setEventHandler(GUI_context * context, unsigned int eventType, void (*handler)(GUI_context * context)){
    if(!HLS_get(context->eventHandlers, eventType)){
        HLS_add(&context->eventHandlers, eventType, handler, &fakeDestructor);
    }
    else{
        HLS_set(context->eventHandlers, eventType, handler, &fakeDestructor, 0);
    }
}