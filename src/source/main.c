#include "../include/gui.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <salvagames/xmlReader.h>

GUI_window * win;

int main(int argc, char * argv[]){
    GUI_init(SDL_INIT_VIDEO);
    win = GUI_createWindow(":3", 1280, 720, 0);

    //should render 3 blue "buttons"
    win->guiBase = GUI_readGUI("src/pub/interface.xml");
    GUI_bakeGUI(win->guiBase, win->sur->format);

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

        GUI_renderGUI(win->guiBase, win->sur);
        SDL_UpdateWindowSurface(win->win);
    }

    GUI_destroyWindow(win);
    GUI_quit();

    printf("Program turned off safely\n");

    return 0;
}