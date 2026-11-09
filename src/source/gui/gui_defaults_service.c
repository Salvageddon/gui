#include "../../include/gui_defaults_service.h"
#include <stdio.h>

ListenerData hover, oldHover;

SDL_Surface * getCurrentSurface(EventSurface eventSurface, ContextState contextState){
    if(contextState.isDisabled){
        return eventSurface.disabled;
    }
    else if(contextState.isClicked){
        return eventSurface.click;
    }
    else if(contextState.isHovering){
        return eventSurface.hover;
    }
    else{
        return eventSurface.normal;
    }
}

Uint32 getCurrentColor(EventColor eventColor, ContextState contextState){
    if(contextState.isDisabled){
        return eventColor.disabled;
    }
    else if(contextState.isClicked){
        return eventColor.click;
    }
    else if(contextState.isHovering){
        return eventColor.hover;
    }
    else{
        return eventColor.normal;
    }
}

void renderView(void * renderArgs){
    RenderArgs * ra = renderArgs;
    SDL_Surface * border = ra->theme.borderGradient.normal;

    fillTheme(ra->sur, 0, 0, ra->rect.w, ra->rect.h, ra->rect.x, ra->rect.y, border, ra->theme.invMapWidth, ra->theme.invMapHeight);
}

void renderButton(void * buttonRenderArgs){
    ButtonRenderArgs * ra = buttonRenderArgs;
    
    SDL_Surface * primary = getCurrentSurface(ra->theme.primaryGradient, ra->contextState);
    SDL_Surface * border = getCurrentSurface(ra->theme.borderGradient, ra->contextState);
    Uint32 foreGround = getCurrentColor(ra->theme.foregroundColor, ra->contextState);
    int borderSize = ra->theme.defaultBorderThickness;

    fillTheme(ra->sur, 0, 0, ra->rect.w, ra->rect.h, ra->rect.x, ra->rect.y, border, ra->theme.invMapWidth, ra->theme.invMapHeight);
    fillTheme(ra->sur, borderSize, borderSize, ra->rect.w - (2*borderSize), ra->rect.h - (2*borderSize), ra->rect.x + borderSize, ra->rect.y + borderSize, primary, ra->theme.invMapWidth, ra->theme.invMapHeight);
    renderText(ra->sur, ra->renderData, ra->rect.x, ra->rect.y, ra->rect.w, ra->rect.h, foreGround);
}

void buttonEventListener(ListenerData data){
    if(data.contextState->isHovering){
        switch(data.event.type){
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch(data.event.button.button){
                    case SDL_BUTTON_LEFT:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_LEFTCLICK);
                        data.contextState->isClicked = 1;
                    break;

                    case SDL_BUTTON_MIDDLE:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_MIDDLECLICK);
                    break;

                    case SDL_BUTTON_RIGHT:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_RIGHTCLICK);
                    break;
                }
            break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                switch(data.event.button.button){
                    case SDL_BUTTON_LEFT:
                        data.contextState->isClicked = 0;
                    break;
                }
            break;
        }
    }
}