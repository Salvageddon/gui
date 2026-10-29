#include "../../include/gui_defaults_service.h"
#include <stdio.h>

ListenerData hover, oldHover;

void renderView(void * renderArgs){
    RenderArgs * ra = renderArgs;
    GUI_rgb color;
    color.r = 0;
    color.g = 255 - ra->generation * 20;
    color.b = 0;

    fillRectNV(ra->sur, 0, 0, ra->rect.w, ra->rect.h, mapRGB(color, SDL_GetPixelFormatDetails(ra->sur->format)));
}

void renderButton(void * buttonRenderArgs){
    ButtonRenderArgs * ra = buttonRenderArgs;
    GUI_rgb color;
    color.r = 0;
    color.g = 0;
    color.b = 255 - ra->generation * 20;

    fillRectNV(ra->sur, 0, 0, ra->rect.w, ra->rect.h, mapRGB(color, SDL_GetPixelFormatDetails(ra->sur->format)));
    renderText(ra->sur, ra->text, ra->textSize, ra->rect.x, ra->rect.y, ra->rect.w, ra->rect.h, ra->font);
}

void renderLinearView(void * renderArgs){
    RenderArgs * ra = renderArgs;
    GUI_rgb color;
    color.r = 255 - ra->generation * 20;
    color.g = 0;
    color.b = 0;

    fillRectNV(ra->sur, 0, 0, ra->rect.w, ra->rect.h, mapRGB(color, SDL_GetPixelFormatDetails(ra->sur->format)));
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