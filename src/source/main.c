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

int main(int argc, char * argv[]){
    GUI_init(SDL_INIT_VIDEO);
    win = GUI_createWindow(":3", 1280, 720, 0);

    if(!win){
        return failApplication();
    }

    int loop = 1;

    while(loop){
        SDL_Event events;

        while(SDL_PollEvent(&events)){
            switch(events.type){
                case SDL_EVENT_QUIT:
                    loop = 0;
                break;
            }
        }
        
        GUI_fillRectG(win->sur, 50, 50, 200, 200, 0xFF0000, 0x00FF00);
        GUI_fillRectG(win->sur, 300, 50, 200, 200, 0x00FF00, 0x0000FF);
        GUI_fillRectG(win->sur, 550, 50, 200, 200, 0x0000FF, 0xFF0000);

        SDL_UpdateWindowSurface(win->win);
    }

    GUI_destroyWindow(win);
    GUI_quit();

    printf("Program turned off safely\n");

    return 0;
}