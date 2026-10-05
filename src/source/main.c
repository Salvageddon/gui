#include "../include/gui.h"
#include <stdio.h>
#include <SDL3/SDL.h>

GUI_window * win;

int main(int argc, char * argv[]){
    GUI_init(SDL_INIT_VIDEO);
    win = GUI_createWindow(":3", 1280, 720, 0);

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

        GUI_fillRect(win->sur, 100, 100, 200, 50, 0xFF00FF);
        GUI_drawRect(win->sur, 300, 100, 200, 50, 0xFF0000);
        GUI_drawRect(win->sur, 100, 150, 200, 50, 0x0000FF);

        SDL_UpdateWindowSurface(win->win);
    }

    GUI_destroyWindow(win);
    GUI_quit();

    printf("Program turned off safely\n");

    return 0;
}