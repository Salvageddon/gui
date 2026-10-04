#include "../../include/gui_init_service.h"
#include <SDL3/SDL.h>

void init(Uint32 flags){
    SDL_Init(flags);
}

void quit(void){
    SDL_Quit();
}