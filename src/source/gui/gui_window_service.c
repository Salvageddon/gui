#include "../../include/gui_window_service.h"
#include <stdlib.h>
#include <stdio.h>

GUI_window * createWindow(char * title, int w, int h, Uint32 flags){
    GUI_window * win = malloc(sizeof(GUI_window));

    win->win = SDL_CreateWindow(title, w, h, flags);

    if(!win->win){
        setErrorMessage("Window creation failed. Call SDL_getError() for more info.\n");
        free(win);
        return NULL;
    }

    win->sur = SDL_GetWindowSurface(win->win);

    if(!win->sur){
        setErrorMessage("Surface download failed. Call SDL_getError() for more info.\n");
        SDL_DestroyWindow(win->win);
        free(win);
        return NULL;
    }

    win->w = w;
    win->h = h;
    win->guiBase = NULL;

    SDL_ShowWindow(win->win);

    return win;
}

void destroyWindow(GUI_window * win){
    if(win->guiBase) destroyContext(win->guiBase);

    SDL_DestroyWindowSurface(win->win);
    SDL_DestroyWindow(win->win);
    free(win);
}