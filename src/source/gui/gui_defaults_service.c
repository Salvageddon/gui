#include "../../include/gui_defaults_service.h"
#include <stdio.h>

ListenerData hover, oldHover;

void renderView(SDL_Surface * sur, GUI_irect rect, int generation){
    GUI_rgb color;
    color.r = 0;
    color.g = 255 - generation * 20;
    color.b = 0;

    fillRectNV(sur, 0, 0, rect.w, rect.h, mapRGB(color, SDL_GetPixelFormatDetails(sur->format)));
}

void renderButton(SDL_Surface * sur, GUI_irect rect, int generation){
    GUI_rgb color;
    color.r = 0;
    color.g = 0;
    color.b = 255 - generation * 20;

    fillRectNV(sur, 0, 0, rect.w, rect.h, mapRGB(color, SDL_GetPixelFormatDetails(sur->format)));
}

void renderLinearView(SDL_Surface * sur, GUI_irect rect, int generation){
    GUI_rgb color;
    color.r = 255 - generation * 20;
    color.g = 0;
    color.b = 0;

    fillRectNV(sur, 0, 0, rect.w, rect.h, mapRGB(color, SDL_GetPixelFormatDetails(sur->format)));
}

void buttonEventListener(ListenerData data){
    if(data.contextState.isHovering){
        switch(data.event.type){
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                switch(data.event.button.button){
                    case SDL_BUTTON_LEFT:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_LEFTCLICK);
                    break;

                    case SDL_BUTTON_MIDDLE:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_MIDDLECLICK);
                    break;

                    case SDL_BUTTON_RIGHT:
                        callEventHandler(data.context, data.eventHandlers, GUI_EVENT_RIGHTCLICK);
                    break;
                }
            break;
        }
    }
}