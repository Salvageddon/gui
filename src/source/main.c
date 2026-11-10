#include "../include/gui.h"
#include <stdio.h>
#include <SDL3/SDL.h>

#define FONTKEY 0xAAA

GUI_window * win;

int failApplication(){
    printf("Application failed.\n%s\n", GUI_getErrorMessage());
    printf("SDL ADDITIONAL INFO:\n%s\n", SDL_GetError());
    GUI_destroyWindow(win);
    GUI_quit();
    return 0;
}

void clickEventHandler(GUI_context * context){
    printf("Don't touch my button!! >//w//<\n");
}

int main(int argc, char * argv[]){
    GUI_init(SDL_INIT_VIDEO);
    win = GUI_createWindow(":3", 1280, 720, 0);

    if(!win){
        return failApplication();
    }

    win->guiBase = GUI_readGUI("src/pub/interface.xml", win->sur);

    if(!win->guiBase){
        return failApplication();
    }

    GUI_font * font = GUI_createFont("src/pub/font.bmp", 6, 10, 15, 0);
    GUI_addFont(win->guiBase, font, FONTKEY);
    GUI_setFocusFont(win->guiBase, FONTKEY);

    GUI_context * button = GUI_findContextById(win->guiBase, 0xA00);
    GUI_appendEventHandler(button, GUI_EVENT_LEFTCLICK, &clickEventHandler);

    GUI_bakeGUI(win->guiBase, win->sur->format);

    int loop = 1;

    while(loop){
        SDL_Event events;

        while(SDL_PollEvent(&events)){
            GUI_listenForEvents(win->guiBase, events);

            switch(events.type){
                case SDL_EVENT_QUIT:
                    loop = 0;
                break;
            }
        }

        GUI_renderGUI(win->guiBase, win->sur);
        SDL_UpdateWindowSurface(win->win);
    }

    GUI_destroyWindow(win);
    GUI_quit();

    printf("Program turned off safely\n");

    return 0;
}