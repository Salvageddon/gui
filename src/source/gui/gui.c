#include "../../include/gui.h"
#include "../../include/gui_window_service.h"
#include "../../include/gui_render_service.h"
#include <stdio.h>

GUI_window * GUI_createWindow(char * title, int w, int h, Uint32 flags){
    if(!title){
        printf("GUI (createWindow()): Window title cannot be NULL.\n");
        return NULL;
    }

    return createWindow(title, w, h, flags);
}

void GUI_destroyWindow(GUI_window * window){
    if(!window){
        printf("GUI (destroyWindow()): Window cannot be NULL.\n");
        return;
    }

    destroyWindow(window);
}

void GUI_init(Uint32 flags){
    init(flags);
}

void GUI_quit(void){
    quit();
}

GUI_rgb GUI_getRGB(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    return getRGB(color, formatDetails);
}

Uint32 GUI_mapRGB(GUI_rgb color, const SDL_PixelFormatDetails * formatDetails){
    return mapRGB(color, formatDetails);
}

GUI_rgba GUI_getRGBA(Uint32 color, const SDL_PixelFormatDetails * formatDetails){
    return getRGBA(color, formatDetails);
}

Uint32 GUI_mapRGBA(GUI_rgba color, const SDL_PixelFormatDetails * formatDetails){
    return mapRGBA(color, formatDetails);
}