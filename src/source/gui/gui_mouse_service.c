#include "../../include/gui_mouse_service.h"
#include <stdio.h>

Mouse getMouseState(void){
    Mouse m;
    float x, y;
    m.buttons = SDL_GetMouseState(&x, &y);
    m.x = x; m.y = y;
    return m;
}