#include "../include/gui.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <salvagames/xmlReader.h>

#define FONTKEY 0xAAA

GUI_window * win;

int failApplication(){
    printf("Application failed.\n%s\n", GUI_getErrorMessage());
    printf("SDL ADDITIONAL INFO:\n%s\n", SDL_GetError());
    GUI_destroyWindow(win);
    GUI_quit();
    return 0;
}

void enterEventHandler(GUI_context * context){
    printf("Enter event worked. GUI is functional ^w^\n");
}

void leaveEventHandler(GUI_context * context){
    printf("Leave event worked. Amaza Amaze Amaze!!!\n");
}

void leftClickEventHandler(GUI_context * context){
    printf("Left click event worked\n");
}

int main(int argc, char * argv[]){
    GUI_init(SDL_INIT_VIDEO);
    win = GUI_createWindow(":3", 1280, 720, 0);

    if(!win){
        return failApplication();
    }

    //red rectangles are linearViews, blue ones are buttons, green are views (plain rectangles)
    win->guiBase = GUI_readGUI("src/pub/interface.xml", win->sur);
    
    if(!win->guiBase){
        return failApplication();
    }

    //Reading and adding font
    GUI_font * font = GUI_createFont("src/pub/font.bmp", 6, 10, 15, 0x000000);
    GUI_addFont(win->guiBase, font, FONTKEY);
    GUI_setFocusFont(win->guiBase, FONTKEY);
    
    //Interact with the upper button and it will output events into console
    GUI_context * button = GUI_findContextById(win->guiBase, 0xa00);
    GUI_appendEventHandler(button, GUI_EVENT_ENTER, &enterEventHandler);
    GUI_appendEventHandler(button, GUI_EVENT_LEAVE, &leaveEventHandler);
    GUI_appendEventHandler(button, GUI_EVENT_LEFTCLICK, &leftClickEventHandler);

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

        /*SDL_Surface * sur = SDL_LoadBMP("src/pub/font.bmp");
        
        for(int y = 0; y < sur->h; y++){
            for(int x = 0; x < sur->w; x++){
                GUI_setPixel(win->sur, x, y, GUI_getPixel(sur, x, y));
            }
        }

        SDL_DestroySurface(sur);*/

        GUI_renderGUI(win->guiBase, win->sur);
        SDL_UpdateWindowSurface(win->win);
    }

    GUI_destroyWindow(win);
    GUI_quit();

    printf("Program turned off safely\n");

    return 0;
}